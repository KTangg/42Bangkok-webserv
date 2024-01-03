/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statusCode.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 21:36:45 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/03 22:39:54 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/statusCode.hpp"

namespace ft {
    const std::vector<int> defaultErrorCodes = {400, 401, 402, 403, 404, 405, 406, 407, 408,
                                                409, 410, 411, 412, 413, 414, 415, 416, 417,
                                                421, 422, 426, 500, 501, 502, 503, 504, 505};

    const std::map<int, std::string> httpStatusCodes = {{100, "Continue"},
                                                        {101, "Switching Protocols"},
                                                        {200, "OK"},
                                                        {201, "Created"},
                                                        {202, "Accepted"},
                                                        {203, "Non-Authoritative Information"},
                                                        {204, "No Content"},
                                                        {205, "Reset Content"},
                                                        {206, "Partial Content"},
                                                        {300, "Multiple Choices"},
                                                        {301, "Moved Permanently"},
                                                        {302, "Found"},
                                                        {303, "See Other"},
                                                        {304, "Not Modified"},
                                                        {305, "Use Proxy"},
                                                        {307, "Temporary Redirect"},
                                                        {400, "Bad Request"},
                                                        {401, "Unauthorized"},
                                                        {402, "Payment Required"},
                                                        {403, "Forbidden"},
                                                        {404, "Not Found"},
                                                        {405, "Method Not Allowed"},
                                                        {406, "Not Acceptable"},
                                                        {407, "Proxy Authentication Required"},
                                                        {408, "Request Timeout"},
                                                        {409, "Conflict"},
                                                        {410, "Gone"},
                                                        {411, "Length Required"},
                                                        {412, "Precondition Failed"},
                                                        {413, "Content Too Large"},
                                                        {414, "URI Too Long"},
                                                        {415, "Unsupported Media Type"},
                                                        {416, "Range Not Satisfiable"},
                                                        {417, "Expectation Failed"},
                                                        {421, "Misdirected Request"},
                                                        {422, "Unprocessable Content"},
                                                        {426, "Upgrade Required"},
                                                        {500, "Internal Server Error"},
                                                        {501, "Not Implemented"},
                                                        {502, "Bad Gateway"},
                                                        {503, "Service Unavailable"},
                                                        {504, "Gateway Timeout"},
                                                        {505, "HTTP Version Not Supported"}

    };
}  // namespace ft
