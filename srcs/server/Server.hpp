/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:41:34 by spoolpra          #+#    #+#             */
/*   Updated: 2024/02/29 19:17:54 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include <config/ServerConfig.hpp>
#include <fstream>
#include <iostream>

#include "http/HttpRequest.hpp"

class Server {
   public:
    Server(const ServerConfig& config);
    ~Server();

    bool          match_name(const std::string& name) const;
    void          serve_request(HttpRequest& req);
    HttpResponse* serve_404();
    HttpResponse* serve_500();
    HttpResponse* serve_static_files(const std::string& path, HttpRequest& req);

    const ServerConfig& getConfig() const;

   private:
    ServerConfig _config;
    const Logger _logger;
};

#endif /* __SERVER_HPP__ */
