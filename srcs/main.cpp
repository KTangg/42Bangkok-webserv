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

    std::string route_path_1 = "/v1";
    std::string root_path_1 = "/var/www/html";

    std::string route_path_2 = "v2";
    std::string root_path_2 = "/var/www/html2/";

    std::string route_path_3 = "/v1/test";
    std::string root_path_3 = "/var/www/test/";

    Route   route_1 = Route(route_path_1, root_path_1);

    Route   route_2 = Route(route_path_2, root_path_2);

    Route   route_3 = Route(route_path_3, root_path_3);

    route_map.insert(
        std::make_pair(route_path_1, route_1)
    );
    route_map.insert(
        std::make_pair(route_path_2, route_2)
    );
    route_map.insert(
        std::make_pair(route_path_3, route_3)
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
