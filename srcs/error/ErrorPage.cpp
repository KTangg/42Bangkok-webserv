/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorPage.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 21:46:27 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/03 22:44:03 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error/ErrorPage.hpp"

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
const int& ErrorPage::getCode() const {
    return _code;
}

/**
 * @brief Get the Path object
 *
 * @return const std::string& The path to the error page.
 */
const std::string& ErrorPage::getPath() const {
    return _path;
}

/**
 * @brief Get the Error String object
 *
 * @return const std::string& The error string.
 */
const std::string& ErrorPage::getErrorString() const {
    try {
        return ft::httpStatusCodes.at(_code);
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
const std::string& ErrorPage::getErrorPage() const {
    try {
        return _M_readErrorPage();
    } catch (const std::runtime_error& e) {
        return _M_getDefaultErrorPage();
    }
}

/**
 * @brief Read the error page from the file.
 *
 * @return std::string The error page.
 */
std::string ErrorPage::_M_readErrorPage() const {
    std::ifstream file(_path);
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
std::string ErrorPage::_M_getDefaultErrorPage() const {
    std::string errorPage;
    std::string errorString;

    try {
        errorString = ft::httpStatusCodes.at(_code);
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
    errorPage += "<h1>Error " + std::to_string(_code) + "</h1>\n";
    errorPage += "<p>" + errorString + "</p>\n";
    errorPage += "</body>\n";
    errorPage += "</html>\n";

    return errorPage;
}
