/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 13:48:14 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/06 15:39:03 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include <fstream>
#include <map>
#include <string>
#include <vector>

#include "config/Config.hpp"
#include "logger/Logger.hpp"

class Parser {
   public:
    Parser(const std::string& file_path);
    ~Parser();

    void parse();

   private:
    Logger              _logger;
    std::string         _contents;
    std::vector<Config> _configs;

    void _M_check_file_path(const std::string& file_path);
    void _M_read_file(std::ifstream& file);

    void _S_check_file(std::ifstream& file);

    void _M_parse();
};

#endif /* __PARSER_HPP__ */
