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
#include <limits.h>
#include "../data_structures/client_msg.h"
#include "../data_structures/codes.h"
#include "../data_structures/server_msg.h"
#include "request_handlers/request_handlers.h"

void run_server(int);

void getClientMsgFromSocketAndSendResponse(int new_socket);

int main(int argc, char *argv[]){
    if(argc != 2) {
      perror("Wrong operationsSerwer argumenst number!");
      exit(EXIT_FAILURE);
    }

    //casting argv[1] to int
    char* p;
    errno = 0;
    long arg = strtol(argv[1], &p, 10);
    if (*p != '\0' || errno != 0) {
        return 1;
    }

    if (arg < INT_MIN || arg > INT_MAX) {
        return 1;
    }

    int serwer_port = arg;

    run_server(serwer_port);
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
    switch (clientMsg->request_type) {
        case OPEN_FILE_REQUEST:
            handleOpenFileRequest(clientMsg, &response);
            break;
        case READ_FILE_REQUEST:
            handleReadFileRequest(clientMsg,&response);
            break;
        case WRITE_FILE_REQUEST:
            handleWriteFileRequest(clientMsg,&response);
            break;
        case LSEEK_FILE_REQUEST:
            handleLSeekFileRequest(clientMsg,&response);
            break;
        case CLOSE_FILE_REQUEST:
            handleCloseFileRequest(clientMsg,&response);
            break;
        case UNLINK_FILE_REQUEST:
            handleUnlinkFileRequest(clientMsg,&response);
            break;
        case FSTAT_FILE_REQUEST:
            handleFstatFileRequest(clientMsg,&response);
            break;
        case DISCONNECT_REQUEST: {
            handleDisconnectRequest(clientMsg,&response);
            send(new_socket, response, sizeof(server_msg), 0);
            exit(0);
        }break;
        default:
            perror("unknown request type");
            exit(EXIT_FAILURE);
    }

    send(new_socket, response, sizeof(server_msg), 0);
    std::cout << "response is sent" << std::endl;
}
