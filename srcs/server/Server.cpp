/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:43:14 by spoolpra          #+#    #+#             */
/*   Updated: 2024/03/01 09:39:26 by tratanat         ###   ########.fr       */
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
    HttpResponse* response = 0;

    try {
        const Route& route = _config.get_route(req.get_path());
        std::string  path = req.get_path().substr(route.get_path().length());

        if (!route.is_method_allowed(req.get_method())) {
            req.set_response(serve_405());
            return;
        }

        if (path.find("/") != 0) path = "/" + path;
        path = route.get_root_directory() + path;

        if (req.get_method() == "GET") {
            response = serve_get_response(path, route, req);
        } else if (req.get_method() == "POST") {
            response = serve_post_response(path, route, req);
        } else if (req.get_method() == "DELETE") {
            response = serve_delete_response(path, route, req);
        } else {
            _logger.log(Logger::ERROR, "Unsupported method: " + req.get_method());
            response = serve_405();
        }
    } catch (std::out_of_range& e) {
        _logger.log(Logger::ERROR, "Route not found: " + req.get_path());
    } catch (std::exception& e) {
        _logger.log(Logger::ERROR, e.what());
        response = serve_500();
    }

    if (!response) {
        response = serve_404();
    }
    req.set_response(response);
}

/**
 * @brief Serve a GET request
 *
 * @param path Request path
 * @param route Route object to process request
 * @param req Request object
 * @return HttpResponse* Response
 */
HttpResponse* Server::serve_get_response(std::string path, Route route, HttpRequest& req) {
    // Append index files if needed
    if (path.end()[-1] == '/') {
        // TODO: Handle directory listing here
        const std::vector<std::string>& index_files = route.get_index_files();
        for (std::vector<std::string>::const_iterator it = index_files.begin();
             it != index_files.end(); it++) {
            std::string   index_path = path + *it;
            std::ifstream file(index_path.c_str());
            if (file.good()) {
                path = index_path;
                break;
            }
        }
    }
    return serve_static_files(path, req);
}

/**
 * @brief Serve a POST request
 *
 * @param path Request path
 * @param route Route object to process request
 * @param req Request object
 * @return HttpResponse*
 */
HttpResponse* Server::serve_post_response(std::string path, Route route, HttpRequest& req) {
    (void)route;
    size_t pos = path.find_last_of(".");
    if (path.end()[-1] == '/' || pos == std::string::npos) {
        throw std::out_of_range("File not found");
    }
    std::string                                        extension = path.substr(pos);
    std::map<std::string, std::string>::const_iterator mime_type = ft::mime_types.find(extension);
    if (mime_type == ft::mime_types.end()) {
        throw std::out_of_range("File not found");
    }
    pos = path.find_last_of("/");
    if (pos == std::string::npos) {
        throw std::out_of_range("File not found");
    }
    // std::string filename = path.substr(pos + 1);
    std::string filepath = path.substr(0, pos);
    struct stat info;
    if (stat(filepath.c_str(), &info) != 0) {
        throw std::out_of_range("File not found");
    }

    std::ofstream file;
    file.open(path.c_str());
    file << req.get_content();
    file.close();
    return serve_201();
}

/**
 * @brief Serve a DELETE request
 *
 * @param path Request path
 * @param route Route object to process request
 * @param req Request object
 * @return HttpResponse*
 */
HttpResponse* Server::serve_delete_response(std::string path, Route route, HttpRequest& req) {
    (void)route;
    (void)req;
    struct stat info;
    if (stat(path.c_str(), &info) != 0) {
        throw std::out_of_range("File not found");
    }
    std::remove(path.c_str());
    return serve_204();
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
    std::string content_type = DEFAULT_MIME_TYPE;

    std::string extension = path.substr(path.find_last_of("."));
    std::map<std::string, std::string>::const_iterator mime_type = ft::mime_types.find(extension);
    if (mime_type != ft::mime_types.end()) {
        content_type = mime_type->second;
    }

    return new HttpResponse(200, req.get_connection(), "", content_type, content);
}

HttpResponse* Server::serve_201() {
    // TODO: Proper 201 handling
    return new HttpResponse(201, "Created");
}

HttpResponse* Server::serve_204() {
    // TODO: Proper 204 handling
    return new HttpResponse(204, "Deleted");
}

HttpResponse* Server::serve_404() {
    // TODO: Proper 404 handling
    return new HttpResponse(404, "File Not Found");
}

HttpResponse* Server::serve_405() {
    // TODO: Proper 405 handling
    return new HttpResponse(405, "Method not allowed");
}

HttpResponse* Server::serve_500() {
    // TODO: Proper 500 handling
    return new HttpResponse(500, "Internal Server Error");
}
