/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerConfig.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 17:53:52 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/03 22:50:33 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SERVERCONFIG_HPP__
#define __SERVERCONFIG_HPP__

#include <map>
#include <string>

#include "error/ErrorPage.hpp"
#include "route/Route.hpp"

namespace ft {
    std::map<int, ErrorPage> initializeErrorPages();
}  // namespace ft

class ServerConfig {
   public:
    ServerConfig(const std::string&                  name = "",
                 const size_t&                       maxBodySize = 1048576,
                 const std::map<std::string, Route>& routes = {},
                 const std::map<int, ErrorPage>&     errorPages = ft::initializeErrorPages());
    ~ServerConfig();

    const std::string& getName() const;
    const size_t&      getMaxBodySize() const;
    const ErrorPage&   getErrorPage(int code) const;
    const Route&       getRoute(const std::string& path) const;

   private:
    std::string                  _name;
    size_t                       _maxBodySize;
    std::map<int, ErrorPage>     _errorPages;
    std::map<std::string, Route> _routes;
};

#endif /* __SERVERCONFIG_HPP__ */
