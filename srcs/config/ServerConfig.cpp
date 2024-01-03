/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerConfig.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 17:54:58 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/03 22:41:37 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config/ServerConfig.hpp"

namespace ft {
    std::map<int, ErrorPage> initializeErrorPages() {
        std::map<int, ErrorPage> defaultErrorPages;

        for (std::vector<int>::const_iterator it = ft::defaultErrorCode.begin();
             it != ft::defaultErrorCode.end(); ++it) {
            defaultErrorPages.insert(std::pair<int, ErrorPage>(*it, ErrorPage(*it, "")));
        }

        return defaultErrorPages;
    }
}  // namespace ft

/**
 * @brief Construct a new ServerConfig:: ServerConfig object
 *
 * @param name The name of the server.
 * @param maxBodySize The maximum body size allowed.
 * @param errorPages The error pages.
 * @param routes The routes.
 */
ServerConfig::ServerConfig(const std::string&                  name,
                           const size_t&                       maxBodySize,
                           const std::map<std::string, Route>& routes,
                           const std::map<int, ErrorPage>&     errorPages)
    : _name(name), _maxBodySize(maxBodySize), _errorPages(errorPages), _routes(routes) {
}

/**
 * @brief Destroy the ServerConfig:: ServerConfig object
 *
 */
ServerConfig::~ServerConfig() {
}

/**
 * @brief Returns the name of the server.
 *
 * @return const std::string& The name of the server.
 */
const std::string& ServerConfig::getName() const {
    return _name;
}

/**
 * @brief Returns the maximum body size allowed.
 *
 * @return const size_t& The maximum body size allowed.
 */
const size_t& ServerConfig::getMaxBodySize() const {
    return _maxBodySize;
}

/**
 * @brief Returns the error page for the given code.
 *
 * @param code The code of the error page.
 * @return const ErrorPage& The error page.
 */
const ErrorPage& ServerConfig::getErrorPage(int code) const {
    std::map<int, ErrorPage>::const_iterator it = _errorPages.find(code);

    if (it == _errorPages.end()) {
        throw std::out_of_range("Error page not found");
    }

    return it->second;
}

/**
 * @brief Returns the route for the given path.
 *
 * @param path The path of the route.
 * @return const Route& The route.
 */
const Route& ServerConfig::getRoute(const std::string& path) const {
    std::map<std::string, Route>::const_iterator it = _routes.find(path);

    if (it == _routes.end()) {
        throw std::out_of_range("Route not found");
    }

    return it->second;
}
