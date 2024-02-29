/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:34:12 by tratanat          #+#    #+#             */
/*   Updated: 2024/02/29 13:14:57 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpResponse.hpp"

HttpResponse::HttpResponse()
    : _status_code(200),
      _server("webserv/1.0.0"),
      _connection("close"),
      _content_type("text/plain") {
    set_date();
}

HttpResponse::HttpResponse(int status_code, const std::string& response_text)
    : _status_code(status_code),
      _server("webserv/1.0.0"),
      _connection("keep-alive"),
      _content_type("text/plain"),
      _content(response_text) {
    _content_length = response_text.length();
    set_date();
}

void HttpResponse::set_date() {
    char      buf[1000];
    time_t    now = time(0);
    struct tm tm = *gmtime(&now);

    strftime(buf, sizeof buf, "%a, %d %b %Y %H:%M:%S %Z", &tm);
    _date = buf;
}

std::string HttpResponse::get_raw_message() {
    std::stringstream msg;
    msg << "HTTP/1.1 " << _status_code << " OK" << CRLF;
    msg << "Date: " << _date << CRLF;
    msg << "Server: " << _server << CRLF;
    msg << "Connection: " << _connection << CRLF;
    if (_keep_alive.length() > 0) msg << "Keep-Alive: " << _keep_alive << CRLF;
    if (_content.length() > 0) msg << "Content-Type: " << _content_type << CRLF;
    if (_content_length > 0) msg << "Content-Length: " << _content_length << CRLF;
    msg << CRLF;
    msg << _content;
    return msg.str();
}