/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 13:48:14 by spoolpra          #+#    #+#             */
/*   Updated: 2024/02/29 18:26:16 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include <cctype>
#include <exception>
#include <fstream>
#include <map>
#include <string>
#include <vector>

#include "config/Config.hpp"
#include "logger/Logger.hpp"
#include "route/Route.hpp"
#include "utils/utils.hpp"

class Parser {
   public:
    Parser(const std::string& file_path);
    ~Parser();

    void                parse();
    std::vector<Config> getConfigs();

   private:
    Logger              _logger;
    std::string         _contents;
    std::vector<Config> _configs;

    void _M_check_file_path(const std::string& file_path);
    void _M_read_file(std::ifstream& file);

    void _S_check_file(std::ifstream& file);

    void                                              _M_parse();
    std::string                                       _M_get_server_block(std::string& content);
    std::vector<std::pair<std::string, std::string> > _M_parse_generic_block(std::string& config);
    Config                                            _M_parse_server_block(std::string& config);
    Route _M_parse_route_block(std::string& config, std::string root);
    void  _M_throw_invalid_config();
};

#endif /* __PARSER_HPP__ */
