/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:36:18 by spoolpra          #+#    #+#             */
/*   Updated: 2024/02/25 15:10:10 by tratanat         ###   ########.fr       */
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

    Logger(const Logger& src);
    Logger(const std::string& name);

    ~Logger();

    void log(LogLevel level, const std::string& message) const;
    void setName(std::string name);

   private:
    Logger();
    Logger& operator=(const Logger& rhs);

    std::string _name;
    const pid_t _pid;
    LogLevel    _level;
    // std::ofstream _logFile;
    std::ostream* _log_stream;
    std::ostream* _log_error_stream;

    void _M_set_log_level();
};

#endif  // __LOGGER_HPP__
