/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_code.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 21:36:45 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/06 14:48:43 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/status_code.hpp"

namespace ft {
    /**
     * @brief Initialize the default error codes.
     *
     * @return const std::vector<int> The default error codes.
     */
    const std::vector<int> initialize_default_error_code() {
        std::vector<int> default_error_code;

        default_error_code.push_back(400);
        default_error_code.push_back(401);
        default_error_code.push_back(402);
        default_error_code.push_back(403);
        default_error_code.push_back(404);
        default_error_code.push_back(405);
        default_error_code.push_back(406);
        default_error_code.push_back(407);
        default_error_code.push_back(408);
        default_error_code.push_back(409);
        default_error_code.push_back(410);
        default_error_code.push_back(411);
        default_error_code.push_back(412);
        default_error_code.push_back(413);
        default_error_code.push_back(414);
        default_error_code.push_back(415);
        default_error_code.push_back(416);
        default_error_code.push_back(417);
        default_error_code.push_back(421);
        default_error_code.push_back(422);
        default_error_code.push_back(426);
        default_error_code.push_back(500);
        default_error_code.push_back(501);
        default_error_code.push_back(502);
        default_error_code.push_back(503);
        default_error_code.push_back(504);
        default_error_code.push_back(505);

        return default_error_code;
    }

    /**
     * @brief Initialize the http status codes.
     *
     * @return const std::map<int, std::string> The http status codes.
     */
    const std::map<int, std::string> initialize_http_status_codes() {
        std::map<int, std::string> http_status_codes;

        http_status_codes[100] = "Continue";
        http_status_codes[101] = "Switching Protocols";
        http_status_codes[200] = "OK";
        http_status_codes[201] = "Created";
        http_status_codes[202] = "Accepted";
        http_status_codes[203] = "Non-Authoritative Information";
        http_status_codes[204] = "No Content";
        http_status_codes[205] = "Reset Content";
        http_status_codes[206] = "Partial Content";
        http_status_codes[300] = "Multiple Choices";
        http_status_codes[301] = "Moved Permanently";
        http_status_codes[302] = "Found";
        http_status_codes[303] = "See Other";
        http_status_codes[304] = "Not Modified";
        http_status_codes[305] = "Use Proxy";
        http_status_codes[307] = "Temporary Redirect";
        http_status_codes[400] = "Bad Request";
        http_status_codes[401] = "Unauthorized";
        http_status_codes[402] = "Payment Required";
        http_status_codes[403] = "Forbidden";
        http_status_codes[404] = "Not Found";
        http_status_codes[405] = "Method Not Allowed";
        http_status_codes[406] = "Not Acceptable";
        http_status_codes[407] = "Proxy Authentication Required";
        http_status_codes[408] = "Request Timeout";
        http_status_codes[409] = "Conflict";
        http_status_codes[410] = "Gone";
        http_status_codes[411] = "Length Required";
        http_status_codes[412] = "Precondition Failed";
        http_status_codes[413] = "Content Too Large";
        http_status_codes[414] = "URI Too Long";
        http_status_codes[415] = "Unsupported Media Type";
        http_status_codes[416] = "Range Not Satisfiable";
        http_status_codes[417] = "Expectation Failed";
        http_status_codes[421] = "Misdirected Request";
        http_status_codes[422] = "Unprocessable Content";
        http_status_codes[426] = "Upgrade Required";
        http_status_codes[500] = "Internal Server Error";
        http_status_codes[501] = "Not Implemented";
        http_status_codes[502] = "Bad Gateway";
        http_status_codes[503] = "Service Unavailable";
        http_status_codes[504] = "Gateway Timeout";
        http_status_codes[505] = "HTTP Version Not Supported";

        return http_status_codes;
    }

    const std::vector<int> default_error_code = initialize_default_error_code();

    const std::map<int, std::string> http_status_codes = initialize_http_status_codes();
};  // namespace ft
