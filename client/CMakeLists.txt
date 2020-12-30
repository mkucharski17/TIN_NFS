cmake_minimum_required(VERSION 3.17)
project(client)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(client
        data_structures
        directoryOperations.h
        fileOperations.cpp
        fileOperations.h
        main.cpp file/open/open.cpp file/open/open.h authorization/authorization.cpp authorization/authorization.h send_message/send_message.cpp send_message/send_message.h)
