/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 18:31:18 by spoolpra          #+#    #+#             */
/*   Updated: 2024/02/28 20:08:25 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include <exception>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

namespace ft {
    template <typename T>
    std::string to_string(T value) {
        std::ostringstream os;
        os << value;

        return os.str();
    }

    std::string                         strip_space(std::string value);
    std::pair<std::string, std::string> split_config(std::string value);
    std::vector<std::string>            split_whitespace(std::string value);
    std::vector<std::string> split(std::string value, std::string delimiter, int limit = 0);
    std::string              string_lower(std::string str);

}  // namespace ft

#endif /* __UTILS_HPP__ */
