/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Route.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 22:44:34 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/03 22:51:04 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "route/Route.hpp"

/**
 * @brief Construct a new Route:: Route object
 *
 * @param path The path of the route.
 * @param rootDirectory The root directory of the route.
 * @param methods The methods allowed for the route.
 * @param redirectPath The redirect path of the route.
 * @param directoryListing The directory listing of the route.
 * @param indexFile The index file of the route.
 * @param cgiExtensions The cgi extensions of the route.
 */
Route::Route(const std::string&                path,
             const std::string&                rootDirectory,
             const std::vector<std::string>&   methods,
             const std::string&                redirectPath,
             const bool&                       directoryListing,
             const std::string&                indexFile,
             const std::map<std::string, Cgi>& cgiExtensions)
    : _path(path),
      _methods(methods),
      _redirectPath(redirectPath),
      _rootDirectory(rootDirectory),
      _directoryListing(directoryListing),
      _indexFile(indexFile),
      _cgiExtensions(cgiExtensions) {
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
const std::string& Route::getPath() const {
    return _path;
}

/**
 * @brief Returns true if the method is allowed for the route.
 *
 * @param method The method to check.
 * @return const bool& True if the method is allowed for the route.
 */
const bool& Route::isMethodAllowed(const std::string& method) const {
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
const std::string& Route::getRedirectPath() const {
    return _redirectPath;
}

/**
 * @brief Returns the root directory of the route.
 *
 * @return const std::string& The root directory of the route.
 */
const std::string& Route::getRootDirectory() const {
    return _rootDirectory;
}

/**
 * @brief Returns the index file of the route.
 *
 * @return const std::string& The index file of the route.
 */
const std::string& Route::getIndexFile() const {
    return _indexFile;
}

/**
 * @brief Returns true if the directory listing is allowed for the route.
 *
 * @return const bool& True if the directory listing is allowed for the route.
 */
const bool& Route::isDirectoryListingAllowed() const {
    return _directoryListing;
}

/**
 * @brief Returns the cgi extension of the route.
 *
 * @param extension The extension of the cgi.
 * @return const Cgi& The cgi.
 */
const Cgi& Route::getCgi(const std::string& extension) const {
    std::map<std::string, Cgi>::const_iterator it = _cgiExtensions.find(extension);

    if (it == _cgiExtensions.end()) {
        throw std::out_of_range("Cgi not found");
    }

    return it->second;
}
