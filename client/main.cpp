
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <iostream>
#include <data_structures/codes.h>
#include <data_structures/client_msg.h>
#include <data_structures/server_msg.h>
#include <unistd.h>

int sendMessageAndGetResponse(char *serverIp, uint16_t port, client_msg *input);

client_msg sendConnectRequest(char *login, char *password);

int main() {
    int choice;
    client_msg input;

    do {
        std::cout << "wybierz jedną z poniższych opcji i zatwierdz przyciskiem enter" << std::endl;
        std::cout << "wyjdz - 0" << std::endl;
        std::cout << "połącz - 1" << std::endl;
        std::cin >> choice;
        switch (choice) {
            case 0:
                choice = -1;
                break;
            case 1:
                input = sendConnectRequest((char *) "michal", (char *) "haslo");
                break;

            default:
                std::cout << "cos poszlo nie tak, sproboj ponownie" << std::endl;
                continue;
        }

        if (choice != -1 && sendMessageAndGetResponse((char *) "127.0.0.1", 8080, &input) != 1) {
            std::cout << "cos poszlo nie tak, sproboj ponownie" << std::endl;

            continue;
        }

    } while (choice != -1);


    return 0;

}

client_msg sendConnectRequest(char *login, char *password) {//send auth request
    client_msg input{
            .request_type = CONNECTION_REQUEST,
    };
    strcpy((char *) input.arguments.connection.login, login);
    strcpy((char *) input.arguments.connection.password, password);
    return input;
}

int sendMessageAndGetResponse(char *serverIp, uint16_t port, struct client_msg *input) {
    int sockfd;
    struct sockaddr_in serv_addr;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cout << "error during socket creating"<<std::endl;
        return ERROR;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, serverIp, &serv_addr.sin_addr) <= 0) {
        std::cout << "inet_pton error"<<std::endl;
        return ERROR;
    }

    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        std::cout << "error during connection setting"<<std::endl;
        return ERROR;
    }

    send(sockfd, input, sizeof(client_msg), 0);
    char response[sizeof(server_msg)];
    server_msg *serverResponseMessage;

    read(sockfd, response, sizeof(server_msg));
    std::cout << "response is received" << std::endl;


    serverResponseMessage = (server_msg *) response;
    switch (serverResponseMessage->response_type) {
        case CONNECTION_RESPONSE:
            std::cout << "new port: " << serverResponseMessage->response.connection.new_server_port << std::endl;
            break;
        default:
            std::cout << "unknown response type" << std::endl;
            return ERROR;

    }
    return OK;
}
