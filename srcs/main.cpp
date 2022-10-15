#include "webserv.hpp"
#include "Worker.hpp"

#define PORT 80

int main(void) {

    sockaddr_in_t                   address;
    std::map<std::string, Route>    route;
    std::map<int, std::string>      error;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    Worker server = Worker(address, route, error);
    server.init();
    server.listen();
}
