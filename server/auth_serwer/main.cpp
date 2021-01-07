#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include "../data_structures/client_msg.h"
#include "../data_structures/codes.h"
#include "../data_structures/server_msg.h"

void run_authorization_server(int);

void getClientAuthorizationMsg(int new_secket);

unsigned int handleConnectionRequest(client_msg *clientAuthMsg, char **response);

bool areAuthorizationDataValid(client_msg *clientAuthMsg);

void getNextLoginAndPassword(char* output_login, char* output_password, std::fstream* data_file);

unsigned int findNewSerwerPort();

int main() {
    run_authorization_server(8080);
}

void run_authorization_server(int portNumber) {
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
        getClientAuthorizationMsg(new_socket);
    }
}

void getClientAuthorizationMsg(int new_socket) {
    //todo ogarnąc jaki rozmiar powinien miec ten bufor
    char *buf = new char[1024];
    char *response;
    //todo ogrnąć ile powinniśmy czytać z bufora (parametr n)
    int bytes = recv(new_socket, buf, 1000, 0);
    if (bytes <= 0) {
        perror("error during receiving data");
        exit(EXIT_FAILURE);
    }
    auto clientMsg = (client_msg *) buf;
    std::cout << "received bytes : " << bytes << std::endl;
    std::cout << "request type : " << clientMsg->request_type << std::endl;

    if(clientMsg->request_type != CONNECTION_REQUEST) {
      perror("Wrong request type for authorization serwer!");
      exit(EXIT_FAILURE);
    }

    int new_server_port=0;
    if((new_server_port = handleConnectionRequest(clientMsg, &response)) != 0) {
      std::string command = "gnome-terminal -e 'sh -c \"./operationsSerwer ";
      command += std::to_string(new_server_port);
      command += "\"'";
      system(command.c_str());
    }
    send(new_socket, response, sizeof(server_msg), 0);
    std::cout << "response is sent" << std::endl;
}



unsigned int handleConnectionRequest(client_msg *clientAuthMsg, char **response) {
    auto *response_auth = (server_msg *) malloc(sizeof(server_msg));

    if (areAuthorizationDataValid(clientAuthMsg)) {
        std::cout << "Correct authorization with account: " << clientAuthMsg->arguments.connection.login << "\n";
        int new_server_port = findNewSerwerPort();
        response_auth->response_type = CONNECTION_RESPONSE;
        response_auth->response = {
                .connection = {
                        .new_server_port = new_server_port,
                }
        };
        *response = (char *) response_auth;
        return new_server_port;
    } else {
        std::cout << "Incorrect authorization with account: " << clientAuthMsg->arguments.connection.login << std::endl;
        response_auth->response_type = CONNECTION_RESPONSE;
        response_auth->error = ERROR;
        *response = (char *) response_auth;
        return 0;
    }
}

bool areAuthorizationDataValid(client_msg *clientAuthMsg) {
    std::fstream auth_data_file;
    auth_data_file.open("auth_data.txt", std::ios::in);
    if(auth_data_file.is_open()) {
        while(!auth_data_file.eof()) {
            char login[128];
            char password[128];
            getNextLoginAndPassword(login, password, &auth_data_file);
            if(strcmp(clientAuthMsg->arguments.connection.login, login) == 0 &&
                strcmp(clientAuthMsg->arguments.connection.password, password) == 0) {
                  auth_data_file.close();
                  return true;
                }
        }
        auth_data_file.close();
        //didn't find right login and password in auth_data.txt
        return false;
    }else{
        perror("Can not open auth_data file!");
        return false;
    }
}

void getNextLoginAndPassword(char* output_login, char* output_password, std::fstream* data_file) {
    (*data_file) >> output_login;
    (*data_file) >> output_password;
}

unsigned int findNewSerwerPort() {
    int test_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(test_socket < 0) {
        perror("Socket error\n");
        return -1;
    }

    struct sockaddr_in serv_addr;
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = 0;
    if (bind(test_socket, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        if(errno == EADDRINUSE) {
            perror("the port is not available. already to other process");
            return -1;
        } else {
            perror("could not bind to process");
            return -1;
        }
    }

    socklen_t len = sizeof(serv_addr);
    if (getsockname(test_socket, (struct sockaddr *)&serv_addr, &len) == -1) {
        perror("Error in getsockname!");
        return -1;
    }
    if (close (test_socket) < 0 ) {
        perror("Did not close socket!");
        return -1;
    }

    return ntohs(serv_addr.sin_port);
}
