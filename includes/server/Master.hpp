/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Master.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 22:19:47 by spoolpra          #+#    #+#             */
/*   Updated: 2023/03/08 15:26:17 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef __MASTER_HPP__
# define __MASTER_HPP__


# include "webserv.hpp"

# include "utils/HttpExceoption.hpp"
# include "config/MasterConfig.hpp"
# include "component/Response.hpp"
# include "component/Request.hpp"


class Master
{
    public:
        Master(const MasterConfig& config);

        virtual ~Master() { };

        bool            init();
        void            listen();

    private:
        Master();
        Master(const Master& rhs);
        Master& operator=(const Master& rhs);

        const sockaddr_in_t     _address;
        const v_server_t        _server_v;

        int                     _listener;
        v_poll_t                _poll_v;
        map_request_t           _request_map;
        map_response_t          _response_map;

        int             _M_listen(v_int_t& del_fd);

        int             _M_accept() const;
        bool            _M_request(const int socket);
        bool            _M_response(const int socket);

        bool            _M_process(const Response& response);

        void            _M_add_client(const int socket, const Request& request);
        void            _M_del_client(const int socket);

        void            _M_del_poll(const v_int_t& delfd);
        void            _M_add_poll(const int socket, const short event = POLLIN | POLLOUT);

        const ServerConfig*     _M_match_server(const std::string& host);
};


#endif
