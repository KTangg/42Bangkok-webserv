/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestParser.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 18:42:24 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/09 13:48:43 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/RequestParser.hpp"

/**
 * @brief Construct a new Request Parser:: Request Parser object
 *
 * @param request The request to parse
 */
RequestParser::RequestParser(Request& request)
    : _request(request),
      _buffer(),
      _request_line_end(std::string::npos),
      _headers_end(std::string::npos),
      _body_end(std::string::npos) {
}

/**
 * @brief Construct a new Request Parser:: Request Parser object
 *
 * @param src The object to do the copy
 */
RequestParser::RequestParser(const RequestParser& src) : _request(src._request) {
}

/**
 * @brief Destroy the Request Parser:: Request Parser object
 *
 */
RequestParser::~RequestParser() {
}

/**
 * @brief Parse the request
 *
 * @param buffer The buffer to parse
 */
void RequestParser::parse(const char* buffer, size_t size) {
    // Add the buffer to the stringstream
    _buffer.write(buffer, size);

    // If the request line is not parsed yet, parse it
    if (_request_line_end == std::string::npos) {
        _request_line_end = _M_parse_request_line();
    }
    // If the headers are not parsed yet, parse them
    if (_headers_end == std::string::npos) {
        _headers_end = _M_parse_headers();
    }
    // If the body is not parsed yet, parse it
    if (_body_end == std::string::npos) {
        _body_end = _M_parse_body();
    }

    // If all complete mark request as complete
    if (_request_line_end != std::string::npos && _headers_end != std::string::npos &&
        _body_end != std::string::npos) {
        _request.set_complete(true);
    }
}

/**
 * @brief Parse the request line
 *
 * @return std::size_t The end of the request line
 */
std::size_t RequestParser::_M_parse_request_line() {
    std::string line;

    // Remember the current position
    std::streampos pos = _buffer.tellg();

    // Get the request line
    bool end_line = _S_read_line(_buffer, line);

    // If the request line is not complete, reset the position
    if (line.empty() || !end_line) {
        _buffer.seekg(pos);
        return std::string::npos;
    }

    // Save the request line to Request object
    _M_add_request_line(line);

    // Return the end of the request line
    return _buffer.tellg();
}

/**
 * @brief Parse the headers
 *
 * @return std::size_t The end of the headers
 */
std::size_t RequestParser::_M_parse_headers() {
    std::string    line;
    bool           end_line;
    std::streampos pos;

    do {
        // Remember the current position
        pos = _buffer.tellg();

        // Get the line
        end_line = _S_read_line(_buffer, line);

        // If endline and line is empty then the headers are complete
        if (line.empty() && end_line) {
            return _buffer.tellg();
        }

        // If endline and line is not empty then save the header
        if (!line.empty() && end_line) {
            _M_add_header(line);
        }
    } while (!line.empty() && end_line);

    // If the headers are not complete, reset the position
    _buffer.seekg(pos);

    return std::string::npos;
}

/**
 * @brief Parse the body
 *
 * @return std::size_t The end of the body
 */
std::size_t RequestParser::_M_parse_body() {
    // If the request is chunked, parse the chunked body
    if (_request.is_chunked()) {
        return _M_parse_chunked_body();
    }

    // If the request is not chunked, check content-length
    return _M_parse_content_length_body();
}

/**
 * @brief Parse the chunked body
 *
 * @return std::size_t The end of the body
 */
std::size_t RequestParser::_M_parse_chunked_body() {
    bool           end_line;
    std::string    size_line;
    std::string    body_line;
    std::streampos pos;

    // Remember the current position
    pos = _buffer.tellg();

    while (true) {
        // Get the size of the chunk
        end_line = _S_read_line(_buffer, size_line);

        // If the size is empty or the end of the line is not reached, reset the position
        if (size_line.empty() || !end_line) {
            _buffer.seekg(pos);
            return std::string::npos;
        }

        // If the size is 0, then the body is complete
        if (size_line == "0") {
            return _buffer.tellg();
        }

        // Get the body of the chunk
        end_line = _S_read_line(_buffer, body_line);

        // If the body is empty or the end of the line is not reached, reset the position
        if (body_line.empty() || !end_line) {
            _buffer.seekg(pos);
            return std::string::npos;
        }

        // If the size is not 0, then add the body line to the body
        _M_add_body(body_line);
    }
}

/**
 * @brief Parse the content-length body
 *
 * @return std::size_t The end of the body
 */
std::size_t RequestParser::_M_parse_content_length_body() {
    std::string    line;
    std::streampos pos;

    // Remember the current position
    pos = _buffer.tellg();

    // Get the body
    _S_read_line(_buffer, line);

    // If the line is not matched with the content-length, reset the position
    if (line.size() != _request.get_content_length()) {
        _buffer.seekg(pos);
        return std::string::npos;
    }

    // Add the body to the request
    _M_add_body(line);

    return _buffer.tellg();
}

/**
 * @brief Add the request line to the request
 *
 * @param line The request line
 */
void RequestParser::_M_add_request_line(const std::string& line) {
    std::string method;
    std::string uri;
    std::string version;

    std::vector<std::string> tokens = ft::split(line, " ");
    if (tokens.size() != 3) {
        _request.set_response_status_code(400);
        return;
    }

    _request.set_method(tokens[0]);
    _request.set_uri(tokens[1]);
    _request.set_version(tokens[2]);
}

/**
 * @brief Add the header to the request
 *
 * @param line The header
 */
void RequestParser::_M_add_header(const std::string& line) {
    std::vector<std::string> tokens = ft::split(line, ": ");
    if (tokens.size() != 2) {
        _request.set_response_status_code(400);
        return;
    }
    // lowercase the header name
    std::transform(tokens[0].begin(), tokens[0].end(), tokens[0].begin(), ::tolower);

    _request.add_header(tokens[0], tokens[1]);
}

/**
 * @brief Add the body to the request
 *
 * @param line The body
 */
void RequestParser::_M_add_body(const std::string& line) {
    _request.add_body(line);
}

/**
 * @brief Read a line from the buffer
 *
 * @param buffer The buffer
 * @param line The line
 * @return true If the \n is reached
 * @return false If the \n is not reached
 */
bool RequestParser::_S_read_line(std::stringstream& buffer, std::string& line) {
    char c;

    line.clear();

    while (buffer.get(c)) {
        if (c == '\r') {
            if (buffer.get(c) && c == '\n') {
                return true;
            }
        }
        line += c;
    }

    return false;
}
