//

#ifndef CLIENT_AUTHORIZATION_H
#define CLIENT_AUTHORIZATION_H

#include <data_structures/client_msg.h>
#include <cstring>
#include <data_structures/codes.h>

unsigned int  sendConnectRequest(char *host,char *login, char *password);

#endif //CLIENT_AUTHORIZATION_H
