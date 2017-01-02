cmake_minimum_required(VERSION 3.6)
project(cppEx2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp MemPool.cpp MemPool.h)
add_executable(cppEx2 ${SOURCE_FILES})