#include <iostream>
#include <cstdlib>
#include "webserv.hpp"
#include "worker/Worker.hpp"

void usage(void);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        usage();
        exit(EXIT_FAILURE);
    }
    (void)argv;
    socket_t sock;

    sock.host = inet_addr("192.168.0.246");
    sock.port = 8000;
    Worker test(sock);
    test.serve();
}

/// @brief Print out to std::cerr or fd = 2 on how to execute this file
void usage(void) {
    std::cerr << "Usage: ./webserv [configuration file]" << std::endl;
}
