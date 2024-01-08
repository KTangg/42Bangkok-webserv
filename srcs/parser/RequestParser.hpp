/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestParser.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 18:42:26 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/08 13:32:48 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __REQUEST_PARSER_HPP__
#define __REQUEST_PARSER_HPP__

#include <algorithm>
#include <sstream>
#include <string>

#include "utils/utils.hpp"

class Request;  // Forward declaration of Request class

class RequestParser {
   public:
    RequestParser(Request& request);
    RequestParser(const RequestParser& src);

    ~RequestParser();

    void parse(const char* buffer, size_t size);

   private:
    RequestParser();
    RequestParser& operator=(const RequestParser& src);

    Request&          _request;
    std::stringstream _buffer;

    std::size_t _request_line_end;
    std::size_t _headers_end;
    std::size_t _body_end;

    std::size_t _M_parse_request_line();
    std::size_t _M_parse_headers();
    std::size_t _M_parse_body();

    std::size_t _M_parse_chunked_body();
    std::size_t _M_parse_content_length_body();

    void _M_add_request_line(const std::string& line);
    void _M_add_header(const std::string& line);
    void _M_add_body(const std::string& line);

    static bool _S_read_line(std::stringstream& buffer, std::string& line);
};

#include "handling/Request.hpp"

#endif /* __REQUEST_PARSER_HPP__ */
