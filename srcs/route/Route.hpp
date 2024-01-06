/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Route.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 18:17:51 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/07 01:03:01 by spoolpra         ###   ########.fr       */
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
    std::vector<std::string> initialize_methods();
    std::vector<std::string> initialize_index_files();
}  // namespace ft

class Route {
   public:
    Route(const Route& src);
    Route& operator=(const Route& rhs);

    Route(const std::string&                path,
          const std::string&                root_directory,
          const std::vector<std::string>&   methods = ft::initialize_methods(),
          const std::string&                redirect_path = "",
          const bool&                       directory_listing = false,
          const std::vector<std::string>&   index_files = ft::initialize_index_files(),
          const std::string&                upload_directory = "",
          const std::map<std::string, Cgi>& cgi_extensions = std::map<std::string, Cgi>());

    ~Route();

    const std::string&              get_path() const;
    const std::string&              get_root_directory() const;
    const std::vector<std::string>& get_methods() const;
    const std::string&              get_redirect_path() const;
    const bool&                     is_directory_listing() const;
    const std::vector<std::string>& get_index_files() const;
    const std::string&              get_upload_directory() const;
    const Cgi&                      get_cgi(const std::string& extension) const;

    void set_path(const std::string& path);
    void set_root_directory(const std::string& root_directory);
    void set_methods(const std::vector<std::string>& methods);
    void set_redirect_path(const std::string& redirect_path);
    void set_directory_listing(const bool& directory_listing);
    void set_index_files(const std::vector<std::string>& index_files);
    void set_upload_directory(const std::string& upload_directory);
    void set_cgi_extensions(const std::map<std::string, Cgi>& cgi_extensions);

    bool is_method_allowed(const std::string& method) const;

   private:
    Route();

    std::string                _path;
    std::string                _root_directory;
    std::vector<std::string>   _methods;
    std::string                _redirect_path;
    bool                       _directory_listing;
    std::vector<std::string>   _index_files;
    std::string                _upload_directory;
    std::map<std::string, Cgi> _cgi_extensions;
};

#endif /* __ROUTE_HPP__ */
