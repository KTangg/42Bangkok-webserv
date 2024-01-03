/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Worker.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 22:51:52 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/03 23:34:40 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __WORKER_HPP__
#define __WORKER_HPP__

#include <config/Config.hpp>

class Master;  // Forward declaration of Master class

class Worker {
   public:
    Worker(Config* config, const Master& master);
    ~Worker();

    void init();
    void run();

   private:
    int                  _socket;
    Poller*              _poller;
    std::vector<Server*> _servers;
    const Master&        _master;
};

#endif /* __WORKER_HPP__ */

#include "server/Master.hpp"
