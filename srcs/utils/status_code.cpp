/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_code.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 21:36:45 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/09 14:46:26 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/status_code.hpp"

namespace ft {
    /**
     * @brief Initialize the http status codes.
     *
     * @return const std::map<int, std::string> The http status codes.
     */
    const std::map<int, std::string> initialize_http_status_codes() {
        std::map<int, std::string> http_status_codes;

        http_status_codes[HTTP_CONTINUE] = "Continue";
        http_status_codes[HTTP_SWITCHING_PROTOCOLS] = "Switching Protocols";
        http_status_codes[HTTP_OK] = "OK";
        http_status_codes[HTTP_CREATED] = "Created";
        http_status_codes[HTTP_ACCEPTED] = "Accepted";
        http_status_codes[HTTP_NON_AUTHORITATIVE_INFORMATION] = "Non-Authoritative Information";
        http_status_codes[HTTP_NO_CONTENT] = "No Content";
        http_status_codes[HTTP_RESET_CONTENT] = "Reset Content";
        http_status_codes[HTTP_PARTIAL_CONTENT] = "Partial Content";
        http_status_codes[HTTP_MULTIPLE_CHOICES] = "Multiple Choices";
        http_status_codes[HTTP_MOVED_PERMANENTLY] = "Moved Permanently";
        http_status_codes[HTTP_FOUND] = "Found";
        http_status_codes[HTTP_SEE_OTHER] = "See Other";
        http_status_codes[HTTP_NOT_MODIFIED] = "Not Modified";
        http_status_codes[HTTP_USE_PROXY] = "Use Proxy";
        http_status_codes[HTTP_TEMPORARY_REDIRECT] = "Temporary Redirect";
        http_status_codes[HTTP_BAD_REQUEST] = "Bad Request";
        http_status_codes[HTTP_UNAUTHORIZED] = "Unauthorized";
        http_status_codes[HTTP_PAYMENT_REQUIRED] = "Payment Required";
        http_status_codes[HTTP_FORBIDDEN] = "Forbidden";
        http_status_codes[HTTP_NOT_FOUND] = "Not Found";
        http_status_codes[HTTP_METHOD_NOT_ALLOWED] = "Method Not Allowed";
        http_status_codes[HTTP_NOT_ACCEPTABLE] = "Not Acceptable";
        http_status_codes[HTTP_PROXY_AUTHENTICATION_REQUIRED] = "Proxy Authentication Required";
        http_status_codes[HTTP_REQUEST_TIMEOUT] = "Request Timeout";
        http_status_codes[HTTP_CONFLICT] = "Conflict";
        http_status_codes[HTTP_GONE] = "Gone";
        http_status_codes[HTTP_LENGTH_REQUIRED] = "Length Required";
        http_status_codes[HTTP_PRECONDITION_FAILED] = "Precondition Failed";
        http_status_codes[HTTP_CONTENT_TOO_LARGE] = "Content Too Large";
        http_status_codes[HTTP_URI_TOO_LONG] = "URI Too Long";
        http_status_codes[HTTP_UNSUPPORTED_MEDIA_TYPE] = "Unsupported Media Type";
        http_status_codes[HTTP_RANGE_NOT_SATISFIABLE] = "Range Not Satisfiable";
        http_status_codes[HTTP_EXPECTATION_FAILED] = "Expectation Failed";
        http_status_codes[HTTP_MISDIRECTED_REQUEST] = "Misdirected Request";
        http_status_codes[HTTP_UNPROCESSABLE_CONTENT] = "Unprocessable Content";
        http_status_codes[HTTP_UPGRADE_REQUIRED] = "Upgrade Required";
        http_status_codes[HTTP_INTERNAL_SERVER_ERROR] = "Internal Server Error";
        http_status_codes[HTTP_NOT_IMPLEMENTED] = "Not Implemented";
        http_status_codes[HTTP_BAD_GATEWAY] = "Bad Gateway";
        http_status_codes[HTTP_SERVICE_UNAVAILABLE] = "Service Unavailable";
        http_status_codes[HTTP_GATEWAY_TIMEOUT] = "Gateway Timeout";
        http_status_codes[HTTP_VERSION_NOT_SUPPORTED] = "HTTP Version Not Supported";

        return http_status_codes;
    }

    const std::map<int, std::string> http_status_codes = initialize_http_status_codes();
};  // namespace ft
