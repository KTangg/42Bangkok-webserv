/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Route.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 22:44:34 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/07 01:24:21 by spoolpra         ###   ########.fr       */
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

        return methods;
    }

    /**
     * @brief Initialize the index files.
     *
     * @return std::vector<std::string> The index files.
     */
    std::vector<std::string> initialize_index_files() {
        std::vector<std::string> index_files;

        index_files.push_back("index.html");
        index_files.push_back("index.htm");

        return index_files;
    }
}  // namespace ft

/**
 * @brief Construct a new Route:: Route object
 *
 * @param src The object to do the copy.
 */
Route::Route(const Route& src) {
    *this = src;
}

/**
 * @brief Construct a new Route:: Route object
 *
 * @param path The path of the route.
 * @param root_directory The root directory of the route.
 * @param methods The methods allowed for the route.
 * @param redirect_path The redirect path of the route.
 * @param directory_listing The directory listing of the route.
 * @param index_files The index files of the route.
 * @param upload_directory The upload directory of the route.
 * @param cgi_extensions The cgi extensions of the route.
 */
Route::Route(const std::string&                path,
             const std::string&                root_directory,
             const std::vector<std::string>&   methods,
             const std::string&                redirect_path,
             const bool&                       directory_listing,
             const std::vector<std::string>&   index_files,
             const std::string&                upload_directory,
             const std::map<std::string, Cgi>& cgi_extensions)
    : _path(path),
      _root_directory(root_directory),
      _methods(methods),
      _redirect_path(redirect_path),
      _directory_listing(directory_listing),
      _index_files(index_files),
      _upload_directory(upload_directory),
      _cgi_extensions(cgi_extensions) {
}

/**
 * @brief Destroy the Route:: Route object
 *
 */
Route::~Route() {
}

/**
 * @brief Get the path of the route.
 *
 * @return const std::string& The path of the route.
 */
const std::string& Route::get_path() const {
    return _path;
}

/**
 * @brief Get the root directory of the route.
 *
 * @return const std::string& The root directory of the route.
 */
const std::string& Route::get_root_directory() const {
    return _root_directory;
}

/**
 * @brief Get the methods allowed for the route.
 *
 * @return const std::vector<std::string>& The methods allowed for the route.
 */
const std::vector<std::string>& Route::get_methods() const {
    return _methods;
}

/**
 * @brief Get the redirect path of the route.
 *
 * @return const std::string& The redirect path of the route.
 */
const std::string& Route::get_redirect_path() const {
    return _redirect_path;
}

/**
 * @brief Get the directory listing of the route.
 *
 * @return const bool& The directory listing of the route.
 */
const bool& Route::is_directory_listing() const {
    return _directory_listing;
}

/**
 * @brief Get the index files of the route.
 *
 * @return const std::vector<std::string>& The index files of the route.
 */
const std::vector<std::string>& Route::get_index_files() const {
    return _index_files;
}

/**
 * @brief Get the upload directory of the route.
 *
 * @return const std::string& The upload directory of the route.
 */
const std::string& Route::get_upload_directory() const {
    return _upload_directory;
}

/**
 * @brief Get the cgi extensions of the route.
 *
 * @param extension The extension of the cgi.
 * @return const Cgi& The cgi of the route.
 */
const Cgi& Route::get_cgi(const std::string& extension) const {
    std::map<std::string, Cgi>::const_iterator it = _cgi_extensions.find(extension);

    if (it == _cgi_extensions.end()) {
        throw std::runtime_error("Cgi extension not found");
    }

    return it->second;
}

/**
 * @brief Check if the method is allowed for the route.
 *
 * @param method The method to check.
 * @return true If the method is allowed for the route.
 * @return false If the method is not allowed for the route.
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
