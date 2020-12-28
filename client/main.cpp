
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <iostream>
#include <data_structures/codes.h>
#include <data_structures/client_msg.h>

int sendMessage(char * serverIp,uint16_t port,  client_msg *input);

int main() {
    //send auth request
     client_msg input{
        .request_type = AUTHORIZATION_REQUEST,
        .arguments = {
                .connection = {
                        "michal",
                        "haslo",
                }
        }
    };
    sendMessage((char*)"127.0.0.1",8080,&input);

    return 0;

}

int sendMessage(char * serverIp,uint16_t port, struct client_msg *input) {
    int sockfd;
    struct sockaddr_in serv_addr;

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cout<<"error during socket creating";
        return ERROR;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if(inet_pton(AF_INET, serverIp, &serv_addr.sin_addr) <= 0)
    {
        std::cout<<"inet_pton error";
        return ERROR;
    }

    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cout<<"error during connection setting";
        return ERROR;
    }

    send(sockfd, input, sizeof (client_msg) , 0);
}
