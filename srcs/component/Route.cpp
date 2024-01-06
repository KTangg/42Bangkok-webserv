/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Route.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:08:46 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/06 14:14:12 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "component/Route.hpp"


Route::Route(
    const std::string&      route,
    const std::string&      root,
    const v_str_t&          allow,
    const bool&             redirect,
    const std::string&      redirect_path,
    const bool&             listing,
    const std::string&      index,
    const map_cgi_t&        cgi_map
    )
{
    _route = ft::parse_path(route);
    _root = ft::trim_path(root);
    _allow = allow;
    _redirect = redirect;
    _redirect_path = redirect_path;
    _listing = listing;
    _index = index;
    _cgi_map = cgi_map;
}


/**
 * @brief Construct a new Route:: Route object
 *
 * @param rhs
 */
Route::Route(const Route& rhs)
{
    *this = rhs;
}


/**
 * @brief
 *
 * @param rhs
 * @return Route&
 */
Route& Route::operator=(const Route& rhs)
{
    _route = rhs._route;
    _root = rhs._root;
    _allow = rhs._allow;
    _redirect = rhs._redirect;
    _redirect_path = rhs._redirect_path;
    _listing = rhs._listing;
    _index = rhs._index;
    _cgi_map = rhs._cgi_map;

    return *this;
}


/**
 * @brief Destroy the Route:: Route object
 *
 */
Route::~Route() { }


/**
 * @brief
 *
 * @return std::string
 */
std::string Route::getRoot() const
{
    return _root;
}


/**
 * @brief
 *
 * @return v_str_t
 */
v_str_t     Route::getAllow() const
{
    return _allow;
}


/**
 * @brief
 *
 * @return std::string
 */
std::string Route::getIndex() const
{
    return _index;
}



bool    Route::isListing() const
{
    return _listing;
}



bool    Route::isRedirect() const
{
    return _redirect;
}



std::string Route::get_redirect_path() const
{
    return _redirect_path;
}



/**
 * @brief Get the CGI path
 *
 * @param ext file extension ex. ".py", ".php"
 * @return std::string CGI path
 * @exception std::out_of_range is throw when extension not found
 */
std::string Route::get_cgi(const std::string& ext) const
{
    return _cgi_map.at(ext);
}


/**
 * @brief Check if method is allow on the route
 *
 * @param method method to check ex. GET POST
 * @return true if allow, otherwise false
 */
bool    Route::isAllow(const std::string& method) const
{
    for (const_it_v_str it = _allow.begin(); it != _allow.end(); ++it)
    {
        if (it->compare(method) == 0)
        {
            return true;
        }
    }

    return false;
}


/**
 * @brief Matching URL with route path
 *
 * @param path url path
 * @return true if path is on this route, otherwise false is returned
 */
bool    Route::matchRoute(const std::string& path) const
{
    v_str_t     path_v = ft::parse_path(path);

    const_it_v_str  it_path = path_v.begin();
    for (const_it_v_str it = _route.begin(); it != _route.end(); ++it, ++it_path)
    {
        if (it_path == path_v.end() || it->compare(*it_path) != 0)
        {
            return false;
        }
    }

    return true;
}
