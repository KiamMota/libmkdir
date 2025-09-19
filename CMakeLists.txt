cmake_minimum_required(VERSION 3.16)
project(libmkdir C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(dirlist test/dirlist.c)

include_directories(${CMAKE_SOURCE_DIR})
