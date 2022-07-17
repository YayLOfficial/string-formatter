cmake_minimum_required(VERSION 3.10)

project(fmt)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(fmt SHARED 
	src/fmt.c
	include/fmt.h)


