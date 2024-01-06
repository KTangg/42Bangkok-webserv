/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Route.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 18:17:51 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/06 17:05:22 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ROUTE_HPP__
#define __ROUTE_HPP__

#include <map>
#include <stdexcept>
#include <string>
#include <vector>

#include "route/Cgi.hpp"

namespace ft {
    std::vector<std::string>   initialize_methods();
    std::map<std::string, Cgi> initialize_cgi_extension();
}  // namespace ft

class Route {
   public:
    Route(const std::string&                path,
          const std::string&                root_directory,
          const std::vector<std::string>&   methods = ft::initialize_methods(),
          const std::string&                redirect_path = "",
          const bool&                       directory_listing = false,
          const std::string&                index_file = "index.html",
          const std::map<std::string, Cgi>& cgi_extensions = ft::initialize_cgi_extension());

    ~Route();

    const std::string& get_path() const;
    bool               is_method_allowed(const std::string& method) const;
    const std::string& get_redirect_path() const;
    const std::string& get_root_directory() const;
    const std::string& get_index_file() const;
    bool               is_directory_listing_allowed() const;
    const Cgi&         get_cgi(const std::string& extension) const;

   private:
    std::string                _path;
    std::vector<std::string>   _methods;
    std::string                _redirect_path;
    std::string                _root_directory;
    bool                       _directory_listing;
    std::string                _index_file;
    std::map<std::string, Cgi> _cgi_extensions;
};

#endif /* __ROUTE_HPP__ */
