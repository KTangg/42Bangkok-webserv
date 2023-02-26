/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 23:43:36 by spoolpra          #+#    #+#             */
/*   Updated: 2023/02/26 21:20:33 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "component/Request.hpp"


Request::Request(const std::string& server_name, std::string& request)
: _server_name(server_name), _request(request)
{ }


Request::~Request() { }


void    Request::append_request(std::string& request) {
    _request = _request + request;
}


Response    Request::process(const route_map_t& route) {
    unsigned char a[] = "<h1>Bad Request</h1>";
    unsigned char b[] = "<h1>Success</h1>";
    (void)route;
    std::string http_version;

    size_t first_sep = _request.find(' ', 0);
    size_t second_sep = _request.find(' ', first_sep + 1);
    size_t third_sep = _request.find('\n', second_sep + 1);
    if (first_sep == std::string::npos \
            || second_sep == std::string::npos \
            || third_sep == std::string::npos
    ) {
        return Response(
            400,
            _server_name,
            a
        );
    }
    try {
        _method = _request.substr(0, first_sep);
        _path = _request.substr(first_sep + 1, second_sep - first_sep - 1);
        http_version = _request.substr(second_sep + 1, third_sep - second_sep - 2);
        if (http_version.compare(HTTP_VERSION) != 0) {
            throw std::out_of_range("Invalid HTTP request");
        }
    } catch (std::out_of_range) {
        return Response(
            400,
            _server_name,
            a
        );
    }
    return Response(
        200,
        _server_name,
        b
    );
}

