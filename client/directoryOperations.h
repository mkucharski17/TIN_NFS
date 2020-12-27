#ifndef CLIENT_DIRECTORYOPERATIONS_H
#define CLIENT_DIRECTORYOPERATIONS_H

///host – nazwa lub adres DNS serwera
///path – jak funkcja opendir()
///zwraca -1 gdy błąd, deskryptor katalogu(!) gdy operacja udana
int mynfs_opendir( char *host, char *path);

///dir_fd – deskryptor rekordu katalogowego zwrócony przez mynfs_opendir()
///Uwaga: systemowe funkcja readdir() zwraca za każdym razem strukturę dirent
/// zawierającą rekordy opisujące kolejne pliki z katalogu, tu wystarczy,
/// że funkcja zwróci samą nazwę.
char *mynfs_readdir(int dirfd); int mynfs_closedir(int dirfd);

///analogicznie do closedir()
mynfs_closedir(int dirfd);

#endif //CLIENT_DIRECTORYOPERATIONS_H
