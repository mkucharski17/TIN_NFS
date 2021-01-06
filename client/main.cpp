
#include <data_structures/codes.h>
#include <file/open/open.h>
#include <authorization/authorization.h>
#include <send_message/send_message.h>
#include "fileOperations.h"


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
#include <limits.h>



int main() {
    ///polaczenie z serwerem
    sendConnectRequest((char *) "127.0.0.1", (char *) "michal", (char *) "haslo");
    ///otwarcie pliku
     auto fd = mynfs_open((char *) "127.0.0.1", (char *) "lel.txt",O_RDWR,777);
     char * text = (char*)(sizeof(char)*1024);


     mynfs_read(fd,(char*) text , 10);
    //std::cout<<"elellel "<<*text;

    return 0;

}


