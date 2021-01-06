#ifndef REQUEST_HANDLERS_H
#define REQUEST_HANDLERS_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>
#include <iostream>
#include <cstring>
#include "../../data_structures/client_msg.h"
#include "../../data_structures/codes.h"
#include "../../data_structures/server_msg.h"

void handleOpenFileRequest(client_msg *clientAuthMsg, char **response);

void handleReadFileRequest(client_msg *clientMsg, char **response) ;

void handleWriteFileRequest(client_msg *clientMsg, char **response);

void handleLSeekFileRequest(client_msg *clientMsg, char **response);

void handleCloseFileRequest(client_msg *clientMsg, char **response);

void handleUnlinkFileRequest(client_msg *clientMsg, char **response);

void handleFstatFileRequest(client_msg *clientMsg, char **response);

void handleDisconnectRequest(client_msg *clientMsg, char **response);

#endif
