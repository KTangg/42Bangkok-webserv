/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpExceoption.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:05:57 by spoolpra          #+#    #+#             */
/*   Updated: 2023/03/07 20:43:06 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef __HTTP_EXCEPTION_HPP__
# define __HTTP_EXCEPTION_HPP__


# include "webserv.hpp"

# include "utils/utils.hpp"
# include "component/Header.hpp"


namespace ft
{
    class HttpException : public std::exception
    {
        public:
            HttpException(
                const http_status_t&    status,
                const std::string&      server,
                const Header&           header = Header(),
                const std::string&      content = ""
                );
            HttpException(const HttpException& rhs);
            HttpException& operator=(const HttpException& rhs);

            virtual ~HttpException() throw();

            int     getCode() const;
            void    send(const int socket) const;

        private:
            HttpException();

            int             _code;
            std::string     _description;
            std::string     _server;
            Header          _header;
            std::string     _content;
    };
}


#endif
