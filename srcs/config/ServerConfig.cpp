/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerConfig.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 16:58:25 by spoolpra          #+#    #+#             */
/*   Updated: 2023/03/06 17:11:10 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "config/ServerConfig.hpp"


ServerConfig::ServerConfig(
    const map_int_str_t&    error_path_map,
    const map_route_t&      route_map,
    const std::string&      server_name,
    const size_t&           body_limit
    )
: _error_path_map(error_path_map),
  _route_map(route_map),
  _server_name(server_name),
  _body_limit(body_limit)
{ }


std::string     ServerConfig::getServerName() const
{
    return _server_name;
}


size_t          ServerConfig::getLimit() const
{
    return _body_limit;
}


const Route*    ServerConfig::searchRoute(const std::string& path) const
{
    for (const_iterator_route it = _route_map.begin(); it != _route_map.end(); ++it)
    {
        try
        {
            it->second.findPath(path);

            return &(it->second);
        }
        catch (const std::invalid_argument&)
        {
            continue;
        }
    }

    return NULL;
}