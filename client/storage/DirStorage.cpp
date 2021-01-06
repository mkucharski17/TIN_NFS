#include "DirStorage.h"

DirStorage::DirStorage() {};

int DirStorage::get(int index) {
    return pathToDesc.at(index);
}

void DirStorage::add(std::string path, int desc) {
    pathToDesc.push_back({ path, desc });
}

void DirStorage::remove(int index) {
    pathToDesc.erase(pathToDesc.begin() + index);
}

void DirStorage::printAll() {
    for (auto const& pathAndDesc : pathToDesc) {
        std::cout << pathAndDesc.first << " : " << pathAndDesc.second << "\n";
    }
}