#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "../operations_serwer/request_handlers/request_handlers.h"

SCENARIO("handleOpenFileRequest test", "[OpenFile]" ) {
    GIVEN("Client message ") {
        client_msg clientAuthMsg {
                .request_type = OPEN_FILE_REQUEST,
                .open {
                    .path = "test_file.txt",
                    .oflag = O_RDONLY,
                    .mode = 0
                }
        };
        char **response;

        WHEN("the request is handled") {
            handleOpenFileRequest(&clientAuthMsg, response);

            server_msg* serverResponse = (server_msg *) response;

            THEN("the response ") {
                REQUIRE( serverResponse->response_type == OPEN_FILE_RESPONSE );
                REQUIRE( serverResponse->response.open.fd > 0 );
            }
        }
    }
}