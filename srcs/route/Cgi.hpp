/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 20:20:30 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/07 00:29:25 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __CGI_HPP__
#define __CGI_HPP__

#include <string>

class Cgi {
   public:
    Cgi(const Cgi& src);
    Cgi& operator=(const Cgi& rhs);

    Cgi(const std::string& path, const std::string& extension);

    ~Cgi();

    const std::string& get_path() const;
    const std::string& getExtension() const;

    void set_path(const std::string& path);
    void set_extension(const std::string& extension);

    // TODO: Add execute method.

   private:
    Cgi();

    std::string _path;
    std::string _extension;
};

#endif /* __CGI_HPP__ */
