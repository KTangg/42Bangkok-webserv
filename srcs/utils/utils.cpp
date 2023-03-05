/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 00:15:40 by spoolpra          #+#    #+#             */
/*   Updated: 2023/03/05 17:23:49 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "webserv.hpp"


l_str_t ft::parse_path_directory(std::string path)
{
    int         i;
    l_str_t  list_path;

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


l_str_t ft::join_list(const l_str_t& a, const l_str_t& b)
{
    l_str_t ab;

    ab.reserve(a.size() + b.size());
    ab.insert(ab.end(), a.begin(), a.end());
    ab.insert(ab.end(), b.begin(), b.end());

    return ab;
}


std::string ft::path_join(const l_str_t& list_path)
{
    std::string path = "/";

    for (l_str_t::const_iterator it = list_path.begin();
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


bool    ft::is_number(const std::string& s)
{
    for (std::string::const_iterator it = s.begin(); it != s.end(); ++it)
    {
        if (!std::isdigit(*it))
        {
            return false;
        }
    }

    return true;
}


size_t   ft::send(int socket, const void* buffer, size_t n)
{
    size_t  ret;
    
#ifdef __APPLE__
    ret = ::send(socket, buffer, n, MSG_DONTWAIT);
#else
    ret = ::send(socket, buffer, n, MSG_NOSIGNAL | MSG_DONTWAIT);
#endif

    return ret;
}


size_t   ft::recv(int socket, void* buffer, size_t n)
{
    size_t ret;

#ifdef __APPLE__
    ret = ::recv(socket, buffer, n, MSG_DONTWAIT);
#else
    ret = ::recv(socket, buffer, n, MSG_NOSIGNAL | MSG_DONTWAIT);
#endif

    return ret;
}


l_str_t     ft::split(bytestring& src, unsigned char sep)
{
    l_str_t         arr_str;
    bytestring      bstr;
    bytestream      bs(src);
    
    while (std::getline(bs, bstr, sep))
    {
        if (!bstr.empty())
        {
            arr_str.push_back(BYTES_TO_STR(bstr.c_str()));
        }
    }
    
    return arr_str;
}


l_str_t     ft::split(bytestring& src, unsigned char sep_1, unsigned char sep_2)
{
    l_str_t         arr_str;
    bytestring      outer_bstr;
    bytestring      inner_bstr;
    bytestream      outer_bs(src);


    while (std::getline(outer_bs, outer_bstr, sep_1))
    {
        bytestream      inner_bs(outer_bstr);
        while (std::getline(inner_bs, inner_bstr, sep_2))
        {
            if (!inner_bstr.empty())
            {
                arr_str.push_back(BYTES_TO_STR(inner_bstr.c_str()));
            }
        }
    }

    return arr_str;
}


std::string     ft::strnow()
{
    std::time_t epoch_time = std::time(NULL);
    char time_string[sizeof("aaa, dd bbb YYYY HH:MM:SS ZZZ")];

    std::strftime(
        time_string,
        sizeof(time_string),
        "%a, %d %b %Y %H:%M:%S %Z",
        std::gmtime(&epoch_time)
        );

    return time_string;
}


std::string     ft::skip_ws(const std::string& str)
{
    for (size_t i = 0; i < str.size(); ++i)
    {
        if (str[i] != '\t' && str[i] != ' ')
        {
            return str.substr(i);
        }
    }

    return std::string("");
}


std::string     ft::tolower(const std::string& str)
{
    std::string lower(str);

    for (std::string::iterator it = lower.begin(); it != lower.end(); ++it)
    {
        *it = std::tolower(*it);
    }

    return lower;
}