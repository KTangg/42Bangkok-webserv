/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 22:19:47 by spoolpra          #+#    #+#             */
/*   Updated: 2022/09/20 00:40:07 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef __WORKER_HPP__
# define __WORKER_HPP__

// General stuff
# include "webserv.hpp"

// Socket stuff
# include <sys/socket.h>

// Macro stuff
# define ERROR_FD -1

class Worker {

    public:
        // Initialize Constructor
        Worker(const socket_t& socket);

        // Assignment operator
        Worker& operator=(const Worker& rhs);

        // Deconstructor
        virtual ~Worker();

        // Initiate Worker socket
        int serve(void);

    private:
        // Default Constructor
        Worker(void);

        // Copy constructor
        Worker(const Worker& src);

        // Attributes
        int             _server_fd;
        fd_set          _request;
        sockaddr_in_t   _address;

}; // class Worker

#endif /* __WORKER_HPP__ */
