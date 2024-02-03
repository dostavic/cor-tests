cmake_minimum_required(VERSION 3.10)
project(AsmP)

set(CMAKE_CXX_STANDART 14)

include_directories(src/Asmp)
include_directories(src/InfilGenerator)

add_subdirectory(src)
add_subdirectory(tst)
add_subdirectory(lib/googletest)