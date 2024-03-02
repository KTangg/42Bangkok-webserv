/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 14:01:37 by spoolpra          #+#    #+#             */
/*   Updated: 2024/03/02 08:57:01 by tratanat         ###   ########.fr       */
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
    while (ft::strip_space(content) != "") {
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
        _M_throw_invalid_config();
    }

    std::string block = content.substr(0, i - 2);
    content = content.substr(i);
    return block;
}

std::vector<std::pair<std::string, std::string> > Parser::_M_parse_generic_block(
    std::string& config) {
    size_t current_start = 0;
    size_t cur = 0;
    int    nested_level = 0;

    std::vector<std::pair<std::string, std::string> > config_map;
    while (cur < config.length()) {
        if (config[cur] == '{')
            nested_level++;
        else if (config[cur] == '}')
            nested_level--;

        if (nested_level == 0 && (config[cur] == ';' || config[cur] == '}')) {
            std::pair<std::string, std::string> entry =
                ft::split_config(config.substr(current_start, cur - current_start));
            config_map.push_back(entry);
            current_start = cur + 1;
        }
        cur++;
    }
    if (current_start < config.length() &&
        ft::strip_space(config.substr(current_start + 1)).length() > 0) {
        _M_throw_invalid_config();
    }
    return config_map;
}

/**
 * @brief Create ServerConfig object from server configuration string
 *
 */
Config Parser::_M_parse_server_block(std::string& config) {
    std::string                  host = DEFAULT_HOST;
    std::string                  server_name_params;
    std::vector<std::string>     route_configs;
    std::map<std::string, Route> routes;
    std::vector<ServerConfig>    server_configs;
    std::string                  root;
    int                          port = -1;
    int                          timeout = DEFAULT_TIMEOUT;
    size_t                       max_body_size = DEFAULT_MAX_BODY_SIZE;
    std::map<int, ErrorPage>     error_pages = ft::initialize_error_pages();

    std::vector<std::pair<std::string, std::string> > config_map = _M_parse_generic_block(config);
    for (std::vector<std::pair<std::string, std::string> >::iterator it = config_map.begin();
         it != config_map.end(); it++) {
        if (it->first == "listen") {
            port = atoi(&(it->second[0]));
        } else if (it->first == "server_name") {
            server_name_params = it->second;
        } else if (it->first == "location") {
            route_configs.push_back(it->second);
        } else if (it->first == "host") {
            host = it->second;
        } else if (it->first == "root") {
            root = it->second;
        } else if (it->first == "request_timeout") {
            timeout = atoi(&(it->second[0]));
        } else if (it->first == "client_max_body_size") {
            max_body_size = atoi(&(it->second[0])) * 1024;
        } else if (it->first == "error_page") {
            std::vector<std::string>           error_page = ft::split_whitespace(it->second);
            int                                error_code = atoi(&(error_page[0][0]));
            std::map<int, ErrorPage>::iterator it = error_pages.find(error_code);
            if (it != error_pages.end()) error_pages.erase(it);
            ErrorPage page = ErrorPage(error_code, error_page[1]);
            error_pages.insert(std::pair<int, ErrorPage>(atoi(&(error_page[0][0])), page));
        }
    }

    Config rtn(port, host);

    for (std::vector<std::string>::iterator it = route_configs.begin(); it != route_configs.end();
         it++) {
        Route       route = _M_parse_route_block(*it, root);
        std::string path = route.get_path();
        routes.insert(std::pair<std::string, Route>(path, route));
    }

    std::vector<std::string> server_names = ft::split_whitespace(host);
    for (std::vector<std::string>::iterator it = server_names.begin(); it != server_names.end();
         it++) {
        rtn.add_server_config(ServerConfig(routes, *it, max_body_size, error_pages, timeout));
    }

    return rtn;
}

/**
 * @brief Parse location block inside the server config
 *
 * @param config The raw text of the location block
 * @param root Root set in the server block if not overridden in location block
 * @return Route
 */
Route Parser::_M_parse_route_block(std::string& config, std::string root) {
    std::string                path = "";
    std::string                root_directory = "";
    std::vector<std::string>   methods = ft::initialize_methods();
    std::string                redirect_path = "";
    bool                       directory_listing = false;
    std::vector<std::string>   index_files = ft::initialize_index_files();
    std::string                upload_directory = "";
    std::map<std::string, Cgi> cgi_extensions = std::map<std::string, Cgi>();

    cgi_extensions.insert(std::pair<std::string, Cgi>("php", Cgi("php-cgi", "php")));

    const size_t end_pos = config.find('{');
    if (end_pos == std::string::npos || end_pos >= config.length()) _M_throw_invalid_config();

    path = config.substr(0, end_pos - 1);
    path = ft::strip_space(path);
    std::string block = config.substr(end_pos + 1);

    std::vector<std::pair<std::string, std::string> > config_map = _M_parse_generic_block(block);
    for (std::vector<std::pair<std::string, std::string> >::iterator it = config_map.begin();
         it != config_map.end(); it++) {
        if (it->first == "root") {
            root_directory = it->second;
        } else if (it->first == "index") {
            index_files = ft::split_whitespace(it->second);
        } else if (it->first == "methods_allowed") {
            methods = ft::split_whitespace(it->second);
        } else if (it->first == "redirect_path") {
            redirect_path = it->second;
        } else if (it->first == "upload_directory") {
            upload_directory = it->second;
        } else if (it->first == "directory_listing") {
            directory_listing = it->second == "on";
        } else if (it->first == "cgi") {
            std::vector<std::string> cgi_values = ft::split_whitespace(it->second);
            if (cgi_values.size() != 2) _M_throw_invalid_config();
            cgi_extensions.insert(
                std::pair<std::string, Cgi>(cgi_values[0], Cgi(cgi_values[1], cgi_values[0])));
        }
    }
    if (root_directory.empty()) root_directory = root;
    return Route(path, root_directory, methods, redirect_path, directory_listing, index_files,
                 upload_directory, cgi_extensions);
}

/**
 * @brief Utils method to throw exception on error parsing configuration file
 *
 */
void Parser::_M_throw_invalid_config() {
    throw std::invalid_argument("invalid configuration file");
}

/**
 * @brief Return list of configs parsed from file
 *
 * @return std::vector<Config>
 */
std::vector<Config> Parser::getConfigs() {
    return _configs;
}