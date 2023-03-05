/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Master.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 10:03:06 by spoolpra          #+#    #+#             */
/*   Updated: 2023/03/05 17:45:16 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "server/Master.hpp"


Master::Master(const MasterConfig& config)
: _address(config.getAddress()),
  _server_map(config.getServerConfig()),
  _listener(-1),
  _listening(false),
  _poll_list(),
  _request_map()
{ }


bool    Master::init()
{
    _listener = socket(AF_INET, SOCK_STREAM, 0);
    if (_listener == -1)
    {
        perror(addressString().c_str());
        return false;
    }

    struct sockaddr* addr = reinterpret_cast<struct sockaddr*>(
                                const_cast<sockaddr_in_t*>(&_address)
                                );

    if (bind(_listener, addr, sizeof(_address)) == -1)
    {
        perror(addressString().c_str());
        return false;
    }

    if (::listen(_listener, SOMAXCONN) == -1)
    {
        perror(addressString().c_str());
        return false;
    }
    // To be delete
    int option = 1;
    setsockopt(_listener, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

#ifdef __APPLE__
    signal(SIGPIPE, SIG_IGN);
    fcntl(_listener, F_SETFL, O_NONBLOCK);
#endif

    return true;
}


bool    Master::listen()
{
    std::vector<int>    del_fd;

    _listening = true;
    _M_add_poll(_listener, POLLIN);

    std::cout << "Listening to http://" << this->addressString() << std::endl;

    while (_listening || _poll_list.size() > 0)
    {
        int poll_cnt = poll(_poll_list.data(), _poll_list.size(), TIMEOUT_POLL);
        if (poll_cnt < 0)
        {
            perror(this->addressString().c_str());
            return false;
        }

        int new_socket = _M_listen(del_fd);

        _M_del_poll(del_fd);
        del_fd.clear();

        if (new_socket != -1)
        {
            _M_add_poll(new_socket);
        }
    }

    return true;
}


std::string     Master::addressString() const
{
    int                 port;
    std::string         host;
    std::stringstream   ss;

    host = inet_ntoa(_address.sin_addr);
    port = ntohs(_address.sin_port);

    ss << host << ":" << port;

    return ss.str();
}


void    Master::_M_add_poll(int socket, short event)
{
    struct pollfd   new_poll;

    new_poll.fd = socket;
    new_poll.events = event;
    new_poll.revents = 0;

    _poll_list.push_back(new_poll);
}


void    Master::_M_del_poll(const std::vector<int>& del_fd)
{
    iterator_poll   start_it = _poll_list.begin();
    for (std::vector<int>::const_iterator del_it = del_fd.begin(); del_it != del_fd.end(); ++del_it)
    {
        for (iterator_poll it = start_it; it != _poll_list.end(); ++it)
        {
            if (it->fd == *del_it)
            {
                start_it = _poll_list.erase(it);
                std::cout << "Close: " << *del_it << std::endl;
                close(*del_it);
                break;
            }
        }

        _request_map.erase(*del_it);
    }
}


int     Master::_M_listen(std::vector<int>& del_fd)
{
    int     new_socket = -1;
    bool    alive;

    for (iterator_poll it = _poll_list.begin(); it != _poll_list.end(); ++it)
    {
        if (it->revents & POLLHUP \
            || it->revents & POLLERR \
            || it->revents & POLLNVAL
            )
        {
            del_fd.push_back(it->fd);
            continue;
        }
        if (it->revents & POLLIN)
        {
            if (it->fd == _listener)
            {
                alive = _M_accept(new_socket);
                if (!alive)
                {
                    del_fd.push_back(_listener);
                    _listener = -1;
                    _listening = false;
                }
            }
            else
            {
                alive = _M_request(it->fd);
                if (!alive)
                {
                    del_fd.push_back(it->fd);
                }
            }
        }
        if (it->revents & POLLOUT)
        {
            alive = _M_response(it->fd);
            if (!alive)
            {
                del_fd.push_back(it->fd);
            }
        }
    }

    return new_socket;
}


bool    Master::_M_accept(int& socket)
{
    sockaddr    addr_remote;
    socklen_t   addr_len = 0;

    socket = accept(_listener, &addr_remote, &addr_len);

    if (socket == -1)
    {
        if (errno != EWOULDBLOCK)
        {
            perror(this->addressString().c_str());

            return false;
        }
    }
    else
    {
        std::cout << "Accept: " << socket << std::endl;
#ifdef __APPLE__
        fcntl(socket, F_SETFL, O_NONBLOCK);
#endif
    }

    return true;
}


bool    Master::_M_request(int socket)
{
    unsigned char   buffer[DEFAULT_BUFFER_SIZE];

    size_t ret = ft::recv(socket, buffer, DEFAULT_BUFFER_SIZE);
    if (ret == 0)
    {
        return false;
    }

    bytestring  byte_read(buffer, ret);
    try
    {
        Request& request = _request_map.at(socket);

        request.appendRequest(byte_read);
    }
    catch (const std::out_of_range&)
    {
        Request request(byte_read);

        _request_map.insert(std::make_pair(socket, request));
    }

    return true;
}


bool    Master::_M_response(int socket)
{
    bool    alive;
    
    try
    {
        Request& request = _request_map.at(socket);
        if (!request.isRequestLine())
        {
            alive = _M_process(socket, request, PROCESS_REQUEST_LINE);
        }
        else if (!request.isHeaderEnd())
        {
            alive = _M_process(socket, request, PROCESS_HEADER);
        }
        // else
        // {
        //     alive = _M_process(socket, request, PROCESS_CONTENT);
        // }

        return alive;
    }
    catch (const std::out_of_range&)
    {
        return true;
    }
}


bool    Master::_M_process(int socket, Request& request, int stage)
{
    try
    {
        switch (stage)
        {
            case PROCESS_REQUEST_LINE:
                request.processRequestLine();
                break;
            
            case PROCESS_HEADER:
                request.processHeader();
                break;
        }

        return true;
    }
    catch (const ft::HttpException& e)
    {
        bytestring  a;
        e.send(socket, a);
    }


    return false;
}
