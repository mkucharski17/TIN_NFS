#ifndef TIN_NFS_CODES_H
#define TIN_NFS_CODES_H
#define ERROR -1;
#define OK 1;

///requests type
#define CONNECTION_REQUEST 0
#define CONNECTION_RESPONSE 1

#define OPEN_FILE_REQUEST 2
#define OPEN_FILE_RESPONSE 3

#define READ_FILE_REQUEST 4
#define READ_FILE_RESPONSE 5

#define WRITE_FILE_REQUEST 6
#define WRITE_FILE_RESPONSE 7

#define LSEEK_FILE_REQUEST 8
#define LSEEK_FILE_RESPONSE 9

#define CLOSE_FILE_REQUEST 10
#define CLOSE_FILE_RESPONSE 11

#define UNLINK_FILE_REQUEST 12
#define UNLINK_FILE_RESPONSE 13

#define FSTAT_FILE_REQUEST 14
#define FSTAT_FILE_RESPONSE 15

#define OPEN_DIR_REQUEST 16
#define OPEN_DIR_RESPONSE 17

#define READ_DIR_REQUEST 18
#define READ_DIR_RESPONSE 19

#define CLOSE_DIR_REQUEST 20
#define CLOSE_DIR_RESPONSE 21

#define DISCONNECT_REQUEST 22

/// file mode
#define O_RDONLY 0
#define O_WRONLY 1
#define O_RDWR 2
#define O_CREAT 3
#endif //TIN_NFS_CODES_H
