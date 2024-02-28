
#include "webserv.hpp"

Master* g_master = NULL;

int main(int argc, char** argv) {
    Logger logger("webserv");

    if (argc != 2) {
        logger.log(Logger::ERROR, "Usage: ./webserv <config_file>");
        return 1;
    }
    Master master(argv[1]);

    try {
        master.init();
    } catch (const std::invalid_argument& err) {
        std::cerr << "Error parsing configuration file: " << err.what() << std::endl;
        std::cerr << "Aborting" << std::endl;
        return 1;
    }
    master.run();
}
