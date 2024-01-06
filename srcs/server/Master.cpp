/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Master.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 10:03:06 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/06 13:51:30 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/Master.hpp"

/**
 * @brief Construct a new Master:: Master object
 *
 * @param configFilePath the path to the config file
 */
Master::Master(const std::string& configFilePath) {
    this->_is_running = false;
    this->_configFilePath = configFilePath;

    // Handler sigint to gracfelly exit
    std::signal(SIGINT, _M_signalHandler);
}

/**
 * @brief Destroy the Master:: Master object
 *
 */
Master::~Master() {
    for (std::vector<Worker*>::iterator it = _workers.begin(); it != _workers.end(); ++it) {
        delete *it;
    }
}

/**
 * @brief Construct workers from config file
 *
 */
void Master::init() {
    _M_loadConfig();

    for (std::vector<Config*>::iterator it = _configs.begin(); it != _configs.end(); ++it) {
        _workers.push_back(new Worker(it, *this));
    }
}

/**
 * @brief Run each worker in a thread
 *
 */
void Master::run() {
    _M_runWorker();

    while (_is_running) {
        sleep(1);
    }

    _M_waitForWorker();
}

/**
 * @brief Load config file and create config objects
 *
 */
void Master::_M_loadConfig() {
    Parser parser(_configFilePath);
    parser.parse();

    std::vector<Config*> configs = parser.getConfigs();
    for (std::vector<Config*>::iterator it = configs.begin(); it != configs.end(); ++it) {
        _configs.push_back(*it);
    }
}

/**
 * @brief Run each worker in a thread, change _is_running to true
 *
 */
void Master::_M_runWorker() {
    this->_is_running = true;

    for (std::vector<Worker*>::iterator it = _workers.begin(); it != _workers.end(); ++it) {
        if (_is_running == false) {
            break;
        }
        std::thread workerThread(&Worker::run, *it);
        _threads.push_back(&workerThread);
    }
}

/**
 * @brief Wait for each worker thread to finish
 *
 */
void Master::_M_waitForWorker() {
    for (std::vector<std::thread*>::iterator it = _threads.begin(); it != _threads.end(); ++it) {
        if ((*it)->joinable()) {
            (*it)->join();
        }
    }
}

/**
 * @brief Handle SIGINT signal
 *
 * @param signum the signal number
 */
void Master::_M_signalHandler(int signum) {
    if (signum == SIGINT) {
        _is_running = false;
    }
}
