/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:41:34 by spoolpra          #+#    #+#             */
/*   Updated: 2024/03/01 09:35:53 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include <sys/stat.h>

#include <config/ServerConfig.hpp>
#include <cstdio>
#include <fstream>
#include <iostream>

#include "http/HttpRequest.hpp"
#include "utils/mime_types.hpp"

class Server {
   public:
    Server(const ServerConfig& config);
    ~Server();

    bool          match_name(const std::string& name) const;
    void          serve_request(HttpRequest& req);
    HttpResponse* serve_get_response(std::string path, Route route, HttpRequest& req);
    HttpResponse* serve_post_response(std::string path, Route route, HttpRequest& req);
    HttpResponse* serve_delete_response(std::string path, Route route, HttpRequest& req);
    HttpResponse* serve_201();
    HttpResponse* serve_204();
    HttpResponse* serve_404();
    HttpResponse* serve_405();
    HttpResponse* serve_500();
    HttpResponse* serve_static_files(const std::string& path, HttpRequest& req);

    const ServerConfig& getConfig() const;

   private:
    ServerConfig _config;
    const Logger _logger;
};

#endif /* __SERVER_HPP__ */
