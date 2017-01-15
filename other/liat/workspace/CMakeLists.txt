cmake_minimum_required(VERSION 2.6)

project(heap_manager)

set(CMAKE_CXX_FLAGS "-Wall -rdynamic -std=c++11")

include_directories(header)

file(GLOB SOURCES src/*.cpp)

add_executable(run_game.o ${SOURCES})
