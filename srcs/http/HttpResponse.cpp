/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:34:12 by tratanat          #+#    #+#             */
/*   Updated: 2024/04/20 12:26:20 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpResponse.hpp"

HttpResponse::HttpResponse()
    : _status_code(200),
      _server("webserv/1.0.0"),
      _connection("close"),
      _content_type("text/plain"),
      _cgi(0) {
    set_date();
}

HttpResponse::HttpResponse(int status_code)
    : _status_code(status_code),
      _server("webserv/1.0.0"),
      _connection("keep-alive"),
      _content_type("text/plain"),
      _cgi(0) {
    set_date();
}

/**
 * @brief Construct a new HttpResponse object from a string
 *
 * @param status_code HTTP status code
 * @param response_text Text content to be sent
 */
HttpResponse::HttpResponse(int status_code, const std::string& response_text)
    : _status_code(status_code),
      _server("webserv/1.0.0"),
      _connection("keep-alive"),
      _content_type("text/plain"),
      _content(response_text),
      _cgi(0) {
    _content_length = response_text.length();
    set_date();
}
HttpResponse::HttpResponse(int                status_code,
                           const std::string& connection,
                           const std::string& keep_alive,
                           const std::string& content_type,
                           const std::string& content)
    : _status_code(status_code),
      _server("webserv/1.0.0"),
      _connection(connection),
      _keep_alive(keep_alive),
      _content_type(content_type),
      _content(content),
      _cgi(0) {
    _content_length = content.length();
    set_date();
}

HttpResponse::~HttpResponse() {
    if (_cgi) delete _cgi;
}

/**
 * @brief Initialize date of Http Response object in IMF-fixdate format:
 *        https://www.rfc-editor.org/rfc/rfc7231#section-7.1.1.1
 *
 */
void HttpResponse::set_date() {
    char      buf[1000];
    time_t    now = time(0);
    struct tm tm = *gmtime(&now);

    strftime(buf, sizeof buf, "%a, %d %b %Y %H:%M:%S %Z", &tm);
    _date = buf;
}

/**
 * @brief Set the Content-Type header of the response.
 *
 * @param content_type The MIME type to be set.
 */
void HttpResponse::set_content_type(const std::string& content_type) {
    _content_type = content_type;
}

/**
 * @brief Set CGI object and execute the CGI call
 *
 * @param cgi CGI object configured with path of CGI executable
 * @param filepath Path of the CGI script
 */
void HttpResponse::set_cgi(Cgi* cgi, const std::string& filepath) {
    _cgi = cgi;
    _cgi->execute(filepath);
}

/**
 * @brief Check whether the response is ready to be sent. If there's a CGI call, it will check
 * the CGI object whether it has finished processing the request.
 *
 * @return true The response is ready to be sent.
 * @return false The response is not ready.
 */
bool HttpResponse::is_ready() {
    if (!_cgi) return true;
    if (!_cgi->is_ready()) return false;
    _content = _cgi->get_content();
    set_content_type(ft::get_mime_type("html"));
    _content_length = _content.length();
    return true;
}

const std::string& HttpResponse::get_redirection() {
    return _redirection;
}

void HttpResponse::set_redirection(std::string location) {
    _redirection = location;
}

void HttpResponse::set_connection(std::string connection) {
    if (connection == "keep-alive" || connection == "close")
        _connection = connection;
    else
        _connection = "keep-alive";
}

/**
 * @brief Generate a string of HTTP response
 *
 * @return std::string
 */
std::string HttpResponse::get_raw_message() {
    std::stringstream msg;

    // Get status message from status code
    std::string                                status_msg = "Unknown";
    std::map<int, std::string>::const_iterator pos = ft::http_status_codes.find(_status_code);
    if (pos != ft::http_status_codes.end()) status_msg = pos->second;

    msg << "HTTP/1.1 " << _status_code << " " << status_msg << CRLF;
    if (_redirection.length() > 0) msg << "Location: " << _redirection << CRLF;
    msg << "Date: " << _date << CRLF;
    msg << "Server: " << _server << CRLF;
    msg << "Connection: " << _connection << CRLF;
    if (_connection == "keep-alive" && _keep_alive.length() > 0)
        msg << "Keep-Alive: " << _keep_alive << CRLF;
    msg << "Content-Type: " << _content_type << CRLF;
    msg << "Content-Length: " << _content_length << CRLF;
    msg << CRLF;
    msg << _content;
    return msg.str();
}

int HttpResponse::get_status_code() const {
    return _status_code;
}

void HttpResponse::render_error_page(const ErrorPage& error) {
    _content_type = ft::get_mime_type("html");
    _content = error.get_error_page();
    _content_length = _content.length();
}