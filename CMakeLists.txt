cmake_minimum_required(VERSION 3.6)
project(cppEx2)

set(CMAKE_CXX_STANDARD 11)


set(SOURCE_FILES main.cpp MemPool.h MemoryManager.cpp MemoryManager.h MyAllocator.h freeblock.cpp freeblock.h FirstFitStrategy.cpp FirstFitStrategy.h AllocationStrategy.h blocksLinkedList.cpp blocksLinkedList.h CyclicGenericList.h MemPool.cpp)
add_executable(cppEx2 ${SOURCE_FILES})
