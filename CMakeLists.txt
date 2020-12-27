cmake_minimum_required(VERSION 3.17)
project(TIN_NFS)

set(CMAKE_CXX_STANDARD 14)

add_executable(TIN_NFS main.cpp data_structures/client_msg.h data_structures/server_msg.h data_structures/codes.h)