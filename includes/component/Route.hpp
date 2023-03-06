/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Route.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 22:19:47 by spoolpra          #+#    #+#             */
/*   Updated: 2023/03/06 17:04:38 by spoolpra         ###   ########.fr       */
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
            const std::string&      route_path,
            const std::string&      root_path,
            const l_str_t&          allow_method = l_str_t(1, "GET"),
            const std::string&      redirect = "",
            const bool&             listing = false,
            const std::string&      file = "index.html",
            const map_cgi_t&        cgi_map = map_cgi_t()
        );

        virtual ~Route();

        bool            isRedirect() const;
        bool            isListing() const;
        std::string     getFile() const;
        std::string     findPath(const std::string& path) const;
        bool            checkMethod(const std::string& method) const;

    private:
        l_str_t         _l_route_path;
        std::string     _root_path;
        l_str_t         _allow_method;
        std::string     _redirect;
        bool            _listing;
        std::string     _file;
        map_cgi_t       _cgi_map;
};


typedef std::map<std::string, Route, std::greater<std::string> >    map_route_t;
typedef map_route_t::iterator                                       iterator_route;
typedef map_route_t::const_iterator                                 const_iterator_route;


#endif
