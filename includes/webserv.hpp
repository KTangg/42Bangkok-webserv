/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 20:10:46 by spoolpra          #+#    #+#             */
/*   Updated: 2023/03/06 17:06:21 by spoolpra         ###   ########.fr       */
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
typedef std::basic_string<unsigned char>                bytestring;
typedef std::basic_stringstream<unsigned char>          bytestream;
typedef bytestream::pos_type                            bytepos;
typedef std::vector<std::string>                        l_str_t;
typedef std::vector<struct pollfd>                      l_poll_t;
typedef std::vector<struct pollfd>::iterator            iterator_poll;
typedef std::vector<struct pollfd>::const_iterator      const_iterator_poll;
typedef std::map<int, std::string>                      map_int_str_t;
typedef std::pair<int, std::string>                     http_status_t;
typedef std::map<std::string, std::string>              map_str_str_t;



// Macro stuff
# define TIMEOUT_POLL       1000
# define BYTE_TO_CHAR(x)    static_cast<char>(x)
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
# define DEFAULT_BUFFER_SIZE    102400
# define DEFAULT_BODY_LIMIT     8192
# define DEFAULT_HTTP_LIMIT     8192
# define PROCESS_REQUEST_LINE   0
# define PROCESS_HEADER         1
# define PROCESS_CONTENT        2
# define PROCESS_REQUEST        3


// HTTP define
# define GET                    "GET"
# define POST                   "POST"
# define DELETE                 "DELETE"
# define CHUNK_ENCODE           "chunked"
# define HTTP_SLASH             "HTTP/"
# define HTTP_VERSION           1.1
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
# define HTTP_SERVER_ERROR      http_status_t(500, "Internal Server Error")
# define HTTP_UNSUPPORT_VERSION http_status_t(505, "HTTP Version Not Supported")


// Header define
# define HEADER_HOST                "host"
# define HEADER_TRANSFER_ENCODE     "transfer-encoding"
# define HEADER_CONTENT_LENGTH      "content-length"


// ft namespace
namespace ft
{
    l_str_t         parse_path_directory(std::string path);
    l_str_t         join_list(const l_str_t& a, const l_str_t& b);
    std::string     path_join(l_str_t::const_iterator first, l_str_t::const_iterator last);
    bool            is_number(const std::string& s);
    ssize_t         send(int socket, const void* buffer, size_t n);
    ssize_t         recv(int socket, void* buffer, size_t n);
    l_str_t         split(bytestring& bstr, unsigned char sep);
    l_str_t         split(bytestring& src, unsigned char sep_1, unsigned char sep_2);
    std::string     strnow();
    std::string     skip_ws(const std::string& str);
    std::string     tolower(const std::string& str);
    ssize_t         hex_to_dec(const std::string& str);


    // template <typename T>
    // struct is_bigger
    // {
    //     bool operator()(const T& x, const T& y) const
    //     {
    //         return x.size() > y.size();
    //     }
    // };


    class HttpException : public std::exception
    {
        public:
            HttpException(const http_status_t& status);
            
            virtual ~HttpException() throw() {};

            int     getCode() const;
            void    send(const int& socket, const bytestring& bstr) const;

        private:
            int             _code;
            std::string     _description;
    };
}


#endif /* __WEBSERV_HPP__ */
