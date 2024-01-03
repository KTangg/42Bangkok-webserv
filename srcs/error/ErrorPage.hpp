/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorPage.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 21:25:33 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/03 22:42:50 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ERRORPAGE_HPP__
#define __ERRORPAGE_HPP__

#include <fstream>
#include <string>

#include "utils/statusCode.hpp"

class ErrorPage {
   public:
    ErrorPage(int code, const std::string& path);
    ~ErrorPage();

    const int&         getCode() const;
    const std::string& getPath() const;
    const std::string& getErrorString() const;

    const std::string& getErrorPage() const;

   private:
    const int         _code;
    const std::string _path;

    std::string _M_readErrorPage() const;
    std::string _M_getDefaultErrorPage() const;
};

#endif /* __ERRORPAGE_HPP__ */
