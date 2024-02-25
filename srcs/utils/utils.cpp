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