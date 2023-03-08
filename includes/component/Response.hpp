/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:13:02 by spoolpra          #+#    #+#             */
/*   Updated: 2023/03/08 16:42:01 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef __RESPONSE_HPP__
# define __RESPONSE_HPP__


# include "webserv.hpp"

# include "component/Request.hpp"
# include "config/ServerConfig.hpp"

class Response
{
    public:
        Response(const Request& request);
        Reponse(const Reponset& rhs);
        Response&   operator=(const Response& rhs);

        virtual ~Response();

        bool    isServer() const;
        void    setServer(const ServerConfig* server);

        std::string     preprocess() const;
        void            process();
        bool            respond();

    private:
        Response();

        const Request&          _request;
        const ServerConfig*     _server;

        std::string             _path;
        const Route*            _route;
        std::fstream*           _content;
};


typedef std::map<int, Response>             map_response_t;
typedef map_response_t::iterator            it_reponse;
typedef map_response_t::const_iterator      const_it_reponse;


#endif
