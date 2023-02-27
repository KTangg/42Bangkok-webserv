#include "webserv.hpp"
#include "server/Worker.hpp"

#define PORT 8080

int main(int argc, char* argv[]) {

    sockaddr_in_t                   address;
    // std::map<int, std::string>      error;
    route_map_t     route_map;
    std::string path_1 = "/";
    std::string path_2 = "/tmp/image/";
    std::string path_3 = "/tmp/image/longer";
    Route route_1 = Route(path_1);
    Route route_2 = Route(path_2);
    Route route_3 = Route(path_3);
    route_map.insert(std::make_pair(path_1, route_1));
    route_map.insert(std::make_pair(path_2, route_2));
    route_map.insert(std::make_pair(path_3, route_3));

    int port;
    if (argc > 1) {
        port = std::atoi(argv[1]);
    } else {
        port = PORT;
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    Worker server = Worker(address, route_map);
    server.init();
    server.listen();
}
