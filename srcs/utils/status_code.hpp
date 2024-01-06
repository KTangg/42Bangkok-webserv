/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_code.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 21:38:04 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/06 14:40:59 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __STATUS_CODE_HPP__
#define __STATUS_CODE_HPP__

#include <map>
#include <string>
#include <vector>

#define UNDEFINED_ERROR "Undefined error"

namespace ft {
    const std::vector<int>           initialize_default_error_code();
    const std::map<int, std::string> initialize_http_status_codes();

    extern const std::vector<int>           default_error_code;
    extern const std::map<int, std::string> http_status_codes;
}  // namespace ft

#endif /* __STATUS_CODE_HPP__ */
