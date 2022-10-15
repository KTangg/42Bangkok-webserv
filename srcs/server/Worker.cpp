/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Worker.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 22:19:50 by spoolpra          #+#    #+#             */
/*   Updated: 2022/10/07 10:56:59 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Worker.hpp"


/// @brief Initialize necessary attribute constructor
/// @param address socket address to be bind to
/// @param name server name
/// @param error map<error code, path to error page> to be error page of this server
/// @param limit limit request size
/// @param route map<string, Route> define Route of this server
Worker::Worker(
            const sockaddr_in_t&                address,
            const std::map<std::string, Route>& route,
            const std::map<int, std::string>&   error,
            const std::string&                  name,
            const size_t                        limit
        )
: _address(address), _route(route), _error(error), _name(name), _limit(limit)
{ }

/// @brief Deconstructor use to destroy object
Worker::~Worker() { }

/// @brief Create, bind and listen to _address socket
/// @return Server fd on success, -1 on error
int Worker::init(void) {
    // Create new socket
    _listener = socket(AF_INET, SOCK_STREAM, 0);
    if (_listener == ERROR) {
        perror("Worker Init");
        return ERROR;
    }

    // Set Socket option Remove address alreadys used for next time
    int yes = 1;
    if (setsockopt(_listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == ERROR) {
        perror("Worker Init");
        return ERROR;
    }

    // Bind fd to host:port
    if (bind(_listener, (struct sockaddr*)&_address, sizeof(_address)) == ERROR) {
        perror("Worker Init");
        return ERROR;
    }
    // Start listen to socket
    if (::listen(_listener, SOMAXCONN) == ERROR) {
        perror("Worker Init");
        return ERROR;
    }

    // Set socket to be Non-Blocking I/O
    fcntl(_listener, F_SETFL, O_NONBLOCK);

    // Add Listener poll to _poll
    _M_add_poll(_listener, POLLIN | POLLNVAL);

    return _listener;
}


/// @brief Listen to event happened in poll socket
/// @return 0 on success, -1 on error
int Worker::listen(void) {

    bool status = true;

    // Print out listening information
    std::cout << "Listening to http://";
    std::cout << inet_ntoa(_address.sin_addr);
    std::cout << ":" << ntohs(_address.sin_port) << std::endl;

    while (status) {

        // Poll and check timeout to exit loop
        int poll_cnt = poll(_poll.data(), _poll.size(), TIMEOUT_POLL);

        if (poll_cnt == -1) {
            perror("Worker Listen");
            return ERROR;
        }

        iterator_poll end = _poll.end();
        for (iterator_poll it = _poll.begin(); it != end; ++it) {
            if (it->revents & POLLHUP) {
                it = _M_del_poll(it);
                --it;
                --end;
            }
            else if (it->revents & POLLIN) {
                std::cout << "it in: " << it->fd << std::endl;
                if (it->fd == _listener) {
                    _M_accept();
                } else {
                    if (_M_recieve(it->fd) == ERROR) {
                        it = _M_del_poll(it);
                        --it;
                        --end;
                    }
                }
            } else if (it->revents & POLLOUT) {
                std::cout << "it out: " << it->fd << std::endl;
                _M_response(it->fd);
            } else if (it->revents & POLLNVAL) {
                it = _M_del_poll(it);
                --it;
                --end;
            }
        }
    }
    return 0;
}


/// @brief Add fd to poll list
/// @param fd fd to be listen
/// @param events event to be listen
void    Worker::_M_add_poll(int fd, short events) {
    struct pollfd   new_poll;

    new_poll.fd = fd;
    new_poll.events = events;
    new_poll.revents = 0;

    _poll.push_back(new_poll);
}


/// @brief Delete fd from poll list
/// @param it position of poll to be deleted
iterator_poll   Worker::_M_del_poll(iterator_poll& it) {
    std::cout << "Close: " << it->fd << std::endl;
    close(it->fd);
    return _poll.erase(it);
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


/// @brief Accept new incoming request move communication to another socket
/// Add new socket to poll list
void    Worker::_M_accept(void) {
    int         socket;
    sockaddr    addr_remote;
    socklen_t   addr_len;

    socket = accept(_listener, &addr_remote, &addr_len);

    if (socket == -1) {
        perror("Worker Accept");
    } else {
        std::cout << "Accept: " << socket << std::endl;
        fcntl(socket, F_SETFL, O_NONBLOCK);
        if (_S_keepalive(socket) != ERROR) {
            _M_add_poll(socket);
        }
    }
}


/// @brief Read data from socket and collect it as an request
/// @param socket socket fd to be read from
/// @return Socket fd on success, -1 on Error
int     Worker::_M_recieve(int socket) {
    (void)socket;
    std::cout << _limit << std::endl;
    std::cout << _status << std::endl;
    return 0;
}


/// @brief
/// @param socket
void    Worker::_M_response(int socket) {
    char buffer[1024];

    int fd = open("test.html", O_RDONLY);

    int ret = read(fd, buffer, 1024);

    send(socket, buffer, ret, MSG_NOSIGNAL);

    _request.erase(socket);
}
