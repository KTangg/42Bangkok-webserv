/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:13:17 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/06 14:12:56 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "component/Response.hpp"


/**
 * @brief Construct a new Response:: Reponse object
 *
 * @param request request to corresponse to the response
 */
Response::Reponse(const Request& request)
{
    _request = request;
    _server = NULL;
    _path = std::string();
    _route = NULL;
    _content = NULL;
}


/**
 * @brief Construct a new Response:: Response object
 *
 * @param rhs Response to be copied
 */
Response::Response(const Response& rhs)
{
    *this = rhs;
}


/**
 * @brief Set this object to be a copy of rhs
 *
 * @param rhs object to be copy
 * @return Response& copied object
 */
Response& Response::operator=(const Response& rhs)
{
    _request = _request;
    _server = _server;
    _path = _path;
    _route = _route;
    _content = _content;

    return *this;
}


/**
 * @brief Destroy the Response:: Reponse object
 *
 */
Response::~Reponse() { }


/**
 * @brief Check if response got any server yet
 *
 * @return true if response bind to a server else false
 */
bool    Response::isServer() const
{
    return _server != NULL;
}


/**
 * @brief Bind response to a server
 *
 * @param server config to use for response
 */
void    Response::setServer(const ServerConfig* server)
{
    _server = _server;
}


/**
 * @brief Preprocess request line, header in request
 *
 * @return std::string host value in request
 * @exception ft::RequestNotReady if request header not end yet
 * @exception ft::HttpException if request couldn't be process further
 */
std::string     Response::preprocess() const
{
    if (_request.get_path().empty())
    {
        _request.parseRequestLine();
    }
    else if (_request.isHeaderEnd())
    {
       _request.parseHeaderLine();
    }

    return _request.get_host();
}



