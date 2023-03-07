/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 00:15:40 by spoolpra          #+#    #+#             */
/*   Updated: 2023/03/07 20:55:27 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "webserv.hpp"

#include "utils/utils.hpp"


/**
 * @brief Check whether given string only contain 0-9 char
 *
 * @param s string to be check
 * @return true if all char in string is 0-9 otherwise, false is return
 */
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


/**
 * @brief Send message to given socket
 *
 * @param socket socket fd to sent
 * @param buffer message
 * @param n message length
 * @return ssize_t number of character send, -1 on error
 */
ssize_t   ft::send(int socket, const void* buffer, size_t n)
{
    ssize_t  ret;

#ifdef __APPLE__
    ret = ::send(socket, buffer, n, MSG_DONTWAIT);
#else
    ret = ::send(socket, buffer, n, MSG_NOSIGNAL | MSG_DONTWAIT);
#endif

    return ret;
}


/**
 * @brief Read message from socket
 *
 * @param socket socket fd to be read
 * @param buffer message container
 * @param n size of message container
 * @return ssize_t number of character read, -1 on error
 */
ssize_t   ft::recv(int socket, void* buffer, size_t n)
{
    ssize_t ret;

#ifdef __APPLE__
    ret = ::recv(socket, buffer, n, MSG_DONTWAIT);
#else
    ret = ::recv(socket, buffer, n, MSG_NOSIGNAL | MSG_DONTWAIT);
#endif

    return ret;
}


/**
 * @brief Get string of current time "Mon, 01, Jan 2023 00:00:00 GMT" format
 *
 * @return std::string current time in string object
 */
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


/**
 * @brief Skipping all space and tab at start of string
 *
 * @param str string to trim
 * @return std::string trimmed string
 */
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


/**
 * @brief Lower all character in string
 *
 * @param str string to be lower
 * @return std::string lower form of string
 */
std::string     ft::tolower(const std::string& str)
{
    std::string lower(str);

    for (std::string::iterator it = lower.begin(); it != lower.end(); ++it)
    {
        *it = std::tolower(*it);
    }

    return lower;
}


/**
 * @brief Convert hexadecimal string to decimal
 *
 * @param str hexadecimal
 * @return ssize_t decimal
 */
ssize_t      ft::hex_to_dec(const std::string& str)
{
    std::stringstream ss(str);

    ssize_t  nb;

    ss >> std::hex >> nb;

    return nb;
}


/**
 * @brief Capitalize string
 *
 * @param str string to be capitalized
 * @return std::string capitalized string
 */
std::string     ft::capitalize(const std::string& str)
{
    std::string cap(str);

    if (!cap.empty())
    {
        cap[0] = std::toupper(cap[0]);
    }

    return cap;
}


/**
 * @brief Parse path with "/" as delimiter
 *
 * @param path string to be tokenized
 * @return v_str_t Vector of string tokenized from path
 */
v_str_t     ft::parse_path(const std::string& path)
{
    v_str_t             v;
    std::string         each;
    std::stringstream   ss(path);

    if (ss.peek() == '/')
    {
        ss.get();
    }
    while(std::getline(ss, each, '/'))
    {
        v.push_back(each);
    }

    return v;
}


/**
 * @brief Remove trailing '/' from path
 *
 * @param path string to be remove
 * @return std::string trim string
 */
std::string     ft::trim_path(const std::string& path)
{
    std::string trim = path;
    size_t      size = trim.size();

    if (size <= 1)
    {
        return trim;
    }

    if (trim[size - 1] == '/')
    {
        trim.erase(size - 1);
    }

    return trim;
}
