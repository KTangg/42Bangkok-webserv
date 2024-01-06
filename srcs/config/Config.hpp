/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:04:41 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/07 00:03:02 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __CONFIG_HPP__
#define __CONFIG_HPP__

#include <string>
#include <vector>

#include "config/ServerConfig.hpp"

class Config {
   public:
    Config(int port, const std::string& host);
    ~Config();

    const int&         get_port() const;
    const std::string& get_host() const;

    void                              add_server_config(ServerConfig* server_configs);
    const std::vector<ServerConfig*>& get_server_configs() const;

   private:
    const int                  _port;
    const std::string          _host;
    std::vector<ServerConfig*> _server_configs;
};

#endif  // __CONFIG_HPP__
