#ifndef TIN_NFS_DIRSTORAGE_H
#define TIN_NFS_DIRSTORAGE_H

#include <map>
#include <vector>
#include <dirent.h>
#include <iostream>

class DirStorage {
private:
    std::vector<std::pair<std::string, int>> pathToDesc;
    std::vector<std::pair<std::string, int>> files;
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
    bool dirEmpty();

    std::pair<std::string, int> getFile(int index);
    void addFile(std::string path, int desc);
    void removeFile(int index);
    void printAllFiles();
    bool fileEmpty();
};

#endif //TIN_NFS_DIRSTORAGE_H
