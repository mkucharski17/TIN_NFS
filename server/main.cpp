#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <cstring>
#include "data_structures/client_msg.h"
#include "data_structures/codes.h"
#include "data_structures/server_msg.h"

void run_server(int);

void getClientMsgFromSocketAndSendResponse(int new_socket);

void handleConnectionRequest(client_msg *clientAuthMsg, char **response);

void handleOpenFileRequest(client_msg *clientAuthMsg, char **response);

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

    //sockets' handling
    while (true) {
        new_socket = accept(server_fd, (struct sockaddr *) &address,
                            (socklen_t *) &addrlen);
        if (new_socket < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        getClientMsgFromSocketAndSendResponse(new_socket);
    }
}

void getClientMsgFromSocketAndSendResponse(int new_socket) {
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
    //todo tutaj trzeba bedzie zrobić switcha na rozne typy requestow
    switch (clientMsg->request_type) {
        case CONNECTION_REQUEST:
            handleConnectionRequest(clientMsg, &response);
            break;
        case OPEN_FILE_REQUEST:
            handleOpenFileRequest(clientMsg, &response);
            break;
        default:
            perror("unknown request type");
            exit(EXIT_FAILURE);
    }

    send(new_socket, response, sizeof(server_msg), 0);
    std::cout << "response is sent" << std::endl;
}

void handleConnectionRequest(client_msg *clientAuthMsg, char **response) {
    std::cout << "login : " << clientAuthMsg->arguments.connection.login << "\n";
    std::cout << "password : " << clientAuthMsg->arguments.connection.password << "\n";
    //todo tutaj mamy juz dane do autoryzacji , wiec trzeba dodac dalsze działania dotyczace autoryzacji
    // na razie sprawdzanie dla przykladowych danych login:michal haslo:haslo
    auto *response_auth = (server_msg *) malloc(sizeof(server_msg));

    if (strcmp(clientAuthMsg->arguments.connection.password, "haslo") == 0) {
        response_auth->response_type = CONNECTION_RESPONSE;
        response_auth->response = {
                .connection = {
                        8081,
                }
        };
        *response = (char *) response_auth;
        std::cout << "authorized properly" << std::endl;
    } else {
        std::cout << "authorization failed" << std::endl;
    }
}

void handleOpenFileRequest(client_msg *clientAuthMsg, char **response) {
    std::cout << "path : " << clientAuthMsg->arguments.open.path << "\n";
    std::cout << "oflag : " << clientAuthMsg->arguments.open.oflag << "\n";
    std::cout << "mode : " << clientAuthMsg->arguments.open.mode << "\n";

    auto *openFileResponse = (server_msg *) malloc(sizeof(server_msg));


    openFileResponse->response_type = OPEN_FILE_RESPONSE;
    openFileResponse->response = {
            .open = {
                    111111111,
            }
    };
    *response = (char *) openFileResponse;
    std::cout << "file is open" << std::endl;

}

