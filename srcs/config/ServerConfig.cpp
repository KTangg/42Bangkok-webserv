/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerConfig.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 16:58:25 by spoolpra          #+#    #+#             */
/*   Updated: 2023/03/07 20:30:43 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "config/ServerConfig.hpp"


/*
Constructor / Deconstructor
*/


/**
 * @brief Construct a new Server Config:: Server Config object
 *
 * @param host Hostname (will be converted to lower)
 * @param name Server name
 * @param limit Body limit
 * @param error_map Map of status code to error file path
 * @param route_map Map of route path to Route object
 */
ServerConfig::ServerConfig(
    const std::string&      host,
    const std::string&      name,
    const size_t&           limit,
    const map_error_t&      error_map,
    const map_route_t&      route_map
    )
{
    _host = ft::tolower(host);
    _name = name;
    _limit = limit;
    _error_map = error_map;
    _route_map = route_map;
}


/**
 * @brief Construct a new Server Config:: Server Config object
 *
 * @param rhs Object to be copied
 */
ServerConfig::ServerConfig(const ServerConfig& rhs)
{
    *this = rhs;
}


/**
 * @brief Set Server Config value as another Server Config object
 *
 * @param rhs Object to be copied
 * @return ServerConfig& Copied object
 */
ServerConfig&   ServerConfig::operator=(const ServerConfig& rhs)
{
    _host = rhs._host;
    _name = rhs._name;
    _limit = rhs._limit;
    _error_map = rhs._error_map;
    _route_map = rhs._route_map;

    return *this;
}


/**
 * @brief Destroy the Server Config:: Server Config object
 *
 */
ServerConfig::~ServerConfig() { }


/*
Public Method
*/


/**
 * @brief Get hostname
 *
 * @return std::string hostname
 */
std::string     ServerConfig::getHost() const
{
    return _host;
}


/**
 * @brief Get server name
 *
 * @return std::string server name
 */
std::string     ServerConfig::getName() const
{
    return _name;
}


/**
 * @brief Get body limit
 *
 * @return size_t body limit
 */
size_t          ServerConfig::getLimit() const
{
    return _limit;
}


/**
 * @brief Search for error file related to status code
 *
 * @param code error status code
 * @return const std::string& path to error file
 * @exception std::out_of_range is thrown if error code not found
 */
const std::string&  ServerConfig::searchError(const int code) const
{
    return _error_map.at(code);
}


/**
 * @brief Search for route that path should be processed
 *
 * @param path searching path
 * @return const Route& Route object where path should be processed
 * @exception std::out_of_range is thrown if path not belong to any route
 */
const Route&    ServerConfig::searchRoute(const std::string& path) const
{
    for (const_it_route it = _route_map.begin(); it != _route_map.end(); ++it)
    {
        if (it->second.matchRoute(path))
        {
            return it->second;
        }
    }

    throw std::out_of_range("Path not match any routes");
}
