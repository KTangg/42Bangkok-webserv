/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Route.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 22:19:47 by spoolpra          #+#    #+#             */
/*   Updated: 2023/02/28 00:55:57 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef __ROUTE_HPP__
# define __ROUTE_HPP__

// General stuff
# include "webserv.hpp"


typedef std::map<std::string, std::string>                      cgi_map_t;
typedef cgi_map_t::iterator                                     iterator_cgi;
typedef cgi_map_t::const_iterator                               const_iterator_cgi;


class Route {

    public:
        // Initialize Constructor
        Route(
            list_str_t                          list_root_path,
            list_str_t                          allow_method = list_str_t(1, "GET"),
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
        list_str_t      get_list_path() const;
        bool            is_allow(std::string& method) const;
        bool            is_redirect() const;
        std::string     get_redirect() const;
        bool            is_listing() const;
        std::string     get_default_file_name() const;
        bool            is_post_and_get() const;
        bool            check_client_dir(
                            const list_str_t&   client_dir,
                            const list_str_t&   list_route_path,
                            list_str_t&         list_path_tail
                        ) const;


    private:
        // Attributes
        list_str_t                          _list_root_path;
        list_str_t                          _allow_method;
        bool                                _redirect;
        std::string                         _redirect_path;
        bool                                _directory_listing;
        std::string                         _default_file;
        bool                                _post_and_get;
        cgi_map_t                           _cgi_map;

        // Private method

}; // class Route

typedef std::map<list_str_t, Route, is_bigger<list_str_t> >                     route_map_t;
typedef route_map_t::iterator                                                   iterator_route;
typedef route_map_t::const_iterator                                             const_iterator_route;

#endif /* __ROUTE_HPP__ */
