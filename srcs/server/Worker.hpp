/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Worker.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 22:51:52 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/06 13:41:31 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __WORKER_HPP__
#define __WORKER_HPP__

#include <arpa/inet.h>
#include <sys/socket.h>

#include "config/Config.hpp"
#include "logger/Logger.hpp"
#include "server/Poller.hpp"
#include "utils/exception.hpp"

typedef struct sockaddr_in sockaddr_in_t;
class Master;  // Forward declaration of Master class

class Worker {
   public:
    Worker(Config* config, const Master& master);
    ~Worker();

    void init();
    void run();

   private:
    Logger              _logger;
    int                 _socket;
    Poller              _poller;
    sockaddr_in_t       _addr;
    std::vector<Server> _servers;
    const Master&       _master;

    void _M_run();

    void _M_init_socket();
    void _M_init_poller();

    poller_it_t _M_handle_new_connection(poller_it_t& it);
    poller_it_t _M_handle_client_disconnection(poller_it_t& it);

    void _M_handle_client_request(poller_it_t& it);
    void _M_handle_server_response(poller_it_t& it);

    static _S_non_block_fd(int fd);
};

#endif /* __WORKER_HPP__ */

#include "server/Master.hpp"
