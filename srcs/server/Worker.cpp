/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Worker.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:44:56 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/06 16:10:24 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/Worker.hpp"

/**
 * @brief Construct a new Worker:: Worker object
 *
 * @param config the config object
 * @param master the master object
 */
Worker::Worker(Config* config, const Master& master) : _socket(-1), _master(master) {
    // Init the logger
    _logger.setName("Worker");

    // Init the address
    _addr.sin_addr.s_addr = inet_addr(config->get_host().c_str());
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(config->get_port());

    for (std::vector<ServerConfig>::iterator it = config->getServerConfigs().begin();
         it != config->getServers().end(); ++it) {
        _servers.push_back(Server(*it));
    }
}

/**
 * @brief Destroy the Worker:: Worker object
 *
 */
Worker::~Worker() {
}

/**
 * @brief Init the worker
 *
 */
void Worker::init() {
    _M_init_socket();
    _M_init_poller();
}

/**
 * @brief Run the worker
 *
 */
void Worker::run() {
    while (_master.is_running()) {
        try {
            _M_run();
        } catch (const ft::WorkerFatalException& e) {
            _logger.log(Logger::ERROR, e.what());
            break;
        }
    }
}

/**
 * @brief Poll the sockets and handle events
 *
 */
void Worker::_M_run() {
    // Poll
    int poll_cnt = _poller.poll();
    if (poll_cnt == -1) {
        throw ft::WorkerNonFatalException("Failed to poll");
    }

    // Handle events
    for (poller_it_t it = _poller.get_fds_begin(); it != _poller.get_fds_end();) {
        if (it->revents & POLLIN) {
            if (it->fd == _socket) {
                it = _M_handle_new_connection(it);
            } else {
                it = _M_handle_client_request(it);
            }
        } else if (it->revents & POLLOUT) {
            it = _M_handle_server_response(it);
        }

        if (it->revents & (POLLHUP | POLLERR | POLLNVAL)) {
            if (it->fd == _socket) {
                throw ft::WorkerFatalException("Listener socket corrupted");
            } else {
                if (it->revents & (POLLNVAL | POLLERR)) {
                    _logger.log(Logger::ERROR,
                                "Client socket " + ft::to_string(it->fd) + " corrupted");
                }
                it = _M_handle_client_disconnection(it);
                // Don't increment the iterator
                continue;
            }
        }

        ++it;
    }
}

/**
 * @brief Init the socket
 *
 */
void Worker::_M_init_socket() {
    _socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_socket == -1) {
        throw ft::WorkerFatalException("Failed to create socket");
    }

    int opt = 1;
    if (setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        _logger.log(Logger::WARNING, "Failed to set socket options");
    }

    if (bind(_socket, (struct sockaddr*)&_addr, sizeof(_addr)) == -1) {
        throw ft::WorkerFatalException("Failed to bind socket");
    }

    if (::listen(_socket, 128) == -1) {
        throw ft::WorkerFatalException("Failed to listen on socket");
    }
}

/**
 * @brief Init the poller
 *
 */
void Worker::_M_init_poller() {
    _logger.log(Logger::INFO, "Adding listener socket " + ft::to_string(_socket) + " to poller");
    _poller->add_fd(_socket, POLLIN | POLLHUP | POLLERR | POLLNVAL);
}

/**
 * @brief Handle a new connection
 *
 * @return poller_it_t the iterator to the listener fd
 */
poller_it_t& Worker::_M_handle_new_connection(poller_it_t& it) {
    sockaddr_in_t addr;
    socklen_t     addr_len = sizeof(addr);
    int           client_fd = accept(_socket, (struct sockaddr*)&addr, &addr_len);

    if (client_fd == -1) {
        _logger.log(Logger::ERROR, "Failed to accept connection");
    }
    if (_S_non_block_fd(client_fd) == -1) {
        _logger.log(Logger::ERROR, "Failed to set socket to non blocking");

        close(client_fd);
        return it;
    };

    _logger.log(Logger::INFO, "New connection " + ft::to_string(client_fd) + " accepted");
    _poller->add_fd(client_fd);

    ptrdiff_t offset = std::distance(_poller.get_fds_begin(), it);

    return _poller.get_fds_begin() + offset;
}

/**
 * @brief Handle a client disconnection
 *
 * @return poller_it_t the iterator to the listener fd
 */
poller_it_t& Worker::_M_handle_client_disconnection(poller_it_t& it) {
    _logger.log(Logger::INFO, "Client " + ft::to_string(it->fd) + " disconnected");

    close(it->fd);

    return _poller.remove_fd(it);
}

/**
 * @brief Handle a client request
 *
 */
void Worker::_M_handle_client_request(poller_it_t& it) {
    _logger.log(Logger::INFO, "Client " + ft::to_string(it->fd) + " sent a request");

    char buf[1024];
    int  ret = recv(it->fd, buf, 1024, 0);

    if (ret == -1) {
        _logger.log(Logger::ERROR, "Failed to receive data from client " + ft::to_string(it->fd));
        it->revents |= POLLERR;
    } else if (ret == 0) {
        it->revents |= POLLHUP;
    } else {
        _logger.log(Logger::INFO, "Received " + ft::to_string(ret) + " bytes from client " +
                                      ft::to_string(it->fd));
    }
    // TODO handle client request
}

/**
 * @brief Handle a server response
 *
 */
void Worker::_M_handle_server_response(poller_it_t& it) {
    _logger.log(Logger::INFO, "Server " + ft::to_string(it->fd) + " sent a response");

    // TODO handle server response
    char* res = "HTTP/1.1 200 OK\r\n\r\nHello World!";

    int ret = send(it->fd, res, strlen(res), 0);

    if (ret == -1) {
        _logger.log(Logger::ERROR, "Failed to send data to client " + ft::to_string(it->fd));
        it->revents |= POLLERR;
    } else {
        _logger.log(Logger::INFO,
                    "Sent " + ft::to_string(ret) + " bytes to client " + ft::to_string(it->fd));
    }
}

/**
 * @brief Set a file descriptor to non blocking
 *
 * @param fd the file descriptor
 * @return int 0 on success, -1 on error
 */
int Worker::_S_non_block_fd(int fd) {
    return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}
