#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include "data_structures/client_msg.h"

void run_server(int);

void getDataFromSocket(int new_socket);

int main() {

    run_server(8080);


}

void run_server(int portNumber) {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);


    // Creating socket file descriptor
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // attach socket on 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(portNumber);


    if (bind(server_fd, (struct sockaddr *) &address,
             sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 5) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }


    while (true) {
        new_socket = accept(server_fd, (struct sockaddr *) &address,
                            (socklen_t *) &addrlen);
        if (new_socket < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        getDataFromSocket(new_socket);
    }
}

void getDataFromSocket(int new_socket) {
    char *buf = new char[1461];
    int bytes = recv(new_socket, buf, 1000, 0);
    if (bytes <= 0) {
        perror("receive");
        exit(EXIT_FAILURE);
    }
    auto clientAuthRequest = (client_msg *) buf;
    std::cout << "received bytes : " << bytes << std::endl;
    if (clientAuthRequest->request_type == 0) {
        std::cout << " request type : " << clientAuthRequest->request_type << std::endl;
        std::cout<<"login : "<<clientAuthRequest->arguments.connection.login<<"\n";
        std::cout<<"password : "<<clientAuthRequest->arguments.connection.password<<"\n";

    }std::cout.flush();
}
