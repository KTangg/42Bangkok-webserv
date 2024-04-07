/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Master.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 22:19:47 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/07 02:25:18 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MASTER_HPP__
#define __MASTER_HPP__

#include <pthread.h>

#include <csignal>
#include <string>
#include <vector>

#include "config/Config.hpp"
#include "logger/Logger.hpp"
#include "parser/Parser.hpp"
#include "server/Worker.hpp"

class Master {
   public:
    Master(const std::string& config_file_path);

    ~Master();

    bool is_running() const;

    void set_is_running(bool is_running);

    int  init();
    void run();

   private:
    Master();
    Master(const Master& src);
    Master& operator=(const Master& rhs);

    const Logger      _logger;
    const std::string _config_file_path;

    bool                   _is_running;
    std::vector<Config>    _configs;
    std::vector<Worker*>   _workers;
    std::vector<pthread_t> _threads;

    void _M_load_config();
    int  _M_create_workers();
    void _M_run_workers();
    void _M_wait_for_workers();

    static void* _S_worker_routine(void* arg);
    static void  _S_signal_handler(int signum);
};

extern Master* g_master;

#endif  // MASTER_HPP
