/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 18:31:18 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/06 14:54:18 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include <sstream>

namespace ft {
    template <typename T>
    std::string to_string(T value) {
        std::ostringstream os;
        os << value;

        return os.str();
    }
}  // namespace ft

#endif /* __UTILS_HPP__ */
