/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mime_types.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 20:18:52 by tratanat          #+#    #+#             */
/*   Updated: 2024/03/01 23:05:06 by tratanat         ###   ########.fr       */
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

    const std::string get_mime_type(std::string extension);
}  // namespace ft

#endif