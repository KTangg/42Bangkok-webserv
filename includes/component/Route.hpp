/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Route.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 22:19:47 by spoolpra          #+#    #+#             */
/*   Updated: 2023/03/04 00:00:43 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef __ROUTE_HPP__
# define __ROUTE_HPP__


# include "webserv.hpp"

# include "component/Cgi.hpp"


class Route
{
    public:
        Route(
            l_str_t         l_route_path,
            l_str_t         l_root_path,
            l_str_t         allow_method = l_str_t(1, "GET"),
            bool            redirect = false,
            std::string     redirect_path = "",
            bool            directory_listing = false,
            std::string     default_file = "index.html",
            bool            post_and_get = false,
            map_cgi_t       cgi_map = map_cgi_t()
        );

        virtual ~Route();

    private:
        l_str_t         _l_route_path;
        l_str_t         _l_root_path;
        l_str_t         _allow_method;
        bool            _redirect;
        std::string     _redirect_path;
        bool            _directory_listing;
        std::string     _default_file;
        bool            _post_and_get;
        map_cgi_t       _cgi_map;
};


typedef std::map<l_str_t, Route, is_bigger<l_str_t> >   map_route_t;
typedef map_route_t::iterator                           iterator_route;
typedef map_route_t::const_iterator                     const_iterator_route;


#endif
