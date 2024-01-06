/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 20:20:30 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/06 14:12:56 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __CGI_HPP__
#define __CGI_HPP__

#include <string>

class Cgi {
   public:
    Cgi(const std::string& path, const std::string& extension);
    ~Cgi();

    const std::string& get_path() const;
    const std::string& getExtension() const;

    // TODO: Add execute method.

   private:
    const std::string _path;
    const std::string _extension;
};

#endif /* __CGI_HPP__ */
