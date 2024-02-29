/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:43:14 by spoolpra          #+#    #+#             */
/*   Updated: 2024/02/29 19:38:47 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/Server.hpp"

/**
 * @brief Construct a new Server:: Server object
 *
 * @param config
 */
Server::Server(const ServerConfig& config) : _config(config), _logger("Server") {
}

/**
 * @brief Destroy the Server:: Server object
 *
 */
Server::~Server() {
}

/**
 * @brief Get the Config object
 *
 * @return const ServerConfig&
 */
const ServerConfig& Server::getConfig() const {
    return _config;
}

/**
 * @brief Check if a given name matches the server
 *
 * @param name Name to match
 * @return true The name matches a server_name configured in server
 * @return false The name doesn't match the server
 */
bool Server::match_name(const std::string& name) const {
    return name == _config.get_name();
}

/**
 * @brief Server request and inject response into the request object
 *
 * @param req HttpRequest object
 */
void Server::serve_request(HttpRequest& req) {
    try {
        const Route& route = _config.get_route(req.get_path());
        std::string  path = req.get_path().substr(route.get_path().length());
        if (path.find("/") != 0) path = "/" + path;
        path = route.get_root_directory() + path;

        req.set_response(serve_static_files(path, req));
        return;
    } catch (std::out_of_range& e) {
        _logger.log(Logger::ERROR, "Route not found: " + req.get_path());
    } catch (std::exception& e) {
        _logger.log(Logger::ERROR, e.what());
        req.set_response(serve_500());
    }

    req.set_response(serve_404());
}

/**
 * @brief Serve static files from given path
 *
 * @param path
 * @param req
 * @return HttpResponse*
 */
HttpResponse* Server::serve_static_files(const std::string& path, HttpRequest& req) {
    std::ifstream file(path.c_str());
    if (file.good() == false) {
        throw std::out_of_range("File not found");
    }
    std::ostringstream oss;
    oss << file.rdbuf();
    std::string content = oss.str();
    std::string content_type = "text/plain";

    // TODO: Refactor mime types
    if (path.rfind(".html") == path.length() - 5) {
        content_type = "text/html";
    }

    return new HttpResponse(200, req.get_connection(), "", content_type, content);
}

HttpResponse* Server::serve_404() {
    // TODO: Proper 404 handling
    return new HttpResponse(404, "File Not Found");
}

HttpResponse* Server::serve_500() {
    // TODO: Proper 500 handling
    return new HttpResponse(500, "Internal Server Error");
}
