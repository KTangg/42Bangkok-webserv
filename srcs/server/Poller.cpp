/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Poller.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:41:39 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/07 02:51:11 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/Poller.hpp"

/**
 * @brief Construct a new Poller:: Poller object
 *
 */
Poller::Poller() : _logger("Poller"), _fds() {
}

/**
 * @brief Construct a new Poller:: Poller object
 *
 * @param src the object to do the copy
 */

Poller::Poller(const Poller& src) : _logger("Poller"), _fds(src._fds) {
}

/**
 * @brief Destroy the Poller:: Poller object
 *
 */
Poller::~Poller() {
    _logger.log(Logger::DEBUG, "Destroying poller");
}

/**
 * @brief Get the file descriptors
 *
 * @return std::vector<pollfd_t> the file descriptors
 */
const std::vector<pollfd_t>& Poller::get_fds() const {
    return _fds;
}

/**
 * @brief Get the iterator to the first file descriptor
 *
 * @return std::vector<pollfd_t>::iterator& the iterator to the first file descriptor
 */
std::vector<pollfd_t>::iterator Poller::get_fds_begin() {
    return _fds.begin();
}

/**
 * @brief Get the iterator to the last file descriptor
 *
 * @return std::vector<pollfd_t>::iterator the iterator to the last file descriptor
 */
std::vector<pollfd_t>::iterator Poller::get_fds_end() {
    return _fds.end();
}

/**
 * @brief Add a file descriptor
 *
 * @param fd the file descriptor
 * @param events the events to watch
 */

void Poller::add_fd(int fd, short int events) {
    _logger.log(Logger::DEBUG, "Adding fd " + ft::to_string(fd) + " to poller");

    pollfd_t newFd;
    newFd.fd = fd;
    newFd.events = events;
    newFd.revents = 0;

    _fds.push_back(newFd);

    _logger.log(Logger::DEBUG, "Total size " + ft::to_string(_fds.size()) + " in poller");
}

/**
 * @brief Remove a file descriptor
 *
 * @param it the iterator to the file descriptor
 * @return std::vector<pollfd_t>::iterator the iterator to the next file descriptor
 */
std::vector<pollfd_t>::iterator Poller::remove_fd(std::vector<pollfd_t>::iterator it) {
    _logger.log(Logger::DEBUG, "Removing fd " + ft::to_string(it->fd) + " from poller");

    it = _fds.erase(it);

    _logger.log(Logger::DEBUG, "Total size " + ft::to_string(_fds.size()) + " in poller");

    return it;
}

/**
 * @brief Poll the file descriptors
 *
 * @param timeout the timeout
 * @return int the number of events
 */
int Poller::poll(int timeout) {
    _logger.log(Logger::DEBUG, "Polling " + ft::to_string(_fds.size()) + "fds");

    int i = ::poll(_fds.data(), _fds.size(), timeout);

    _logger.log(Logger::DEBUG, "Polling done with " + ft::to_string(i) + " events");

    return i;
}
