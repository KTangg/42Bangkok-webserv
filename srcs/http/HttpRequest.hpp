/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:02:19 by tratanat          #+#    #+#             */
/*   Updated: 2024/04/07 16:34:09 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __HTTPREQUEST_HPP__
#define __HTTPREQUEST_HPP__

#include <string>
#include <vector>

#include "constants.hpp"
#include "http/HttpResponse.hpp"
#include "logger/Logger.hpp"
#include "server/Server.hpp"
#include "utils/exception.hpp"
#include "utils/utils.hpp"

class HttpRequest {
   public:
    HttpRequest(const Logger      &logger,
                const std::string &method,
                const std::string &path,
                const std::string &host,
                const std::string &connection,
                const int          content_length,
                const std::string &content_type,
                const std::string &content);
    ~HttpRequest();
    const std::string  &get_host() const;
    const std::string  &get_path() const;
    const std::string  &get_connection() const;
    const std::string  &get_method() const;
    const std::string  &get_content() const;
    int                 get_content_length() const;
    const std::string  &get_content_type() const;
    int                 get_timeout() const;
    HttpResponse       *get_response() const;
    Server             &get_server() const;
    static HttpRequest *parse_request(char *raw_msg, int len, const Logger &logger);
    void                append_content(const std::string &content, int len);
    bool                is_completed() const;

    void set_response(HttpResponse *res);
    void set_timeout(int timeout);
    void set_server(Server &server);

    bool check_timeout() const;

   private:
    HttpRequest();
    const Logger     &_logger;
    const std::string _method;
    const std::string _path;
    const std::string _host;
    const std::string _connection;
    const int         _content_length;
    const std::string _content_type;
    std::string       _content;
    Server           *_server;

    HttpResponse *_response;
    bool          _is_completed;
    time_t        _time;
    int           _timeout;
};

#endif