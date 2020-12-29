#ifndef TIN_NFS_SERVER_MSG_H
#define TIN_NFS_SERVER_MSG_H


struct server_connection {
    unsigned int new_server_port;
};

struct server_open {
    unsigned int fd;
};

struct server_close {
} ;

struct server_read {
    unsigned int size;
    unsigned int *data;
};

struct server_write {
    unsigned int size;
};

struct server_lseek {
    unsigned int offset;
};

struct server_unlink {
};


struct server_fstat {
    //todo zdefiniuj struskturę stat
};

struct server_opendir {
    unsigned int dir_fd;
};

struct server_closedir {

};

struct server_readdir {
    char *name;
};

struct server_disconnect {
} ;

struct server_msg {
    unsigned short response_type;
    unsigned short error;
    union {
        struct server_connection connection;
        struct server_open open;
        struct server_close close;
        struct server_read read;
        struct server_write write;
        struct server_lseek lseek;
        struct server_unlink unlink;
        struct server_fstat fstat;
        struct server_opendir opendir;
        struct server_closedir closedir;
        struct server_readdir readdir;
        struct server_disconnect disconnect1;
    } response;
};

#endif //TIN_NFS_SERVER_MSG_H
