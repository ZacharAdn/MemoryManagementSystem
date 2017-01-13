//
// Created by zahar on 11/01/17.
//

#ifndef CPPEX2_FIRSTFITSTRATEGY_H
#define CPPEX2_FIRSTFITSTRATEGY_H

#include <vector>
#include <math.h>
#include "AllocationStrategy.h"
#include "freeblock.h"
#include "MyAllocator.h"


class FirstFitStrategy : public AllocationStrategy {
public:

    FirstFitStrategy(MemPool *pool);

    virtual ~FirstFitStrategy();

    void* operator new(size_t size);

    void operator delete(void* ptr);

    void* myAllocate(size_t size);

    void myFree(void *ptr);

    int findBlock(void* ptr);

private:

    std::vector<freeblock*, mystd::allocator<freeblock*>> freeList;

    std::vector<freeblock*, mystd::allocator<freeblock*>> blocksList;


};


#endif //CPPEX2_FIRSTFITSTRATEGY_H
