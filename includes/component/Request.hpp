/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 22:19:47 by spoolpra          #+#    #+#             */
/*   Updated: 2023/03/08 19:04:26 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef __REQUEST_HPP__
# define __REQUEST_HPP__


# include "webserv.hpp"

# include "component/Header.hpp"

# define METHOD_INDEX 0
# define PATH_INDEX 1
# define HTTP_VERSION_INDEX 2


class Request
{
    public:
        Request(const char* buffer, const size_t n);
        Request(const Request& rhs);
        Request&    operator=(const Request& rhs);

        virtual ~Request();

        std::string     getMethod() const;
        std::string     getPath() const;
        std::string     getHost() const;
        std::string     getHeader(const std::string& key) const;
        bool            isComplete() const;
        bool            isHeaderEnd() const;
        void            appendRequest(const char* buffer, size_t n);

        void            parseRequestLine();
        void            parseHeaderLine();

    private:
        Request();

        std::stringstream   _request;
        Header              _header;

        std::string         _method;
        std::string         _path;
        std::string         _content;
        size_t              _header_size;
        bool                _header_end;
        bool                _chunk;
        bool                _complete;

        void                _M_append_request(const char* buffer, size_t n);
        std::string         _M_read_line(bool wait);

        void                _M_parse_request_line(const std::string& line);

        static std::string  _S_validate_path(const std::string& path);
        static std::string  _S_validate_method(const std::string& method);
        static void         _S_validate_http(const std::string& http_version);
        static void         _S_validate_version_number(const std::string& version);
};


typedef std::map<int, Request>          map_request_t;
typedef map_request_t::iterator         it_request;
typedef map_request_t::const_iterator   const_it_request;


#endif
