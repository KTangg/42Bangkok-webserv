/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerConfig.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 16:07:09 by spoolpra          #+#    #+#             */
/*   Updated: 2023/03/07 19:24:29 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef __SERVER_CONFIG_HPP__
# define __SERVER_CONFIG_HPP__


# include "webserv.hpp"

# include "component/Route.hpp"


typedef std::map<int, std::string>      map_error_t;
typedef map_error_t::iterator           it_error;
typedef map_error_t::const_iterator     const_it_error;


class ServerConfig
{
    public:
        ServerConfig(
            const std::string&      host,
            const std::string&      name = DEFAULT_SERVER_NAME,
            const size_t&           limit = DEFAULT_BODY_LIMIT,
            const map_error_t&      error_map = map_error_t(),
            const map_route_t&      route_map = map_route_t()
        );
        ServerConfig(const ServerConfig& rhs);
        ServerConfig& operator=(const ServerConfig& rhs);

        virtual ~ServerConfig();

        std::string         getHost() const;
        std::string         getName() const;
        size_t              getLimit() const;
        const std::string&  searchError(const int code) const;
        const Route&        searchRoute(const std::string& path) const;

    private:
        ServerConfig();

        std::string     _host;
        std::string     _name;
        size_t          _limit;
        map_error_t   _error_map;
        map_route_t     _route_map;
};


typedef std::vector<ServerConfig>   v_server_t;
typedef v_server_t::iterator        it_server;
typedef v_server_t::const_iterator  const_it_server;


#endif
