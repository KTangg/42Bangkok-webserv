/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorPage.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 21:25:33 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/07 00:22:07 by spoolpra         ###   ########.fr       */
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
    ErrorPage(const ErrorPage& src);
    ErrorPage& operator=(const ErrorPage& rhs);

    ErrorPage(int code, const std::string& path);

    ~ErrorPage();

    const int&         get_code() const;
    const std::string& get_path() const;

    void set_code(const int& code);
    void set_path(const std::string& path);

    const std::string get_error_string() const;
    const std::string get_error_page() const;

   private:
    ErrorPage();

    int         _code;
    std::string _path;

    std::string _M_read_error_page() const;
    std::string _M_get_default_error_page() const;
};

#endif /* __ERRORPAGE_HPP__ */
