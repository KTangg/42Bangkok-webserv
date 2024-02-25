/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 14:01:37 by spoolpra          #+#    #+#             */
/*   Updated: 2024/02/25 16:24:09 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/Parser.hpp"

/**
 * @brief Construct a new Parser:: Parser object
 *
 * @param file_path the path to the config file
 */
Parser::Parser(const std::string& file_path) : _logger("Parser") {
    // Check if file path available
    _M_check_file_path(file_path);

    // Open file
    std::ifstream file(file_path.c_str());

    // Check if file is open
    _S_check_file(file);

    // Read file
    _M_read_file(file);

    // Close file
    file.close();
}

/**
 * @brief Destroy the Parser:: Parser object
 *
 */
Parser::~Parser() {
}

/**
 * @brief Parse the config file
 *
 */
void Parser::parse() {
    _logger.log(Logger::INFO, "Parsing config file");
    _M_parse();
}

/**
 * @brief Check if file path is valid
 *
 * @param file_path the path to the config file
 */
void Parser::_M_check_file_path(const std::string& file_path) {
    if (file_path.empty()) {
        _logger.log(Logger::ERROR, "Config file path is empty");
        throw std::runtime_error("Config file path is empty");
    }

    if (file_path.find(".conf") == std::string::npos) {
        _logger.log(Logger::ERROR, "Config file path is invalid only .conf files are allowed");
        throw std::runtime_error("Config file path is invalid");
    }

    if (access(file_path.c_str(), F_OK) == -1) {
        _logger.log(Logger::ERROR, "Config file is not accessible");
        throw std::runtime_error("Config file is not accessible");
    }
}

/**
 * @brief Read file and store it in _contents
 *
 * @param file the file to read
 */
void Parser::_M_read_file(std::ifstream& file) {
    std::string line;

    while (std::getline(file, line)) {
        _contents += line + "\n";
    }
}

/**
 * @brief Check if file is open
 *
 * @param file the file to check
 */
void Parser::_S_check_file(std::ifstream& file) {
    if (file.bad()) {
        _logger.log(Logger::ERROR, "Critical error while opening file");
        throw std::runtime_error("Critical error while opening file");
    } else if (!file.is_open()) {
        _logger.log(Logger::ERROR, "Failed to open file");
        throw std::runtime_error("Failed to open file");
    }
}

/**
 * @brief Parse the config file
 *
 */
void Parser::_M_parse() {
    std::string server_block;
    // ServerConfig server_config;

    // Get server blocks
    std::string content = _contents;
    while (content != "") {
        std::string block = _M_get_server_block(content);
        Config      server_config = _M_parse_server_block(block);
        _configs.push_back(server_config);
    }
}

/**
 * @brief Parse value of config file content
 *
 */
std::string Parser::_M_get_server_block(std::string& content) {
    int    level = 0;
    size_t i = 0;

    content = ft::strip_space(content);
    if (content.length() <= 0) {
        return content;
    }
    if (content.find("server") != 0) {
        std::cerr << "Error: invalid configuration" << std::endl;
    }
    content = ft::strip_space(content.substr(6));
    if (content.find('{') != 0) {
        std::cerr << "Error: invalid configuration" << std::endl;
    }

    content = content.substr(1);
    level++;

    while (level > 0 && i < content.length()) {
        if (content[i] == '{') level++;
        if (content[i++] == '}') level--;
    }
    if (level != 0) {
        std::cerr << "Error: invalid configuration" << std::endl;
    }

    std::string block = content.substr(0, i - 2);
    content = content.substr(i);
    return block;
}

/**
 * @brief Create ServerConfig object from server configuration string
 *
 */
Config Parser::_M_parse_server_block(std::string& config) {
    std::cout << "Config parsing: " << config << std::endl;
    return Config(80, "test");
}

/**
 * @brief Return list of configs parsed from file
 *
 * @return std::vector<Config>
 */
std::vector<Config> Parser::getConfigs() {
    return _configs;
}