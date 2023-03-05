/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 23:43:36 by spoolpra          #+#    #+#             */
/*   Updated: 2023/03/05 17:36:05 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "component/Request.hpp"


Request::Request(const bytestring& bstr)
: _request(),
  _method(),
  _path(),
  _server(),
  _header(),
  _header_end(),
  _header_size(),
  _latest_header()
{ 
    _request = new bytestream(bstr);
}


Request::Request(const Request& rhs)
{
    *this = rhs;
}


Request&    Request::operator=(const Request& rhs)
{
    _request = new bytestream(rhs._request->str());
    _method = rhs._method;
    _path = rhs._path;
    _server = rhs._server;
    _header = rhs._header;
    _header_end = rhs._header_end;
    _header_size = rhs._header_size;
    _latest_header = rhs._latest_header;

    return *this;
}


Request::~Request() 
{
    delete _request;
}


bytestream*  Request::getRequest() const
{
    return _request;
}


void    Request::appendRequest(const bytestring& new_byte)
{
    _request->clear();
    _request->seekp(0, std::ios::end);
    _request->write(new_byte.c_str(), new_byte.size());
}


bool    Request::isRequestLine() const
{
    return !(_method.empty() || _path.empty());
}


void    Request::processRequestLine()
{
    bytestring      line;
    std::string     line_str;
    bytepos         before_pos;
    bytepos         new_pos;

    while (true)
    {
        before_pos = _request->tellg();
        std::getline(*_request, line, CHAR_TO_BYYE('\n'));

        line_str = BYTES_TO_STR(line.c_str());
        if (!line_str.compare("\r") || line_str.empty())
        {
            if (_request->eof())
            {
                _request->clear();
                _request->seekg(before_pos);
                return ;
            }
            continue;
        }
        else
        {
            break;
        }
    }
    if (!std::isupper(line_str[0]))
    {
        std::cerr << "Request Line not start with upper" << std::endl;
        throw ft::HttpException(HTTP_BAD_REQUEST);
    }
    l_str_t l_content = ft::split(line, CHAR_TO_BYYE(' '), CHAR_TO_BYYE('\t'));
    
    if (_request->eof())
    {
        _S_validate_request_line(l_content);
        _request->clear();
        _request->seekg(before_pos);
    }
    else
    {
        if (!_S_validate_request_line(l_content))
        {
            std::cerr << "Incomplete Request status" << std::endl;
            throw ft::HttpException(HTTP_BAD_REQUEST);
        }
        _method = l_content[0];
        _path = l_content[1];
    }
}


bool    Request::isHeaderEnd() const
{
    return _header_end;
}


void    Request::processHeader()
{
    bytestring      line;
    bytepos         before_pos;
    
    while (true)
    {
        before_pos = _request->tellg();
        std::getline(*_request, line, CHAR_TO_BYYE('\n'));
        std::string line_str = BYTES_TO_STR(line.c_str());
    
        if (_request->eof())
        {
            _request->clear();
            _request->seekg(before_pos);
            _M_process_header(line_str, false);
            break;
        }
        else if (!line_str.compare("\r") || line_str.empty())
        {
            try
            {
                _header.at(HEADER_HOST);
            }
            catch (const std::out_of_range&)
            {
                std::cerr << "Missing HOST header" << std::endl;
                throw ft::HttpException(HTTP_BAD_REQUEST);
            }
            _header_end = true;
            break;
        }
        else
        {
            _M_process_header(line_str, true);
        }
    }
}


void    Request::_M_process_header(const std::string& str, bool insert)
{
    size_t  str_size = str.size();
    if (_header_size + str_size > DEFAULT_HTTP_LIMIT)
    {
        std::cerr << "Too Large header" << std::endl;
        throw ft::HttpException(HTTP_BAD_REQUEST);
    }

    if (str[0] == ' ' || str[0] == '\t')
    {
        std::string     value = ft::skip_ws(str);
        if (!_latest_header.empty())
        {
            if (insert)
            {
                _header_size = _header_size + str_size;
                try
                {
                    std::string& prev_val = _header.at(_latest_header);
                    prev_val = prev_val + " " + value;
                }
                catch (const std::out_of_range&)
                { }
            }
        }
    }
    else
    {
        bool    success;
        std::pair<std::string, std::string>     item;

        success = Request::_S_parse_header(item, str);
        if (!success)
        {
            _latest_header = "";
            _header_size = _header_size + str_size;
        }
        else if (insert)
        {
            _latest_header = item.first;
            _header_size = _header_size + str_size;
            try
            {
                _header.at(item.first);
                std::cerr << "Duplicate header" << std::endl;
                throw ft::HttpException(HTTP_BAD_REQUEST);
            }
            catch (const std::out_of_range&)
            {
                _header.insert(item);
            }
        }
    }
}


bool    Request::_S_validate_request_line(const l_str_t& l_content)
{
    int     i = 0;
    bool    complete = false;

    for (l_str_t::const_iterator it = l_content.begin(); it != l_content.end(); ++it, ++i)
    {
        if (i == 0)
        {
            _S_validate_method(*it);
        }
        else if (i == 1)
        {
            _S_validate_path(*it);
        }
        else if (i == 2)
        {
            complete = _S_validate_version(*it);
        }
        else
        {
            std::cerr << "Too Many Request component" << std::endl;
            throw ft::HttpException(HTTP_BAD_REQUEST);
        }
    }

    return complete;
}


void    Request::_S_validate_method(const std::string& str)
{
    for (std::string::const_iterator it = str.begin(); it != str.end(); ++it)
    {
        if (!std::isupper(*it))
        {
            std::cerr << "Lowercase method" << std::endl;
            throw ft::HttpException(HTTP_BAD_REQUEST);
        }
    }
}


void    Request::_S_validate_path(const std::string& str)
{
    if (str[0] != '/')
    {
        std::cerr << "Path not start with /" << std::endl;
        throw ft::HttpException(HTTP_BAD_REQUEST);
    }
    else if (str.size() > DEFAULT_HTTP_LIMIT)
    {
        std::cerr << "URI too long" << std::endl;
        throw ft::HttpException(HTTP_LONG_URI);
    }
}


bool    Request::_S_validate_version(const std::string& str)
{
    std::string     prefix = HTTP_SLASH;
    size_t          str_size = str.size();
    size_t          prefix_size = prefix.size();

    if (str_size <= prefix_size)
    {
        if (str.compare(0, str_size, prefix.c_str(), str_size))
        {
            std::cerr << "HTTP version not start with HTTP/" << std::endl;
            throw ft::HttpException(HTTP_BAD_REQUEST);
        }

        return false;
    }
    else
    {
        if (str.compare(0, prefix_size, prefix.c_str(), prefix_size))
        {
            std::cerr << "HTTP version not start with HTTP/" << std::endl;
            throw ft::HttpException(HTTP_BAD_REQUEST);
        }
        
        std::string v_str = str.substr(prefix.size());
        if (!std::isdigit(v_str[0]) || v_str[0] == '0')
        {
            std::cerr << "HTTP version 0" << std::endl;
            throw ft::HttpException(HTTP_BAD_REQUEST);
        }
        double v = std::atof(v_str.c_str());

        if (v < 1)
        {
            std::cerr << "HTTP version 0" << std::endl;
            throw ft::HttpException(HTTP_BAD_REQUEST);
        }
        else if (v > 1.1)
        {
            std::cerr << "Not support version" << std::endl;
            throw ft::HttpException(HTTP_NOT_SUPPORT);
        }
        int i = 0;
        for (std::string::const_iterator it = v_str.begin(); it != v_str.end(); ++it, ++i)
        {
            char    c = *it;
            int     is_digit = std::isdigit(c);

            if (i == 1)
            {
                if (c != '.')
                {
                    std::cerr << "HTTP version . " << std::endl;
                    throw ft::HttpException(HTTP_BAD_REQUEST);
                }
            }
            else
            {
                if (!is_digit)
                {
                    if (c == '\r' && (it + 1) == v_str.end())
                    {
                        continue;
                    }
                    std::cerr << "HTTP version is not digit" << std::endl;
                    throw ft::HttpException(HTTP_BAD_REQUEST);
                }
                else if (i > 4)
                {
                    std::cerr << "HTTP version too long" << std::endl;
                    throw ft::HttpException(HTTP_BAD_REQUEST);
                }
            }
        }

        if (i < 3)
        {
            return false;
        }
        return true;
    }
}


bool    Request::_S_parse_header(std::pair<std::string, std::string>& item, const std::string& str)
{
    size_t  sep_pos;

    sep_pos = str.find(':');
    
    if (sep_pos == std::string::npos || sep_pos == 0)
    {
        return false;
    }
    
    item.first = ft::tolower(str.substr(0, sep_pos));
    try
    {
        std::string buffer = str.substr(sep_pos + 1);
        item.second = ft::skip_ws(buffer);

        return true;
    }
    catch (const std::out_of_range&)
    {
        return false;
    }
}