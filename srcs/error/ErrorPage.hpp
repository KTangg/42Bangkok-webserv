/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorPage.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 21:25:33 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/06 14:52:47 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ERRORPAGE_HPP__
#define __ERRORPAGE_HPP__

#include <fstream>
#include <string>

#include "utils/status_code.hpp"
#include "utils/utils.hpp"

class ErrorPage {
   public:
    ErrorPage(int code, const std::string& path);
    ~ErrorPage();

    const int&         get_code() const;
    const std::string& get_path() const;
    const std::string  get_error_string() const;

    const std::string get_error_page() const;

   private:
    const int         _code;
    const std::string _path;

    std::string _M_read_error_page() const;
    std::string _M_get_default_error_page() const;
};

#endif /* __ERRORPAGE_HPP__ */
