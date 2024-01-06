/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:44:16 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/07 02:15:43 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config/Config.hpp"

/**
 * @brief Construct a new Config:: Config object
 *
 * @param src The object to do the copy.
 */
Config::Config(const Config& src)
    : _port(src._port), _host(src._host), _server_configs(src._server_configs) {
}

/**
 * @brief Construct a new Config:: Config object
 *
 * @param port The port.
 * @param host The host.
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
 * @brief Returns the port.
 *
 * @return const int& The port.
 */
const int& Config::get_port() const {
    return _port;
}

/**
 * @brief Returns the host.
 *
 * @return const std::string& The host.
 */
const std::string& Config::get_host() const {
    return _host;
}

/**
 * @brief Add a server config.
 *
 * @param server_config The server config.
 */
void Config::add_server_config(ServerConfig server_config) {
    _server_configs.push_back(server_config);
}

/**
 * @brief Returns the server configs.
 *
 * @return const std::vector<ServerConfig>& The server configs.
 */
const std::vector<ServerConfig>& Config::get_server_configs() const {
    return _server_configs;
}
