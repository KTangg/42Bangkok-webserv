#include "webserv.hpp"
#include "server/Master.hpp"

#define PORT 8080

int main(int argc, char* argv[])
{
    int         port;
    std::string host;
    if (argc > 1)
    {
        port = atoi(argv[1]);
    }
    else
    {
        port = PORT;
    }

    map_int_str_t   error_map;

    error_map.insert(std::make_pair(401, "unauth"));
    error_map.insert(std::make_pair(404, "Not found"));

    map_route_t     route_map;

    std::string route_path_1 = "/";
    std::string root_path_1 = "/var/www/html";

    std::string route_path_2 = "v2";
    std::string root_path_2 = "/var/www/html2/";

    Route   route_1 = Route(
        ft::parse_path_directory(route_path_1),
        ft::parse_path_directory(root_path_1)
    );

    Route   route_2 = Route(
        ft::parse_path_directory(route_path_2),
        ft::parse_path_directory(root_path_2)
    );

    route_map.insert(
        std::make_pair(
            ft::parse_path_directory(route_path_1),
            route_1
        )
    );
    route_map.insert(
        std::make_pair(
            ft::parse_path_directory(route_path_2),
            route_2
        )
    );

    MasterConfig    m_config = MasterConfig("0.0.0.0", port);
    ServerConfig    w_config = ServerConfig(error_map, route_map);

    m_config.addServer(w_config);
    Master  a = Master(m_config);

    bool x = a.init();
    if (x)
    {
        a.listen();
    }
}
