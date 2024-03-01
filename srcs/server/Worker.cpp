/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Worker.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:44:56 by spoolpra          #+#    #+#             */
/*   Updated: 2024/03/02 00:25:51 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/Worker.hpp"

/**
 * @brief Construct a new Worker:: Worker object
 *
 * @param config the config
 * @param master the master
 */
Worker::Worker(const Config& config, const Master& master)
    : _logger("Worker"), _socket(-1), _poller(), _master(master) {
    _M_init_addr(config.get_host().c_str(), config.get_port());
    _M_init_servers(config.get_server_configs());
}

/**
 * @brief Destroy the Worker:: Worker object
 *
 */
Worker::~Worker() {
    for (std::map<int, std::queue<HttpRequest*> >::iterator it = _request_queue.begin();
         it != _request_queue.end(); it++) {
        while ((*it).second.size() > 0) {
            HttpRequest* cur = (*it).second.front();
            (*it).second.pop();
            delete cur;
        }
    }
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
        }

        if (it->revents & POLLOUT && _request_queue[it->fd].size() > 0) {
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

    _logger.log(Logger::INFO, "New connection " + ft::to_string(client_fd) + " accepted");
    _poller.add_fd(client_fd);

    return _poller.get_fds_begin();
}

/**
 * @brief Handle a client disconnection
 *
 * @return poller_it_t the iterator to the listener fd
 */
poller_it_t Worker::_M_handle_client_disconnection(poller_it_t& it) {
    _logger.log(Logger::DEBUG, "Client " + ft::to_string(it->fd) + " disconnected");

    close(it->fd);
    while (_request_queue[it->fd].size() > 0) {
        HttpRequest* req = _request_queue[it->fd].front();
        _request_queue[it->fd].pop();
        delete req;
    }

    return _poller.remove_fd(it);
}

/**
 * @brief Handle a client request
 *
 */
void Worker::_M_handle_client_request(poller_it_t& it) {
    _logger.log(Logger::DEBUG, "Client " + ft::to_string(it->fd) + " sent a request");

    char buf[1024];
    int  ret = recv(it->fd, buf, 1024, 0);

    if (ret == -1) {
        _logger.log(Logger::ERROR, "Failed to receive data from client " + ft::to_string(it->fd));
        it->revents |= POLLERR;
        return;
    } else if (ret == 0) {
        it->revents |= POLLHUP;
        return;
    } else {
        _logger.log(Logger::DEBUG, "Received " + ft::to_string(ret) + " bytes from client " +
                                       ft::to_string(it->fd));
    }

    if (_request_queue.count(it->fd) == 0) {
        std::queue<HttpRequest*> new_queue;
        _request_queue.insert(std::pair<int, std::queue<HttpRequest*> >(it->fd, new_queue));
    }

    // Create request abstraction
    HttpRequest* request = 0;

    if (_request_queue[it->fd].size() > 0 && !_request_queue[it->fd].front()->is_completed()) {
        request = _request_queue[it->fd].front();
        request->append_content(std::string(buf, ret), ret);
    } else {
        try {
            request = HttpRequest::parse_request(buf, ret, _logger);
            _request_queue[it->fd].push(request);

            _logger.log(Logger::INFO, "[" + ft::to_string(it->fd) + "] Received HTTP Request: " +
                                          request->get_method() + " " + request->get_path());

            if (!_M_validate_request(*request)) {
                it->revents |= POLLHUP;
                return;
            }
        } catch (ft::InvalidHttpRequest& e) {
            _logger.log(Logger::ERROR, e.what());
            it->revents |= POLLHUP;
            return;
        }
    }

    if (!request->is_completed()) return;

    Server& server = _M_route_server(*request);
    server.serve_request(*request);
}

/**
 * @brief Route a request to the proper server.
 * If no exact match, will return the first server.
 *
 * @param req HttpRequest
 * @return Server& Server that matches the request
 */
Server& Worker::_M_route_server(HttpRequest& req) {
    Server* server = 0;
    for (std::vector<Server>::iterator it = _servers.begin(); it != _servers.end(); it++) {
        if (it->match_name(req.get_host())) {
            server = &(*it);
        }
    }
    if (!server) {
        server = &(_servers.front());
    }
    return *server;
}

bool Worker::_M_validate_request(HttpRequest& req) {
    Server& server = _M_route_server(req);
    int     timeout = server.getConfig().get_timeout();
    req.set_timeout(timeout);

    if (size_t(req.get_content_length()) > server.getConfig().get_max_body_size()) {
        HttpResponse* response = new HttpResponse(413, "Request Entity Too Large");
        response->set_connection("close");
        req.set_response(response);
        return false;
    }

    try {
        const Route& route = server.getConfig().get_route(req.get_path());
        if (route.get_redirect_path().length() > 0) {
            HttpResponse* response = new HttpResponse(301, "Moved Permanently");
            response->set_redirection(route.get_redirect_path() +
                                      req.get_path().substr(route.get_path().length()));
            response->set_connection("close");
            req.set_response(response);
            return false;
        }
    } catch (std::out_of_range& e) {
        HttpResponse* response = new HttpResponse(404, "Not Found");
        response->set_connection("close");
        req.set_response(response);
        return false;
    }
    return true;
}

/**
 * @brief Handle a server response
 *
 */
void Worker::_M_handle_server_response(poller_it_t& it) {
    _logger.log(Logger::DEBUG, "Server " + ft::to_string(it->fd) + " sent a response");

    while (_request_queue[it->fd].size() > 0) {
        HttpRequest*  req = _request_queue[it->fd].front();
        HttpResponse* res = req->get_response();
        if (req->check_timeout()) {
            req->set_response(new HttpResponse(408, "Connection Timed Out"));
            res = req->get_response();
            res->set_connection("close");
            it->revents |= POLLHUP;
        }
        if (!res) break;
        std::string response_msg = res->get_raw_message();

        _request_queue[it->fd].pop();
        delete req;

        int ret = send(it->fd, response_msg.c_str(), response_msg.size(), 0);

        if (ret == -1) {
            _logger.log(Logger::ERROR, "Failed to send data to client " + ft::to_string(it->fd));
            it->revents |= POLLERR;
        } else {
            _logger.log(Logger::DEBUG,
                        "Sent " + ft::to_string(ret) + " bytes to client " + ft::to_string(it->fd));
            std::istringstream iss(response_msg);
            std::string        response_status;
            std::getline(iss, response_status);
            _logger.log(Logger::INFO,
                        "[" + ft::to_string(it->fd) + "] Sent HTTP Response: " + response_status);
        }
    }
}

/**
 * @brief Set a file descriptor to non blocking
 *
 * @param fd the file descriptor
 * @return int 0 on success, -1 on error
 */
int Worker::_S_non_block_fd(int fd) {
    return fcntl(fd, F_SETFL, O_NONBLOCK);
}
