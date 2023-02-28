/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 20:10:46 by spoolpra          #+#    #+#             */
/*   Updated: 2023/03/01 00:16:53 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __WEBSERV_HPP__
# define __WEBSERV_HPP__

// General include
# include <unistd.h>
# include <ctime>
# include <cerrno>
# include <cstdio>
# include <cstdlib>
# include <cstring>
# include <iostream>
# include <fstream>
# include <sstream>
# include <string>

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

// system stuff
# include <sys/socket.h>
# include <sys/stat.h>

// typedef alias
typedef struct sockaddr_in                      sockaddr_in_t;
typedef struct std::basic_string<unsigned char> bytestring;
typedef struct std::vector<std::string>         list_str_t;

// Macro stuff
# define ERROR              -1
# define SUCCESS            0
# define DEFAULT_EVENT      POLLIN | POLLOUT | POLLHUP
# define TIMEOUT_POLL       1000
# define STR_TO_BYTES(x)    reinterpret_cast<unsigned char*>(const_cast<char*>(x))
# define BYTES_TO_STR(x)    reinterpret_cast<char *>(const_cast<unsigned char*>(x))
# define BYTES_TO_VOID(x)   reinterpret_cast<void *>(const_cast<unsigned char*>(x))
# define SS_TO_STR(x)       static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

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

// Function Prototypes
std::string     path_join(const list_str_t& list_path);
list_str_t      parse_path_directory(std::string path);
list_str_t      join_list(const list_str_t& a, const list_str_t& b);

// Templates
template <typename T>
struct is_bigger {
    bool operator()(const T& x, const T& y) const {
        return x.size() > y.size();
    }
};

#endif /* __WEBSERV_HPP__ */
