/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 16:01:43 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/09 13:10:36 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handling/Request.hpp"

/**
 * @brief Construct a new Request:: Request object
 *
 */
Request::Request() : _start_time(std::time(NULL)), _parser(*this) {
}

/**
 * @brief Construct a new Request:: Request object
 *
 * @param src The object to do the copy
 */
Request::Request(const Request& src)
    : _start_time(src._start_time),
      _method(src._method),
      _uri(src._uri),
      _version(src._version),
      _headers(src._headers),
      _body(src._body),
      _response(src._response),
      _parser(*this) {
}

/**
 * @brief Destroy the Request:: Request object
 *
 */
Request::~Request() {
}

/**
 * @brief Set the method of the request
 *
 * @param method The method of the request
 */
void Request::set_method(const std::string& method) {
    _method = method;
}

/**
 * @brief Set the uri of the request
 *
 * @param uri The uri of the request
 */
void Request::set_uri(const std::string& uri) {
    _uri = uri;
}

/**
 * @brief Set the version of the request
 *
 * @param version The version of the request
 */
void Request::set_version(const std::string& version) {
    _version = version;
}

/**
 * @brief Add a header to the request
 *
 * @param key The key of the header
 * @param value The value of the header
 */
void Request::add_header(const std::string& key, const std::string& value) {
    // If key exist, add comma separated value
    if (_headers.has(key)) {
        _headers[key] += ", " + value;
    } else {
        _headers.add(key, value);
    }
}

/**
 * @brief Add a body to the request
 *
 * @param body The body to add
 */
void Request::add_body(const std::string& body) {
    std::size_t content_length = get_content_length();
    if (content_length == 0) {
        _body.reserve(content_length);
    }

    _body += body;
}

/**
 * @brief Get the start time of the request
 *
 * @return std::size_t The start time of the request
 */
std::size_t Request::get_start_time_ms() const {
    return TIME_T_TO_MS(_start_time);
}

/**
 * @brief Get the method of the request
 *
 * @return const std::string& The method of the request
 */
const std::string& Request::get_method() const {
    return _method;
}

/**
 * @brief Get the uri of the request
 *
 * @return const std::string& The uri of the request
 */
const std::string& Request::get_uri() const {
    return _uri;
}

/**
 * @brief Get the version of the request
 *
 * @return const std::string& The version of the request
 */
const std::string& Request::get_version() const {
    return _version;
}

/**
 * @brief Get the header of the request
 *
 * @param key The key of the header
 * @return const std::string& The header of the request
 */
std::string Request::get_header(const std::string& key) const {
    return _headers.get(key);
}

/**
 * @brief Get the headers of the request
 *
 * @return const Header& The headers of the request
 */
const Header& Request::get_headers() const {
    return _headers;
}

/**
 * @brief Get the body of the request
 *
 * @return const std::string& The body of the request
 */
const std::string& Request::get_body() const {
    return _body;
}

/**
 * @brief Check if the request is chunked
 *
 * @return true If the request is chunked
 * @return false If the request is not chunked
 */
bool Request::is_chunked() const {
    return _headers.has("Transfer-Encoding") && _headers.get("Transfer-Encoding") == "chunked";
}

/**
 * @brief Get the content length of the request
 *
 * @return std::size_t The content length of the request
 */
std::size_t Request::get_content_length() const {
    return std::strtoul(_headers.get("Content-Length").c_str(), NULL, 10);
}

/**
 * @brief Set the response status code
 *
 * @param code The status code
 */
void Request::set_response_status_code(int code) {
    _response.set_status_code(code);
}

/**
 * @brief Check if the request is ready to respond
 *
 * @return true If the request is ready to respond
 * @return false If the request is not ready to respond
 */
bool Request::ready_to_respond() const {
    return _response.is_ready();
}

/**
 * @brief Get the response
 *
 * @return std::string The response
 */
std::string Request::get_response() const {
    return _response.get_response();
}

/**
 * @brief Read the request
 *
 * @param buffer The buffer to read
 * @param size The size of the buffer
 */
void Request::read(const char* buffer, size_t size) {
    _parser.parse(buffer, size);
}
