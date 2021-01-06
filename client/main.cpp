#include <data_structures/codes.h>
#include <authorization//authorization.h>
#include <iostream>

bool connected = false;

void createConnection() {
    sendConnectRequest((char *) "127.0.0.1", (char *) "login", (char *) "haslologinu");
    connected = true;
}
int printMenu() {
    std::cout << "*******************************************\n";
    std::cout << "Choose operation::\n" << "1. open\n" << "2. read\n" <<
        "3. write\n" << "4. lseek\n" << "5. close\n" << "6. unlink\n" << "7. fstat\n" <<
        "8. opendir\n" << "9. readdir\n" << "10. closedir\n" << "11. disconnect\n";
    std::cout << "*******************************************\n";
    int input;
    do{
        std::cin >> input;
    }while(input < 1 || input > 11);
    return 2*input;
}

void menuSwitch(int selectedOperation) {
    //todo::uzupelnic tego switcha
    switch(selectedOperation){
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

            connected = false;
        }break;
        default:{
            perror("menuSwitch default value");
        }break;
    }
}

int main() {

    createConnection();
    while(connected){
        int selectedOperation = printMenu();
        menuSwitch(selectedOperation);
    }

    return 0;
}


