/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Route.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 22:44:34 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/06 14:39:16 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "route/Route.hpp"

namespace ft {

    /**
     * @brief Initialize the methods.
     *
     * @return std::vector<std::string> The methods.
     */
    std::vector<std::string> initialize_methods() {
        std::vector<std::string> methods;

        methods.push_back("GET");
        methods.push_back("POST");

        // methods.push_back("HEAD");
        // methods.push_back("PUT");
        // methods.push_back("DELETE");
        // methods.push_back("OPTIONS");

        return methods;
    }

    /**
     * @brief Initialize the cgi extensions.
     *
     * @return std::map<std::string, Cgi> The cgi extensions.
     */
    std::map<std::string, Cgi> initialize_cgi_extension() {
        std::map<std::string, Cgi> cgi_extensions;

        return cgi_extensions;
    }
}  // namespace ft

/**
 * @brief Construct a new Route:: Route object
 *
 * @param path The path of the route.
 * @param root_directory The root directory of the route.
 * @param methods The methods allowed for the route.
 * @param redirect_path The redirect path of the route.
 * @param directory_listing The directory listing of the route.
 * @param index_file The index file of the route.
 * @param cgi_extensionsThe cgi extensions of the route.
 */
Route::Route(const std::string&                path,
             const std::string&                root_directory,
             const std::vector<std::string>&   methods,
             const std::string&                redirect_path,
             const bool&                       directory_listing,
             const std::string&                index_file,
             const std::map<std::string, Cgi>& cgi_extensions)
    : _path(path),
      _methods(methods),
      _redirect_path(redirect_path),
      _root_directory(root_directory),
      _directory_listing(directory_listing),
      _index_file(index_file),
      _cgi_extensions(cgi_extensions) {
}

/**
 * @brief Destroy the Route:: Route object
 *
 */
Route::~Route() {
}

/**
 * @brief Returns the path of the route.
 *
 * @return const std::string& The path of the route.
 */
const std::string& Route::get_path() const {
    return _path;
}

/**
 * @brief Returns true if the method is allowed for the route.
 *
 * @param method The method to check.
 * @return const bool& True if the method is allowed for the route.
 */
bool Route::is_method_allowed(const std::string& method) const {
    for (std::vector<std::string>::const_iterator it = _methods.begin(); it != _methods.end();
         ++it) {
        if (*it == method) {
            return true;
        }
    }

    return false;
}

/**
 * @brief Returns the redirect path of the route.
 *
 * @return const std::string& The redirect path of the route.
 */
const std::string& Route::get_redirect_path() const {
    return _redirect_path;
}

/**
 * @brief Returns the root directory of the route.
 *
 * @return const std::string& The root directory of the route.
 */
const std::string& Route::get_root_directory() const {
    return _root_directory;
}

/**
 * @brief Returns the index file of the route.
 *
 * @return const std::string& The index file of the route.
 */
const std::string& Route::get_index_file() const {
    return _index_file;
}

/**
 * @brief Returns true if the directory listing is allowed for the route.
 *
 * @return const bool& True if the directory listing is allowed for the route.
 */
bool Route::is_directory_listing_allowed() const {
    return _directory_listing;
}

/**
 * @brief Returns the cgi extension of the route.
 *
 * @param extension The extension of the cgi.
 * @return const Cgi& The cgi.
 */

const Cgi& Route::get_cgi(const std::string& extension) const {
    std::map<std::string, Cgi>::const_iterator it = _cgi_extensions.find(extension);

    if (it == _cgi_extensions.end()) {
        throw std::out_of_range("Cgi not found");
    }

    return it->second;
}
