/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 20:24:58 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/03 21:44:39 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "route/Cgi.hpp"

/**
 * @brief Construct a new cgi::cgi object
 *
 * @param path The path to the CGI executable.
 * @param extension The extension of the CGI executable.
 */
Cgi::Cgi(const std::string& path, const std::string& extension)
    : _path(path), _extension(extension) {
}

/**
 * @brief Destroy the cgi::cgi object
 *
 */
Cgi::~Cgi() {
}

/**
 * @brief Returns the path to the CGI executable.
 *
 * @return const std::string& The path to the CGI executable.
 */
const std::string& Cgi::getPath() const {
    return _path;
}

/**
 * @brief Returns the extension of the CGI executable.
 *
 * @return const std::string& The extension of the CGI executable.
 */
const std::string& Cgi::getExtension() const {
    return _extension;
}
