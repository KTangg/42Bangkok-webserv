/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 23:43:36 by spoolpra          #+#    #+#             */
/*   Updated: 2023/03/01 00:22:19 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "component/Request.hpp"

Request::Request(const std::string &server_name, bytestring &request)
    : _server_name(server_name), _request(request)
{
}

Request::~Request() {}

void Request::append_request(bytestring &request)
{
    _request = _request + request;
}

Response Request::process(const route_map_t &route_map)
{
    std::string http_version;
    bytestring content;

    size_t first_sep = _request.find(' ', 0);
    size_t second_sep = _request.find(' ', first_sep + 1);
    size_t third_sep = _request.find('\r', second_sep + 1);
    if (first_sep == std::string::npos || second_sep == std::string::npos || third_sep == std::string::npos)
    {
        return _M_error(HTTP_BAD_REQUEST);
    }
    try
    {
        _method = BYTES_TO_STR(
            _request.substr(0, first_sep).c_str()
            );
        _path = BYTES_TO_STR(
            _request.substr(first_sep + 1, second_sep - first_sep - 1).c_str()
            );
        http_version = BYTES_TO_STR(
            _request.substr(second_sep + 1, third_sep - second_sep - 1).c_str()
            );
        if (http_version.compare(HTTP_VERSION) != 0)
        {
            if (http_version.compare("HTTP/") == 0)
            {
                throw std::invalid_argument("Invalid HTTP version");
            }
            else
            {
                throw std::out_of_range("Invalid Header");
            }
        }
    }
    catch (std::out_of_range const&)
    {
        return _M_error(HTTP_BAD_REQUEST);
    }
    catch (std::invalid_argument const&)
    {
        return _M_error(HTTP_NOT_SUPPORT);
    }

    return _M_match_route_response(route_map);
}

Response Request::_M_match_route_response(const route_map_t &route_map) const
{
    list_str_t  client_list_path;
    list_str_t  list_path_tail;

    client_list_path = parse_path_directory(_path);

    for (const_iterator_route it = route_map.begin(); it != route_map.end(); ++it)
    {
        bool valid_route = it->second.check_client_dir(
                                client_list_path,
                                it->first,
                                list_path_tail
                            );
        if (valid_route)
        {
            return _M_get_route_response(it->second, list_path_tail);
        }
    }

    return _M_error(HTTP_NOT_FOUND);
}

Response Request::_M_error(const int status_code) const
{
    unsigned char error[] = "TODO add dynamic error";

    return Response(
        status_code,
        _server_name,
        error
        );
}

Response Request::_M_get_route_response(
            const Route &route,
            list_str_t& list_path_tail
            ) const
{
    list_str_t list_full_path = join_list(route.get_list_path(), list_path_tail);

    std::string path_to_file = path_join(list_full_path);
    bytestring answer = STR_TO_BYTES((std::string("Response from ") + path_to_file).c_str());

    struct stat stat_meta;

    if (stat(path_to_file.c_str(), &stat_meta) == 0)
    {
        return Response(
            HTTP_OK,
            _server_name,
            answer
            );
    }

    return _M_error(HTTP_NOT_FOUND);
}
