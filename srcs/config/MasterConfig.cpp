/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MasterConfig.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 16:40:18 by spoolpra          #+#    #+#             */
/*   Updated: 2023/03/04 04:28:33 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "config/MasterConfig.hpp"


MasterConfig::MasterConfig(
    const std::string&  host,
    const uint16_t&     port
    )
: _host(host), _port(port), _server_map()
{ }


sockaddr_in_t   MasterConfig::getAddress() const
{
    sockaddr_in_t   address;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(_host.c_str());
    address.sin_port = htons(_port);

    return address;
}


map_server_t    MasterConfig::getServerConfig() const
{
    return _server_map;
}


void    MasterConfig::addServer(ServerConfig config)
{
    _server_map.insert(std::make_pair(config.getServerName(), config));
}
