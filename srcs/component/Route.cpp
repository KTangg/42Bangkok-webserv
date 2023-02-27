/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Route.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:08:46 by spoolpra          #+#    #+#             */
/*   Updated: 2023/02/28 01:03:30 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "component/Route.hpp"


Route::Route(
    std::string                         root_path,
    std::vector<std::string>            allow_method,
    bool                                redirect,
    std::string                         redirect_path,
    bool                                directory_listing,
    std::string                         default_file,
    bool                                post_and_get,
    std::map<std::string, std::string>  cgi_map
) : _root_path(root_path),
    _allow_method(allow_method),
    _redirect(redirect),
    _redirect_path(redirect_path),
    _directory_listing(directory_listing),
    _default_file(default_file),
    _post_and_get(post_and_get),
    _cgi_map(cgi_map)
{
    _route_directory = parse_path_directory(root_path);
    (void)_redirect;
    (void)_allow_method;
    (void)_directory_listing;
    (void)_post_and_get;
}


Route::~Route() { }


std::string Route::get_path() const {
    return _root_path;
}


bool    Route::check_client_dir(const std::vector<std::string>& client_dir) const {
    std::vector<std::string>::const_iterator    it;
    std::vector<std::string>::const_iterator    client_it;

    client_it = client_dir.begin();
    for (it = _route_directory.begin(); it != _route_directory.end(); ++it, ++client_it) {
        if (client_it == client_dir.end()) {
            return false;
        } else if (it->compare(*client_it) != 0) {
            return false;
        }
    }

    return true;
}
