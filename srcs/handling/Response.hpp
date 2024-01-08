/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 12:05:27 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/08 14:30:25 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __RESPONSE_HPP__
#define __RESPONSE_HPP__

#include <sys/socket.h>

#include <sstream>
#include <stdexcept>

#include "handling/Header.hpp"
#include "utils/status_code.hpp"

class Response {
   public:
    Response();
    Response(const Response& src);
    Response& operator=(const Response& src);

    ~Response();

    bool is_ready() const;

    void set_version(const std::string& version);
    void set_status_code(const int& status_code);

    std::string get_response() const;

   private:
    bool        _is_ready;
    std::string _version;
    int         _status_code;
    std::string _reason_phrase;

    Header      _headers;
    std::string _body;

    std::string _M_generate_response() const;
};

#endif /* __RESPONSE_HPP__ */
