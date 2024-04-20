/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorPage.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 21:46:27 by spoolpra          #+#    #+#             */
/*   Updated: 2024/04/07 14:21:10 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error/ErrorPage.hpp"

/**
 * @brief Construct a new Error Page:: Error Page object
 *
 * @param src
 */
ErrorPage::ErrorPage(const ErrorPage& src) {
    *this = src;
}

/**
 * @brief Copy this object.
 *
 * @param rhs The object to copy.
 * @return ErrorPage& A reference to the copied object.
 */
ErrorPage& ErrorPage::operator=(const ErrorPage& rhs) {
    if (this != &rhs) {
        _code = rhs._code;
        _path = rhs._path;
    }
    return *this;
}

/**
 * @brief Construct a new ErrorPage:: ErrorPage object
 *
 * @param code The code of the error page.
 * @param path The path to the error page.
 */
ErrorPage::ErrorPage(int code, const std::string& path) : _code(code), _path(path) {
}

/**
 * @brief Destroy the ErrorPage:: ErrorPage object
 */
ErrorPage::~ErrorPage() {
}

/**
 * @brief Get the Code object
 *
 * @return const int& The code of the error page.
 */
const int& ErrorPage::get_code() const {
    return _code;
}

/**
 * @brief Get the Path object
 *
 * @return const std::string& The path to the error page.
 */
const std::string& ErrorPage::get_path() const {
    return _path;
}

/**
 * @brief Set the Code object
 *
 * @param code The code of the error page.
 */
void ErrorPage::set_code(const int& code) {
    _code = code;
}

/**
 * @brief Set the Path object
 *
 * @param path The path to the error page.
 */
void ErrorPage::set_path(const std::string& path) {
    _path = path;
}

/**
 * @brief Get the Error String object
 *
 * @return const std::string& The error string.
 */
const std::string ErrorPage::get_error_string() const {
    try {
        return ft::http_status_codes.at(_code);
    } catch (const std::out_of_range& e) {
        // Return internal server error incase of invalid code
        return UNDEFINED_ERROR;
    }
}

/**
 * @brief Get the Error Page object
 *
 * @return const std::string& The error page.
 */
const std::string ErrorPage::get_error_page() const {
    try {
        return _M_read_error_page();
    } catch (const std::runtime_error& e) {
        return _M_get_default_error_page();
    }
}

/**
 * @brief Read the error page from the file.
 *
 * @return std::string The error page.
 */
std::string ErrorPage::_M_read_error_page() const {
    std::ifstream file(_path.c_str());
    std::string   line;
    std::string   errorPage;

    if (file.fail()) {
        if (file.bad()) {
            throw std::runtime_error("ErrorPage: Critical error while opening file.");
        } else if (!file.is_open()) {
            throw std::runtime_error("ErrorPage: Failed to open file.");
        } else {
            throw std::runtime_error("ErrorPage: Unknown error while opening file.");
        }
    }

    while (std::getline(file, line)) {
        errorPage += line + "\n";
    }

    file.close();

    return errorPage;
}

/**
 * @brief Get the default error page.
 *
 * @return std::string The default error page.
 */
std::string ErrorPage::_M_get_default_error_page() const {
    std::string errorPage;
    std::string errorString;

    try {
        errorString = ft::http_status_codes.at(_code);
    } catch (const std::out_of_range& e) {
        // Return Undefined error incase of invalid code
        errorString = UNDEFINED_ERROR;
    }

    errorPage += "<!DOCTYPE html>\n";
    errorPage += "<html lang=\"en\">\n";
    errorPage += "<head>\n";
    errorPage += "<meta charset=\"UTF-8\">\n";
    errorPage += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
    errorPage += "<title>Error</title>\n";
    errorPage += "</head>\n";
    errorPage += "<body>\n";
    errorPage += "<h1>Error " + ft::to_string(_code) + "</h1>\n";
    errorPage += "<p>" + errorString + "</p>\n";
    errorPage += "</body>\n";
    errorPage += "</html>\n";

    return errorPage;
}
