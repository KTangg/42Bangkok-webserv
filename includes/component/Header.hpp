/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Header.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:37:53 by spoolpra          #+#    #+#             */
/*   Updated: 2023/03/07 20:37:10 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef __HEADER_HPP__
# define __HEADER_HPP__


# include "webserv.hpp"

# include "utils/utils.hpp"


typedef std::pair<std::string, std::string>     header_t;
typedef std::map<std::string, std::string>      map_header_t;
typedef map_header_t::iterator                  it_header;
typedef map_header_t::const_iterator            const_it_header;


class Header
{
    public:
        Header();
        Header(const header_t& header);
        Header& operator=(const Header& rhs);

        virtual ~Header();

        bool            addHeader(const header_t& header);
        bool            addHeader(const std::string& line);
        std::string     getHeader(const std::string& key) const;
        void            generateHeader(std::stringstream& ss) const;

    private:
        Header(const Header& rhs);

        std::string     _latest;
        map_header_t    _header;

        bool            _M_add_header(const header_t& header);
        bool            _M_append_value(const std::string& line);

        static header_t _S_parse_header(const std::string& line);
};


#endif
