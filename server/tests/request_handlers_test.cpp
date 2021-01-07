#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <unistd.h>
#include <dirent.h>
#include <fstream>
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
                REQUIRE( ntohl(serverResponse->response.open.fd) > 0 );
            }
        }
    }
}

SCENARIO("handleReadFileRequest test", "[ReadFile]" ) {
    GIVEN("File descriptor and read size") {
        int fd = open("test_dir/test_file.txt", O_RDONLY, 0);
        int id = Storage::instance().addFD(fd);
        client_msg clientAuthMsg {
            .request_type = READ_FILE_REQUEST,
            .arguments {
                .read { htonl(id), htonl(10) }
            }
        };
        char *response;

        WHEN("the request is handled") {
            handleReadFileRequest(&clientAuthMsg, &response);

            server_msg* serverResponse = (server_msg *) response;

            THEN("the response has type READ_FILE_RESPONSE and read size == 4") {
                REQUIRE( serverResponse->response_type == READ_FILE_RESPONSE );
                REQUIRE( ntohl(serverResponse->response.read.size) == 4 );
            }
        }
    }
}

SCENARIO("handleWriteFileRequest test", "[WriteFile]" ) {
    GIVEN("File descriptor, write size and data") {
        int fd = open("test_dir/test_file.txt", O_WRONLY, 0);
        int id = Storage::instance().addFD(fd);
        client_msg clientAuthMsg {
            .request_type = WRITE_FILE_REQUEST,
            .arguments {
                .write { htonl(id), htonl(10), "write test" }
            }
        };
        char *response;

        WHEN("the request is handled") {
            handleWriteFileRequest(&clientAuthMsg, &response);

            server_msg* serverResponse = (server_msg *) response;

            THEN("the response has type WRITE_FILE_RESPONSE and write size == 10") {
                REQUIRE( serverResponse->response_type == WRITE_FILE_RESPONSE );
                REQUIRE( ntohl(serverResponse->response.write.size) == 10 );
            }
        }
    }
}

SCENARIO("handleLSeekFileRequest test", "[LSeekFile]" ) {
    GIVEN("File descriptor, offset and whence") {
        int fd = open("test_dir/test_file.txt", O_RDWR, 0);
        int id = Storage::instance().addFD(fd);
        client_msg clientAuthMsg {
            .request_type = LSEEK_FILE_REQUEST,
            .arguments {
                .lseek { htonl(id), htonl(1), htonl(0) }
            }
        };
        char *response;

        WHEN("the request is handled") {
            handleLSeekFileRequest(&clientAuthMsg, &response);

            server_msg* serverResponse = (server_msg *) response;

            THEN("the response has type LSEEK_FILE_RESPONSE and ") {
                REQUIRE( serverResponse->response_type == LSEEK_FILE_RESPONSE );
                REQUIRE( ntohl(serverResponse->response.lseek.offset) == 1 );
            }
        }
    }
}

SCENARIO("handleCloseFileRequest test", "[CloseFile]" ) {
    GIVEN("File descriptor") {
        int fd = open("test_dir/test_file.txt", O_RDONLY, 0);
        int id = Storage::instance().addFD(fd);
        client_msg clientAuthMsg {
            .request_type = CLOSE_FILE_REQUEST,
            .arguments {
                .close { htonl(id) }
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
        std::ofstream test_file;
        test_file.open("test_dir/test_file.txt");
        test_file << "test";
        test_file.close();
    }
}

SCENARIO("handleFstatFileRequest test", "[FstatFile]" ) {
    GIVEN("File descriptor") {
        int fd = open("test_dir/test_file.txt", O_RDONLY, 0);
        int id = Storage::instance().addFD(fd);
        client_msg clientAuthMsg {
            .request_type = UNLINK_FILE_REQUEST,
            .arguments {
                .fstat { htonl(id) }
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
                .opendir { "test_dir" }
            }
        };
        char *response;

        WHEN("the request is handled") {
            handleOpenDirRequest(&clientAuthMsg, &response);

            server_msg* serverResponse = (server_msg *) response;

            THEN("the response has type OPEN_DIR_RESPONSE and fd > 0") {
                REQUIRE( serverResponse->response_type == OPEN_DIR_RESPONSE );
                REQUIRE( ntohl(serverResponse->response.opendir.dir_fd) > 0 );
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
        auto dird = opendir("test_dir");
        int dir_fd = dirfd(dird);
        Storage::instance().add(dir_fd, dird);
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