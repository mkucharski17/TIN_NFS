#include "Storage.h"

DIR* Storage::get(int fd) {
    return map.find(fd)->second;
}

void Storage::add(int fd, DIR *dir) {
    map.insert({ fd, dir });
}

void Storage::remove(int fd) {
    map.erase(fd);
}