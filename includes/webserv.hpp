/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 20:10:46 by spoolpra          #+#    #+#             */
/*   Updated: 2022/09/20 00:40:02 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __WEBSERV_HPP__
# define __WEBSERV_HPP__

// General include
# include <iostream>

// inet(ip) <-> address conversion
# include <arpa/inet.h>

// typedef alias
typedef struct sockaddr_in  sockaddr_in_t;


/// @brief socket type that contain host and port destination
/// @remark host should be in network order
typedef struct socket {
    uint32_t    host;
    uint32_t    port;
} socket_t;

#endif /* __WEBSERV_HPP__ */
