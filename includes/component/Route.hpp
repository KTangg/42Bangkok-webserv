/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Route.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 22:19:47 by spoolpra          #+#    #+#             */
/*   Updated: 2023/02/26 17:42:57 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef __ROUTE_HPP__
# define __ROUTE_HPP__

// General stuff
# include "webserv.hpp"


// Other Class

class Route {

    public:
        // Initialize Constructor
        Route(
            std::string                         root_path,
            std::vector<std::string>            allow_method = std::vector<std::string>(1, "GET"),
            bool                                redirect = false,
            std::string                         redirect_path = "",
            bool                                directory_listing = false,
            std::string                         default_file = "index.html",
            bool                                post_and_get = false,
            std::map<std::string, std::string>  cgi_map = std::map<std::string, std::string>()  
        );

        // Deconstructor
        virtual ~Route();

        // Member function
        

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
        
        // Private method

}; // class Route

typedef std::map<std::string, Route, std::greater<std::string> > route_map_t;

#endif /* __ROUTE_HPP__ */
