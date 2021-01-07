#include "fileOperations.h"

 

int mynfs_read(int fd, void *buf, int count)
{
    client_msg clientMsg;
    server_msg *serverMsg;

    clientMsg.request_type = READ_FILE_REQUEST;
    clientMsg.arguments.read.fd = htonl(fd);
    clientMsg.arguments.read.read_size = htonl(count);

    sendMessageAndGetResponse(current_connection.first, current_connection.second, &clientMsg, &serverMsg);

    int len = ntohl(serverMsg->response.read.size);
    std::cout << "RECEIVED mynfs_read RESPONSE size: " << len << std::endl;

    memcpy(buf, serverMsg->response.read.data, count);
    return len;
}

int mynfs_write(int fd,  void *buf, int count)
{
    client_msg clientMsg;
    server_msg *serverMsg;

    clientMsg.request_type = WRITE_FILE_REQUEST;
    clientMsg.arguments.write.fd = htonl(fd);
    clientMsg.arguments.write.write_size = htonl(count);

    char * buff = (char*)buf;
    memcpy( clientMsg.arguments.write.data,buff, count);

    sendMessageAndGetResponse(current_connection.first, current_connection.second, &clientMsg, &serverMsg);

    int len = ntohl(serverMsg->response.write.size);
    std::cout << "RECEIVED mynfs_write RESPONSE size: " << len << std::endl;


    return len;
}

int mynfs_lseek(int fd, int offset, int whence) {
    client_msg clientMsg;
    server_msg *serverMsg;

    clientMsg.request_type =  LSEEK_FILE_REQUEST;
    clientMsg.arguments.lseek.fd = htonl(fd);
    clientMsg.arguments.lseek.offset = htonl(offset);
    clientMsg.arguments.lseek.whence = htonl(whence);

    sendMessageAndGetResponse(current_connection.first, current_connection.second, &clientMsg, &serverMsg);

    int len = ntohl(serverMsg->response.lseek.offset);
    std::cout << "RECEIVED mynfs_lseek RESPONSE offset: " << len << std::endl;

    return len;
}

int mynfs_close(int fd) {
    client_msg clientMsg;
    server_msg *serverMsg;

    clientMsg.request_type =  CLOSE_FILE_REQUEST;
    clientMsg.arguments.close.fd = htonl(fd);

    sendMessageAndGetResponse(current_connection.first, current_connection.second, &clientMsg, &serverMsg);

    int status = ntohl(serverMsg->response.close.status);
    std::cout << "RECEIVED mynfs_close RESPONSE status: " << status << std::endl;

    return status;
}

int mynfs_unlink(char *host, char *path) {
    client_msg clientMsg;
    server_msg *serverMsg;

    clientMsg.request_type =  UNLINK_FILE_REQUEST;
    strcpy((char*)clientMsg.arguments.unlink.path,path);

    sendMessageAndGetResponse(current_connection.first, current_connection.second, &clientMsg, &serverMsg);

    int status = ntohl(serverMsg->response.unlink.status);
    std::cout << "RECEIVED mynfs_unlink RESPONSE status: " << status << std::endl;

    return status;
}

int mynfs_fstat(int mynfs_fd,struct stat *statbuf) {
    client_msg clientMsg;
    server_msg *serverMsg;

    clientMsg.request_type =  FSTAT_FILE_REQUEST;
    clientMsg.arguments.fstat.fd = htonl(mynfs_fd);

    sendMessageAndGetResponse(current_connection.first, current_connection.second, &clientMsg, &serverMsg);

    *statbuf = serverMsg->response.fstat.buffer;
    int status = ntohl(serverMsg->response.fstat.status);

    std::cout << "RECEIVED mynfs_fstat RESPONSE status: " << status << std::endl;
    return status;
}
