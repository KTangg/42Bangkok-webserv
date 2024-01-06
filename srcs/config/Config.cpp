/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:44:16 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/04 21:44:20 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config/Config.hpp"

/**
 * @brief Construct a new Config:: Config object
 *
 */
Config::Config(int port, const std::string& host) : _port(port), _host(host) {
}

/**
 * @brief Destroy the Config:: Config object
 *
 */
Config::~Config() {
}

/**
 * @brief Returns the port number for the configuration.
 *
 * @return const int& The port number.
 */
const int& Config::get_port() const {
    return _port;
}

/**
 * @brief Returns the host for the configuration.
 *
 * @return const std::string& The host.
 */
const std::string& Config::get_host() const {
    return _host;
}

/**
 * @brief Adds a server configuration to the configuration.
 *
 * @param serverConfig The server configuration to be added.
 */
void Config::addServerConfig(ServerConfig* serverConfig) {
    _serverConfigs.push_back(serverConfig);
}

/**
 * @brief Returns the server configurations for the configuration.
 *
 * @return const std::vector<ServerConfig*>& The server configurations.
 */
const std::vector<ServerConfig*>& Config::getServerConfigs() const {
    return _serverConfigs;
}
