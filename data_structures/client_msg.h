//
// Created by michal on 12/27/20.
//

#ifndef TIN_NFS_CLIENT_MSG_H
#define TIN_NFS_CLIENT_MSG_H
struct client_msg {
    unsigned short request_type;
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
    } arguments;
}

typedef
struct connect {
    char *login;
    char *password;
} connect;

typedef struct open {
    char *path;
    unsigned int oflag;
    unsigned int mode;
} open;

typedef struct close {
    unsigned int fd;
} close;

typedef struct read {
    unsigned int fd;
    unsigned int read_size;
} read;

typedef struct write {
    unsigned int fd;
    unsigned int write_size;
    void *data;
} write;

typedef struct lseek {
    unsigned int fd;
    unsigned int offset;
    unsigned int whence;
} lseek;

typedef struct unlink {
    char *path;
} unlink;


typedef struct fstat {
    unsigned int fd;
} fstat;

typedef struct opendir {
    char *path;
} opendir;

typedef struct closedir {
    unsigned int dir_fd;
} closedir;

typedef struct readdir {
    unsigned int dir_fd;
} readdir;

typedef struct disconnect {
} disconnect;
#endif //TIN_NFS_CLIENT_MSG_H
