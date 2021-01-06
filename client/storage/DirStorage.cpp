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