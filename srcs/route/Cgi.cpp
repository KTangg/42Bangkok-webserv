/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 20:24:58 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/07 00:31:55 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "route/Cgi.hpp"

/**
 * @brief Construct a new Cgi:: Cgi object
 *
 * @param src The object to do the copy.
 */
Cgi::Cgi(const Cgi& src) {
    *this = src;
}

/**
 * @brief Copy this object.
 *
 * @param rhs The object to copy.
 * @return Cgi& A reference to the copied object.
 */
Cgi& Cgi::operator=(const Cgi& rhs) {
    if (this != &rhs) {
        _path = rhs._path;
        _extension = rhs._extension;
    }
    return *this;
}

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
const std::string& Cgi::get_path() const {
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

/**
 * @brief Sets the path to the CGI executable.
 *
 * @param path The path to the CGI executable.
 */
void Cgi::set_path(const std::string& path) {
    _path = path;
}

/**
 * @brief Sets the extension of the CGI executable.
 *
 * @param extension The extension of the CGI executable.
 */
void Cgi::set_extension(const std::string& extension) {
    _extension = extension;
}
