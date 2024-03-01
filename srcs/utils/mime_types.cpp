/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mime_types.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 20:20:07 by tratanat          #+#    #+#             */
/*   Updated: 2024/03/01 09:31:29 by tratanat         ###   ########.fr       */
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

        mime_types[".html"] = "text/html";
        mime_types[".htm"] = "text/html";
        mime_types[".jpg"] = "image/jpeg";
        mime_types[".jpeg"] = "image/jpeg";
        mime_types[".png"] = "image/png";
        mime_types[".svg"] = "image/svg";
        mime_types[".webp"] = "image/webp";
        mime_types[".js"] = "text/javascript";
        mime_types[".css"] = "text/css";
        mime_types[".csv"] = "text/csv";
        mime_types[".json"] = "application/json";
        mime_types[".mp4"] = "video/mp4";
        mime_types[".txt"] = "text/plain";
        mime_types[".zip"] = "application/zip";

        return mime_types;
    }

    const std::map<std::string, std::string> mime_types = initialize_mime_types();
}  // namespace ft