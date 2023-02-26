/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Master.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 22:19:47 by spoolpra          #+#    #+#             */
/*   Updated: 2023/02/26 10:02:48 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef __REQUEST_HPP__
# define __REQUEST_HPP__

// General stuff
# include "webserv.hpp"


// Other Class
# include "server/Worker.hpp"
// # include "Request.hpp"
// # include "Session.hpp"

class Master {

    public:
        // Initialize Constructor
        Master(std::vector<Config>& config);

        // Deconstructor
        virtual ~Master();

        // Member function
        int init(void);
        int run(void);

    private:
        // Attributes
        std::map<std::string, Worker> _worker_map;

}; // class Request

#endif /* __REQUEST_HPP__ */
