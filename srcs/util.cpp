#include "webserv.hpp"

std::vector<std::string>    parse_path_directory(std::string path) {
    int i = 0;
    std::vector<std::string>    path_directory;

    while (path.size() > 0) {
        std::string dir;
        size_t next_pos;
        next_pos = path.find('/');
        if (next_pos == std::string::npos) {
            dir = path;
            path.clear();
        }
        else {
            dir = path.substr(0, next_pos);
            path = path.substr(next_pos + 1);
        }
        if (dir.empty() && i++ == 0) {
            continue;
        }
        path_directory.push_back(dir);
    }

    return path_directory;
}
