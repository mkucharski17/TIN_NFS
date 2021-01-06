//

#include "send_message.h"

int sendMessageAndGetResponse(char *serverIp, uint16_t port, client_msg *input, server_msg **serverResponse) {
    int socketFd;
    struct sockaddr_in serv_addr;

    if ((socketFd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cout << "error during socket creating" << std::endl;
        return ERROR;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, serverIp, &serv_addr.sin_addr) <= 0) {
        std::cout << "inet_pton error" << std::endl;
        return ERROR;
    }

    if (connect(socketFd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        std::cout << "error during connection setting" << std::endl;
        return ERROR;
    }

    send(socketFd, input, sizeof(client_msg), 0);
    char response[sizeof(server_msg)];


    read(socketFd, response, sizeof(server_msg));
    //to jest tylko zeby zalogowac w konsoli czy dobre dane przyszły

    (*serverResponse) = (server_msg *) response;
    std::cout << "response is received" << std::endl;
    std::cout << "response type : " << (*serverResponse)->response_type << std::endl;

    switch ((*serverResponse)->response_type) {
        case CONNECTION_RESPONSE:
            std::cout << "new port: " << (*serverResponse)->response.connection.new_server_port << std::endl;
            break;
        case OPEN_FILE_RESPONSE:
            std::cout << "file descriptor: " << (*serverResponse)->response.open.fd << std::endl;
            break;
        case OPEN_DIR_RESPONSE:
            std::cout << "dir descriptor: " << (*serverResponse)->response.opendir.dir_fd << std::endl;
            break;
        case READ_FILE_RESPONSE:
            std::cout << "read:  " << (*serverResponse)->response.read.data << std::endl;
            break;
        case READ_DIR_RESPONSE:
            std::cout << "read dir:  " << (*serverResponse)->response.readdir.name << std::endl;
            break;
        case WRITE_FILE_RESPONSE:
            std::cout << "write:  " << (*serverResponse)->response.write.size << std::endl;
            break;
        case LSEEK_FILE_RESPONSE:
            std::cout << "lseek:  " << (*serverResponse)->response.lseek.offset << std::endl;
            break;
        case CLOSE_FILE_RESPONSE:
            std::cout << "close:  " << (*serverResponse)->response.close.status << std::endl;
            break;
        case CLOSE_DIR_RESPONSE:
            std::cout << "close dir:  " << (*serverResponse)->response.closedir.status << std::endl;
            break;
        case UNLINK_FILE_RESPONSE:
            std::cout << "unlink:  " << (*serverResponse)->response.unlink.status << std::endl;
            break;
        case FSTAT_FILE_RESPONSE:
            std::cout << "fstat:  " << (*serverResponse)->response.fstat.status << std::endl;
            break;
        case DISCONNECT_REQUEST:
            std::cout << "Disconnect" << std::endl;
            break;
        default:
            std::cout << "unknown response type" << std::endl;
            return ERROR;
    }


    return OK;
}
