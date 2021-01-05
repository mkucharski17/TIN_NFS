//

#ifndef CLIENT_OPEN_H
#define CLIENT_OPEN_H
unsigned int mynfs_open (char *host, char *path, int oflag, int mode);
unsigned int mynfs_opendir(char *host, char *path);

#endif //CLIENT_OPEN_H
