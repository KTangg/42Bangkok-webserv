/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Header.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 18:17:13 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/08 13:59:08 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handling/Header.hpp"

/**
 * @brief Construct a new Header:: Header object
 *
 */
Header::Header() {
}

/**
 * @brief Construct a new Header:: Header object
 *
 * @param src the object to do the copy
 */
Header::Header(const Header& src) {
    *this = src;
}

/**
 * @brief Destroy the Header:: Header object
 *
 */
Header::~Header() {
}

/**
 * @brief Copy this object
 *
 * @param rhs the object to copy
 * @return Header& a reference to the copied object
 */
Header& Header::operator=(const Header& rhs) {
    if (this != &rhs) {
        _headers = rhs._headers;
    }
    return *this;
}

/**
 * @brief Get the header
 *
 * @param key the key
 * @return std::string& the header
 */
std::string& Header::operator[](const std::string& key) {
    return _headers[key];
}

/**
 * @brief Add a header
 *
 * @param key the key
 * @param value the value
 */
void Header::add(const std::string& key, const std::string& value) {
    _headers[key] = value;
}

/**
 * @brief Remove a header
 *
 * @param key the key
 */
void Header::remove(const std::string& key) {
    _headers.erase(key);
}

/**
 * @brief Clear the headers
 *
 */
void Header::clear() {
    _headers.clear();
}

/**
 * @brief Check if the header exists
 *
 * @param key the key
 * @return true if the header exists
 * @return false otherwise
 */
bool Header::has(const std::string& key) const {
    return _headers.find(key) != _headers.end();
}

/**
 * @brief Get the header
 *
 * @param key the key
 * @return std::string the header
 */
std::string Header::get(const std::string& key) const {
    std::map<std::string, std::string>::const_iterator it = _headers.find(key);
    if (it == _headers.end()) {
        return "";
    }
    return it->second;
}

/**
 * @brief Convert the headers to a string
 *
 * @return std::string the headers as a string
 */
std::string Header::to_string() const {
    std::string str;
    for (std::map<std::string, std::string>::const_iterator it = _headers.begin();
         it != _headers.end(); ++it) {
        str += it->first + ": " + it->second + "\r\n";
    }
    return str;
}
