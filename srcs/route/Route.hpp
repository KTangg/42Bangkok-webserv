/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Route.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 18:17:51 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/03 22:50:39 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ROUTE_HPP__
#define __ROUTE_HPP__

#include <map>
#include <string>
#include <vector>

#include "route/Cgi.hpp"

class Route {
   public:
    Route(const std::string&                path,
          const std::string&                rootDirectory,
          const std::vector<std::string>&   methods = {"GET", "POST"},
          const std::string&                redirectPath = "",
          const bool&                       directoryListing = false,
          const std::string&                indexFile = "index.html",
          const std::map<std::string, Cgi>& cgiExtensions = {});

    ~Route();

    const std::string& getPath() const;
    const bool&        isMethodAllowed(const std::string& method) const;
    const std::string& getRedirectPath() const;
    const std::string& getRootDirectory() const;
    const std::string& getIndexFile() const;
    const bool&        isDirectoryListingAllowed() const;
    const Cgi&         getCgi(const std::string& extension) const;

   private:
    std::string                _path;
    std::vector<std::string>   _methods;
    std::string                _redirectPath;
    std::string                _rootDirectory;
    bool                       _directoryListing;
    std::string                _indexFile;
    std::map<std::string, Cgi> _cgiExtensions;
};

#endif /* __ROUTE_HPP__ */
