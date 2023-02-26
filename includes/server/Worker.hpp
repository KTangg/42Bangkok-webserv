/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Worker.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 22:19:47 by spoolpra          #+#    #+#             */
/*   Updated: 2023/02/26 17:44:59 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef __WORKER_HPP__
# define __WORKER_HPP__

// General stuff
# include "webserv.hpp"

// Other Class
# include "component/Request.hpp"
# include "component/Route.hpp"

typedef std::vector<struct pollfd>::iterator iterator_poll;
typedef std::map<int, Request>::iterator iterator_request;

class Worker {

    public:
        // Initialize Constructor
        Worker(
            const sockaddr_in_t&                addr,
            const route_map_t&                  route,
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
        const route_map_t                   _route;
        // const std::map<int, std::string>    _error;
        const std::string                   _name;
        const size_t                        _limit;

        bool                            _status;
        int                             _listener;
        std::vector<struct pollfd>      _poll;
        std::map<int, Request>          _request_map;

        // Private Method
        void            _M_add_poll(int socket, short events = DEFAULT_EVENT);
        void            _M_del_poll(std::vector<int>& del_poll);
        int             _M_accept(int& socket);
        int             _M_request(int socket);
        int             _M_response(int socket) const;

        // Private Static Method
        static int      _S_keepalive(int socket);
}; // class Worker

#endif /* __WORKER_HPP__ */
