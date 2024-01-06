/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:37:24 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/06 14:29:00 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "logger/Logger.hpp"

/**
 * @brief Construct a new Logger:: Logger object
 *
 */
Logger::Logger() {
    _pid = getpid();
    _M_setLogLevel();
    _logStream = &std::cout;
    _logErrorStream = &std::cerr;
}

/**
 * @brief Construct a new Logger:: Logger object
 *
 * @param name the name of the logger
 */
Logger::Logger(const std::string& name) {
    _pid = getpid();
    _M_setLogLevel();
    _name = name;
    _logStream = &std::cout;
    _logErrorStream = &std::cerr;
}

/**
 * @brief Destroy the Logger:: Logger object
 *
 */
Logger::~Logger() {
    _logStream = NULL;
    _logErrorStream = NULL;
}

/**
 * @brief Set the name of the logger
 *
 * @param name the name of the logger
 */
void Logger::setName(const std::string& name) {
    _name = name;
}

// /**
//  * @brief Construct a new Logger:: Logger object
//  *
//  * @param filename the log file
//  */
// Logger::Logger(const std::string& filename) {
//     _logFile.open(filename);
//     _M_setLogLevel();

//     if (_logFile.fail()) {
//         std::cerr
//             << "Failed to open log file. Using stderr for error messages and stdout for other
//             logs."
//             << std::endl;
//         _logErrorStream = &std::cerr;
//         _logStream = &std::cout;
//     } else {
//         _logErrorStream = &_logFile;
//         _logStream = &_logFile;
//     }
// }

/**
 * @brief Log a message
 *
 * @param level the log level
 * @param message the message
 */
void Logger::log(LogLevel level, const std::string& message) {
    if (level < _level) {
        return;
    }

    std::string levelStr;

    switch (level) {
        case DEBUG:
            levelStr = "DEBUG";
            break;
        case INFO:
            levelStr = "INFO";
            break;
        case WARNING:
            levelStr = "WARNING";
            break;
        case ERROR:
            levelStr = "ERROR";
            break;
    }

    if (level == ERROR) {
        *_logErrorStream << RED_START << "[" << levelStr << "] " << ft::to_string(_pid) << " "
                         << _name << " " << message << COLOR_END << std::endl;
    } else {
        *_logStream << YELLOW_START << "[" << levelStr << "] " << ft::to_string(_pid) << " "
                    << _name << " " << message << COLOR_END << std::endl;
    }
}

/**
 * @brief Set the log level
 *
 * @param level the log level
 */
void Logger::_M_setLogLevel() {
    const char* envLogLevel = std::getenv("LOG_LEVEL");
    if (envLogLevel == NULL) {
        _level = INFO;  // Default log level
    } else if (std::string(envLogLevel) == "DEBUG") {
        _level = DEBUG;
    } else if (std::string(envLogLevel) == "INFO") {
        _level = INFO;
    } else if (std::string(envLogLevel) == "WARNING") {
        _level = WARNING;
    } else if (std::string(envLogLevel) == "ERROR") {
        _level = ERROR;
    } else {
        std::cerr << "Invalid LOG_LEVEL environment variable. Using INFO as default." << std::endl;
        _level = INFO;
    }
}
