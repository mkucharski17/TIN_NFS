#ifndef TIN_NFS_STORAGE_H
#define TIN_NFS_STORAGE_H

#include <unordered_map>
#include <dirent.h>

class Storage {
private:
    std::unordered_map<int, DIR*> map;
    Storage();
public:
    static Storage& instance() {
        static Storage INSTANCE;
        return INSTANCE;
    }
    DIR* get(int fd);
    void add(int fd, DIR *dir);
    void remove(int fd);
};

#endif //TIN_NFS_STORAGE_H
