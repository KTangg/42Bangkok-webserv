/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Route.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 22:19:47 by spoolpra          #+#    #+#             */
/*   Updated: 2023/03/07 20:31:34 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef __ROUTE_HPP__
# define __ROUTE_HPP__


# include "webserv.hpp"
# include "utils/utils.hpp"


typedef std::map<std::string, std::string>      map_cgi_t;
typedef map_cgi_t::iterator                     it_cgi;
typedef map_cgi_t::const_iterator               const_it_cgi;


class Route
{
    public:
        Route(
            const std::string&      route,
            const std::string&      root,
            const v_str_t&          allow = v_str_t(1, "GET"),
            const bool&             redirect = false,
            const std::string&      redirect_path = "",
            const bool&             listing = false,
            const std::string&      index = "index.html",
            const map_cgi_t&        cgi_map = map_cgi_t()
        );
        Route(const Route& rhs);
        Route& operator=(const Route& rhs);

        virtual ~Route();

        std::string     getRoot() const;
        v_str_t         getAllow() const;
        std::string     getIndex() const;
        bool            isListing() const;
        bool            isRedirect() const;
        std::string     getRedirectPath() const;
        std::string     getCgi(const std::string& ext) const;
        bool            isAllow(const std::string& method) const;
        bool            matchRoute(const std::string& path) const;

    private:
        Route();

        v_str_t         _route;
        std::string     _root;
        v_str_t         _allow;
        bool            _redirect;
        std::string     _redirect_path;
        bool            _listing;
        std::string     _index;
        map_cgi_t       _cgi_map;
};


typedef std::map<std::string, Route, std::greater<std::string> >    map_route_t;
typedef map_route_t::iterator                                       it_route;
typedef map_route_t::const_iterator                                 const_it_route;


#endif
