//

#include <data_structures/client_msg.h>
#include <data_structures/codes.h>
#include <data_structures/server_msg.h>
#include <cstring>
#include <send_message/send_message.h>
#include "open.h"

unsigned int mynfs_open (char *host, char *path, int oflag, int mode) {

    client_msg openRequest;
    server_msg *openResponse;
    openRequest.request_type = OPEN_FILE_REQUEST;
    strcpy((char*)openRequest.arguments.open.path, path);
    openRequest.arguments.open.oflag = oflag;
    openRequest.arguments.open.mode = mode;
    sendMessageAndGetResponse(current_connection.first, current_connection.second, &openRequest, &openResponse);

    return openResponse->response.open.fd;
}
