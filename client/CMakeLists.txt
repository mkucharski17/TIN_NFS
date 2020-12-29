cmake_minimum_required(VERSION 3.17)
project(client)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(client
        data_structures
        directoryOperations.h
        fileOperations.cpp
        fileOperations.h
        main.cpp)
