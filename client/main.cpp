
#include <data_structures/codes.h>
#include <file/open/open.h>
#include <authorization/authorization.h>


int main() {
    ///polaczenie z serwerem
    sendConnectRequest((char *) "127.0.0.1", (char *) "login", (char *) "haslologinu");
    ///otwarcie pliku
//    mynfs_open((char *) "127.0.0.1", (char *) "home/desktop", O_RDONLY, 999);


    return 0;

}


