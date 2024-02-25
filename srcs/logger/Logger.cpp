/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:37:24 by spoolpra          #+#    #+#             */
/*   Updated: 2024/02/25 15:09:58 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "logger/Logger.hpp"

/**
 * @brief Construct a new Logger:: Logger object
 *
 * @param src the object to do the copy
 */
Logger::Logger(const Logger& src) : _name(src._name), _pid(getpid()) {
    _level = src._level;
    _log_stream = src._log_stream;
    _log_error_stream = src._log_error_stream;
}

/**
 * @brief Construct a new Logger:: Logger object
 *
 * @param name the name of the logger
 */
Logger::Logger(const std::string& name) : _name(name), _pid(getpid()) {
    _M_set_log_level();
    _log_stream = &std::cout;
    _log_error_stream = &std::cerr;
}

/**
 * @brief Destroy the Logger:: Logger object
 *
 */
Logger::~Logger() {
    _log_stream = NULL;
    _log_error_stream = NULL;
}

// /**
//  * @brief Construct a new Logger:: Logger object
//  *
//  * @param filename the log file
//  */
// Logger::Logger(const std::string& filename) {
//     _logFile.open(filename);
//     _M_set_log_level();

//     if (_logFile.fail()) {
//         std::cerr
//             << "Failed to open log file. Using stderr for error messages and stdout for other
//             logs."
//             << std::endl;
//         _log_error_stream = &std::cerr;
//         _log_stream = &std::cout;
//     } else {
//         _log_error_stream = &_logFile;
//         _log_stream = &_logFile;
//     }
// }

/**
 * @brief Log a message
 *
 * @param level the log level
 * @param message the message
 */
void Logger::log(LogLevel level, const std::string& message) const {
    if (level < _level) {
        return;
    }

    std::string level_str;

    switch (level) {
        case DEBUG:
            level_str = "DEBUG";
            break;
        case INFO:
            level_str = "INFO";
            break;
        case WARNING:
            level_str = "WARNING";
            break;
        case ERROR:
            level_str = "ERROR";
            break;
    }

    if (level == ERROR) {
        *_log_error_stream << RED_START << "[" << level_str << "] " << ft::to_string(_pid) << " "
                           << _name << " " << message << COLOR_END << std::endl;
    } else {
        *_log_stream << YELLOW_START << "[" << level_str << "] " << ft::to_string(_pid) << " "
                     << _name << " " << message << COLOR_END << std::endl;
    }
}

/**
 * @brief Set the log level
 *
 * @param level the log level
 */
void Logger::_M_set_log_level() {
    const char* env_log_level = std::getenv("LOG_LEVEL");
    if (env_log_level == NULL) {
        _level = INFO;  // Default log level
    } else if (std::string(env_log_level) == "DEBUG") {
        _level = DEBUG;
    } else if (std::string(env_log_level) == "INFO") {
        _level = INFO;
    } else if (std::string(env_log_level) == "WARNING") {
        _level = WARNING;
    } else if (std::string(env_log_level) == "ERROR") {
        _level = ERROR;
    } else {
        std::cerr << "Invalid LOG_LEVEL environment variable. Using INFO as default." << std::endl;
        _level = INFO;
    }
}

void Logger::setName(std::string name) {
    _name = name;
}
