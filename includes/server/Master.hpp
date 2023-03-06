/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Master.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 22:19:47 by spoolpra          #+#    #+#             */
/*   Updated: 2023/03/06 10:07:20 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef __MASTER_HPP__
# define __MASTER_HPP__


# include "webserv.hpp"
# include "config/MasterConfig.hpp"
# include "component/Request.hpp"


class Master
{
    public:
        Master(const MasterConfig& config);

        virtual ~Master() { };

        bool            init();
        bool            listen();

        std::string     addressString() const;

    private:
        const sockaddr_in_t     _address;
        const map_server_t      _server_map;

        int             _listener;
        bool            _listening;
        l_poll_t        _poll_list;
        map_request_t   _request_map;

        void            _M_add_poll(int socket, short event = DEFAULT_EVENT);
        void            _M_del_poll(const std::vector<int> & delfd);
        int             _M_listen(std::vector<int>& del_fd);
        bool            _M_accept(int& socket) const;

        bool            _M_request(int socket);

        bool            _M_response(int socket);
        bool            _M_process(int socket, Request& request, int stage);

        void                    _M_validate_request(Request& request);
        const ServerConfig*     _M_match_config(const std::string& server_name);
};


#endif
