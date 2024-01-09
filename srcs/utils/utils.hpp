/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 18:31:18 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/09 13:11:04 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include <sstream>
#include <string>
#include <vector>

#define TIME_T_TO_MS(x) (x * 1000)

namespace ft {
    template <typename T>
    std::string to_string(T value) {
        std::ostringstream os;
        os << value;

        return os.str();
    }

    std::vector<std::string> split(const std::string& str, const std::string& delim);
}  // namespace ft

#endif /* __UTILS_HPP__ */
