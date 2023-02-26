/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Route.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:08:46 by spoolpra          #+#    #+#             */
/*   Updated: 2023/02/26 23:31:15 by spoolpra         ###   ########.fr       */
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
    _route_directory = std::vector<std::string>();
    int i = 0;
    while (root_path.size() > 0) {
        std::string dir;
        size_t next_pos;
        std::cout << root_path << std::endl;
        next_pos = root_path.find('/');
        if (next_pos == std::string::npos) {
            dir = root_path;
            root_path.clear();
        }
        else {
            dir = root_path.substr(0, next_pos);
            root_path = root_path.substr(next_pos + 1);
        }
        if (dir.empty() && i++ == 0) {
            continue;
        }
        _route_directory.push_back(dir);
    }
    (void)_redirect;
    (void)_allow_method;
    (void)_directory_listing;
    (void)_post_and_get;
}


Route::~Route() { }