cmake_minimum_required(VERSION 3.16)
project(libmkdir C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(main test/main.c)
add_executable(rename test/rename.c)

include_directories(include)
