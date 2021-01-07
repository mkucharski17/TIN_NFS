#include "DirStorage.h"

DirStorage::DirStorage() {};

std::pair<std::string, int> DirStorage::get(int index) {
    return pathToDesc.at(index);
}

void DirStorage::add(std::string path, int desc) {
    pathToDesc.push_back({ path, desc });
}

void DirStorage::remove(int index) {
    pathToDesc.erase(pathToDesc.begin() + index);
}

void DirStorage::printAll() {
    std::vector<std::pair<std::string, int>>::size_type i;
    for (i = 0; i != pathToDesc.size(); i++) {
        std::cout << i << ". " << pathToDesc.at(i).first  << "\n";
    }
}

std::pair<std::string, int> getFile(int index)
{
    return files.at(index);
}
void addFile(std::string path, int desc)
{
    files.push_back({path,desc});
}
void removeFile(int index)
{
    files.erase(files.begin()+index);
}
void printAllFiles()
{
     std::vector<std::pair<std::string, int>>::size_type i;
    for (i = 0; i != files.size(); i++) {
        std::cout << i << ". " << files.at(i).first  << "\n";
    }
}