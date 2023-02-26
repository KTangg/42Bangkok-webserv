/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 11:54:08 by spoolpra          #+#    #+#             */
/*   Updated: 2023/02/26 18:49:50 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "component/Response.hpp"


Response::Response(
    int             status_code,
    std::string     server_name,
    bytestring      content
    // std::string     content_type
    )
    :_status_code(status_code),
    _server_name(server_name),
    _content(content)
    // _content_type(content_type)    
{ }


Response::~Response() { }


std::map<int, std::string> Response::_S_setStatusCodeMap() {
    std::map<int, std::string>  new_map;

    new_map.insert(std::make_pair(200, "success"));
    new_map.insert(std::make_pair(404, "not found"));

    return new_map;
}


std::map<int, std::string>  Response::status_code_map = Response::_S_setStatusCodeMap();


bytestring  Response::_M_generate_response() {
    bytestring  header;
    bytestring  response_byte;

    std::time_t     epoch_time = std::time(nullptr);
    char            time_string[sizeof("aaa, dd bb YYYY HH:MM:SS ZZZ") + 1];
    std::strftime(
        time_string, 
        sizeof(time_string),
        "%a, %d %b %Y %H:%M:%S %Z",
        std::gmtime(&epoch_time)
    );

    header.reserve(DEFAULT_HEADER_RESERVE);
    header = header + STR_TO_BYTE(HTTP_VERSION);
    header = header + STR_TO_BYTE(" ");
    header = header + STR_TO_BYTE(std::to_string(_status_code).c_str());
    header = header + STR_TO_BYTE(" ");
    header = header + STR_TO_BYTE(status_code_map[_status_code].c_str());
    header = header + STR_TO_BYTE("\n");

    header = header + STR_TO_BYTE("Server: ");
    header = header + STR_TO_BYTE(_server_name.c_str());
    header = header + STR_TO_BYTE("\n");
    
    header = header + STR_TO_BYTE("Date: ");
    header = header + STR_TO_BYTE(time_string);
    header = header + STR_TO_BYTE("\n");

    header = header + STR_TO_BYTE("Connection: keep-alive");
    header = header + STR_TO_BYTE("\n");
    
    header = header + STR_TO_BYTE("Content-Length: ");
    header = header + STR_TO_BYTE(std::to_string(_content.size()).c_str());
    header = header + STR_TO_BYTE("\n");

    header = header + STR_TO_BYTE("\n");

    response_byte = header + _content;
    return response_byte;
}


void    Response::_M_send(int socket, void* buffer, size_t size) {
#ifndef __APPLE__
    send(socket, buffer, ret, MSG_NOSIGNAL | MSG_DONTWAIT);
#else
    signal(SIGPIPE, SIG_IGN);
    send(socket, buffer, size, MSG_DONTWAIT);
#endif
}


void    Response::response(int socket) {
    bytestring response_byte = _M_generate_response();
    _M_send(
        socket,
        BYTE_TO_VOID(response_byte.data()),
        response_byte.size()
    );
}
