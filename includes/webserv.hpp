/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 20:10:46 by spoolpra          #+#    #+#             */
/*   Updated: 2023/03/05 08:13:45 by spoolpra         ###   ########.fr       */
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
typedef struct sockaddr_in                          sockaddr_in_t;
typedef std::basic_string<unsigned char>            bytestring;
typedef std::basic_stringstream<unsigned char>      bytestream;
typedef bytestream::pos_type                        bytepos;
typedef std::vector<std::string>                    l_str_t;
typedef std::vector<struct pollfd>                  l_poll_t;
typedef std::vector<struct pollfd>::iterator        iterator_poll;
typedef std::vector<struct pollfd>::const_iterator  const_iterator_poll;
typedef std::map<int, std::string>                  map_int_str_t;
typedef std::pair<int, std::string>                 http_status_t;


// Macro stuff
# define TIMEOUT_POLL       1000
# define CHAR_TO_BYYE(x)    static_cast<unsigned char>(x)
# define STR_TO_BYTES(x)    reinterpret_cast<unsigned char*>(const_cast<char*>(x))
# define BYTES_TO_STR(x)    reinterpret_cast<char *>(const_cast<unsigned char*>(x))
# define BYTES_TO_VOID(x)   reinterpret_cast<void *>(const_cast<unsigned char*>(x))
# define SS_TO_STR(x)       static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()


// Default value
# define SERVER_VERSION         "KTangg/1.0.0"
# define DEFAULT_EVENT          POLLIN | POLLOUT
# define DEFAULT_SERVER_NAME    ""
# define DEFAULT_BUFFER_SIZE    1
# define DEFAULT_BODY_LIMIT     102400
# define DEFAULT_HEADER_LIMIT   8192


// HTTP define
# define GET                "GET"
# define POST               "POST"
# define DELETE             "DELETE"
# define HTTP_HEADER_END    "\r\n\r\n"
# define HTTP_SLASH         "HTTP/"
# define HTTP_VERSION       1.1
# define HTTP_CONTINUE      http_status_t(100, "Continue")
# define HTTP_OK            http_status_t(200, "OK")
# define HTTP_CREATED       http_status_t(201, "Created")
# define HTTP_NO_CONTENT    http_status_t(204, "No Content")
# define HTTP_REDIRECT      http_status_t(301, "Moved Permanently")
# define HTTP_BAD_REQUEST   http_status_t(400, "Bad Request")
# define HTTP_UNAUTH        http_status_t(401, "Unauthorized")
# define HTTP_FORBIDDEN     http_status_t(403, "Forbidden")
# define HTTP_NOT_FOUND     http_status_t(404, "Not Found")
# define HTTP_NOT_ALLOW     http_status_t(405, "Method Not Allowed")
# define HTTP_LENGTH_REQ    http_status_t(411, "Length Required")
# define HTTP_TOO_LARGE     http_status_t(413, "Content Too Large")
# define HTTP_LONG_URI      http_status_t(414, "URI Too Long")
# define HTTP_SERVER_ERROR  http_status_t(500, "Internal Server Error")
# define HTTP_NOT_SUPPORT   http_status_t(505, "HTTP Version Not Supported")


// Templates
template <typename T>
struct is_bigger
{
    bool operator()(const T& x, const T& y) const
    {
        return x.size() > y.size();
    }
};


// ft namespace
namespace ft
{
    l_str_t         parse_path_directory(std::string path);
    l_str_t         join_list(const l_str_t& a, const l_str_t& b);
    std::string     path_join(const l_str_t& l_path);
    bool            is_number(const std::string& s);
    size_t          send(int socket, const void* buffer, size_t n);
    size_t          recv(int socket, void* buffer, size_t n);
    l_str_t         split(bytestream& bs, unsigned char sep);
    l_str_t         split(bytestring& bstr, unsigned char sep);

    class   http_not_support : public std::exception {};
    class   http_bad_request : public std::exception {};
}

#endif /* __WEBSERV_HPP__ */
