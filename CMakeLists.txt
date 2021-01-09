cmake_minimum_required(VERSION 3.7)

project(server)
add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall -pthread")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

add_executable(server src/main.cpp src/socket.cpp src/socket_address.cpp)

target_link_libraries(server pthread)
