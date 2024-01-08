/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 03:17:00 by spoolpra          #+#    #+#             */
/*   Updated: 2024/01/08 14:59:02 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    int                sockfd;
    struct sockaddr_in servaddr;

    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " <host> <port>" << std::endl;
        return 1;
    }

    std::string host = argv[1];
    int         port = std::stoi(argv[2]);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        return 1;
    }

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    if (inet_pton(AF_INET, host.c_str(), &servaddr.sin_addr) <= 0) {
        return 1;
    }

    if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1) {
        return 1;
    }

    std::string msg = "GET / HTTP/1.1\r\nHost: localhost:8080\r\n\r\n";
    send(sockfd, msg.c_str(), msg.length(), 0);

    char buffer[1024];
    int  n = recv(sockfd, buffer, 1024, 0);
    buffer[n] = '\0';
    printf("%s\n", buffer);

    shutdown(sockfd, SHUT_RDWR);
    close(sockfd);

    return 0;
}
