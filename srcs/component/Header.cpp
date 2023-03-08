/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Header.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 18:04:15 by spoolpra          #+#    #+#             */
/*   Updated: 2023/03/08 17:34:15 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "component/Header.hpp"

#include "utils/HttpExceoption.hpp"


/**
 * @brief Construct a new Header:: Header object
 *
 */
Header::Header() : _latest(), _header() { }


/**
 * @brief Construct a new Header:: Header object
 *
 * @param header pair of header (key, value)
 */
Header::Header(const header_t& header) : _latest(), _header()
{
    _M_add_header(header);
}


/**
 * @brief Set left hand side to be equal as right hand side
 *
 * @param rhs right hand side object
 * @return Header& copied object
 */
Header& Header::operator=(const Header& rhs)
{
    _latest = rhs._latest;
    _header = rhs._header;

    return *this;
}


/**
 * @brief Destroy the Header:: Header object
 *
 */
Header::~Header() { }


/**
 * @brief Add new header
 *
 * @param header pair of header (key, value)
 * @return true if key add, otherwise false
 */
bool    Header::addHeader(const header_t& header)
{
    bool add = _M_add_header(header);

    return add;
}


/**
 * @brief Parse line to (key: value) and add to Header
 * if line start with space value will be append to latest header
 *
 * @param line string to be parsed
 * @return true if new key, value is appended
 * @exception May thrown ft::HttpException on duplicate case
 */
bool    Header::addHeader(const std::string& line)
{
    bool ret;

    try
    {
        header_t header = _S_parse_header(line);

        ret = _M_add_header(header);

        if (ret == false)
        {
            throw ft::HttpException(HTTP_BAD_REQUEST);
        }
        return ret;
    }
    catch (const std::invalid_argument&)
    {
        ret = _M_append_value(line);

        return ret;
    }
    catch (const std::out_of_range&)
    {
        _latest.clear();
        return false;
    }
}


/**
 * @brief Get value according to given key
 *
 * @param key header key to search
 * @return std::string header value
 * @exception std::out_of_range thrown when key not exist
 */
std::string Header::getHeader(const std::string& key) const
{
    return _header.at(ft::tolower(key));
}


/**
 * @brief Append header to string stream in "Key: value/r/n" format
 * then add "/r/n" to end the header section
 *
 * @param ss std::stringstream to appennd header string to
 */
void    Header::generateHeader(std::stringstream& ss) const
{
    for (const_it_header it = _header.begin(); it != _header.end(); ++it)
    {
        ss << ft::capitalize(it->first) << HEADER_SEP << it->second << CRLF;
    }
    ss << CRLF;
}



bool    Header::_M_add_header(const header_t& header)
{
    header_t lower_header(ft::tolower(header.first), header.second);

    std::pair<it_header, bool> ret = _header.insert(lower_header);

    if (ret.second)
    {
        _latest = lower_header.first;
    }

    return ret.second;
}


bool    Header::_M_append_value(const std::string& line)
{
    if (line.empty() || _latest.empty())
    {
        _latest.clear();
        return false;
    }
    else if (line[0] != '\t' && line[0] != ' ')
    {
        _latest.clear();
        return false;
    }

    std::string value = ft::skip_ws(line);

    if (value.empty())
    {
        _latest.clear();
        return false;
    }

    std::string& prev = _header.at(_latest);
    prev = prev + " " + value;

    return true;
}


header_t    Header::_S_parse_header(const std::string& line)
{
    if (line.empty() || line[0] == ' ' || line[0] == '\t')
    {
        throw std::invalid_argument("Header line is empty");
    }

    size_t  sep = line.find(HEADER_SEP);

    if (sep == std::string::npos)
    {
        throw std::out_of_range("Header is not on \"Key: value\" format");
    }

    std::string key = line.substr(0, sep);
    std::string value = line.substr(sep + std::strlen(HEADER_SEP));

    return header_t(key, value);
}
