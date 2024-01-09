/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Worker.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:44:56 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/09 13:13:29 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/Worker.hpp"

/**
 * @brief Construct a new Worker:: Worker object
 *
 * @param src the object to do the copy
 */
Worker::Worker(const Worker& src)
    : _logger("Worker"),
      _socket(src._socket),
      _poller(src._poller),
      _master(src._master),
      _is_running(src._is_running),
      _addr(src._addr),
      _servers(src._servers) {
}

/**
 * @brief Construct a new Worker:: Worker object
 *
 * @param config the config
 * @param master the master
 */
Worker::Worker(const Config& config, const Master& master)
    : _logger("Worker"), _socket(-1), _poller(), _master(master), _is_running(false) {
    _M_init_addr(config.get_host().c_str(), config.get_port());
    _M_init_servers(config.get_server_configs());
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
    _is_running = true;
    while (_master.is_running()) {
        try {
            _M_run();
        } catch (const ft::WorkerFatalException& e) {
            _logger.log(Logger::ERROR, e.what());
            break;
        }
    }
    _is_running = false;
}

/**
 * @brief Check if the worker is running
 *
 * @return true if the worker is running
 * @return false otherwise
 */
bool Worker::is_running() const {
    return _is_running;
}

/**
 * @brief Poll the sockets and handle events
 *
 */
void Worker::_M_run() {
    // Poll
    int poll_cnt = _poller.poll();
    if (poll_cnt == -1) {
        _logger.log(Logger::WARNING, "Failed to poll sockets");
        return;
    }

    // Handle events
    for (poller_it_t it = _poller.get_fds_begin(); it != _poller.get_fds_end();) {
        if (it->revents & POLLIN) {
            if (it->fd == _socket) {
                it = _M_handle_new_connection(it);
            } else {
                _M_handle_client_request(it);
            }
        } else if (it->revents & POLLOUT) {
            _M_handle_server_response(it);
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
 * @brief Init the address
 *
 * @param host the host
 * @param port the port
 */
void Worker::_M_init_addr(const char* host, int port) {
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(port);
    _addr.sin_addr.s_addr = inet_addr(host);
}

/**
 * @brief Init the servers
 *
 * @param server_configs the server configs
 */
void Worker::_M_init_servers(const std::vector<ServerConfig>& server_configs) {
    for (std::vector<ServerConfig>::const_iterator it = server_configs.begin();
         it != server_configs.end(); ++it) {
        _servers.push_back(Server(*it));
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

    std::string host = inet_ntoa(_addr.sin_addr);
    int         port = ntohs(_addr.sin_port);

    _logger.log(Logger::INFO, "Listening on " + host + ":" + ft::to_string(port));
}

/**
 * @brief Init the poller
 *
 */
void Worker::_M_init_poller() {
    _logger.log(Logger::DEBUG, "Adding listener socket " + ft::to_string(_socket) + " to poller");
    _poller.add_fd(_socket, POLLIN | POLLHUP | POLLERR | POLLNVAL);
}

/**
 * @brief Handle a new connection
 *
 * @return poller_it_t the iterator to the listener fd
 */
poller_it_t Worker::_M_handle_new_connection(poller_it_t& it) {
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

    _logger.log(Logger::DEBUG, "New connection " + ft::to_string(client_fd) + " accepted");
    _poller.add_fd(client_fd);
    _M_add_client(client_fd);

    return _poller.get_fds_begin();
}

/**
 * @brief Handle a client disconnection
 *
 * @return poller_it_t the iterator to the listener fd
 */
poller_it_t Worker::_M_handle_client_disconnection(poller_it_t& it) {
    _logger.log(Logger::DEBUG, "Client " + ft::to_string(it->fd) + " disconnected");

    _M_remove_client(it->fd);
    close(it->fd);

    return _poller.remove_fd(it);
}

/**
 * @brief Handle a client request
 *
 */
void Worker::_M_handle_client_request(poller_it_t& it) {
    _logger.log(Logger::DEBUG, "Client " + ft::to_string(it->fd) + " sent a request");

    std::size_t buffer_size = 1024;

    char buffer[buffer_size];
    int  ret = 0;
    int  tot_ret = 0;

    // Check if timeout
    if (_S_check_timeout(_clients[it->fd])) {
        _clients[it->fd].set_response_status_code(408);
        it->revents |= POLLHUP;
        return;
    }

    while ((ret = recv(it->fd, &buffer, buffer_size, 0)) > 0) {
        tot_ret += ret;
        _clients[it->fd].read(buffer, ret);
    }

    if (ret == -1 || tot_ret == 0) {
        it->revents |= POLLHUP;
    } else {
        _logger.log(Logger::DEBUG, "Received " + ft::to_string(tot_ret) + " bytes from client " +
                                       ft::to_string(it->fd));
    }

    // Debug Request
    // _logger.log(Logger::DEBUG, "Request: " + _clients[it->fd].get_method() + " " +
    //                                _clients[it->fd].get_uri() + " " +
    //                                _clients[it->fd].get_version());
    // _logger.log(Logger::DEBUG, "Headers: " + _clients[it->fd].get_headers().to_string());
    // _logger.log(Logger::DEBUG, "Body: " + _clients[it->fd].get_body());
}

/**
 * @brief Handle a server response
 *
 */
void Worker::_M_handle_server_response(poller_it_t& it) {
    _M_process_server_response(_clients[it->fd]);

    if (!_clients[it->fd].ready_to_respond()) {
        return;
    }

    // TODO handle server response
    std::string res = _clients[it->fd].get_response();

    int ret = send(it->fd, res.c_str(), res.size(), 0);

    if (ret == -1) {
        _logger.log(Logger::ERROR, "Failed to send data to client " + ft::to_string(it->fd));
        it->revents |= POLLERR;
    } else {
        _logger.log(Logger::DEBUG,
                    "Sent " + ft::to_string(ret) + " bytes to client " + ft::to_string(it->fd));
    }
}

/**
 * @brief Add a client to the map
 *
 * @param fd the client fd
 */
void Worker::_M_add_client(int fd) {
    _clients.insert(std::pair<int, Request>(fd, Request()));
}

/**
 * @brief Remove a client from the map
 *
 * @param fd the client fd
 */
void Worker::_M_remove_client(int fd) {
    _clients.erase(fd);
}

/**
 * @brief Process the server response
 *
 * @param request the request
 */
void Worker::_M_process_server_response(Request& request) const {
    if (_S_check_timeout(request)) {
        request.set_response_status_code(408);
        return;
    } else {
        request.set_response_status_code(200);
    }
}

/**
 * @brief Set a file descriptor to non blocking
 *
 * @param fd the file descriptor
 * @return int 0 on success, -1 on error
 */
int Worker::_S_non_block_fd(int fd) {
    int keep_alive = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &keep_alive, sizeof(keep_alive)) < 0) {
        return -1;
    }
    return fcntl(fd, F_SETFL, O_NONBLOCK);
}

/**
 * @brief Check if the request has timed out
 *
 * @param request the request
 * @return true if the request has timed out
 * @return false otherwise
 */
bool Worker::_S_check_timeout(const Request& request) {
    if ((request.get_start_time_ms() + DEFAULT_TIMEOUT_MS) < TIME_T_TO_MS(std::time(NULL))) {
        return false;
    }
    return true;
}
