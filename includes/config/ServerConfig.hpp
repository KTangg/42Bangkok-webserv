/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerConfig.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 16:07:09 by spoolpra          #+#    #+#             */
/*   Updated: 2023/03/04 04:24:20 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef __WORKER_CONFIG_HPP__
# define __WORKER_CONFIG_HPP__


#include "webserv.hpp"

#include "component/Route.hpp"


class ServerConfig
{
    public:
        ServerConfig(
            const map_int_str_t&    error_path_map,
            const map_route_t&      route_map,
            const std::string&      server_name = DEFAULT_SERVER_NAME,
            const size_t&           body_limit = DEFAULT_BODY_LIMIT
        );

        virtual ~ServerConfig() { };

        std::string     getServerName() const;

    protected:
        const map_int_str_t _error_path_map;
        const map_route_t   _route_map;
        const std::string   _server_name;
        const size_t        _body_limit;
};


typedef std::map<std::string, ServerConfig>     map_server_t;
typedef map_server_t::iterator                  iterator_server;
typedef map_server_t::const_iterator            const_iterator_server;


#endif
