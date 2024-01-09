/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 16:01:35 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/09 13:47:28 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __REQUEST_HPP__
#define __REQUEST_HPP__

#include <algorithm>
#include <map>
#include <string>

#include "handling/Header.hpp"
#include "handling/Response.hpp"
#include "parser/RequestParser.hpp"

class Request {
   public:
    Request();
    Request(const Request& src);
    ~Request();

    void set_method(const std::string& method);
    void set_uri(const std::string& uri);
    void set_version(const std::string& version);
    void add_header(const std::string& key, const std::string& value);
    void add_body(const std::string& body);
    void set_complete(const bool& complete);

    const std::string& get_method() const;
    const std::string& get_uri() const;
    const std::string& get_version() const;
    std::string        get_header(const std::string& key) const;
    const Header&      get_headers() const;
    const std::string& get_body() const;
    const bool&        is_complete() const;

    bool        is_chunked() const;
    std::size_t get_content_length() const;

    void        set_response_status_code(int code);
    bool        ready_to_respond() const;
    std::string get_response() const;

    void read(const char* buffer, size_t size);

   private:
    Request& operator=(const Request& src);

    std::string _method;
    std::string _uri;
    std::string _version;
    Header      _headers;
    std::string _body;

    bool     _is_complete;
    Response _response;

    RequestParser _parser;
};

#endif /* __REQUEST_HPP__ */
