#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <unistd.h>
#include <dirent.h>
#include "../operations_serwer/request_handlers/request_handlers.h"

SCENARIO("handleOpenFileRequest test", "[OpenFile]" ) {
    GIVEN("Client message OPEN_FILE_REQUEST O_RDONLY 0") {
        client_msg clientAuthMsg {
            .request_type = OPEN_FILE_REQUEST,
            .arguments {
                .open { "test_dir/test_file.txt", O_RDONLY, 0 }
            }
        };
        char *response;

        WHEN("the request is handled") {
            handleOpenFileRequest(&clientAuthMsg, &response);

            server_msg* serverResponse = (server_msg *) response;

            THEN("the response has type OPEN_FILE_RESPONSE and fd > 0") {
                REQUIRE( serverResponse->response_type == OPEN_FILE_RESPONSE );
                REQUIRE( serverResponse->response.open.fd > 0 );
            }
        }
    }
}

SCENARIO("handleReadFileRequest test", "[ReadFile]" ) {
    GIVEN("File descriptor and read size") {
        int fd = open("test_dir/test_file.txt", O_RDONLY, 0);
        client_msg clientAuthMsg {
            .request_type = READ_FILE_REQUEST,
            .arguments {
                .read { htonl(fd), htonl(10) }
            }
        };
        char *response;

        WHEN("the request is handled") {
            handleReadFileRequest(&clientAuthMsg, &response);

            server_msg* serverResponse = (server_msg *) response;

            THEN("the response has type READ_FILE_RESPONSE and read size == 4") {
                REQUIRE( serverResponse->response_type == READ_FILE_RESPONSE );
                REQUIRE( serverResponse->response.read.size == 4 );
            }
        }
    }
}

SCENARIO("handleWriteFileRequest test", "[WriteFile]" ) {
    GIVEN("File descriptor, write size and data") {
        int fd = open("test_dir/test_file.txt", O_WRONLY, 0);
        client_msg clientAuthMsg {
            .request_type = WRITE_FILE_REQUEST,
            .arguments {
                .write { htonl(fd), htonl(10), (char*) "write test" }
            }
        };
        char *response;

        WHEN("the request is handled") {
            handleWriteFileRequest(&clientAuthMsg, &response);

            server_msg* serverResponse = (server_msg *) response;

            THEN("the response has type WRITE_FILE_RESPONSE and write size == 10") {
                REQUIRE( serverResponse->response_type == WRITE_FILE_RESPONSE );
                REQUIRE( serverResponse->response.write.size == 4 );
            }
        }
    }
}

SCENARIO("handleLSeekFileRequest test", "[LSeekFile]" ) {
    GIVEN("File descriptor, offset and whence") {
        int fd = open("test_dir/test_file.txt", O_RDWR, 0);
        client_msg clientAuthMsg {
            .request_type = LSEEK_FILE_REQUEST,
            .arguments {
                .lseek { htonl(fd), htonl(1), htonl(0) }
            }
        };
        char *response;

        WHEN("the request is handled") {
            handleLSeekFileRequest(&clientAuthMsg, &response);

            server_msg* serverResponse = (server_msg *) response;

            THEN("the response has type LSEEK_FILE_RESPONSE and ") {
                REQUIRE( serverResponse->response_type == LSEEK_FILE_RESPONSE );
                REQUIRE( serverResponse->response.lseek.offset == 1 );
            }
        }
    }
}

SCENARIO("handleCloseFileRequest test", "[CloseFile]" ) {
    GIVEN("File descriptor") {
        int fd = open("test_dir/test_file.txt", O_RDONLY, 0);
        client_msg clientAuthMsg {
            .request_type = CLOSE_FILE_REQUEST,
            .arguments {
                .close { htonl(fd) }
            }
        };
        char *response;

        WHEN("the request is handled") {
            handleCloseFileRequest(&clientAuthMsg, &response);

            server_msg* serverResponse = (server_msg *) response;

            THEN("the response has type CLOSE_FILE_RESPONSE and status == 0") {
                REQUIRE( serverResponse->response_type == CLOSE_FILE_RESPONSE );
                REQUIRE( serverResponse->response.close.status == 0 );
            }
        }
    }
}

