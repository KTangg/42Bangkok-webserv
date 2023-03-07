/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 20:10:46 by spoolpra          #+#    #+#             */
/*   Updated: 2023/03/07 20:24:56 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __WEBSERV_HPP__
# define __WEBSERV_HPP__

// General include
# include <unistd.h>
# include <ctime>
# include <cerrno>
# include <cstring>
# include <cstdlib>
# include <iostream>
# include <sstream>
# include <string>

// inet(ip) <-> address conversion
# include <arpa/inet.h>

// File constrol
# include <fcntl.h>

// Poll function and structure
# include <poll.h>

// system stuff
# include <sys/socket.h>
# include <sys/stat.h>

// Container
# include <algorithm>
# include <vector>
# include <map>


// typedef alias
typedef struct sockaddr_in                              sockaddr_in_t;
typedef std::vector<std::string>                        v_str_t;
typedef v_str_t::iterator                               it_v_str;
typedef v_str_t::const_iterator                         const_it_v_str;
typedef std::vector<struct pollfd>                      v_poll_t;
typedef v_poll_t::iterator                              it_poll;
typedef v_poll_t::const_iterator                        const_it_poll;
typedef std::pair<int, const std::string>               http_status_t;


// Default value
# define DEFAULT_SERVER_NAME    "webserv"
# define DEFAULT_BUFFER_SIZE    8192
# define DEFAULT_BODY_LIMIT     8192
# define DEFAULT_HTTP_LIMIT     8192
# define TIMEOUT_POLL           1000

// HTTP define
# define CRLF                   "\r\n"
# define GET                    "GET"
# define POST                   "POST"
# define DELETE                 "DELETE"
# define HTTP                   "HTTP"
# define HTTP_PREFIX            "http://"
# define HTTPS_PREFIX           "https://"
# define HTTP_VERSION           1.1
# define HTTP_FAILED            http_status_t(-1, "")
# define HTTP_OK                http_status_t(200, "OK")
# define HTTP_CONTINUE          http_status_t(100, "Continue")
# define HTTP_CREATED           http_status_t(201, "Created")
# define HTTP_NO_CONTENT        http_status_t(204, "No Content")
# define HTTP_REDIRECT          http_status_t(301, "Moved Permanently")
# define HTTP_BAD_REQUEST       http_status_t(400, "Bad Request")
# define HTTP_UNAUTH            http_status_t(401, "Unauthorized")
# define HTTP_FORBIDDEN         http_status_t(403, "Forbidden")
# define HTTP_NOT_FOUND         http_status_t(404, "Not Found")
# define HTTP_NOT_ALLOW         http_status_t(405, "Method Not Allowed")
# define HTTP_TOO_LARGE         http_status_t(413, "Request Entity Too Large")
# define HTTP_LONG_URI          http_status_t(414, "URI Too Long")
# define HTTP_UNSUPPORT_MEDIA   http_status_t(415, "Unsupported Media Type")
# define HTTP_TEAPOT            http_status_t(418, "I'm a teapot")
# define HTTP_SERVER_ERROR      http_status_t(500, "Internal Server Error")
# define HTTP_UNSUPPORT_VERSION http_status_t(505, "HTTP Version Not Supported")

// Header define
# define HEADER_SEP                 ": "
# define HEADER_HOST                "Host"
# define HEADER_CONNECTION          "Connection"
# define HEADER_SERVER              "Server"
# define HEADER_DATE                "Date"
# define HEADER_CONNECTION          "Connection"
# define HEADER_CONTENT_TYPE        "Content-Type"
# define HEADER_CONTENT_LENGTH      "Content-Length"
# define HEADER_ENCODE              "Transfer-Encoding"

// Header value
# define CHUNK_ENCODE               "chunked"
# define CONNECTION_CLOSE           "close"
# define CONNECTION_ALIVE           "keep-alive"
# define TEXT_HTML                  "text/html"


#endif /* __WEBSERV_HPP__ */
