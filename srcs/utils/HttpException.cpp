/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpException.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 12:13:02 by spoolpra          #+#    #+#             */
/*   Updated: 2023/03/05 14:29:31 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "webserv.hpp"


ft::HttpException::HttpException(const http_status_t& status)
{
    _code = status.first;
    _description = status.second;
}


int     ft::HttpException::getCode() const
{
    return _code;
}


void    ft::HttpException::send(const int& socket, const bytestring& bstr) const
{
    std::stringstream    ss;
    (void)bstr;
    ss << "HTTP/1.1 " << _code << " " << _description << "\n" << "Server: KTangg\n";
    ss << "Date: " << ft::strnow() << "\n";
    ss << "Connection: close\n" << "Content-Length: 0\n\n";

    ft::send(socket, ss.str().c_str(), ss.str().size());
}