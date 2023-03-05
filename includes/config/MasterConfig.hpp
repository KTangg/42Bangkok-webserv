/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MasterConfig.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 15:27:07 by spoolpra          #+#    #+#             */
/*   Updated: 2023/03/04 04:23:50 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef __MASTER_CONFIG_HPP__
# define __MASTER_CONFIG_HPP__


# include "webserv.hpp"
# include "config/ServerConfig.hpp"


class MasterConfig
{
    public:
        MasterConfig(
            const std::string&  host,
            const uint16_t&     port
        );

        virtual ~MasterConfig() { };

        sockaddr_in_t   getAddress() const;
        map_server_t    getServerConfig() const;
        void            addServer(ServerConfig config);

    protected:
        const std::string   _host;
        const uint16_t      _port;
        map_server_t        _server_map;
};


#endif
