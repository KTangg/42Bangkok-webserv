#include <iostream>
#include <cstdlib>
#include <unistd.h>

void usage(void);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        usage();
        exit(EXIT_FAILURE);
    }
    (void)argv;
}

/// @brief Print out to std::cerr or fd = 2 on how to execute this file
void usage(void) {
    std::cerr << "Usage: ./webserv [configuration file]" << std::endl;
}
