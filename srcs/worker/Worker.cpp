/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Worker.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 22:19:50 by spoolpra          #+#    #+#             */
/*   Updated: 2022/09/20 00:40:11 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "Worker.hpp"

/// @brief Initialize address in of this Worker as given socket
/// @param socket socket to this worker will work on
Worker::Worker(const socket_t& socket) {
    // Reset value in _request
    FD_ZERO(&_request);
    // Reset any store value in _address
    bzero(&_address, sizeof(sockaddr_in_t));

    // Initial _server_fd to -1 as error fd
    _server_fd = ERROR_FD;
    // Assign socket to sockaddr_in
    _address.sin_family = AF_INET;
    _address.sin_port = htons(socket.port);
    _address.sin_addr.s_addr = socket.host;
}

/// @brief Assign right-hand-side value to left-hand-side
/// @param rhs value to be copied
/// @return copied object of rhs
Worker& Worker::operator=(const Worker& rhs) {
    // Reset value in _request
    FD_ZERO(&_request);
    // Reset any store value in _address
    bzero(&_address, sizeof(sockaddr_in_t));

    // Assign process
    _server_fd = rhs._server_fd;
    FD_COPY(&rhs._request, &_request);
    _address = rhs._address;

    return *this;
}

/// @brief Deconstructor use to destroy object
Worker::~Worker() {
    // Clear any possible socket left
    FD_ZERO(&_request);
}

/// @brief Create, bind and listen to _address socket
/// @return Server fd on success, -1 on error
int Worker::serve(void) {
    // Create new socket
    _server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (_server_fd == -1) {
        perror("Worker");
        return -1;
    }
    // Bind fd to host:port
    if (bind(_server_fd, (struct sockaddr*)&_address, sizeof(_address)) == -1) {
        perror("Worker");
        return -1;
    }
    // Start listen to socket
    if (listen(_server_fd, SOMAXCONN) == -1) {
        perror("Worker");
        return -1;
    }
    std::cout << "Listen on http://" << inet_ntoa(_address.sin_addr);
    std::cout << ":" << ntohs(_address.sin_port) << "/" << std::endl;
    return _server_fd;
}
