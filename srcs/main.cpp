#include "webserv.hpp"
#include "server/Worker.hpp"

#define PORT 8080

int main(void) {

    sockaddr_in_t                   address;
    // std::map<int, std::string>      error;
    route_map_t     route_map;
    std::string path_1 = "/tmp/html/";
    std::string path_2 = "/tmp/image/";
    Route route_1 = Route(path_1);
    Route route_2 = Route(path_2);
    route_map.insert(std::make_pair(path_1, route_1));
    route_map.insert(std::make_pair(path_2, route_2));


    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    Worker server = Worker(address, route_map);
    server.init();
    server.listen();
}
