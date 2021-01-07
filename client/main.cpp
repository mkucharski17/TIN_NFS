#include "data_structures/codes.h"
#include "authorization/authorization.h"
#include <iostream>
#include "storage/DirStorage.h"
#include "directoryOperations.h"
#include "file/open/open.h"
#include "fileOperations.h"

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
    if(fd ==-1) {
        std::cout<<"An error occured during dir opening\n";
        fprintf(stderr, "Value of errno: %d\n", errno);
        return;
    }
    DirStorage::instance().add(path, dir_fd);
}

void readDirectory() {
    if(DirStorage::instance().dirEmpty()) {
        std::cout << "There is no open directory!\n";
        return;
    }
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
    if(DirStorage::instance().dirEmpty()) {
        std::cout << "There is no open directory!\n";
        return;
    }
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

void openFile() {
    std::string path;
    std::cout << "Provide file path:\n";
    std::cin >> path;
    std::cout << "path: " << path << "\n";
    
    int oflag;
    std::cout << "Choose file access flag:\n";
    std::cout << "0. read-only\n";
    std::cout << "1. write-only\n";
    std::cout << "2. read/write\n";
    std::cin >> oflag;

    int mode;
    std::cout << "Provide mode:\n";
    std::cin >> mode;

    int fd =  mynfs_open ( (char*) path.c_str(),  oflag,  mode);

    if(fd ==-1)
    {
        std::cout<<"An error occured during file opening\n";
        fprintf(stderr, "Value of errno: %d\n", errno);
        return;
    }
   
    DirStorage::instance().addFile(path, fd);
}

int readFile() {
    if(DirStorage::instance().fileEmpty()) {
        std::cout << "There is no open file!\n";
        return -1;
    }
    int index = 0;
    std::cout << "Choose file to read:\n";
    DirStorage::instance().printAllFiles();
    while (true) {
        std::cin >> index;
        try {
            int fd = DirStorage::instance().getFile(index).second;
		
            int bytes_number;
            std::cout<< "How many bytes read:\n";
            std::cin >> bytes_number;
            if(bytes_number == 0 || bytes_number>1023) {
                    std::cout<<"invalid bytes number\n";
                    return -1;
            }
            void* buffer;
            buffer = (void*)malloc(bytes_number*sizeof(char));

            int result = mynfs_read(fd, buffer , bytes_number);
            if(result ==-1) {
                //błąd
                std::cout<<"An error occured during reading\n";
                fprintf(stderr, "Value of errno: %d\n", errno);
                return -1;
            }
            std::cout << "Bytes read: " << (char*)buffer<<std::endl;
            return 0;
        } catch (const std::out_of_range& e) {
            std::cout << "Index out of range!\n";
        }
    }
}
int writeFile() {
    if(DirStorage::instance().fileEmpty()) {
        std::cout << "There is no open file!\n";
        return -1;
    }
    int index = 0;
    std::cout << "Choose file to write:\n";
    DirStorage::instance().printAllFiles();
    while (true) {
        std::cin >> index;
        try {
            int fd = DirStorage::instance().getFile(index).second;
            std::string text;
            
            std::cout << "Write text:" << std::endl;
            std::getline(std::cin >> std::ws, text);
            if(text.length()==0 || text.length()>1023) {
                std::cout<<"invalid text length\n";
                return -1;
            }
            char char_array[1024];
            strcpy(char_array, text.c_str());

            int result = mynfs_write(fd, &char_array , text.length());
            if(result ==-1) {
                //błąd
                std::cout<<"An error occured during writing\n";
                fprintf(stderr, "Value of errno: %d\n", errno);
                return -1;
            }
            std::cout << "Bytes written:" << result<<std::endl;
            return 0;
        } catch (const std::out_of_range& e) {
            std::cout << "Index out of range!\n";
        }
    }
}
void lSeekFile() {
    if(DirStorage::instance().fileEmpty()) {
        std::cout << "There is no open file!\n";
        return;
    }
    int index = 0;
    std::cout << "Choose file to lseek:\n";
    DirStorage::instance().printAllFiles();
    while (true) {
        std::cin >> index;
        try {
            int fd = DirStorage::instance().getFile(index).second;
            
            int offset,whence;
            
            std::cout << "Write offset:" << std::endl;
            std::cin>>offset;
            if(offset<0) {
                std::cout<<"invalid offset\n";
                return ;
            }

            std::cout << "Choose whence:\n";
            std::cout << "0. SEEK_SET\n";
            std::cout << "1. SEEK_CUR\n";
            std::cout << "2. SEEK_END\n";
            std::cin >> whence;
            
            if(whence<0 || whence >2) {
                std::cout<<"invalid whence\n";
                return ;
            }
            int result = mynfs_lseek( fd,  offset, whence); 

            if(result ==-1) {
                //błąd
                std::cout<<"An error occured during writing\n";
                fprintf(stderr, "Value of errno: %d\n", errno);
                return;
            }
            return;
        } catch (const std::out_of_range& e) {
            std::cout << "Index out of range!\n";
        }
    }
}


void closeFile() {
    if(DirStorage::instance().fileEmpty()) {
        std::cout << "There is no open file!\n";
        return;
    }
    int index = 0;
    std::cout << "Choose file to close:\n";
    DirStorage::instance().printAllFiles();
    while (true) {
        std::cin >> index;
        try {
           int fd = DirStorage::instance().getFile(index).second;
            
           int result= mynfs_close(fd);
           if(result ==-1) {
                //błąd
                std::cout<<"An error occured during closing\n";
                fprintf(stderr, "Value of errno: %d\n", errno);
                return;
            } else {
                DirStorage::instance().removeFile(fd);
                std::cout<<"File is closed\n";
                return;
            }
        } catch (const std::out_of_range& e) {
            std::cout << "Index out of range!\n";
        }
    }
}

void unlinkFile() {
    std::string path;
    std::cout << "Provide file path:\n";
    std::cin >> path;
    std::cout << "path: " << path << "\n";

    int result= mynfs_unlink((char*) path.c_str()) ;

    if(result ==-1) {
        //błąd
        std::cout<<"An error occured during unlinking\n";
        fprintf(stderr, "Value of errno: %d\n", errno);
        return;
    } 
    std::cout<<"File is unlinked\n";
}

void fstatFile() {
    if(DirStorage::instance().fileEmpty()) {
        std::cout << "There is no open file!\n";
        return;
    }
    int index = 0;
    std::cout << "Choose file to fstat:\n";
    DirStorage::instance().printAllFiles();
    while (true) {
        std::cin >> index;
        try {
            int fd = DirStorage::instance().getFile(index).second;
            
            struct stat file_stats;
           int result= mynfs_fstat(fd,&file_stats);

            if(result ==-1) {
                //błąd
                std::cout<<"An error occured during fstat\n";
                fprintf(stderr, "Value of errno: %d\n", errno);
                return;
            }

            printf(" device: %lld\n",                       file_stats.st_dev);
            printf(" inode: %ld\n",                         file_stats.st_ino);
            printf(" protection: %o\n",                     file_stats.st_mode);
            printf(" number of hard links: %d\n",           file_stats.st_nlink);
            printf(" user ID of owner: %d\n",               file_stats.st_uid);
            printf(" group ID of owner: %d\n",              file_stats.st_gid);
            printf(" device type (if inode device): %lld\n",file_stats.st_rdev);
            printf(" total size, in bytes: %ld\n",          file_stats.st_size);
            printf(" blocksize for filesystem I/O: %ld\n",  file_stats.st_blksize);
            printf(" number of blocks allocated: %ld\n",    file_stats.st_blocks);
            printf(" time of last access: %ld : %s",        file_stats.st_atime, ctime(&file_stats.st_atime));
            printf(" time of last modification: %ld : %s",  file_stats.st_mtime, ctime(&file_stats.st_mtime));
            printf(" time of last change: %ld : %s",        file_stats.st_ctime, ctime(&file_stats.st_ctime));
            
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
                openFile();
            }break;
	    case READ_FILE_REQUEST: {
                readFile();
            }break;
            case WRITE_FILE_REQUEST: {
                writeFile();
            }break;
            case LSEEK_FILE_REQUEST: {
                lSeekFile();
            }break;
            case CLOSE_FILE_REQUEST: {
                closeFile();
            }break;
            case UNLINK_FILE_REQUEST: {
                unlinkFile();
            }break;
            case FSTAT_FILE_REQUEST: {
                fstatFile();
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


