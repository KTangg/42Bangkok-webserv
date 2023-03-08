/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MasterConfig.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 16:40:18 by spoolpra          #+#    #+#             */
/*   Updated: 2023/03/08 18:32:52 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "config/MasterConfig.hpp"


/*
Constructor / Deconstructor
*/

/**
 * @brief Construct a new Master Config:: Master Config object
 *
 * @param port Listening port
 */
MasterConfig::MasterConfig(const uint16_t& port)
: _addr(), _server_v()
{
    _addr.sin_family = AF_INET;
    _addr.sin_addr.s_addr = INADDR_ANY;
    _addr.sin_port = htons(port);
}


/**
 * @brief Construct a new Master Config:: Master Config object
 *
 * @param rhs Object to be copied
 */
MasterConfig::MasterConfig(const MasterConfig& rhs)
{
    *this = rhs;
    std::string a;
}


/**
 * @brief Set Master Config value as another Master Config object
 *
 * @param rhs Object to be copied
 * @return MasterConfig& Copied object
 */
MasterConfig&   MasterConfig::operator=(const MasterConfig&rhs)
{
    _addr = rhs._addr;
    _server_v = rhs._server_v;

    return *this;
}


/**
 * @brief Destroy the Master Config:: Master Config object
 *
 */
MasterConfig::~MasterConfig() { }


/*
Public Method
*/


/**
 * @brief Get listen address
 *
 * @return sockaddr_in_t Listen address
 */
sockaddr_in_t   MasterConfig::getAddress() const
{
    return _addr;
}


/**
 * @brief Get vector of Server Config
 *
 * @return v_server_t Vector of Server Config
 */
v_server_t      MasterConfig::getServerConfig() const
{
    return _server_v;
}


/**
 * @brief Add new Server Config to Master Config
 *
 * @param config Server Config to be added
 */
void    MasterConfig::addServer(const ServerConfig& config)
{
    _server_v.push_back(config);
}



/**
 * @brief Check whether if host is exist (case-insensitive)
 *
 * @param host Host name to be checked
 * @return true if host already exist, otherwise false
 */
bool    MasterConfig::existHost(const std::string& host) const
{
    for (const_it_server it = _server_v.begin(); it != _server_v.end(); ++it)
    {
        std::string check_name = it->getName();
        if (check_name.compare(ft::tolower(host)) == 0)
        {
            return true;
        }
    }

    return false;
}
