/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Poller.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:28:55 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/04 22:31:49 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __POLLER_HPP__
#define __POLLER_HPP__

#include <poll.h>

#include <vector>

#include "logger/Logger.hpp"
#include "utils/utils.hpp"

#ifndef DEFAULT_POLL_EVENT
#define DEFAULT_POLL_EVENT = POLLIN | POLLOUT | POLLHUP | POLLERR | POLLNVAL
#endif

#ifndef DEFAULT_POLL_TIMEOUT
#define DEFAULT_POLL_TIMEOUT 1000
#endif

typedef struct pollfd                   pollfd_t;
typedef std::vector<pollfd_t>::iterator poller_it_t;

class Poller {
   public:
    Poller();
    ~Poller();

    const std::vector<pollfd_t>& get_fds() const;
    poller_it_t                  get_fds_begin();
    poller_it_t                  get_fds_end();

    void        add_fd(int fd, short int events = DEFAULT_POLL_EVENT);
    poller_it_t remove_fd(poller_it_t it);

    int poll(int timeout = DEFAULT_POLL_TIMEOUT);

   private:
    Logger                _logger;
    std::vector<pollfd_t> _fds;
};

#endif /* __POLLER_HPP__ */
