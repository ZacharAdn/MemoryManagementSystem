//
// Created by zahar on 11/01/17.
//

#ifndef CPPEX2_FIRSTFITSTRATEGY_H
#define CPPEX2_FIRSTFITSTRATEGY_H

#define MIN_CELL_SIZE 4
#include <vector>
#include <math.h>
#include "AllocationStrategy.h"
#include "freeblock.h"
#include "MyAllocator.h"
#include "blocksLinkedList.h"


class FirstFitStrategy : public AllocationStrategy {
public:

    FirstFitStrategy(MemPool *pool);

    virtual ~FirstFitStrategy();

    void* operator new(size_t size);

    void operator delete(void* ptr);

    void* myAllocate(size_t size);

    void myFree(void *ptr);

private:

    blocksLinkedList *freeList;

    std::map<void*,freeblock*, less<void*>, mystd::allocator<pair<void* ,freeblock*>>> associativeArray;

    freeblock *findCustomBlock(size_t size);

    size_t howMuchToCut(size_t currentBlockSize, size_t size);
};


#endif //CPPEX2_FIRSTFITSTRATEGY_H
