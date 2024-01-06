
#include "webserv.hpp"

Master* g_master = NULL;

int main(int argc, char** argv) {
    Logger logger("webserv");

    if (argc != 2) {
        logger.log(Logger::ERROR, "Usage: ./webserv <config_file>");
        return 1;
    }
    Master master(argv[1]);

    master.init();
    master.run();
}