SCENARIO("handleUnlinkFileRequest test", "[UnlinkFile]" ) {
    GIVEN("File path") {
        client_msg clientAuthMsg {
            .request_type = UNLINK_FILE_REQUEST,
            .arguments {
                .unlink { "test_dir/test_file.txt" }
            }
        };
        char *response;

        WHEN("the request is handled") {
            handleUnlinkFileRequest(&clientAuthMsg, &response);

            server_msg* serverResponse = (server_msg *) response;

            THEN("the response has type UNLINK_FILE_RESPONSE and status == 0") {
                REQUIRE( serverResponse->response_type == UNLINK_FILE_RESPONSE );
                REQUIRE( serverResponse->response.unlink.status == 0 );
            }
        }
    }
}

SCENARIO("handleFstatFileRequest test", "[FstatFile]" ) {
    GIVEN("File descriptor") {
        int fd = open("test_dir/test_file.txt", O_RDONLY, 0);
        client_msg clientAuthMsg {
            .request_type = UNLINK_FILE_REQUEST,
            .arguments {
                .fstat { htonl(fd) }
            }
        };
        char *response;

        WHEN("the request is handled") {
            handleFstatFileRequest(&clientAuthMsg, &response);

            server_msg* serverResponse = (server_msg *) response;

            THEN("the response has type FSTAT_FILE_RESPONSE and status == 0") {
                REQUIRE( serverResponse->response_type == FSTAT_FILE_RESPONSE );
                REQUIRE( serverResponse->response.fstat.status == 0 );
            }
        }
    }
}

SCENARIO("handleDisconnectRequest test", "[Disconnect]" ) {
    GIVEN("Disconnect request") {
        client_msg clientAuthMsg;
        char *response;

        WHEN("the request is handled") {
            handleDisconnectRequest(&clientAuthMsg, &response);

            server_msg* serverResponse = (server_msg *) response;

            THEN("the response has type DISCONNECT_REQUEST") {
                REQUIRE( serverResponse->response_type == DISCONNECT_REQUEST );
            }
        }
    }
}

SCENARIO("handleOpenDirRequest test", "[OpenDir]" ) {
    GIVEN("Client message OPEN_DIR_REQUEST") {
        client_msg clientAuthMsg {
            .request_type = OPEN_DIR_REQUEST,
            .arguments {
                .opendir { "test_dir/test_file.txt" }
            }
        };
        char *response;

        WHEN("the request is handled") {
            handleOpenDirRequest(&clientAuthMsg, &response);

            server_msg* serverResponse = (server_msg *) response;

            THEN("the response has type OPEN_DIR_RESPONSE and fd > 0") {
                REQUIRE( serverResponse->response_type == OPEN_DIR_RESPONSE );
                REQUIRE( serverResponse->response.opendir.fd > 0 );
            }
        }
    }
}

SCENARIO("handleReadDirRequest test", "[ReadDir]" ) {
    GIVEN("Client message READ_DIR_REQUEST") {
        int dir_fd = dirfd(opendir("test_dir"));
        client_msg clientAuthMsg {
            .request_type = READ_DIR_REQUEST,
            .arguments {
                .readdir { htonl(dir_fd) }
            }
        };
        char *response;

        WHEN("the request is handled") {
            handleReadDirRequest(&clientAuthMsg, &response);

            server_msg* serverResponse = (server_msg *) response;

            THEN("the response has type READ_DIR_RESPONSE and name lenght > 0") {
                REQUIRE( serverResponse->response_type == READ_DIR_RESPONSE );
                REQUIRE( strlen(serverResponse->response.readdir.name) > 0 );
            }
        }
    }
}

SCENARIO("handleCloseDirRequest test", "[CloseDir]" ) {
    GIVEN("Client message CLOSE_DIR_REQUEST") {
        int dir_fd = dirfd(opendir("test_dir"));
        client_msg clientAuthMsg {
            .request_type = CLOSE_DIR_REQUEST,
            .arguments {
                .closedir { htonl(dir_fd) }
            }
        };
        char *response;

        WHEN("the request is handled") {
            handleCloseDirRequest(&clientAuthMsg, &response);

            server_msg* serverResponse = (server_msg *) response;

            THEN("the response has type CLOSE_DIR_RESPONSE and status == 0") {
                REQUIRE( serverResponse->response_type == CLOSE_DIR_RESPONSE );
                REQUIRE( serverResponse->response.closedir.status == 0 );
            }
        }
    }
}