/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Master.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 10:03:06 by spoolpra          #+#    #+#             */
/*   Updated: 2024/02/25 15:43:08 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/Master.hpp"

/**
 * @brief Construct a new Master:: Master object
 *
 * @param config_file_path Path to the config file
 */
Master::Master(const std::string& config_file_path)
    : _logger("Master"), _config_file_path(config_file_path), _is_running(false) {
    g_master = this;

    std::signal(SIGINT, _S_signal_handler);
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
 * @brief Check if the master is running
 *
 * @return true if the master is running
 * @return false otherwise
 */
bool Master::is_running() const {
    return _is_running;
}

/**
 * @brief Set the is running flag
 *
 * @param is_running true if the master is running
 */
void Master::set_is_running(bool is_running) {
    _is_running = is_running;
}

/**
 * @brief Load the config file and create the workers
 *
 */
void Master::init() {
    _M_load_config();
    _M_create_workers();
}

/**
 * @brief Run the workers
 *
 */
void Master::run() {
    _logger.log(Logger::DEBUG, "Running workers");
    _is_running = true;
    _M_run_workers();

    // Wait for the SIGINT signal
    while (_is_running) {
        sleep(1);
    }

    // Wait for the workers to finish
    _M_wait_for_workers();
}

/**
 * @brief Load the config file
 *
 */
void Master::_M_load_config() {
    Parser parser(_config_file_path);
    parser.parse();
    std::vector<Config> configs = parser.getConfigs();

    for (std::vector<Config>::const_iterator it = configs.begin(); it != configs.end(); ++it) {
        _configs.push_back(*it);
    }

    _logger.log(Logger::DEBUG, "Loaded " + ft::to_string(_configs.size()) + " configs");
}

/**
 * @brief Create the workers
 *
 */
void Master::_M_create_workers() {
    for (std::vector<Config>::iterator it = _configs.begin(); it != _configs.end(); ++it) {
        Worker* worker = new Worker(*it, *this);
        worker->init();

        _workers.push_back(worker);
    }
}

/**
 * @brief Run the workers
 *
 */
void Master::_M_run_workers() {
    for (std::vector<Worker*>::iterator it = _workers.begin(); it != _workers.end(); ++it) {
        pthread_t thread;

        int ret = pthread_create(&thread, NULL, _S_worker_routine, *it);

        if (ret != 0) {
            _logger.log(Logger::ERROR, "Failed to create a worker thread");
        }

        _threads.push_back(thread);
    }
}

/**
 * @brief Wait for the workers to finish
 *
 */
void Master::_M_wait_for_workers() {
    for (std::vector<pthread_t>::iterator it = _threads.begin(); it != _threads.end(); ++it) {
        pthread_join(*it, NULL);
    }
}

/**
 * @brief Worker routine
 *
 * @param arg Pointer to the worker
 * @return void* NULL
 */
void* Master::_S_worker_routine(void* arg) {
    Worker* worker = static_cast<Worker*>(arg);

    worker->run();

    return NULL;
}

/**
 * @brief Signal handler
 *
 * @param signum Signal number
 */
void Master::_S_signal_handler(int signum) {
    if (signum == SIGINT) {
        if (g_master != NULL) {
            g_master->set_is_running(false);
        }
    }
}
