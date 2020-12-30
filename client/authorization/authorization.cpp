//

#include <data_structures/server_msg.h>
#include <send_message/send_message.h>
#include "authorization.h"

unsigned int sendConnectRequest(char *host, char *login, char *password) {

    server_msg *serverResponse;


    client_msg input{
            .request_type = CONNECTION_REQUEST,
    };
    strcpy((char *) input.arguments.connection.login, login);
    strcpy((char *) input.arguments.connection.password, password);
    sendMessageAndGetResponse(host, 8080, &input, &serverResponse);

    return serverResponse->response.connection.new_server_port;
}
