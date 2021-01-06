
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
     auto fd = mynfs_open((char *) "127.0.0.1", (char *) "lel.txt",O_RDWR ,777);
     /*char  text [100] = "hello worlddddddd";
    //std::cout<<mynfs_unlink((char *) "127.0.0.1", (char *) "lel.txt");

     mynfs_write(fd, &text , 12);
     char  text2[50] = "helloooooooooooooooooooooooo";

     mynfs_lseek(fd,0,SEEK_CUR);
    mynfs_write(fd, &text2 , 20);
    char text3[1000];
    //mynfs_read(fd,&text3,100);
    //std::cout<<"odczytano "<<text3 <<std::endl;*/
     struct stat st;
     mynfs_fstat(fd,&st);

     mynfs_close(fd);

    return 0;

}


