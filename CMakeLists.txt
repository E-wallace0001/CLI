cmake_minimum_required(VERSION 3.12)


set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

project(cli)
add_executable( cli main.c cli.c )

target_include_directories(cli PRIVATE ${CMAKE_CURRENT_LIST_DIR})

