/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 22:19:47 by spoolpra          #+#    #+#             */
/*   Updated: 2023/03/06 16:14:20 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef __REQUEST_HPP__
# define __REQUEST_HPP__


# include "webserv.hpp"

# include "config/ServerConfig.hpp"
# include "component/Route.hpp"


class Request {

    public:
        Request(const bytestring& bs);
        Request(const Request& rhs);
        Request&    operator=(const Request& rhs);

        virtual ~Request();

        bytestream*     getRequest() const;
        void            appendRequest(const bytestring& request);
        void            setConfig(const ServerConfig* config);
        std::string     getServer() const;

        bool            isRequestLine() const;
        void            processRequestLine();
        
        bool            isHeaderEnd() const;
        void            processHeader();
        void            postHeaderValidate();

        bool            isContentEnd() const;
        void            processContent();

    private:
        bytestream*             _request;
        
        std::string             _method;
        std::string             _path;
        std::string             _server;
        const ServerConfig*     _config;
        const Route*            _route;

        map_str_str_t           _header;
        bool                    _header_end;
        size_t                  _header_size;
        std::string             _latest_header;

        bool                    _chunk;
        bytestring              _content;
        bool                    _content_end;


        void            _M_process_header(const std::string& str, bool insert);
        void            _M_get_mandatory_header();
        bool            _M_process_chunk_content();
        bool            _M_process_content();
        unsigned char*  _M_read_content(size_t read_size, bool strict);
        void            _M_append_content(unsigned char* buffer, ssize_t len);
        
        static bool     _S_parse_header(std::pair<std::string, std::string>& item, const std::string& str);
        static bool     _S_check_transfer_encode(const std::string& value);
        static bool     _S_validate_request_line(const l_str_t& l_content);
        static void     _S_validate_method(const std::string& str);
        static void     _S_validate_path(const std::string& str);
        static bool     _S_validate_version(const std::string& str);
};


typedef std::map<int, Request>          map_request_t;
typedef map_request_t::iterator         iterator_request;
typedef map_request_t::const_iterator   const_iterator_request;


#endif
