/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 23:43:36 by spoolpra          #+#    #+#             */
/*   Updated: 2023/02/26 22:51:58 by spoolpra         ###   ########.fr       */
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


Response    Request::process(const route_map_t& route_map) {
    std::string http_version;
    bytestring  content;

    size_t first_sep = _request.find(' ', 0);
    size_t second_sep = _request.find(' ', first_sep + 1);
    size_t third_sep = _request.find('\r', second_sep + 1);
    if (first_sep == std::string::npos \
            || second_sep == std::string::npos \
            || third_sep == std::string::npos
    ) {
        return _M_error(HTTP_BAD_REQUEST);
    }
    try {
        _method = _request.substr(0, first_sep);
        _path = _request.substr(first_sep + 1, second_sep - first_sep - 1);
        http_version = _request.substr(second_sep + 1, third_sep - second_sep - 1);
        if (http_version.compare(HTTP_VERSION) != 0) {
            throw std::out_of_range("Invalid HTTP request");
        }
    } catch (std::out_of_range) {
        return _M_error(HTTP_BAD_REQUEST);
    }
    
    return _M_match_route_response(route_map);
}


Response    Request::_M_match_route_response(const route_map_t& route_map) const {
    for (const_iterator_route it = route_map.begin(); it != route_map.end(); ++it) {

        // TODO Matching algorithm array compare using '/' as delim
        std::cout << "Compare: " << "( " << _path << ", " << it->first << " )" << std::endl;
        std::string prefix = _path.substr(0, (it->first).size());
        std::cout << "Prefix: " << std::endl;
        if (prefix.compare(it->first) == 0) {
            return _M_get_route_response(it->second);
        }
    }

    return _M_error(HTTP_NOT_FOUND);
}


Response    Request::_M_error(const int status_code) const {
    unsigned char   error[] = "TODO add dynamic error";
    
    return Response(
        status_code,
        _server_name,
        error
    );
}


Response    Request::_M_get_route_response(const Route& route) const {
    (void)route;
    unsigned char   answer[] = "TODO add answer";

    return Response(
        HTTP_OK,
        _server_name,
        answer
    );
}

