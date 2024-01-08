/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:06:37 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/08 14:11:11 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/utils.hpp"

namespace ft {
    std::vector<std::string> split(const std::string& str, const std::string& delim) {
        std::vector<std::string> tokens;
        size_t                   prev = 0;
        size_t                   pos = 0;

        do {
            pos = str.find(delim, prev);
            if (pos == std::string::npos) {
                pos = str.length();
            }
            std::string token = str.substr(prev, pos - prev);
            if (!token.empty()) {
                tokens.push_back(token);
            }
            prev = pos + delim.length();
        } while (pos < str.length());

        return tokens;
    }
}  // namespace ft
