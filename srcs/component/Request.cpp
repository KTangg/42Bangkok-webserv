/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 23:43:36 by spoolpra          #+#    #+#             */
/*   Updated: 2023/03/08 19:11:27 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "component/Request.hpp"
#include "utils/HttpExceoption.hpp"


/**
 * @brief Construct a new Request:: Request object
 *
 * @param buffer raw request
 * @param n buffer size
 */
Request::Request(const char* buffer, const size_t n) : _request()
{
    _M_append_request(buffer, n);
    _request.seekg(0, std::ios_base::beg);
    _header = Header();
    _method = std::string();
    _path = std::string();
    _content = std::string();
    _header_size = 0;
    _header_end = false;
    _chunk = false;
    _complete = false;
}


Request::Request(const Request& rhs)
{
    *this = rhs;
}


Request& Request::operator=(const Request& rhs)
{
    _request.str("");
    _request << rhs._request.str();
    _request.seekg(0, std::ios_base::beg);
    _header = rhs._header;
    _method = rhs._method;
    _path = rhs._path;
    _content = rhs._content;
    _header_size = rhs._header_size;
    _header_end = rhs._header_end;
    _chunk = rhs._chunk;
    _complete = rhs._complete;

    return *this;
}


/**
 * @brief Destroy the Request:: Request object
 *
 */
Request::~Request() { }


/**
 * @brief Get method
 *
 * @return std::string method
 */
std::string Request::getMethod() const
{
    return _method;
}


/**
 * @brief Get URL path
 *
 * @return std::string
 */
std::string Request::getPath() const
{
    return _path;
}


/**
 * @brief Get header value according to key
 *
 * @param key Header key to search
 * @return std::string value according to key
 * @exception std::out_of_range if key not found
 */
std::string Request::getHeader(const std::string& key) const
{
    return _header.getHeader(key);
}


/**
 * @brief Check wheter request is finish reading
 *
 * @return true all data is read, otherwise false
 */
bool    Request::isComplete() const
{
    return _complete;
}


/**
 * @brief Check wheter all header is already parsed or not
 *
 * @return true on 2 x CRLF seperate Header with content found, else none
 */
bool    Request::isHeaderEnd() const
{
    return _header_end;
}


/**
 * @brief Append buffer to request
 *
 * @param buffer bytes buffer
 * @param n size of buffer
 */
void    Request::appendRequest(const char* buffer, size_t n)
{
    _M_append_request(buffer, n);
}


/**
 * @brief Find first line of request line and parse path/method found
 *
 * @exception ft::HttpException in case of invalid request
 * @exception ft::RequestNotReady if request not ready to process yet
 */
void    Request::parseRequestLine()
{
    std::string line;

    while (true)
    {
        line = _M_read_line(true);

        std::string trim = ft::skip_ws(line);
        if (!trim.empty())
        {
            break;
        }
    }

    _M_parse_request_line(line);
}


/**
 * @brief Append read buffer to request stream
 *
 * @param buffer content buffer
 * @param n size to be read from buffer
 */
void    Request::_M_append_request(const char* buffer, size_t n)
{
    _request.seekp(0, std::ios_base::end);
    _request.write(buffer, n);
}


/**
 * @brief Read line that end with \\n and trim out trailing \\r
 * in case of any error rewind _request read pos back
 *
 * @param wait wait for more request or not
 * @return std::string retrun clean line with out \\r\\n ending
 * @exception ft::RequestNotReady will be throw if eof is not accept and file reach eof
 */
std::string     Request::_M_read_line(bool wait)
{
    std::string line;

    std::stringstream::pos_type before_pos = _request.tellg();

    std::getline(_request, line, '\n');

    if (_request.eof() && wait)
    {
        _request.clear();
        _request.seekg(before_pos);

        throw ft::RequestNotReady();
    }

    if (!line.empty() && line[line.size() - 1] == '\r')
    {
        line.erase(line.size() - 1);
    }

    return line;
}


/**
 * @brief Validate request line and save value to object
 *
 * @param line request line without \\r\\n trailing
 * @exception ft::HttpException is thrown if request line isn't compatible
 */
void    Request::_M_parse_request_line(const std::string& line)
{
    if (!std::isupper(line[0]))
    {
        throw ft::HttpException(HTTP_BAD_REQUEST);
    }
    v_str_t content_v = ft::parse_ws(line);

    int i = 0;
    for (const_it_v_str it = content_v.begin(); it != content_v.end(); ++it, ++i)
    {
        switch (i)
        {
            case METHOD_INDEX:
                _method = _S_validate_method(*it);
                break;
            case PATH_INDEX:
                _path = _S_validate_path(*it);
                break;
            case HTTP_VERSION_INDEX:
                _S_validate_http(*it);
                break;
            default:
                throw ft::HttpException(HTTP_BAD_REQUEST);
                break;
        }
    }

    if (i < 3)
    {
        throw ft::HttpException(HTTP_BAD_REQUEST);
    }
}


/**
 * @brief Validate method, method should be all uppercase
 * this not checking is the method is allow or not
 *
 * @param method string to be check
 * @return std::string the same given string
 * @exception ft::HttpException will be thrown when method is invalid
 */
std::string Request::_S_validate_method(const std::string& method)
{
    for (std::string::const_iterator it = method.begin(); it != method.end(); ++it)
    {
        if (!std::isupper(*it))
        {
            throw ft::HttpException(HTTP_BAD_REQUEST);
        }
    }

    return method;
}


/**
 * @brief Validate path, path should be start with '/'
 * path should not longer than limit value (default 8 kb)
 *
 * @param path URL path string
 * @return std::string the same given string
 * @exception ft::HttpException will be thrown if path is invalid
 */
std::string Request::_S_validate_path(const std::string& path)
{
    if (path[0] != '/')
    {
        throw ft::HttpException(HTTP_BAD_REQUEST);
    }

    if (path.size() > DEFAULT_HTTP_LIMIT)
    {
        throw ft::HttpException(HTTP_LONG_URI);
    }

    return path;
}


/**
 * @brief Check if HTTP version is match to support verion
 *
 * @param http_version HTTP/VERSION format string to be checked
 * @exception ft::HttpException will be thrown if version is not supported
 */
void    Request::_S_validate_http(const std::string& http_version)
{
    std::string prefix(HTTP);

    size_t  prefix_size = prefix.size();

    if (http_version.size() <= prefix_size)
    {
        throw ft::HttpException(HTTP_BAD_REQUEST);
    }
    else if (prefix.compare(0, prefix_size, http_version.c_str(), prefix_size) != 0)
    {
        throw ft::HttpException(HTTP_BAD_REQUEST);
    }
    else if (http_version[prefix_size] != '/')
    {
        throw ft::HttpException(HTTP_BAD_REQUEST);
    }

    try
    {
        std::string version = http_version.substr(prefix_size + 1);

        _S_validate_version_number(version)
    }
    catch (const std::out_of_range&)
    {
        throw ft::HttpException(HTTP_BAD_REQUEST);
    }
}


/**
 * @brief
 *
 * @param version
 */
void    Request::_S_validate_version_number(const std::string& version)
{
    // TODO
}
