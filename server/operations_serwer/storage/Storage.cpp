#include "Storage.h"

Storage::Storage() {};

DIR* Storage::get(int fd) {
    return map.find(fd)->second;
}

void Storage::add(int fd, DIR *dir) {
    map.insert({ fd, dir });
}

void Storage::remove(int fd) {
    map.erase(fd);
}

int getFD(int fd)
{
    return fileMap.find(fd)->second;
}
int addFD(int fd)
{
    if(fd == -1) return -1;
    fileMap.insert({ lastFD, fd });
    return lastFD++;
}
    
void removeFD(int fd)
{
    fileMap.erase(fd);
}