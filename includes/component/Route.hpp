/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Route.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 22:19:47 by spoolpra          #+#    #+#             */
/*   Updated: 2023/02/26 23:16:23 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef __ROUTE_HPP__
# define __ROUTE_HPP__

// General stuff
# include "webserv.hpp"


typedef std::map<std::string, std::string>                      cgi_map_t;
typedef std::map<std::string, std::string>::iterator            iterator_cgi;
typedef std::map<std::string, std::string>::const_iterator      const_iterator_cgi;


class Route {

    public:
        // Initialize Constructor
        Route(
            std::string                         root_path = "",
            std::vector<std::string>            allow_method = std::vector<std::string>(1, "GET"),
            bool                                redirect = false,
            std::string                         redirect_path = "",
            bool                                directory_listing = false,
            std::string                         default_file = "index.html",
            bool                                post_and_get = false,
            cgi_map_t                           cgi_map = cgi_map_t()
        );

        // Deconstructor
        virtual ~Route();

        // Member function
        std::string     get_path() const;
        bool            is_allow(std::string& method) const;
        bool            is_redirect() const;
        std::string     get_redirect() const;
        bool            is_listing() const;
        std::string     get_default_file_name() const;
        bool            is_post_and_get() const;
        

    private:
        // Attributes
        std::string                         _root_path;
        std::vector<std::string>            _allow_method;
        bool                                _redirect;
        std::string                         _redirect_path;
        bool                                _directory_listing;
        std::string                         _default_file;
        bool                                _post_and_get;
        std::map<std::string, std::string>  _cgi_map;

        std::vector<std::string>            _route_directory;
        
        // Private method

}; // class Route

typedef std::map<std::string, Route, std::greater<std::string> >                    route_map_t;
typedef std::map<std::string, Route, std::greater<std::string> >::iterator          iterator_route;
typedef std::map<std::string, Route, std::greater<std::string> >::const_iterator    const_iterator_route;

#endif /* __ROUTE_HPP__ */
