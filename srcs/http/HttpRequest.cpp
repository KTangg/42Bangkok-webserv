/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:12:16 by tratanat          #+#    #+#             */
/*   Updated: 2024/04/07 16:35:51 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http/HttpRequest.hpp"

HttpRequest::HttpRequest(const Logger      &logger,
                         const std::string &method,
                         const std::string &path,
                         const std::string &host,
                         const std::string &connection,
                         const int          content_length = -1,
                         const std::string &content_type = "text/plain",
                         const std::string &content = "")
    : _logger(logger),
      _method(method),
      _path(path),
      _host(host),
      _connection(connection),
      _content_length(content_length),
      _content_type(content_type),
      _content(content),
      _response(0),
      _is_completed(false),
      _time(time(0)),
      _timeout(60) {
    if (content_length <= int(_content.length())) {
        _is_completed = true;
    }
}

HttpRequest::~HttpRequest() {
    if (_response) {
        delete _response;
    }
}

const std::string &HttpRequest::get_host() const {
    return _host;
}

const std::string &HttpRequest::get_path() const {
    return _path;
}

const std::string &HttpRequest::get_connection() const {
    return _connection;
}

const std::string &HttpRequest::get_method() const {
    return _method;
}

const std::string &HttpRequest::get_content() const {
    return _content;
}

int HttpRequest::get_content_length() const {
    return _content_length;
}

int HttpRequest::get_timeout() const {
    return _timeout;
}

HttpResponse *HttpRequest::get_response() const {
    if (!_response || !_response->is_ready()) return 0;
    return _response;
}

bool HttpRequest::is_completed() const {
    return _is_completed;
}

void HttpRequest::append_content(const std::string &content, int len) {
    _content += content.substr(0, len);
    if (_content.length() >= size_t(_content_length)) {
        _is_completed = true;
    }
}

void HttpRequest::set_response(HttpResponse *res) {
    int status_code = res->get_status_code();
    for (std::vector<int>::const_iterator it = ft::default_error_code.begin();
         it != ft::default_error_code.end(); ++it) {
        if (*it != status_code) continue;
        const ErrorPage &path = _server->getConfig().get_error_page(status_code);
        res->render_error_page(path);
    }
    _response = res;
    _is_completed = true;
}

void HttpRequest::set_timeout(int timeout) {
    _timeout = timeout;
}

void HttpRequest::set_server(Server &server) {
    _server = &server;
}

Server &HttpRequest::get_server() const {
    return *_server;
}

const std::string &HttpRequest::get_content_type() const {
    return _content_type;
}

bool HttpRequest::check_timeout() const {
    time_t cur_time = time(0);
    if (difftime(cur_time, _time) >= _timeout) {
        return true;
    }
    return false;
}

/**
 * @brief Parse raw HTTP request and returns an HttpRequest object
 *
 * @param raw_msg Raw HTTP request message
 * @param logger Parent's logger
 * @return HttpRequest* Request object
 */
HttpRequest *HttpRequest::parse_request(char *raw_msg, int len, const Logger &logger) {
    std::string              msg(raw_msg, len);
    std::vector<std::string> fields;
    size_t                   pos;
    std::string              method;
    std::string              path;
    std::string              host;
    std::string              connection = "close";
    std::string              content_type;
    int                      content_length = 0;
    std::string              content;

    pos = msg.find(CRLF);
    if (pos == std::string::npos) {
        throw ft::InvalidHttpRequest("Malformed headers: 0");
    }
    std::string              path_string = msg.substr(0, pos);
    std::vector<std::string> path_params = ft::split(path_string, " ", 2);
    if (path_params.size() >= 1) method = path_params[0];
    if (path_params.size() >= 2) path = path_params[1];

    if (pos < msg.length()) msg = msg.substr(pos + 1);

    int len_offset = 0;
    if (len < int(msg.length())) len_offset = int(msg.length() - len);

    while (msg.length() > 0) {
        pos = msg.find(CRLF);
        if (pos == 0) {
            if (content_length > 0 && content_length < int(msg.length()) - len_offset) {
                content = msg.substr(2, content_length);
            } else {
                content = msg.substr(2, int(msg.length()) - len_offset);
            }
            break;
        }
        std::string              line = msg.substr(0, pos);
        std::vector<std::string> split = ft::split(line, ":", 1);
        if (split.size() < 2) {
            throw ft::InvalidHttpRequest("Malformed headers: " + line);
        }
        std::string header_name = ft::string_lower(split[0]);

        if (header_name == "content-type") {
            content_type = split[1];
        } else if (header_name == "host") {
            host = split[1];
            size_t port_pos = host.find(":");
            if (port_pos != std::string::npos) host = host.substr(0, port_pos);
        } else if (header_name == "connection") {
            connection = split[1];
        } else if (header_name == "content-length") {
            std::stringstream length;
            length << split[1];
            length >> content_length;
        }

        if (pos == msg.length()) break;
        msg = msg.substr(pos + 2);
    }

    HttpRequest *request = new HttpRequest(logger, method, path, host, connection, content_length,
                                           content_type, content);
    return request;
}