/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:03:41 by spoolpra          #+#    #+#             */
/*   Updated: 2023/03/08 17:50:22 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef __UTILS_HPP__
# define __UTILS_HPP__


# include "webserv.hpp"


namespace ft
{
    std::string     strnow();
    bool            is_number(const std::string& s);
    std::string     skip_ws(const std::string& str);
    std::string     tolower(const std::string& str);
    v_str_t         parse_ws(const std::string& str);
    std::string     capitalize(const std::string& str);
    ssize_t         hex_to_dec(const std::string& str);
    std::string     trim_path(const std::string& path);
    v_str_t         parse_path(const std::string& path);
    ssize_t         recv(int socket, void* buffer, size_t n);
    ssize_t         send(int socket, const void* buffer, size_t n);
}


#endif
