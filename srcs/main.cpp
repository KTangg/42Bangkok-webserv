
#include "parser/Parser.hpp"

int main(int argc, char** argv) {
    Logger logger("webserv");

    if (argc != 2) {
        logger.log(Logger::ERROR, "Usage: ./webserv <config_file>");
        return 1;
    }

    try {
        Parser parser(argv[1]);
        parser.parse();
    } catch (const std::runtime_error& e) {
        return 1;
    }

    return 0;
}
