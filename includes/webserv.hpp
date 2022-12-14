/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 20:10:46 by spoolpra          #+#    #+#             */
/*   Updated: 2022/10/05 17:39:25 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __WEBSERV_HPP__
# define __WEBSERV_HPP__

// General include
# include <unistd.h>
# include <cstdlib>
# include <cstring>
# include <iostream>

// Container
# include <algorithm>
# include <vector>
# include <map>

// inet(ip) <-> address conversion
# include <arpa/inet.h>

// File constrol
# include <fcntl.h>

// Poll function and structure
# include <poll.h>

// Socket stuff
# include <sys/socket.h>

// typedef alias
typedef struct sockaddr_in  sockaddr_in_t;
typedef std::vector<struct pollfd>::iterator iterator_poll;

// Macro stuff
# define ERROR -1
# define DEFAULT_EVENT POLLIN | POLLOUT | POLLHUP | POLLNVAL
# define TIMEOUT_POLL 1000

// Default value
# define DEFAULT_SERVER_NAME "webserv"
# define DEFAULT_BODY_LIMIT 4096

#endif /* __WEBSERV_HPP__ */
