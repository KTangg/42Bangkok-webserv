/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 20:20:30 by spoolpra          #+#    #+#             */
/*   Updated: 2024/04/07 19:08:58 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __CGI_HPP__
#define __CGI_HPP__

#include <sys/wait.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

#include "constants.hpp"

class Cgi {
   public:
    Cgi(const Cgi& src, std::string method, std::string req_content, std::string req_type);
    Cgi(const std::string& path, const std::string& extension, std::string req_content);

    ~Cgi();

    const std::string& get_path() const;
    const std::string& get_extension() const;
    bool               is_ready();
    const std::string& get_content() const;
    void               execute(const std::string& filepath);

   private:
    Cgi();
    Cgi& operator=(const Cgi& rhs);

    const std::string _path;
    const std::string _extension;
    std::string       _content;
    pid_t             _child_pid;
    int               _pipefd[2];
    std::string       _method;
    std::string       _req_content;
    std::string       _req_type;

    bool _M_check_child();
};

#endif /* __CGI_HPP__ */
