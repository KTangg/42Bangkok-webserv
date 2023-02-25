/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Worker.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 22:19:47 by spoolpra          #+#    #+#             */
/*   Updated: 2023/01/01 10:22:03 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef __WORKER_HPP__
# define __WORKER_HPP__

// General stuff
# include "webserv.hpp"

// Other Class
// # include "Route.hpp"
// # include "Request.hpp"
// # include "Session.hpp"

/// @brief  Worker class for Recieve/Reponse client request
class Worker {

    public:
        // Initialize Constructor
        Worker(
            const sockaddr_in_t&                addr,
            // const std::map<std::string, Route>& route,
            // const std::map<int, std::string>&   error,
            const std::string&                  name = DEFAULT_SERVER_NAME,
            const size_t                        limit = DEFAULT_BODY_LIMIT
        );

        // Deconstructor
        virtual ~Worker();

        // Member function
        int init(void);
        int listen(void);

    private:
        // Attributes
        const sockaddr_in_t                 _address;
        // const std::map<std::string, Route>  _route;
        // const std::map<int, std::string>    _error;
        const std::string                   _name;
        const size_t                        _limit;

        bool                            _status;
        int                             _listener;
        std::vector<struct pollfd>      _poll;
        // std::map<int, Request>          _request;
        // std::map<int, Session>          _session;

        // Private Method
        void            _M_add_poll(int socket, short events = DEFAULT_EVENT);
        iterator_poll   _M_del_poll(iterator_poll& it);
        void            _M_accept(void);
        int             _M_request(int socket);
        void            _M_response(int socket);

        // Private Static Method
        static int      _S_keepalive(int socket);
}; // class Worker

#endif /* __WORKER_HPP__ */
