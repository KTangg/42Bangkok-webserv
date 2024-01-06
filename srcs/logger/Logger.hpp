/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:36:18 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/06 14:52:10 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__

// #include <fstream>
#include <unistd.h>

#include <cstdlib>
#include <iostream>
#include <string>

#include "utils/utils.hpp"

#define RED_START "\033[31m"
#define YELLOW_START "\033[33m"
#define COLOR_END "\033[0m"

class Logger {
   public:
    enum LogLevel { DEBUG, INFO, WARNING, ERROR };
    Logger();
    Logger(const std::string& name);
    ~Logger();

    void setName(const std::string& name);
    // Logger(const std::string& filename);

    void log(LogLevel level, const std::string& message);

   private:
    pid_t       _pid;
    std::string _name;
    LogLevel    _level;
    // std::ofstream _logFile;
    std::ostream* _logStream;
    std::ostream* _logErrorStream;

    void _M_setLogLevel();
};

#endif  // __LOGGER_HPP__
