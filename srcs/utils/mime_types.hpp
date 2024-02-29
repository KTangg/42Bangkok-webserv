/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mime_types.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 20:18:52 by tratanat          #+#    #+#             */
/*   Updated: 2024/02/29 20:30:12 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MIME_TYPES__
#define __MIME_TYPES__

#include <map>
#include <string>

#define DEFAULT_MIME_TYPE "application/octet-stream"

namespace ft {
    const std::map<std::string, std::string> initialize_mime_types();

    extern const std::map<std::string, std::string> mime_types;
}  // namespace ft

#endif