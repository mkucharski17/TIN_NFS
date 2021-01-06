#include "request_handlers.h"


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
