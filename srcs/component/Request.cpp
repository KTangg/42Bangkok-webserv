/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 23:43:36 by spoolpra          #+#    #+#             */
/*   Updated: 2023/03/05 08:15:35 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "component/Request.hpp"


Request::Request(const bytestring& bstr)
: _request(),
  _method(),
  _path(),
  _server(),
  _status_line(false),
  _ready(false),
  _error_code(HTTP_OK)
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
    _status_line = rhs._status_line;
    _ready = rhs._ready;
    _error_code = rhs._error_code;

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


bool    Request::isStatusLine() const
{
    return _status_line;
}


void    Request::processStatusLine()
{
    bytestring      line;
    bytepos         new_pos;

    std::getline(*_request, line, CHAR_TO_BYYE('\n'));
    l_str_t l_content = ft::split(line, CHAR_TO_BYYE(' '));
    
    if (_request->eof())
    {
        _S_validate_status_line(l_content);
        _request->clear();
        _request->seekg(0, std::ios::beg);
    }
    else
    {
        if (!_S_validate_status_line(l_content))
        {
            throw ft::http_bad_request();
        }
        _method = l_content[0];
        _path = l_content[1];
        _status_line = true;
    }
}


bool    Request::isReady() const
{
    return _ready;
}


http_status_t   Request::getError() const
{
    return _error_code;
}


bool    Request::_S_validate_status_line(const l_str_t& l_content)
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
            throw ft::http_bad_request();
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
            throw ft::http_bad_request();
        }
    }
}


void    Request::_S_validate_path(const std::string& str)
{
    if (str[0] != '/')
    {
        throw ft::http_bad_request();
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
            throw ft::http_bad_request();
        }

        return false;
    }
    else
    {
        if (str.compare(0, prefix_size, prefix.c_str(), prefix_size))
        {
            throw ft::http_bad_request();
        }
        
        std::string v_str = str.substr(prefix.size());
        if (!std::isdigit(v_str[0]) || v_str[0] == '0')
        {
            throw ft::http_bad_request();
        }
        double v = std::atof(v_str.c_str());

        std::cout << "Compare: " << v << " vs " << 1.1 << std::endl;
        std::cout << "Result: " << (v == 1.1) << std::endl;

        if (v < 1)
        {
            throw ft::http_bad_request();
        }
        else if (v > 1.1)
        {
            throw ft::http_not_support();
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
                    throw ft::http_bad_request();
                }
            }
            else
            {
                if (!is_digit)
                {
                    throw ft::http_bad_request();
                }
                else if (i > 4)
                {
                    throw ft::http_bad_request();
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
