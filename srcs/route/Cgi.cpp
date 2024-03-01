/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 20:24:58 by spoolpra          #+#    #+#             */
/*   Updated: 2024/03/01 23:36:28 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "route/Cgi.hpp"

/**
 * @brief Construct a new Cgi:: Cgi object
 *
 * @param src The object to do the copy.
 */
Cgi::Cgi(const Cgi& src) : _path(src._path), _extension(src._extension) {
}

/**
 * @brief Construct a new cgi::cgi object
 *
 * @param path The path to the CGI executable.
 * @param extension The extension of the CGI executable.
 */
Cgi::Cgi(const std::string& path, const std::string& extension)
    : _path(path), _extension(extension) {
}

/**
 * @brief Destroy the cgi::cgi object
 *
 */
Cgi::~Cgi() {
    // TODO: Make sure to clean up the child process in case of timeout.
}

/**
 * @brief Returns the path to the CGI executable.
 *
 * @return const std::string& The path to the CGI executable.
 */
const std::string& Cgi::get_path() const {
    return _path;
}

/**
 * @brief Returns the extension of the CGI executable.
 *
 * @return const std::string& The extension of the CGI executable.
 */
const std::string& Cgi::get_extension() const {
    return _extension;
}

/**
 * @brief Fork the process to execute the CGI script and pipe back the output.
 *
 * @param filepath Path of the script file requested.
 */
void Cgi::execute(const std::string& filepath) {
    pipe(_pipefd);
    (void)filepath;

    char* argv[] = {const_cast<char*>(_path.c_str()), const_cast<char*>(filepath.c_str()), NULL};
    char* envp[] = {const_cast<char*>("REDIRECT_STATUS="), const_cast<char*>("PATH_INFO=/"), NULL};

    _child_pid = fork();
    if (_child_pid == -1) {
        throw std::runtime_error("fork failed");
    } else if (_child_pid == 0) {
        close(_pipefd[0]);
        dup2(_pipefd[1], 1);
        dup2(_pipefd[1], 2);
        close(_pipefd[1]);
        execve(argv[0], argv, envp);
        perror("CGI failed");
        exit(EXIT_FAILURE);
    } else {
        close(_pipefd[1]);
    }
}

/**
 * @brief Check whether the child process has finished executing the CGI script.
 * Read the output from the pipe and store it in the content.
 *
 * @return true The child process has finished executing the CGI script.
 * @return false
 */
bool Cgi::_M_check_child() {
    pid_t pid = waitpid(_child_pid, NULL, WNOHANG);
    if (pid < 0) throw std::runtime_error("waitpid failed");
    if (pid == 0) return false;

    char buffer[4096];
    int  n;
    while ((n = read(_pipefd[0], buffer, 4096)) > 0) {
        _content.append(buffer, n);
    }
    close(_pipefd[0]);
    if (n < 0) throw std::runtime_error("read failed");
    return true;
}

/**
 * @brief Check whether the CGI execution has completed and the content has been retrieved.
 *
 * @return true The CGI execution has completed.
 * @return false
 */
bool Cgi::is_ready() {
    bool ready = _M_check_child();
    return ready;
}

/**
 * @brief Get the content of the CGI execution.
 *
 * @return const std::string& Result
 */
const std::string& Cgi::get_content() const {
    return _content;
}
