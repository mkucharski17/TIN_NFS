#ifndef CLIENT_DIRECTORYOPERATIONS_H
#define CLIENT_DIRECTORYOPERATIONS_H

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

#include "data_structures/client_msg.h"
#include "data_structures/codes.h"
#include "data_structures/server_msg.h"

#include "authorization/authorization.h"

#include "send_message/send_message.h"

///host – nazwa lub adres DNS serwera
///path – jak funkcja opendir()
///zwraca -1 gdy błąd, deskryptor katalogu(!) gdy operacja udana
int mynfs_opendir(char *host, char *path);

///dir_fd – deskryptor rekordu katalogowego zwrócony przez mynfs_opendir()
///Uwaga: systemowe funkcja readdir() zwraca za każdym razem strukturę dirent
/// zawierającą rekordy opisujące kolejne pliki z katalogu, tu wystarczy,
/// że funkcja zwróci samą nazwę.
char *mynfs_readdir(int dirfd); int mynfs_closedir(int dirfd);

///analogicznie do closedir()
int mynfs_closedir(int dirfd);

#endif //CLIENT_DIRECTORYOPERATIONS_H
