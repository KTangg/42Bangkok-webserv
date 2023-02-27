/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Worker.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 22:19:50 by spoolpra          #+#    #+#             */
/*   Updated: 2023/02/28 00:07:48 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/Worker.hpp"


/// @brief Initialize necessary attribute constructor
/// @param address socket address to be bind to
/// @param name server name
/// @param error map<error code, path to error page> to be error page of this server
/// @param limit limit request size
/// @param route map<string, Route> define Route of this server
Worker::Worker(
            const sockaddr_in_t&                address,
            const route_map_t&                  route,
            // const std::map<int, std::string>&   error,
            const std::string&                  name,
            const size_t                        limit
        )
:   _address(address),
    _route(route),
    _name(name),
    _limit(limit)
{
    _poll.clear();
    _request_map.clear();
}

/// @brief Deconstructor use to destroy object
Worker::~Worker() { }

/// @brief Create, bind and listen to _address socket
/// @return Server fd on success, -1 on error
int Worker::init(void) {

    std::string error_prefix = _name + " init";

    // Create new socket
    _listener = socket(AF_INET, SOCK_STREAM, 0);
    if (_listener == ERROR) {
        perror(error_prefix.c_str());
        return ERROR;
    }

    // Set Socket option Remove address alreadys used for next time
    int yes = 1;
    if (setsockopt(_listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == ERROR) {
        perror(error_prefix.c_str());
        return ERROR;
    }

    // Bind fd to host:port
    if (bind(_listener, (struct sockaddr*)&_address, sizeof(_address)) == ERROR) {
        perror(error_prefix.c_str());
        return ERROR;
    }
    // Start listen to socket
    if (::listen(_listener, SOMAXCONN) == ERROR) {
        perror(error_prefix.c_str());
        return ERROR;
    }

    // Set socket to be Non-Blocking I/O
    fcntl(_listener, F_SETFL, O_NONBLOCK);

    // Add Listener poll to _poll
    _M_add_poll(_listener, POLLIN | POLL_HUP);

    // Set _status to be true as it ready to listen
    _status = true;

    return _listener;
}


/// @brief Listen to event happened in poll socket
/// @return 0 on success, -1 on error
int Worker::listen(void) {

    if (_status) {
        // Print out listening information
        std::cout << "Listening to http://";
        std::cout << inet_ntoa(_address.sin_addr);
        std::cout << ":" << ntohs(_address.sin_port) << std::endl;
    }

    std::vector<int> del_fd;

    while (_status) {

        if (_poll.size() <= 0) {
            std::cerr << _name << ": corrupted listener" << std::endl;

            return ERROR;
        }

        // Poll and check timeout to exit loop
        int poll_cnt = poll(_poll.data(), _poll.size(), TIMEOUT_POLL);

        if (poll_cnt < 0) {
            std::string error_prefix = _name + " poll";
            perror(error_prefix.c_str());

            return ERROR;
        } else if (poll_cnt == 0) {
            continue;
        }

        int new_socket = ERROR;

        for (iterator_poll it = _poll.begin(); it != _poll.end(); ++it) {

            if (it->revents & POLLHUP) {
                del_fd.push_back(it->fd);
            } else if (it->revents & POLLIN) {
                if (it->fd == _listener) {
                    int accept_status = _M_accept(new_socket);
                    if (accept_status == ERROR) {
                        del_fd.push_back(_listener);
                    }
                } else {
                    if (_M_request(it->fd) == ERROR) {
                        del_fd.push_back(it->fd);
                    }
                }
            } else if (it->revents & POLLOUT) {
                _M_response(it->fd);
            }
        }
        _M_del_poll(del_fd);
        del_fd.clear();

        if (new_socket != ERROR) {
            _M_add_poll(new_socket);
        }
    }

    return SUCCESS;
}


void    Worker::_M_add_poll(int socket, short events) {
    struct pollfd   new_poll;

    new_poll.fd = socket;
    new_poll.events = events;
    new_poll.revents = 0;

    _poll.push_back(new_poll);
}


void    Worker::_M_del_poll(std::vector<int>& del_fd) {

    iterator_poll start_it = _poll.begin();
    for (std::vector<int>::iterator del_it = del_fd.begin(); del_it != del_fd.end(); ++del_it) {
        for (iterator_poll it = start_it; it != _poll.end(); ++it) {
            if (it->fd == *del_it) {
                start_it = _poll.erase(it);
                std::cout << "Close: " << *del_it << std::endl;
                close(*del_it);
                break;
            }
        }

        try {
            _request_map.erase(*del_it);
        } catch (std::out_of_range) { }
    }
}


/// @brief Set socket to be keep alive
/// @param socket fd to be set
int     Worker::_S_keepalive(int socket) {
    int ret;

    // Turn on keepalive option
    int yes = 1;
    ret = setsockopt(socket, SOL_SOCKET, SO_KEEPALIVE, &yes, sizeof(yes));
    if (ret == ERROR) {
        perror("Keepalive");
        return ERROR;
    }
    return ret;
}


int Worker::_M_accept(int &socket) {
    sockaddr    addr_remote;
    socklen_t   addr_len = 0;

    socket = accept(_listener, &addr_remote, &addr_len);

    std::string error_prefix = _name + " accept";
    if (socket == -1) {
        if (errno != EWOULDBLOCK)
        {
            perror(error_prefix.c_str());
            _status = false;
        }

        return ERROR;
    } else {
        std::cout << "Accept: " << socket << std::endl;
        fcntl(socket, F_SETFL, O_NONBLOCK);
        _S_keepalive(socket);

        return SUCCESS;
    }
}


int     Worker::_M_request(int socket) {

    unsigned char   buffer[_limit];
    int read_cnt = recv(socket, buffer, _limit, 0);

    bytestring request_byte(buffer, read_cnt);

    try {
        Request& exist_request = _request_map.at(socket);
        exist_request.append_request(request_byte);
    } catch (std::out_of_range) {
        std::pair<int, Request> request_pair(socket, Request(_name, request_byte));
        _request_map.insert(request_pair);
    }

    return SUCCESS;
}


int Worker::_M_response(int socket) const {

    try {
        Request request = _request_map.at(socket);
        Response response = request.process(_route);
        response.response(socket);
    } catch (std::out_of_range) {
        return ERROR;
    }

    return SUCCESS;
}
