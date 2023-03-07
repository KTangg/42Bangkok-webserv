/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MasterConfig.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 15:27:07 by spoolpra          #+#    #+#             */
/*   Updated: 2023/03/07 20:19:04 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef __MASTER_CONFIG_HPP__
# define __MASTER_CONFIG_HPP__


# include "webserv.hpp"
# include "config/ServerConfig.hpp"


class MasterConfig
{
    public:
        MasterConfig(const uint16_t& port);
        MasterConfig(const MasterConfig& rhs);
        MasterConfig& operator=(const MasterConfig& rhs);

        virtual ~MasterConfig();

        sockaddr_in_t           getAddress() const;
        v_server_t              getServerConfig() const;
        void                    addServer(const ServerConfig& config);
        bool                    existHost(const std::string& host) const;

    protected:
        sockaddr_in_t       _addr;
        v_server_t          _server_v;

    private:
        MasterConfig();
};


#endif
