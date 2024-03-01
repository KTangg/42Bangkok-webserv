/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 20:20:30 by spoolpra          #+#    #+#             */
/*   Updated: 2024/03/01 22:07:51 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __CGI_HPP__
#define __CGI_HPP__

#include <sys/wait.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

class Cgi {
   public:
    Cgi(const Cgi& src);
    Cgi(const std::string& path, const std::string& extension);

    ~Cgi();

    const std::string& get_path() const;
    const std::string& get_extension() const;
    bool               is_ready();
    const std::string& get_content() const;
    void               execute(const std::string& filepath);

    // TODO: Add execute method.

   private:
    Cgi();
    Cgi& operator=(const Cgi& rhs);

    const std::string _path;
    const std::string _extension;
    std::string       _content;
    pid_t             _child_pid;
    int               _pipefd[2];

    bool _M_check_child();
};

#endif /* __CGI_HPP__ */
