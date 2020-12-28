#ifndef TIN_NFS_CLIENT_MSG_H
#define TIN_NFS_CLIENT_MSG_H

struct connection {
    char login[128];
    char password[128];
};
struct open {
    char *path;
    unsigned int oflag;
    unsigned int mode;
};

struct close {
    unsigned int fd;
};

struct read {
    unsigned int fd;
    unsigned int read_size;
};

struct write {
    unsigned int fd;
    unsigned int write_size;
    void *data;
};

struct lseek {
    unsigned int fd;
    unsigned int offset;
    unsigned int whence;
};

struct unlink {
    char *path;
};


struct fstat {
    unsigned int fd;
};

struct opendir {
    char *path;
};

struct closedir {
    unsigned int dir_fd;
};

struct readdir {
    unsigned int dir_fd;
};

struct disconnect {
};

struct client_msg {
    unsigned short request_type;
    union {
        struct connection connection;
        struct open open;
        struct close close;
        struct read read;
        struct write write;
        struct lseek lseek;
        struct unlink unlink;
        struct fstat fstat;
        struct opendir opendir;
        struct closedir closedir;
        struct readdir readdir;
        struct disconnect disconnect1;
    } arguments;
};
#endif //TIN_NFS_CLIENT_MSG_H
