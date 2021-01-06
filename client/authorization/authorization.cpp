#include "authorization.h"

std::pair<char*, unsigned int> current_connection;
std::vector<std::pair<char*, unsigned int>> connections;

unsigned int sendConnectRequest(char *host, char *login, char *password) {
    server_msg *serverResponse;

    client_msg input{
            .request_type = CONNECTION_REQUEST,
    };
    strcpy((char *) input.arguments.connection.login, login);
    strcpy((char *) input.arguments.connection.password, password);
    sendMessageAndGetResponse(host, 8080, &input, &serverResponse);

    if(serverResponse->error == (unsigned int)33)
    {
        return 0;
    } else {
        current_connection = std::make_pair(host,serverResponse->response.connection.new_server_port);
        connections.push_back(current_connection);

        return serverResponse->response.connection.new_server_port;
    }
}

void changeCurrentConnection(int connection_index)
{
    current_connection = connections.at(connection_index);
}

void sendDisconnectRequest() {
    server_msg *serverResponse;
    client_msg input{
            .request_type = DISCONNECT_REQUEST,
    };
    sendMessageAndGetResponse(current_connection.first, current_connection.second, &input, &serverResponse);

    int index = 0;
    for(auto & connection : connections)
    {
        if(connection.first == current_connection.first && connection.second == current_connection.second)
            break;
        index++;
    }
    connections.erase(connections.begin() + index);

    if(connections.empty()){
        current_connection.first = nullptr;
        current_connection.second = 0;
    } else {
        current_connection = connections.at(0);
    }
}