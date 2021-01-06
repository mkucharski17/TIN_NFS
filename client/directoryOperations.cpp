#include "directoryOperations.h"

int mynfs_opendir(char *host, char *path) {
    client_msg openRequest;
    server_msg *openResponse;
    openRequest.request_type = OPEN_DIR_REQUEST;
    strcpy((char*)openRequest.arguments.opendir.path, path);

    sendMessageAndGetResponse(current_connection.first, current_connection.second, &openRequest, &openResponse);

    return ntohl(openResponse->response.opendir.dir_fd);
}

char* mynfs_readdir(int dir_fd) {
    client_msg clientMsg;
    server_msg *serverMsg;

    clientMsg.request_type = READ_DIR_REQUEST;
    clientMsg.arguments.readdir.dir_fd = htonl(dir_fd);

    sendMessageAndGetResponse(current_connection.first, current_connection.second, &clientMsg, &serverMsg);

    std::cout << "RECEIVED mynfs_readdir RESPONSE: " << serverMsg->response.readdir.name << std::endl;

    return serverMsg->response.readdir.name;
}

int mynfs_closedir(int dir_fd) {
    client_msg clientMsg;
    server_msg *serverMsg;

    clientMsg.request_type =  CLOSE_DIR_REQUEST;
    clientMsg.arguments.closedir.dir_fd = htonl(dir_fd);

    sendMessageAndGetResponse(current_connection.first, current_connection.second, &clientMsg, &serverMsg);

    int status = ntohl(serverMsg->response.closedir.status);
    std::cout << "RECEIVED mynfs_closedir RESPONSE status: " << status << std::endl;

    return status;
}