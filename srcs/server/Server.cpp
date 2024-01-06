/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:43:14 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/04 15:44:33 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/Server.hpp"

/**
 * @brief Construct a new Server:: Server object
 *
 * @param config
 */
Server::Server(const ServerConfig& config) : _config(config) {}

/**
 * @brief Destroy the Server:: Server object
 *
 */
Server::~Server() {}

/**
 * @brief Get the Config object
 *
 * @return const ServerConfig&
 */
const ServerConfig& Server::getConfig() const { return _config; }

