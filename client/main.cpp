#include <data_structures/codes.h>
#include <authorization//authorization.h>
#include <iostream>

#define DIFFERENT_CONNECTION -2
#define EXIT_KEY 30

void createConnection() {
    char *host, *login, *password;
    host = (char*)malloc(15*sizeof(char));
    login = (char*)malloc(128*sizeof(char));
    password = (char*)malloc(128*sizeof(char));
    std::cout << "Podaj adres hosta: ";
    std::cin >> host;
    std::cout << "Podaj login: ";
    std::cin >> login;
    std::cout << "Podaj haslo: ";
    std::cin >> password;
    if(!sendConnectRequest(host, login, password))
    {
        std::cout << "Authorization error!\n";
    }
}

void disconnect() {
    sendDisconnectRequest();
}

void changeConnection() {
    std::cout << "Choose connection:\n";
    int connection_counter = 0;
    for(auto & connection : connections)
    {
        std::cout << connection_counter << ". " <<  connection.first << ":" << connection.second << std::endl;
        connection_counter++;
    }
    std::cin >> connection_counter;
    changeCurrentConnection(connection_counter);
}

int printMenu() {
    std::cout << "*******************************************\n";
    if(connections.empty())
        std::cout << "No current connection\n";
    else
        std::cout << "Current connection: " << current_connection.first << ":" << current_connection.second << std::endl;
    std::cout << "Choose operation::\n"<< "-1. choose different connection\n" << "0. create connection\n" << "1. open\n"
        << "2. read\n" <<
        "3. write\n" << "4. lseek\n" << "5. close\n" << "6. unlink\n" << "7. fstat\n" <<
        "8. opendir\n" << "9. readdir\n" << "10. closedir\n" << "11. disconnect\n" << "15. exit\n";
    std::cout << "*******************************************\n";
    int input;
    do{
        std::cin >> input;
    }while((input < -1 || input > 11) && input != 15);
    return 2*input;
}

void menuSwitch(int selectedOperation) {
    //todo::uzupelnic tego switcha
    if(connections.empty() && (selectedOperation != CONNECTION_REQUEST && selectedOperation != EXIT_KEY)){
        std::cout << "Nie jestes polaczony, ta operacja jest niedostepna!\n";
    } else {
        switch(selectedOperation){
            case DIFFERENT_CONNECTION: {
                changeConnection();
            }break;
            case CONNECTION_REQUEST: {
                createConnection();
            }break;
            case OPEN_FILE_REQUEST: {

            }break;
            case WRITE_FILE_REQUEST: {

            }break;
            case LSEEK_FILE_REQUEST: {

            }break;
            case CLOSE_FILE_REQUEST: {

            }break;
            case UNLINK_FILE_REQUEST: {

            }break;
            case FSTAT_FILE_REQUEST: {

            }break;
            case OPEN_DIR_REQUEST: {

            }break;
            case READ_DIR_REQUEST: {

            }break;
            case CLOSE_DIR_REQUEST: {

            }break;
            case DISCONNECT_REQUEST: {
                disconnect();
            }break;
            case EXIT_KEY: {

            }break;
            default:{
                perror("menuSwitch default value");
            }break;
        }
    }
}

int main() {
    int selectedOperation;
    do{
        selectedOperation = printMenu();
        menuSwitch(selectedOperation);
    }while(selectedOperation != EXIT_KEY);

    return 0;
}


