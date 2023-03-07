/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Route.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:08:46 by spoolpra          #+#    #+#             */
/*   Updated: 2023/03/07 06:59:25 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "component/Route.hpp"

Route::Route(
    const std::string&      route_path,
    const std::string&      root_path,
    const l_str_t&          allow_method,
    const std::string&      redirect,
    const bool&             listing,
    const std::string&      file,
    const map_cgi_t&        cgi_map
    )
: _l_route_path(),
  _root_path(root_path),
  _allow_method(allow_method),
  _redirect(redirect),
  _listing(listing),
  _file(file),
  _cgi_map(cgi_map)
{ 
    _l_route_path = ft::parse_path_directory(route_path);
    if (_root_path.size() > 1)
    {
        size_t  last_index = _root_path.size() - 1;
        if (_root_path[last_index] == '/')
        {
            _root_path.erase(last_index);
        }
    }
}


Route::~Route() {}


bool    Route::isRedirect() const
{
    return !_redirect.empty();
}


bool    Route::isListing() const
{
    return _listing;
}


std::string     Route::getFile() const
{
    return _file;
}


std::string     Route::findPath(const std::string& path) const
{
    l_str_t l_path = ft::parse_path_directory(path);
    l_str_t::const_iterator it_path = l_path.begin();

    for (l_str_t::const_iterator it = _l_route_path.begin(); it != _l_route_path.end(); ++it)
    {
        if (it_path == l_path.end() || it_path->compare(*it))
        {
            throw std::invalid_argument("");
        }
        ++it_path;
    }

    std::string add_path = ft::path_join(l_path.begin(), l_path.end());

    return _root_path + add_path;
}


bool    Route::checkMethod(const std::string& method) const
{
    for (l_str_t::const_iterator it = _allow_method.begin(); it != _allow_method.end(); ++it)
    {
        if (!method.compare(*it))
        {
            return true;
        }
    }

    return false;
}