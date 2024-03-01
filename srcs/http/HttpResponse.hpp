/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 09:36:06 by tratanat          #+#    #+#             */
/*   Updated: 2024/02/29 19:36:05 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __HTTP_RESPONSE_HPP__
#define __HTTP_RESPONSE_HPP__

#include <ctime>
#include <iostream>
#include <sstream>
#include <string>

#include "constants.hpp"
#include "utils/status_code.hpp"

class HttpResponse {
   public:
    HttpResponse(int status_code, const std::string& response_text);
    HttpResponse(int                status_code,
                 const std::string& connection,
                 const std::string& keep_alive,
                 const std::string& content_type,
                 const std::string& content);
    ~HttpResponse();
    std::string get_raw_message();

   private:
    HttpResponse();
    void set_date();

    int         _status_code;
    std::string _date;
    std::string _server;
    std::string _connection;
    std::string _keep_alive;
    std::string _content_type;
    size_t      _content_length;
    std::string _content;
};

#endif