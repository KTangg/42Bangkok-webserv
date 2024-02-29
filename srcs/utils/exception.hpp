/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 21:21:30 by spoolpra          #+#    #+#             */
/*   Updated: 2024/02/29 09:23:07 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __EXCEPTION_HPP__
#define __EXCEPTION_HPP__

#include <exception>
#include <string>

namespace ft {
    class WorkerFatalException : public std::exception {
       public:
        WorkerFatalException(const std::string& msg) throw() : _msg(msg) {
        }
        virtual ~WorkerFatalException() throw() {
        }
        virtual const char* what() const throw() {
            return _msg.c_str();
        }

       private:
        std::string _msg;
    };

    class WorkerNonFatalException : public std::exception {
       public:
        WorkerNonFatalException(const std::string& msg) throw() : _msg(msg) {
        }
        virtual ~WorkerNonFatalException() throw() {
        }
        virtual const char* what() const throw() {
            return _msg.c_str();
        }

       private:
        std::string _msg;
    };

    class InvalidHttpRequest : public std::exception {
       public:
        InvalidHttpRequest(const std::string& msg) throw() : _msg(msg) {
        }
        virtual ~InvalidHttpRequest() throw() {
        }
        virtual const char* what() const throw() {
            return _msg.c_str();
        }

       private:
        std::string _msg;
    };
}  // namespace ft

#endif /* __EXCEPTION_HPP__ */
