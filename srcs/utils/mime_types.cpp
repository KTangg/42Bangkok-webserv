/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mime_types.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 20:20:07 by tratanat          #+#    #+#             */
/*   Updated: 2024/03/01 23:10:33 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/mime_types.hpp"

namespace ft {
    /**
     * @brief Initialize the default mime types. This list is not exhaustive.
     *
     * @return const std::map<std::string, std::string> Default mime types.
     */
    const std::map<std::string, std::string> initialize_mime_types() {
        std::map<std::string, std::string> mime_types;

        mime_types["html"] = "text/html";
        mime_types["htm"] = "text/html";
        mime_types["php"] = "application/x-httpd-php";
        mime_types["jpg"] = "image/jpeg";
        mime_types["jpeg"] = "image/jpeg";
        mime_types["png"] = "image/png";
        mime_types["svg"] = "image/svg";
        mime_types["webp"] = "image/webp";
        mime_types["js"] = "text/javascript";
        mime_types["css"] = "text/css";
        mime_types["csv"] = "text/csv";
        mime_types["json"] = "application/json";
        mime_types["pdf"] = "application/pdf";
        mime_types["mp4"] = "video/mp4";
        mime_types["txt"] = "text/plain";
        mime_types["tar"] = "application/x-tar";
        mime_types["gz"] = "application/gzip";
        mime_types["zip"] = "application/zip";
        mime_types["default"] = "application/zip";

        return mime_types;
    }

    const std::map<std::string, std::string> mime_types = initialize_mime_types();

    const std::string get_mime_type(std::string extension) {
        std::map<std::string, std::string>::const_iterator mime_type =
            ft::mime_types.find(extension);
        if (mime_type == ft::mime_types.end()) {
            return "application/octet-stream";
        }
        return mime_type->second;
    }
}  // namespace ft