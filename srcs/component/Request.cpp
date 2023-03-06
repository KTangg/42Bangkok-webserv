/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 23:43:36 by spoolpra          #+#    #+#             */
/*   Updated: 2023/03/06 17:07:01 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "component/Request.hpp"


Request::Request(const bytestring& bstr)
: _request(),
  _method(),
  _path(),
  _server(),
  _config(),
  _route(),
  _header(),
  _header_end(),
  _header_size(),
  _latest_header(),
  _chunk(),
  _content(),
  _content_end()
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
    _config = rhs._config;
    _route = rhs._route;
    _header = rhs._header;
    _header_end = rhs._header_end;
    _header_size = rhs._header_size;
    _latest_header = rhs._latest_header;
    _chunk = rhs._chunk;
    _content = rhs._content;
    _content_end = rhs._content_end;

    return *this;
}


Request::~Request() 
{
    _request->str((unsigned char*)"");
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


void    Request::setConfig(const ServerConfig* config)
{
    _config = config;
}


std::string Request::getServer() const
{
    return _server;
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
            _M_get_mandatory_header();
            _header_end = true;
            break;
        }
        else
        {
            _M_process_header(line_str, true);
        }
    }
}


bool    Request::isContentEnd() const
{
    return _content_end;
}


void    Request::processContent()
{
    if (_chunk)
    {
        _content_end = _M_process_chunk_content();
    }
    else
    {
        _content_end = _M_process_content();
    }
}


void    Request::postHeaderValidate()
{
    try
    {
        std::string value = _header.at(HEADER_CONTENT_LENGTH);
        if (!ft::is_number(value))
        {
            std::cerr << "Invalid Content-Length header" << std::endl;
            throw ft::HttpException(HTTP_BAD_REQUEST);
        }
        if (!_chunk)
        {
            size_t  length = std::atol(value.c_str());
            if (length > _config->getLimit())
            {
                throw ft::HttpException(HTTP_TOO_LARGE);
            }
        }
    }
    catch (const std::out_of_range&)
    { }
    
    _route = _config->searchRoute(_path);
    if (_route == NULL)
    {
        throw ft::HttpException(HTTP_NOT_FOUND);
    }
    else if (!_route->checkMethod(_method))
    {
        throw ft::HttpException(HTTP_NOT_ALLOW);
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


void    Request::_M_get_mandatory_header()
{
    try
    {
        _server = _header.at(HEADER_HOST);
    }
    catch (const std::out_of_range&)
    {
        std::cerr << "Host Header not found" << std::endl;
        throw ft::HttpException(HTTP_BAD_REQUEST);
    }
    try
    {
        std::string value = _header.at(HEADER_TRANSFER_ENCODE);
        _chunk = _S_check_transfer_encode(value);
    }
    catch (const std::out_of_range&)
    { }
}


bool    Request::_M_process_chunk_content()
{
    ssize_t         read_cnt;
    bytepos         before_pos;
    bytestring      line;
    unsigned char   sep = '\n';

    while (true)
    {
        before_pos = _request->tellg();
        std::getline(*_request, line, sep);
        if (_request->eof())
        {
            _request->clear();
            _request->seekg(before_pos);
            return false;
        }
        read_cnt = ft::hex_to_dec(BYTES_TO_STR(line.c_str()));

        if (read_cnt < 0)
        {
            std::cerr << "chunk size less than 0" << std::endl;
            throw ft::HttpException(HTTP_BAD_REQUEST);
        }
        else if (read_cnt == 0)
        {
            return true;
        }
        try
        {
            unsigned char* buffer = _M_read_content(read_cnt, true);
            if (buffer == NULL)
            {
                return true;
            }
            
            std::getline(*_request, line, sep);
            if (_request->eof())
            {
                throw std::out_of_range("");
            }
            
            _M_append_content(buffer, read_cnt);
        }
        catch (const std::out_of_range&)
        {
            _request->clear();
            _request->seekg(before_pos);
            return false;
        }
    }
}


bool    Request::_M_process_content()
{
    ssize_t         len;
    unsigned char*  buffer;
    
    try
    {
        std::string val = _header.at(HEADER_CONTENT_LENGTH);
        ssize_t     len = std::atol(val.c_str());
        bytepos     before_pos;
        
        try
        {
            buffer = _M_read_content(len, true);
            if (buffer != NULL)
            {
                _M_append_content(buffer, len);
            }
        }
        catch (const std::out_of_range&)
        {
            _request->clear();
            _request->seekg(before_pos);

            return false;
        }
    }
    catch (const std::out_of_range&)
    {
        bytepos before;
        bytepos end;

        before = _request->tellg();
        _request->seekg(0, std::ios::end);
        end = _request->tellg();

        len = end - before;
        if (len > static_cast<ssize_t>(_config->getLimit()))
        {
            throw ft::HttpException(HTTP_TOO_LARGE);
        }
        
        buffer = _M_read_content(len, false);
        if (buffer != NULL)
        {
            _M_append_content(buffer, len);
        }
    }

    return true;
}


unsigned char*  Request::_M_read_content(size_t read_size, bool strict)
{
    unsigned char*  buffer;

    if (read_size == 0)
    {
        return NULL;
    }
    try
    {
        buffer = new unsigned char[read_size];
    }
    catch(const std::bad_alloc&)
    {
        throw ft::HttpException(HTTP_SERVER_ERROR);
    }
    
    _request->read(buffer, read_size);

    switch (strict)
    {
        case true:
            if (static_cast<size_t>(_request->gcount()) != read_size)
            {
                delete buffer;
                throw std::out_of_range("");
            }
            break;
        
        case false:
            break;

    }

    return buffer;
}


void    Request::_M_append_content(unsigned char* buffer, ssize_t len)
{
    _content = _content + bytestring(buffer, len);
    delete buffer;
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
            throw ft::HttpException(HTTP_UNSUPPORT_VERSION);
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

        buffer = ft::skip_ws(buffer);
        if (buffer[buffer.size() - 1] == '\r')
        {
            buffer = buffer.erase(buffer.size() - 1);
        }

        item.second = buffer;

        return true;
    }
    catch (const std::out_of_range&)
    {
        return false;
    }
}


bool    Request::_S_check_transfer_encode(const std::string& value)
{
    if (!value.compare(CHUNK_ENCODE))
    {
        return true;
    }

    char    c;
    size_t  pos = value.find(CHUNK_ENCODE, 0);
    size_t  len = std::strlen(CHUNK_ENCODE);

    if (pos == std::string::npos)
    {
        return false;
    }
    else if (pos == 0)
    {
        try
        {
            c = value.at(pos + len);
            if (c != ',')
            {
                return false;
            }
        }
        catch (const std::out_of_range&)
        {
            return true;
        }
    }
    else
    {
        try
        {
            c = value.at(pos - 1);
            if (c != ' ' && c != ',')
            {
                return false;
            }
            c = value.at(pos + len);
            if (c != ',')
            {
                return false;
            }
        }
        catch (const std::out_of_range&)
        {
            return true;
        }
    }

    return true;
}