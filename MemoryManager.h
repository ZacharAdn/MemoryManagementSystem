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
#include "math.h"
#include "AllocationStrategy.h"

using namespace std;

class MemoryManager {
public:

    enum AllocationType{
        FirstFit
    };

    static MemoryManager* getInstane(size_t heapSize=0, int type = FirstFit);

    //the class are singleton - the copy ctr and operator=, not need to be used
    MemoryManager(MemoryManager const&) = delete;

    void operator=(MemoryManager const&) = delete;


    void* operator new (size_t size);

    void operator delete(void* ptr);


    void* myAllocate(size_t size);

    void myFree(void *ptr);

    ~MemoryManager();

    AllocationStrategy *strategy;


private:

    MemoryManager();

    MemoryManager(size_t heapSize,int strategyType);

    static MemoryManager *instance;

    MemPool *pool;

    size_t heapSize;

    size_t numOfBlocks;

    size_t numOfBytes;

    void * setStrategy(int pStrategy);
};


#endif //CPPEX2_MEMORYMANAGER_H
