/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 16:21:10 by tratanat          #+#    #+#             */
/*   Updated: 2024/03/01 21:13:21 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

std::string ft::strip_space(std::string value) {
    size_t i = 0;
    size_t j = value.length() - 1;

    if (value.length() == 0) return value;
    while (i < value.length() && isspace(value[i])) i++;
    while (j > 0 && isspace(value[j])) j--;
    if (i != 0) value = value.substr(i, j - i + 1);
    return value;
}

std::pair<std::string, std::string> ft::split_config(std::string value) {
    value = ft::strip_space(value);
    size_t pos = 0;

    for (size_t i = 0; i < value.length(); i++) {
        if (isspace(value[i])) {
            pos = i;
            break;
        }
    }
    if (pos == value.length()) {
        throw std::invalid_argument("invalid key-value combination");
    }
    std::pair<std::string, std::string> rtn =
        std::make_pair(ft::strip_space(value.substr(0, pos)), ft::strip_space(value.substr(pos)));
    return rtn;
}

std::vector<std::string> ft::split_whitespace(std::string value) {
    size_t                   word_start = 0;
    size_t                   pos = 0;
    std::vector<std::string> list;

    while (pos < value.length()) {
        while (pos < value.length() && isspace(value[pos])) pos++;
        word_start = pos;
        while (pos < value.length() && !isspace(value[pos])) pos++;
        list.push_back(value.substr(word_start, pos++));
    }

    return list;
}

std::vector<std::string> ft::split(std::string value, std::string delimiter, int limit) {
    int                      split_count = 0;
    size_t                   pos = 0;
    std::vector<std::string> list;

    while (value.length() > 0) {
        pos = value.find(delimiter);
        if (pos == std::string::npos) break;

        std::string member = value.substr(0, pos);
        list.push_back(ft::strip_space(member));
        split_count++;

        if (pos == value.length()) break;
        value = value.substr(pos + 1);

        if (limit > 0 && split_count >= limit) {
            std::string remainder = ft::strip_space(value);
            if (remainder.length() > 0) list.push_back(remainder);
        };
    }

    return list;
}

std::string ft::string_lower(std::string str) {
    for (std::string::iterator it = str.begin(); it != str.end(); it++) {
        *it = tolower(*it);
    }
    return str;
}

std::string ft::get_extension(const std::string& path) {
    size_t pos = path.find_last_of(".");
    if (pos == std::string::npos) return "";
    return path.substr(pos + 1);
}