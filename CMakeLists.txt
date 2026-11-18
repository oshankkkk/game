cmake_minimum_required(VERSION 3.16)

project(game C)

set(CMAKE_C_STANDARD 23)

find_package(raylib REQUIRED)

add_executable(game sand.c)

target_link_libraries(game raylib m)

