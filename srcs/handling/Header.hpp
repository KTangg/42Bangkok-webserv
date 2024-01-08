/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Header.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 18:17:14 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/08 14:23:11 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __HEADER_HPP__
#define __HEADER_HPP__

#include <map>
#include <string>

class Header {
   public:
    Header();
    Header(const Header& src);
    Header&      operator=(const Header& src);
    std::string& operator[](const std::string& key);

    ~Header();

    void        add(const std::string& key, const std::string& value);
    void        remove(const std::string& key);
    void        clear();
    bool        has(const std::string& key) const;
    std::string get(const std::string& key) const;
    std::string to_string() const;

    void set_complete(bool is_complete);
    bool is_complete() const;

   private:
    bool                               _is_complete;
    std::map<std::string, std::string> _headers;
};

#endif /* __HEADER_HPP__ */
