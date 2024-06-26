/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerConfig.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 17:54:58 by spoolpra          #+#    #+#             */
/*   Updated: 2024/03/01 18:18:18 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config/ServerConfig.hpp"

namespace ft {
    std::map<int, ErrorPage> initialize_error_pages() {
        std::map<int, ErrorPage> default_error_pages;

        for (std::vector<int>::const_iterator it = ft::default_error_code.begin();
             it != ft::default_error_code.end(); ++it) {
            default_error_pages.insert(std::pair<int, ErrorPage>(*it, ErrorPage(*it, "")));
        }

        return default_error_pages;
    }

}  // namespace ft

/**
 * @brief Construct a new Server Config:: Server Config object
 *
 * @param src The object to do the copy.
 */
ServerConfig::ServerConfig(const ServerConfig& src)
    : _name(src._name),
      _max_body_size(src._max_body_size),
      _error_pages(src._error_pages),
      _routes(src._routes),
      _timeout(src._timeout) {
}

/**
 * @brief Construct a new ServerConfig:: ServerConfig object
 *
 * @param name The name of the server.
 * @param max_body_size The maximum body size allowed.
 * @param error_pages The error pages.
 * @param routes The routes.
 */
ServerConfig::ServerConfig(const std::map<std::string, Route>& routes,
                           const std::string&                  name,
                           const size_t&                       max_body_size,
                           const std::map<int, ErrorPage>&     error_pages,
                           int                                 timeout)
    : _name(name),
      _max_body_size(max_body_size),
      _error_pages(error_pages),
      _routes(routes),
      _timeout(timeout) {
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
const std::string& ServerConfig::get_name() const {
    return _name;
}

/**
 * @brief Returns the maximum body size allowed.
 *
 * @return const size_t& The maximum body size allowed.
 */
const size_t& ServerConfig::get_max_body_size() const {
    return _max_body_size;
}

/**
 * @brief Returns the error page for the given code.
 *
 * @param code The code of the error page.
 * @return const ErrorPage& The error page.
 */
const ErrorPage& ServerConfig::get_error_page(int code) const {
    std::map<int, ErrorPage>::const_iterator it = _error_pages.find(code);

    if (it == _error_pages.end()) {
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
const Route& ServerConfig::get_route(const std::string& path) const {
    std::map<std::string, Route>::const_iterator dest = _routes.end();

    for (std::map<std::string, Route>::const_iterator it = _routes.begin(); it != _routes.end();
         it++) {
        size_t route_length = 0;
        if (it->first.length() == 0 || path.length() == 0) continue;

        // Searching for matching route prefix
        if (path.rfind(it->first, 0) == 0) {
            if (it->first.length() > route_length) {
                route_length = it->first.length();
                dest = it;
            }
        }
    }

    if (dest == _routes.end()) {
        throw std::out_of_range("Route not found");
    }

    return dest->second;
}

int ServerConfig::get_timeout() const {
    return _timeout;
}
