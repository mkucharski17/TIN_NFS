//
// Created by michal on 12/27/20.
//

#ifndef TIN_NFS_SERVER_MSG_H
#define TIN_NFS_SERVER_MSG_H
struct server_msg {
    unsigned short response_type;
    unsigned short error;
    union {
        connect connection;
        open open;
        close close;
        read read;
        write write;
        lseek lseek;
        unlink unlink;
        fstat fstat;
        opendir opendir;
        closedir closedir;
        readdir readdir;
        disconnect disconnect1;
    } response
}

typedef struct connect {
    unsigned int new_server_port;
} connect;

typedef struct open {
    unsigned int fd;
} open;

typedef struct close {
} close;

typedef struct read {
    unsigned int size;
    unsigned int *data;
} read;

typedef struct write {
    unsigned int size;
} write;

typedef struct lseek {
    unsigned int offset;
} lseek;

typedef struct unlink {
} unlink;


typedef struct fstat {
    //todo zdefiniuj struskturę stat
} fstat;

typedef struct opendir {
    unsigned int dir_fd
} opendir;

typedef struct closedir {

} closedir;

typedef struct readdir {
    char *name
} readdir;

typedef struct disconnect {
} disconnect;

#endif //TIN_NFS_SERVER_MSG_H
