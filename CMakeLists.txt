cmake_minimum_required(VERSION 3.0)
project(main)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(lib)

add_executable(exec main.c)

target_link_libraries(exec PRIVATE fmt)
