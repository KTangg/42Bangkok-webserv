/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpException.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 12:13:02 by spoolpra          #+#    #+#             */
/*   Updated: 2023/03/07 20:43:47 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "utils/HttpExceoption.hpp"


ft::HttpException::HttpException(
    const http_status_t&    status,
    const std::string&      server,
    const Header&           header,
    const std::string&      content
    )
{
    _code = status.first;
    _description = status.second;
    _server = server;
    _header = header;
    _content = content;
}


ft::HttpException::HttpException(const HttpException& rhs)
{
    *this = rhs;
}


ft::HttpException& ft::HttpException::operator=(const HttpException& rhs)
{
    _code = rhs._code;
    _description = rhs._description;
    _server = rhs._server;
    _header = rhs._header;
    _content = rhs._content;

    return *this;
}


ft::HttpException::~HttpException() throw() { }


int     ft::HttpException::getCode() const
{
    return _code;
}


void    ft::HttpException::send(const int socket) const
{
    std::stringstream    ss;

    ss << HTTP << "/" << HTTP_VERSION;
    ss << _code << " " << _description << CRLF;
    ss << HEADER_SERVER << HEADER_SEP << _server << CRLF;
    ss << HEADER_DATE << ft::strnow() << CRLF;
    ss << HEADER_CONNECTION << HEADER_SEP << CONNECTION_CLOSE << CRLF;

    _header.generateHeader(ss);

    ss << _content;

    std::string response = ss.str();

    ft::send(socket, response.c_str(), response.size());
}
