
#ifndef CLIENT_OPERATIONS_H
#define CLIENT_OPERATIONS_H

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
/// path, oflag, mode – jak w funkcji systemowej open()
/// (dozwolone są modyfikacje lub ograniczenia)
/// zwraca: -1 gdy błąd, deskryptor pliku gdy operacja udana
/// należy zaimplementować co najmniej następujące tryby otwarcia pliku:
/// O_RDONLY, O_WRONLY, O_RDWR, O_CREAT

int mynfs_read(int fd, void *buf, int count);

int mynfs_write(int fd, const void *buf, int count);
int mynfs_lseek(int fd, int offset, int whence);
int mynfs_close(int fd);
int mynfs_unlink(char *host, char *path);

///pobiera atrybuty otwartego pliku - analogicznie do funkcji systemowej fstat();
int mynfs_fstat(int mynfs_fd,struct stat *statbuf);

#endif //CLIENT_OPERATIONS_H
