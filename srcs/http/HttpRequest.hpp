/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:02:19 by tratanat          #+#    #+#             */
/*   Updated: 2024/02/29 18:54:55 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __HTTPREQUEST_HPP__
#define __HTTPREQUEST_HPP__

#include <string>
#include <vector>

#include "constants.hpp"
#include "http/HttpResponse.hpp"
#include "logger/Logger.hpp"
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
    HttpResponse       *get_response() const;
    static HttpRequest *parse_request(char *raw_msg, const Logger &logger);

    void set_response(HttpResponse *res);

   private:
    HttpRequest();
    const Logger     &_logger;
    const std::string _method;
    const std::string _path;
    const std::string _host;
    const std::string _connection;
    const int         _content_length;
    const std::string _content_type;
    const std::string _content;

    HttpResponse *_response;
};

#endif