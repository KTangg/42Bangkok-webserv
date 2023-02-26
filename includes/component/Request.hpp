/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 22:19:47 by spoolpra          #+#    #+#             */
/*   Updated: 2023/02/26 23:31:22 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef __REQUEST_HPP__
# define __REQUEST_HPP__

// General stuff
# include "webserv.hpp"


// Other Class
# include "component/Response.hpp"
# include "component/Route.hpp"


class Request {

    public:
        // Initialize Constructor
        Request(const std::string& server_name, std::string& request);

        // Deconstructor
        virtual ~Request();

        // Member function
        void        append_request(std::string& request);
        Response    process(const route_map_t& route_map);

    private:
        // Attributes
        std::string _server_name;
        std::string _request;
        std::string _method;
        std::string _path;

        // Private method
        Response    _M_error(const int status_code) const;
        Response    _M_match_route_response(const route_map_t& route_map) const;
        Response    _M_get_route_response(const Route& route) const;

}; // class Request

#endif /* __REQUEST_HPP__ */
