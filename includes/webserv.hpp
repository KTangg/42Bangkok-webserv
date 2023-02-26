/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 20:10:46 by spoolpra          #+#    #+#             */
/*   Updated: 2023/02/26 22:09:27 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __WEBSERV_HPP__
# define __WEBSERV_HPP__

// General include
# include <unistd.h>
# include <cstdlib>
# include <cstring>
# include <iostream>
# include <string>
# include <sstream>
# include <ctime>

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
typedef struct sockaddr_in                      sockaddr_in_t;
typedef struct std::basic_string<unsigned char> bytestring;

// Macro stuff
# define ERROR              -1
# define SUCCESS            0
# define DEFAULT_EVENT      POLLIN | POLLOUT | POLLHUP
# define TIMEOUT_POLL       1000
# define STR_TO_BYTE(x)     reinterpret_cast<unsigned char*>(const_cast<char*>(x))
# define BYTE_TO_VOID(x)    reinterpret_cast<void *>(const_cast<unsigned char *>(x))

// Default value
# define DEFAULT_SERVER_NAME    "webserv"
# define DEFAULT_BODY_LIMIT     102400
# define DEFAULT_HEADER_RESERVE 512

// HTTP define
# define HTTP_VERSION       "HTTP/1.1"
# define CONTENT_HEADER_STR "\r\n\r\n"
# define HTTP_OK            200
# define HTTP_REDIRECT      301
# define HTTP_BAD_REQUEST   400
# define HTTP_UNAUTH        401
# define HTTP_NOT_FOUND     404
# define HTTP_NOT_ALLOW     405
# define HTTP_TIMEOUT       408
# define HTTP_TOO_LARGE     413
# define HTTP_SERVER_ERROR  500
# define HTTP_NOT_SUPPORT   505


#endif /* __WEBSERV_HPP__ */
