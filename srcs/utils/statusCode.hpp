/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statusCode.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 21:38:04 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/03 22:43:12 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __STATUSCODE_HPP__
#define __STATUSCODE_HPP__

#include <map>
#include <string>
#include <vector>

#define UNDEFINED_ERROR "Undefined error"

namespace ft {
    const std::vector<int>           defaultErrorCode;
    const std::map<int, std::string> httpStatusCodes;
}  // namespace ft

#endif /* __STATUSCODE_HPP__ */
