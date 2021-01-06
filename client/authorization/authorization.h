//

#ifndef CLIENT_AUTHORIZATION_H
#define CLIENT_AUTHORIZATION_H

#include <data_structures/client_msg.h>
#include <cstring>
#include <data_structures/codes.h>
#include <data_structures/server_msg.h>
#include <send_message/send_message.h>
#include <vector>

extern std::pair<char*, unsigned int>  current_connection;

extern std::vector<std::pair<char*, unsigned int>> connections;

unsigned int sendConnectRequest(char *host,char *login, char *password);

void changeCurrentConnection(int connection_index);

void sendDisconnectRequest();

#endif //CLIENT_AUTHORIZATION_H
