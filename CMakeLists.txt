cmake_minimum_required(VERSION 3.0)
project(test)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

SET(LIBPATH "/home/zimon/lib")

file(GLOB_RECURSE LIBRARIES CONFIGURE_DEPENDS ${LIBPATH}/lib*.so)

add_executable(exec test/main.c)

# Add other flags to the compiler
add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)

# Include header files
target_include_directories(exec PRIVATE 
	/home/zimon/include)

# Link libraries
target_link_libraries(exec PRIVATE ${LIBRARIES})
