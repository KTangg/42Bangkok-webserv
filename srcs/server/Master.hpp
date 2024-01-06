/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Master.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 22:19:47 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/04 21:45:13 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MASTER_HPP__
#define __MASTER_HPP__

#include <csignal>
#include <string>
#include <thread>
#include <vector>

#include "config/Config.hpp"
#include "parser/Parser.hpp"
#include "server/Worker.hpp"

class Master {
   public:
    Master(const std::string& configFilePath);
    ~Master();

    void init();
    void run();

   private:
    bool              _is_running;
    const std::string _configFilePath;

    std::vector<Config*>      _configs;
    std::vector<Worker*>      _workers;
    std::vector<std::thread*> _threads;

    void _M_loadConfig();
    void _M_runWorker();
    void _M_waitForWorker();

    void _M_signalHandler(int signum);
};

#endif  // MASTER_HPP
