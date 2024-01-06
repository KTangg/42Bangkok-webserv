/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 21:21:30 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/04 21:52:26 by spoolpra         ###   ########.fr       */
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
}  // namespace ft

#endif /* __EXCEPTION_HPP__ */
