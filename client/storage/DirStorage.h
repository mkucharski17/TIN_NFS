#ifndef TIN_NFS_DIRSTORAGE_H
#define TIN_NFS_DIRSTORAGE_H

#include <map>
#include <vector>
#include <dirent.h>
#include <iostream>

class DirStorage {
private:
    std::vector<std::pair<std::string, int>> pathToDesc;
    DirStorage();
public:
    static DirStorage& instance() {
        static DirStorage INSTANCE;
        return INSTANCE;
    }
    std::pair<std::string, int> get(int index);
    void add(std::string path, int desc);
    void remove(int index);
    void printAll();
};

#endif //TIN_NFS_DIRSTORAGE_H
