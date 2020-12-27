
#ifndef CLIENT_OPERATIONS_H
#define CLIENT_OPERATIONS_H


///host – nazwa lub adres DNS serwera
/// path, oflag, mode – jak w funkcji systemowej open()
/// (dozwolone są modyfikacje lub ograniczenia)
/// zwraca: -1 gdy błąd, deskryptor pliku gdy operacja udana
/// należy zaimplementować co najmniej następujące tryby otwarcia pliku:
/// O_RDONLY, O_WRONLY, O_RDWR, O_CREAT
int mynfs_open(char *host, char *path, int oflag, int mode);

int mynfs_read();

int mynfs_write();
int mynfs_lseek();
int mynfs_close();
int mynfs_unlink(char *host, char *path);

///pobiera atrybuty otwartego pliku - analogicznie do funkcji systemowej fstat();
mynfs_fstat(int mynfs_fd);
#endif //CLIENT_OPERATIONS_H
