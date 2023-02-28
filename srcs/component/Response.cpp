/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 11:54:08 by spoolpra          #+#    #+#             */
/*   Updated: 2023/02/28 00:14:52 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "component/Response.hpp"

Response::Response(
    int status_code,
    std::string server_name,
    bytestring content
    // std::string     content_type
    )
    : _status_code(status_code),
      _server_name(server_name),
      _content(content)
// _content_type(content_type)
{
}

Response::~Response() {}

std::map<int, std::string> Response::_S_setStatusCodeMap()
{
    std::map<int, std::string> new_map;

    new_map.insert(std::make_pair(200, "success"));
    new_map.insert(std::make_pair(404, "not found"));

    return new_map;
}

std::map<int, std::string> Response::status_code_map = Response::_S_setStatusCodeMap();

bytestring Response::_M_generate_response()
{
    bytestring          header;
    bytestring          response_byte;

    std::time_t epoch_time = std::time(NULL);
    char time_string[sizeof("aaa, dd bb YYYY HH:MM:SS ZZZ")];
    std::strftime(
        time_string,
        sizeof(time_string),
        "%a, %d %b %Y %H:%M:%S %Z",
        std::gmtime(&epoch_time)
        );

    header.reserve(DEFAULT_HEADER_RESERVE);
    header = header + STR_TO_BYTES(
        SS_TO_STR(
            HTTP_VERSION << " " << _status_code << std::endl
        ).c_str()
    );
    header = header + STR_TO_BYTES(
        SS_TO_STR(
            "Server: " << _server_name << std::endl
        ).c_str()
    );
    header =  header + STR_TO_BYTES(
        SS_TO_STR(
            "Date: " << time_string << std::endl
        ).c_str()
    );
    header = header + STR_TO_BYTES(
        SS_TO_STR(
            "Connection: keep-alive" << std::endl
        ).c_str()
    );
    header = header + STR_TO_BYTES(
        SS_TO_STR(
            "Content-Length: " << _content.size() << std::endl
        ).c_str()
    );
    header = header + STR_TO_BYTES("\n");
    response_byte = header + _content;

    return response_byte;
}

void Response::_M_send(int socket, void *buffer, size_t size)
{
#ifndef __APPLE__
    send(socket, buffer, size, MSG_NOSIGNAL | MSG_DONTWAIT);
#else
    signal(SIGPIPE, SIG_IGN);
    send(socket, buffer, size, MSG_DONTWAIT);
#endif
}

void Response::response(int socket)
{
    bytestring response_byte = _M_generate_response();
    _M_send(
        socket,
        BYTES_TO_VOID(response_byte.data()),
        response_byte.size());
}
