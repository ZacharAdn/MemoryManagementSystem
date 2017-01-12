//
// Created by zahar on 12/01/17.
//

#ifndef CPPEX2_ALLOCATIONSTRATEGY_H
#define CPPEX2_ALLOCATIONSTRATEGY_H


#include <cstdio>
#include "MemPool.h"

class AllocationStrategy {
public:

    AllocationStrategy(MemPool *pool);

    virtual ~AllocationStrategy();

    virtual void* myAllocate(size_t size) =0 ;

    virtual void myFree(void *ptr) =0 ;

    void* operator new (size_t size);

    void operator delete(void* ptr);


protected:

    MemPool *pool;
};


#endif //CPPEX2_ALLOCATIONSTRATEGY_H
