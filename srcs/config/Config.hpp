/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:04:41 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/03 21:43:50 by spoolpra         ###   ########.fr       */
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

    const int&         getPort() const;
    const std::string& getHost() const;

    void                              addServerConfig(ServerConfig* serverConfig);
    const std::vector<ServerConfig*>& getServerConfigs() const;

   private:
    const int                  _port;
    const std::string          _host;
    std::vector<ServerConfig*> _serverConfigs;
};

#endif  // __CONFIG_HPP__
