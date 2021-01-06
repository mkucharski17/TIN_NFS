//

#ifndef CLIENT_SEND_MESSAGE_H
#define CLIENT_SEND_MESSAGE_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <arpa/inet.h>
#include <iostream>
#include <data_structures/codes.h>
#include <data_structures/client_msg.h>
#include <data_structures/server_msg.h>
#include <unistd.h>

int sendMessageAndGetResponse(char *serverIp, uint16_t port, client_msg *input, server_msg **serverResponse);

#endif //CLIENT_SEND_MESSAGE_H
