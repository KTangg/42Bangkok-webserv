/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 16:21:10 by tratanat          #+#    #+#             */
/*   Updated: 2024/02/25 16:22:27 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

std::string ft::strip_space(std::string value) {
    int i = 0;

    if (value.length() == 0) return value;
    while (isspace(value[i])) i++;
    if (i != 0) value = value.substr(i);
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