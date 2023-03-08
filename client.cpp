
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <fstream>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: ./client port request_file\n");

        return -1;
    }
    short   port = atoi(argv[1]);
    char*   file_path = argv[2];

    int status, valread, client_fd;

    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
        <= 0) {
        printf(
            "\nInvalid address/ Address not supported \n");
        return -1;
    }

    if ((status
         = connect(client_fd, (struct sockaddr*)&serv_addr,
                   sizeof(serv_addr)))
        < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
    std::ifstream   in_file(file_path);

    in_file.seekg(0, in_file.end);
    size_t  buffer_size = in_file.tellg();
    in_file.seekg(0, in_file.beg);

    char    out_buffer[buffer_size];
    in_file.read(out_buffer, buffer_size);
    std::cout << out_buffer << std::endl;
    send(client_fd, out_buffer, buffer_size, 0);

    char    in_buffer[1024];
    valread = recv(client_fd, in_buffer, 1024, 0);
    printf("%s\n", (char*)in_buffer);


    return 0;
}
