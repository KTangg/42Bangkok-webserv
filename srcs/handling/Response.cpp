/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:35:55 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/08 14:57:30 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handling/Response.hpp"

/**
 * @brief Construct a new Response:: Response object
 *
 */
Response::Response()
    : _is_ready(false), _version("HTTP/1.1"), _status_code(200), _reason_phrase("OK") {
}

/**
 * @brief Construct a new Response:: Response object
 *
 * @param src The object to do the copy
 */
Response::Response(const Response& src)
    : _is_ready(src._is_ready),
      _version(src._version),
      _status_code(src._status_code),
      _reason_phrase(src._reason_phrase),
      _headers(src._headers),
      _body(src._body) {
}

/**
 * @brief Destroy the Response:: Response object
 *
 */
Response::~Response() {
}

/**
 * @brief Check if the response is ready
 *
 * @return true If the response is ready
 * @return false If the response is not ready
 */
bool Response::is_ready() const {
    return _is_ready;
}

/**
 * @brief Set the version of the response
 *
 * @param version The version of the response
 */
void Response::set_version(const std::string& version) {
    _version = version;
}

/**
 * @brief Set the status code of the response
 *
 * @param status_code The status code of the response
 */
void Response::set_status_code(const int& status_code) {
    _status_code = status_code;
    try {
        _reason_phrase = ft::http_status_codes.at(_status_code);
    } catch (const std::out_of_range& e) {
        _reason_phrase = UNDEFINED_ERROR;
    }

    if (_status_code != 200) {
        _is_ready = true;
    }
}

/**
 * @brief Get the response
 *
 * @return std::string The response
 */
std::string Response::get_response() const {
    return _M_generate_response();
}

/**
 * @brief Generate the response
 *
 * @return std::string The response
 */

std::string Response::_M_generate_response() const {
    std::stringstream ss;

    ss << _version << " " << _status_code << " " << _reason_phrase << "\r\n";
    ss << "Content-Type: text/html; charset=UTF-8\r\n";
    ss << "Content-Length: 70\r\n";
    ss << "\r\n";
    ss << "<html><body><h1>Hello, world!</h1><p>Welcome to our server.</p></body></html>";

    return ss.str();
}
