/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Master.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 10:03:06 by spoolpra          #+#    #+#             */
/*   Updated: 2023/03/08 17:26:29 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "server/Master.hpp"


Master::Master(const MasterConfig& config)
{
    _address = config.getAddress();
    _server_v = config.getServerConfig();

    _listener = -1;
    _poll_v = v_poll_t();
    _request_map = map_request_t();
    _response_map = map_response_t();
}


bool    Master::init()
{
    _listener = socket(AF_INET, SOCK_STREAM, 0);
    if (_listener == -1)
    {
        perror("socket");
        return false;
    }

    struct sockaddr* addr = reinterpret_cast<struct sockaddr*>(
                                const_cast<sockaddr_in_t*>(&_address)
                                );

    if (bind(_listener, addr, sizeof(_address)) == -1)
    {
        perror("bind");
        return false;
    }

    if (::listen(_listener, SOMAXCONN) == -1)
    {
        perror("listen");
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


void    Master::listen()
{
    v_int_t     del_v;

    _M_add_poll(_listener, POLLIN);

    std::cout << "Listening to http://0.0.0.0:" << ntohs(_address.sin_port) << std::endl;

    while (_poll_v.size() > 0)
    {
        int poll_cnt = poll(_poll_list.data(), _poll_list.size(), TIMEOUT_POLL);

        if (poll_cnt < 0)
        {
            perror("poll");

            throw ft::ListenError();
        }

        int new_socket = _M_listen(del_v);

        _M_del_poll(del_v);
        del_v.clear();

        if (new_socket != -1)
        {
            _M_add_poll(new_socket);
        }
    }
}


void    Master::_M_add_poll(const int socket, const short event)
{
    struct pollfd   new_poll;

    new_poll.fd = socket;
    new_poll.events = event;
    new_poll.revents = 0;

    _poll_v.push_back(new_poll);
}


void    Master::_M_del_poll(const v_int_t& del_v)
{
    const_it_poll start_it = _poll_v.begin();

    for (const_it_v_int del_it = del_v.begin(); del_it != del_v.end(); ++del_it)
    {
        for (const_it_poll poll_it = start_it; poll_it != _poll_v.end(); ++poll_it)
        {
            if (it->fd == *del_it)
            {
                start_it = _poll_v.erase(it);
                std::cerr << "Close: " << *del_it << std::endl;
                close(*del_it);
                break;
            }
        }

        _M_del_client(*del_it);
    }
}


int     Master::_M_listen(v_int_t& del_v)
{
    bool    alive;
    int     new_socket = -1;

    for (const_it_poll it = _poll_v.begin(); it != _poll_v.end(); ++it)
    {
        int fd = it->fd;
        const short revent = it->revents;

        if (revent & POLLHUP || revent & POLLERR || revent & POLLNVAL)
        {
            del_v.push_back(fd);
            continue;
        }
        if (revent & POLLIN)
        {
            if (fd == _listener)
            {
                new_socket = _M_accept(new_socket);
            }
            else
            {
                alive = _M_request(fd);
                if (!alive)
                {
                    del_v.push_back(fd);
                }
            }
        }
        if (revent & POLLOUT)
        {
            alive = _M_response(fd);
            if (!alive)
            {
                del_v.push_back(fd);
            }
        }
    }

    return new_socket;
}


int     Master::_M_accept() const
{
    int         socket;
    sockaddr    addr_remote;
    socklen_t   addr_len = 0;

    socket = accept(_listener, &addr_remote, &addr_len);

    if (socket == -1)
    {
        perror("accept");
    }
    else
    {
        std::cerr << "Accept: " << socket << std::endl;
#ifdef __APPLE__
        fcntl(socket, F_SETFL, O_NONBLOCK);
#endif
    }

    return socket;
}


bool    Master::_M_request(const int socket)
{
    char    buffer[DEFAULT_BUFFER_SIZE];

    ssize_t ret = ft::recv(socket, buffer, DEFAULT_BUFFER_SIZE);
    if (ret <= 0)
    {
        return false;
    }

    try
    {
        Request& request = _request_map.at(socket);
        request.appendRequest(buffer, ret);
    }
    catch (const std::out_of_range&)
    {
        Request     request(buffer, ret);

        _M_add_client(socket, request);
    }

    return true;
}


bool    Master::_M_response(const int socket)
{
    Response& response = _response_map.at(socket);

    try
    {
        if (response.isReady())
        {
            return response.respond();
        }
        else
        {
            return _M_process(response);
        }
    }
    catch (const ft::HttpException& e)
    {
        if (e.getCode() != -1)
        {
            e.send(socket);
        }

        return false;
    }
}


bool    Master::_M_process(const Response& response)
{
    if (!response.isServer())
    {
        try
        {
            std::string host = response.preprocess();
            response.setServer(_M_match_server(host));
        }
        catch (const ft::RequestNotReady& e)
        {
            return true;
        }
    }
    else
    {
        return response.process();
    }
}


const ServerConfig* Master::_M_match_server(const std::string& host)
{
    for (const_it_server it = _server_v.begin(); it != _server_v.end(); ++it)
    {
        if (host.compare(it->getHost()) == 0)
        {
            return it;
        }
    }

    return _server_v.begin();
}


void    Master::_M_add_client(const int socket, const Request& request)
{
    Response response(request);

    _request_map.insert(std::make_pair(socket, request));
    _response_map.insert(std::make_pair(socket, response));
}


void    Master::_M_del_client(const int socket)
{
    _response_map.erase(socket);
    _request_map.erase(socket);
}
