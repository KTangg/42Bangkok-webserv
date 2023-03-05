/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Route.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:08:46 by spoolpra          #+#    #+#             */
/*   Updated: 2023/03/03 17:19:13 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "component/Route.hpp"

Route::Route(
    l_str_t         l_route_path,
    l_str_t         l_root_path,
    l_str_t         allow_method,
    bool            redirect,
    std::string     redirect_path,
    bool            directory_listing,
    std::string     default_file,
    bool            post_and_get,
    map_cgi_t       cgi_map
    )
: _l_route_path(l_route_path),
  _l_root_path(l_root_path),
  _allow_method(allow_method),
  _redirect(redirect),
  _redirect_path(redirect_path),
  _directory_listing(directory_listing),
  _default_file(default_file),
  _post_and_get(post_and_get),
  _cgi_map(cgi_map)
{
    (void)_redirect;
    (void)_allow_method;
    (void)_directory_listing;
    (void)_post_and_get;
}


Route::~Route() {}
