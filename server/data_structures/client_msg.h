#ifndef TIN_NFS_CLIENT_MSG_H
#define TIN_NFS_CLIENT_MSG_H


struct client_connection {
    char login[128];
    char password[128];
};

struct client_open {
    char *path;
    unsigned int oflag;
    unsigned int mode;
};

struct client_close {
    unsigned int fd;
};

struct client_read {
    unsigned int fd;
    unsigned int read_size;
};

struct client_write {
    unsigned int fd;
    unsigned int write_size;
    void *data;
};

struct client_lseek {
    unsigned int fd;
    unsigned int offset;
    unsigned int whence;
};

struct client_unlink {
    char *path;
};


struct client_fstat {
    unsigned int fd;
};

struct client_opendir {
    char *path;
};

struct client_closedir {
    unsigned int dir_fd;
};

struct client_readdir {
    unsigned int dir_fd;
};

struct client_disconnect {
};

struct client_msg {
    unsigned short request_type;
    union {
        struct client_connection connection;
        struct client_open open;
        struct client_close close;
        struct client_read read;
        struct client_write write;
        struct client_lseek lseek;
        struct client_unlink unlink;
        struct client_fstat fstat;
        struct client_opendir opendir;
        struct client_closedir closedir;
        struct client_readdir readdir;
        struct client_disconnect disconnect1;
    } arguments;
};
#endif //TIN_NFS_CLIENT_MSG_H
