//

#ifndef CLIENT_AUTHORIZATION_H
#define CLIENT_AUTHORIZATION_H

#include <data_structures/client_msg.h>
#include <cstring>
#include <data_structures/codes.h>
#include <data_structures/server_msg.h>
#include <send_message/send_message.h>

extern unsigned int port;

extern char * host_name;

unsigned int sendConnectRequest(char *host,char *login, char *password);

#endif //CLIENT_AUTHORIZATION_H
