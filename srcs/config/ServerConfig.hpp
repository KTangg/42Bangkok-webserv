/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerConfig.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 17:53:52 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/07 02:08:06 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SERVERCONFIG_HPP__
#define __SERVERCONFIG_HPP__

#include <map>
#include <string>

#include "error/ErrorPage.hpp"
#include "route/Route.hpp"

#ifndef DEFAULT_MAX_BODY_SIZE
#define DEFAULT_MAX_BODY_SIZE 1048576
#endif

namespace ft {
    std::map<int, ErrorPage> initialize_error_pages();
}  // namespace ft

class ServerConfig {
   public:
    ServerConfig(const ServerConfig& src);
    ServerConfig(const std::map<std::string, Route>& routes,
                 const std::string&                  name = "",
                 const size_t&                       max_body_size = DEFAULT_MAX_BODY_SIZE,
                 const std::map<int, ErrorPage>&     error_pages = ft::initialize_error_pages());

    ~ServerConfig();

    const std::string& get_name() const;
    const size_t&      get_max_body_size() const;
    const ErrorPage&   get_error_page(int code) const;
    const Route&       get_route(const std::string& path) const;

   private:
    ServerConfig();
    ServerConfig& operator=(const ServerConfig& rhs);

    const std::string                  _name;
    const size_t                       _max_body_size;
    const std::map<int, ErrorPage>     _error_pages;
    const std::map<std::string, Route> _routes;
};

#endif /* __SERVERCONFIG_HPP__ */
