/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 22:19:47 by spoolpra          #+#    #+#             */
/*   Updated: 2023/02/27 23:54:32 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef __RESPONSE_HPP__
# define __RESPONSE_HPP__

// General stuff
# include "webserv.hpp"


class Response {

    public:
        // Initialize Constructor
        Response(
            int             status_code,
            std::string     server_name,
            bytestring      content
            // std::string     content_type
        );

        // Deconstructor
        virtual ~Response();

        // Member function
        void    response(int socket);

    private:
        // Attributes
        int             _status_code;
        std::string     _server_name;
        bytestring      _content;
        // std::string     _content_type;

        static std::map<int, std::string>   status_code_map;

        // Private method
        void            _M_send(int socket, void* buffer, size_t size);
        bytestring      _M_generate_response();
        static std::map<int, std::string>   _S_setStatusCodeMap();

}; // class Request

#endif /* __REQUEST_HPP__ */
