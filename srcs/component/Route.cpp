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
    list_str_t  list_root_path,
    list_str_t  allow_method,
    bool        redirect,
    std::string redirect_path,
    bool        directory_listing,
    std::string default_file,
    bool        post_and_get,
    cgi_map_t   cgi_map
    ) : _list_root_path(list_root_path),
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


list_str_t Route::get_list_path() const
{
    return _list_root_path;
}


bool Route::check_client_dir(
    const list_str_t&   client_list_path,
    const list_str_t&   list_route_path,
    list_str_t&         list_path_tail
    ) const
{
    list_str_t::const_iterator  it;
    list_str_t::const_iterator  client_it;

    client_it = client_list_path.begin();
    list_path_tail.clear();

    // Check if route path is matched
    for (it = list_route_path.begin(); it != list_route_path.end(); ++it, ++client_it)
    {
        if (client_it == client_list_path.end())
        {
            return false;
        }
        else if (it->compare(*client_it) != 0)
        {
            return false;
        }
    }

    // Collect left over path to be path to file after route root
    for (it = client_it; it != client_list_path.end(); ++it)
    {
        list_path_tail.push_back(*it);
    }

    return true;
}
