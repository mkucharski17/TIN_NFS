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
#include <cstring>
#include <limits.h>
#include "../data_structures/client_msg.h"
#include "../data_structures/codes.h"
#include "../data_structures/server_msg.h"

void run_server(int);

void getClientMsgFromSocketAndSendResponse(int new_socket);

void handleOpenFileRequest(client_msg *clientAuthMsg, char **response);

void handleReadFileRequest(client_msg *clientMsg, char **response) ;

void handleWriteFileRequest(client_msg *clientMsg, char **response);

void handleLSeekFileRequest(client_msg *clientMsg, char **response);

void handleCloseFileRequest(client_msg *clientMsg, char **response);

void handleUnlinkFileRequest(client_msg *clientMsg, char **response);

void handleFstatFileRequest(client_msg *clientMsg, char **response);

int main(int argc, char *argv[]){
    if(argc != 2) {
      perror("Wrong operationsSerwer argumenst number!");
      exit(EXIT_FAILURE);
    }

    //converting argv[1] to portNumber
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
  /*
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
    }*/
    std::cout<<"weszlo do nowego serwera "<<portNumber<<"\n";


              int x;
          std::cin>>x;
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
        default:
            perror("unknown request type");
            exit(EXIT_FAILURE);
    }

    send(new_socket, response, sizeof(server_msg), 0);
    std::cout << "response is sent" << std::endl;
}


void handleOpenFileRequest(client_msg *clientAuthMsg, char **response) {
    std::cout << "path : " << clientAuthMsg->arguments.open.path << "\n";
    std::cout << "oflag : " << clientAuthMsg->arguments.open.oflag << "\n";
    std::cout << "mode : " << clientAuthMsg->arguments.open.mode << "\n";
    int32_t fd;
    fd = open((char *) clientAuthMsg->arguments.open.path, (int)clientAuthMsg->arguments.open.oflag,
              clientAuthMsg->arguments.open.mode);
    auto *openFileResponse = (server_msg *) malloc(sizeof(server_msg));


    openFileResponse->response_type = OPEN_FILE_RESPONSE;
    openFileResponse->response.open.fd = htonl(fd);
    openFileResponse->error = htonl(errno);

    *response = (char *) openFileResponse;
    std::cout << "file is open" << std::endl;

}

void handleReadFileRequest(client_msg *clientMsg, char **response) {

    std::cout<<"read file request"<<std::endl;
    int fd = ntohl( clientMsg->arguments.read.fd);
    int size  = ntohl(clientMsg->arguments.read.read_size);


    char * buffer = (char*) malloc(size);

    int32_t bytesRead = read(fd,buffer,size);
    server_msg *serverMsg;
    if(bytesRead>0)
    {
        serverMsg = (server_msg*) malloc(sizeof(server_msg ) + bytesRead);
        memcpy(serverMsg->response.read.data,buffer,bytesRead);
        serverMsg->response.read.data[bytesRead-1] = '\0';
    } else  serverMsg = (server_msg*) malloc(sizeof(server_msg ));

    serverMsg->response.read.size = htonl(bytesRead);
    serverMsg->error = htonl(errno);
    serverMsg->response_type = READ_FILE_RESPONSE;

    std::cout<<"read: "<<serverMsg->response.read.data<< std::endl;
    free(buffer);
    *response = (char*)serverMsg;
}

void handleWriteFileRequest(client_msg *clientMsg, char **response) {

    std::cout<<"write file request"<<std::endl;
    int fd = ntohl( clientMsg->arguments.write.fd);
    int size  = ntohl(clientMsg->arguments.write.write_size);

    char * buffer = (char*) clientMsg->arguments.write.data;

    ssize_t bytesWritten = write(fd,buffer,strlen(buffer));

    auto *serverMsg = (server_msg*) malloc(sizeof(server_msg ));

    serverMsg->response.write.size = htonl(bytesWritten);
    serverMsg->error = htonl(errno);
    serverMsg->response_type = WRITE_FILE_RESPONSE;


    std::cout<<"write: "<<buffer<<"size: "<<serverMsg->response.write.size<<  std::endl;
    *response = (char*)serverMsg;
}

void handleLSeekFileRequest(client_msg *clientMsg, char **response)
{
    std::cout<<"lseek file request"<<std::endl;
    int fd = ntohl( clientMsg->arguments.lseek.fd);
    off_t offset  = ntohl(clientMsg->arguments.lseek.offset);
    int whence  = ntohl(clientMsg->arguments.lseek.whence);

    off_t lseekOffset =  lseek( fd,  offset,  whence);
    auto *serverMsg = (server_msg*) malloc(sizeof(server_msg ));

    serverMsg->response.lseek.offset =htonl(lseekOffset);
    serverMsg->error = htonl(errno);
    serverMsg->response_type = LSEEK_FILE_RESPONSE;

    std::cout<<"lseek offset:"<<serverMsg->response.lseek.offset<<  std::endl;
    *response = (char*)serverMsg;
}

void handleCloseFileRequest(client_msg *clientMsg, char **response)
{
    std::cout<<"close file request"<<std::endl;
    int fd = ntohl( clientMsg->arguments.close.fd);

    int closeStatus = close(fd);

    auto *serverMsg = (server_msg*) malloc(sizeof(server_msg ));

    serverMsg->response.close.status = closeStatus;
    serverMsg->error = htonl(errno);
    serverMsg->response_type = CLOSE_FILE_RESPONSE;

    std::cout<<"close status:"<<closeStatus <<  std::endl;
    *response = (char*)serverMsg;
}

void handleUnlinkFileRequest(client_msg *clientMsg, char **response)
{
    std::cout<<"unlink file request"<<std::endl;


    int closeStatus = unlink((char*)clientMsg->arguments.unlink.path);

    auto *serverMsg = (server_msg*) malloc(sizeof(server_msg ));

    serverMsg->response.unlink.status = closeStatus;
    serverMsg->error = htonl(errno);
    serverMsg->response_type = UNLINK_FILE_RESPONSE;

    std::cout<<"unlink status:"<<closeStatus <<  std::endl;
    *response = (char*)serverMsg;
}

void handleFstatFileRequest(client_msg *clientMsg, char **response)
{
    std::cout<<"fstat file request"<<std::endl;

    struct stat buffer{};
    int         status;

    int fd = ntohl( clientMsg->arguments.fstat.fd);
    status = fstat(fd, &buffer);

    auto *serverMsg = (server_msg*) malloc(sizeof(server_msg ));

    serverMsg->response.fstat.status = status;
    serverMsg->response.fstat.buffer = buffer;
    serverMsg->error = htonl(errno);
    serverMsg->response_type = FSTAT_FILE_RESPONSE;

    std::cout<<"fstat status:"<<status <<  std::endl;
    *response = (char*)serverMsg;
}
