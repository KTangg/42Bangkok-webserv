/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:41:34 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/04 15:44:31 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include <config/ServerConfig.hpp>

class Server {
   public:
    Server(const ServerConfig& config);
    ~Server();

    const ServerConfig& getConfig() const;

   private:
    ServerConfig _config;
};

#endif /* __SERVER_HPP__ */
