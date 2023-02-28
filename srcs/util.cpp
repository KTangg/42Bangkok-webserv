/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 00:15:40 by spoolpra          #+#    #+#             */
/*   Updated: 2023/03/01 00:22:37 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"


list_str_t parse_path_directory(std::string path)
{
    int         i;
    list_str_t  list_path;

    i = 0;
    while (path.size() > 0)
    {
        size_t      next_pos;
        std::string dir;

        next_pos = path.find('/');
        if (next_pos == std::string::npos)
        {
            dir = path;
            path.clear();
        }
        else
        {
            dir = path.substr(0, next_pos);
            path = path.substr(next_pos + 1);
        }
        if (i++ == 0 && dir.empty())
        {
            continue;
        }
        list_path.push_back(dir);
    }

    return list_path;
}


list_str_t join_list(const list_str_t& a, const list_str_t& b)
{
    list_str_t ab;

    ab.reserve(a.size() + b.size());
    ab.insert(ab.end(), a.begin(), a.end());
    ab.insert(ab.end(), b.begin(), b.end());

    return ab;
}


std::string path_join(const list_str_t& list_path)
{
    std::string path = "/";

    for (list_str_t::const_iterator it = list_path.begin();
         it != list_path.end();
         ++it
        )
    {
        path = path + (*it);
        if (it != (list_path.end() - 1)){
            path = path + "/";
        }
    }

    return path;
}
