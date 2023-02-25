/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Worker.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 22:19:50 by spoolpra          #+#    #+#             */
/*   Updated: 2023/01/01 11:04:32 by spoolpra         ###   ########.fr       */
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
            // const std::map<std::string, Route>& route,
            // const std::map<int, std::string>&   error,
            const std::string&                  name,
            const size_t                        limit
        )
: _address(address), _name(name), _limit(limit)
{ }

/// @brief Deconstructor use to destroy object
Worker::~Worker() { }

/// @brief Create, bind and listen to _address socket
/// @return Server fd on success, -1 on error
int Worker::init(void) {

    std::string error_prefix = _name + " init";

    std::vector<struct pollfd> empty_poll;
    _poll = empty_poll;

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


    while (_status) {

        // Poll and check timeout to exit loop
        int poll_cnt = poll(_poll.data(), _poll.size(), TIMEOUT_POLL);

        if (poll_cnt < 0) {
            std::string error_prefix = _name + " poll";
            perror(error_prefix.c_str());

            return ERROR;
        } else if (poll_cnt == 0) {
            std::cerr << _name << ": corrupted listener" << std::endl;

            return ERROR;
        }

        std::vector<int> add_fd;
        std::vector<int> del_fd;

        for (iterator_poll it = _poll.begin(); it != _poll.end(); ++it) {
            if (it->revents & POLLHUP) {
                del_poll.push_back(*it);
            } else if (it->revents & POLLIN) {
                if (it->fd == _listener) {
                    int accept_status = _M_accept(add_poll);
                    if (accept_status == ERROR) {
                        del_poll.push_back(_poll.front());
                    }
                } else {
                    if (_M_request(it->fd) == ERROR) {
                        std::cout << "Request" << std::endl;
                        del_poll.push_back(*it);
                    }
                }
            } else if (it->revents & POLLOUT) {
                    if (_M_response(it->fd) == SUCCESS) {
                        del_poll.push_back(*it);
                    }
            }
        }
        _M_del_poll(del_fd);
        del_poll.clear();

        _M_add_poll(add_fd);
        add_poll.clear();
    }

    return SUCCESS;
}


void    Worker::_M_add_poll(std::vector<int> &add_fd, short events) {
    struct pollfd   new_poll;

    new_poll.fd = fd;
    new_poll.events = events;
    new_poll.revents = 0;

    std::cout << "before size: " << _poll.size() << std::endl;
    _poll.push_back(new_poll);
    std::cout << "after size: " << _poll.size() << std::endl;
}


void    Worker::_M_del_poll(std::vector<struct pollfd> del_poll) {

    iterator_poll start_it = _poll.begin();
    for (iterator_poll del_it = del_poll.begin(); del_it != del_poll.end(); ++del_it) {
        for (iterator_poll it = start_it; it != _poll.end(); ++it) {
            if (it->fd == del_it->fd) {
                std::cout << "size: " << _poll.size() << std::endl;
                start_it = _poll.erase(it);
                std::cout << "size: " << _poll.size() << std::endl;
                std::cout << "Close: " << it->fd << std::endl;
                close(it->fd);
                break;
            }
        }
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


int Worker::_M_accept(std::vector<struct pollfd> &add_poll) {
    int         socket;
    sockaddr    addr_remote;
    socklen_t   addr_len;

    socket = accept(_listener, &addr_remote, &addr_len);

    std::string error_prefix = _name + " accept";
    if (socket == -1) {
        if (errno != EWOULDBLOCK)
        {
            perror(error_prefix.c_str());
            _status = false;
        }
    } else {
        std::cout << "Accept: " << socket << std::endl;
        fcntl(socket, F_SETFL, O_NONBLOCK);
        _S_keepalive(socket);
        add_poll.push_back()
    }
}


int     Worker::_M_request(int socket) {
    (void)socket;
    (void)_limit;
    // std::cout << _limit << std::endl;
    // std::cout << _status << std::endl;

    return SUCCESS;
}

 
int    Worker::_M_response(int socket) {
    char buffer[1024];

    int fd = open("test.html", O_RDONLY);

    int ret = read(fd, buffer, 1024);

#ifndef __APPLE__
    send(socket, buffer, ret, MSG_NOSIGNAL | MSG_DONTWAIT);
#else
    signal(SIGPIPE, SIG_IGN);
    send(socket, buffer, ret, MSG_DONTWAIT);
#endif

    // _request.erase(socket);

    return SUCCESS;
}
