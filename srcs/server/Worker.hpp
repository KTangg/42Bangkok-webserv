/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Worker.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 22:51:52 by spoolpra          #+#    #+#             */
/*   Updated: 2024/02/29 13:47:19 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __WORKER_HPP__
#define __WORKER_HPP__

#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/socket.h>

#include <map>
#include <queue>

#include "config/Config.hpp"
#include "http/HttpRequest.hpp"
#include "http/HttpResponse.hpp"
#include "logger/Logger.hpp"
#include "server/Poller.hpp"
#include "server/Server.hpp"
#include "utils/exception.hpp"

typedef struct sockaddr_in sockaddr_in_t;
class Master;  // Forward declaration of Master class

class Worker {
   public:
    Worker(const Worker& src);
    Worker(const Config& config, const Master& master);

    ~Worker();

    void init();
    void run();

   private:
    Worker();

    const Logger                             _logger;
    int                                      _socket;
    Poller                                   _poller;
    const Master&                            _master;
    std::map<int, std::queue<HttpRequest*> > _request_queue;

    sockaddr_in_t       _addr;
    std::vector<Server> _servers;

    void _M_run();

    void _M_init_addr(const char* host, int port);
    void _M_init_servers(const std::vector<ServerConfig>& server_configs);
    void _M_init_socket();
    void _M_init_poller();

    poller_it_t _M_handle_new_connection(poller_it_t& it);
    poller_it_t _M_handle_client_disconnection(poller_it_t& it);

    void _M_handle_client_request(poller_it_t& it);
    void _M_handle_server_response(poller_it_t& it);

    Server& _M_route_server(HttpRequest& req);

    static int _S_non_block_fd(int fd);
};

#endif /* __WORKER_HPP__ */

#include "server/Master.hpp"
