/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:12:16 by tratanat          #+#    #+#             */
/*   Updated: 2024/02/28 21:40:28 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http/HttpRequest.hpp"

HttpRequest::HttpRequest(const Logger      &logger,
                         const std::string &method,
                         const std::string &path,
                         const std::string &host,
                         const std::string &connection,
                         const int          content_length = -1,
                         const std::string &content_type = "application/octet-stream",
                         const std::string &content = "")
    : _logger(logger),
      _method(method),
      _path(path),
      _host(host),
      _connection(connection),
      _content_length(content_length),
      _content_type(content_type),
      _content(content) {
    _logger.log(Logger::INFO, "Received HTTP Request: " + _method + " " + _path);
    _logger.log(Logger::DEBUG, "\tHost: " + _host + " Connection: " + _connection);
    _logger.log(Logger::DEBUG, "\tContent-Type: " + _content_type);
    _logger.log(Logger::DEBUG, "\tContent: " + _content);
}

HttpRequest *HttpRequest::parse_request(char *raw_msg, const Logger &logger) {
    std::string              msg(raw_msg);
    std::vector<std::string> fields;
    size_t                   pos;
    std::string              method;
    std::string              path = "/";
    std::string              host;
    std::string              connection;
    std::string              content_type = "application/octet-stream";
    int                      content_length = 0;
    std::string              content;

    pos = msg.find("\r\n");
    if (pos == std::string::npos) {
        // TODO: throw something
    }
    std::string              path_string = msg.substr(0, pos);
    std::vector<std::string> path_params = ft::split(path_string, " ", 2);
    if (path_params.size() <= 0) {
        // TODO: throw something
    }
    method = path_params[0];
    if (path_params.size() >= 2) {
        path = path_params[1];
    }

    msg = msg.substr(pos + 1);

    while (msg.length() > 0) {
        pos = msg.find("\r\n");
        if (pos <= 1) {
            if (content_length > 0) {
                content = msg.substr(1, content_length + 2);
            }
            break;
        }
        std::string              line = msg.substr(0, pos);
        std::vector<std::string> split = ft::split(line, ":", 1);
        if (split.size() < 2) {
            // TODO: throw invalid headers
        }
        std::string header_name = ft::string_lower(split[0]);

        if (header_name == "content-type") {
            content_type = split[1];
        } else if (header_name == "host") {
            host = split[1];
        } else if (header_name == "connection") {
            connection = split[1];
        } else if (header_name == "content-length") {
            std::stringstream length;
            length << split[1];
            length >> content_length;
        }

        if (pos == msg.length()) break;
        msg = msg.substr(pos + 1);
    }

    HttpRequest *request = new HttpRequest(logger, method, path, host, connection, content_length,
                                           content_type, content);
    return request;
}