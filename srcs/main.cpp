#include "webserv.hpp"
#include "server/Worker.hpp"

#define PORT 8080

int main(void) {

    sockaddr_in_t                   address;
    // std::map<std::string, Route>    route;
    // std::map<int, std::string>      error;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    Worker server = Worker(address);
    server.init();
    server.listen();
}
