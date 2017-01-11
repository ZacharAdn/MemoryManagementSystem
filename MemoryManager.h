//
// Created by zahar on 02/01/17.
//

#ifndef CPPEX2_MEMORYMANAGER_H
#define CPPEX2_MEMORYMANAGER_H


#include <cstddef>
#include <vector>
#include "MemPool.h"
#include "MyAllocator.h"
#include "freeblock.h"


class MemoryManager {
public:
    MemoryManager();

    MemoryManager(size_t heapSize);

    virtual ~MemoryManager();

//    size_t getHeapSize() const;

    int findBlock(void* ptr);

    void* allocate(size_t);

    void   free(void*);

private:
//    std::map<size_t, std::list<freeblock, mystd::MyAllocator<freeblock>>,
//            less<size_t>,
//            mystd::MyAllocator<pair<size_t, std::list<freeblock, mystd::MyAllocator<freeblock>>>>> *freeLists;
//
//    std::map<void*,
//            size_t ,
//            less<void*> ,
//            mystd::MyAllocator<pair<void*, size_t>>> associativeArray;


    std::vector<freeblock, mystd::allocator<freeblock>> blocksList;

    std::vector<freeblock, mystd::allocator<freeblock>> freeList;

    MemPool *pool ;

    size_t heapSize;

    size_t numOfBlocks;

    size_t numOfBytes;};


#endif //CPPEX2_MEMORYMANAGER_H
