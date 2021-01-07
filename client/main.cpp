#include "data_structures/codes.h"
#include "authorization//authorization.h"
#include <iostream>
#include "storage/DirStorage.h"
#include "directoryOperations.h"

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

void disconnect_all() {
    while(!connections.empty())
        disconnect();
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

void openDirectory() {
    std::string path;
    std::cout << "Provide directory path:\n";
    std::cin >> path;
    std::cout << "path: " << path << "\n";
    int dir_fd = mynfs_opendir((char*) current_connection.first, (char*) path.c_str());
    DirStorage::instance().add(path, dir_fd);
}

void readDirectory() {
    int index = 0;
    std::cout << "Choose directory to read:\n";
    DirStorage::instance().printAll();
    while (true) {
        std::cin >> index;
        try {
            int dir_fd = DirStorage::instance().get(index).second;
            mynfs_readdir(dir_fd);
            return;
        } catch (const std::out_of_range& e) {
            std::cout << "Index out of range!\n";
        }
    }
}

void closeDirectory() {
    int index = 0;
    std::cout << "Choose directory to close:\n";
    DirStorage::instance().printAll();
    while (true) {
        std::cin >> index;
        try {
            int dir_fd = DirStorage::instance().get(index).second;
            mynfs_closedir(dir_fd);
            DirStorage::instance().remove(index);
            return;
        } catch (const std::out_of_range& e) {
            std::cout << "Index out of range!\n";
        }
    }
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
        while(std::cin.fail()) {
            std::cout << "Error wrong input!" << std::endl;
            std::cin.clear();
            std::cin.ignore(256,'\n');
            std::cin >> input;
        }
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
                openDirectory();
            }break;
            case READ_DIR_REQUEST: {
                readDirectory();
            }break;
            case CLOSE_DIR_REQUEST: {
                closeDirectory();
            }break;
            case DISCONNECT_REQUEST: {
                disconnect();
            }break;
            case EXIT_KEY: {
                disconnect_all();
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


