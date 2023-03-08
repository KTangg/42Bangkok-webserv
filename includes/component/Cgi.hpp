/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 23:03:24 by spoolpra          #+#    #+#             */
/*   Updated: 2023/03/03 23:28:15 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef __CGI_HPP__
# define __CGI_HPP__


# include "webserv.hpp"


class Cgi
{
    public:

    private:
};


typedef std::map<std::string, Cgi>      map_cgi_t;
typedef map_cgi_t::iterator             iterator_cgi;
typedef map_cgi_t::const_iterator       const_iterator_cgi;


#endif
