//
// Created by zahar on 12/01/17.
//

#ifndef CPPEX2_ALLOCATIONSTRATEGY_H
#define CPPEX2_ALLOCATIONSTRATEGY_H


#include <cstdio>
#include "MemPool.h"

class AllocationStrategy {
public:

    /**
     * Abstract class of allocation type
     * @param pool
     */
    AllocationStrategy(MemPool *pool) : pool(pool){}

    /**
     * dstr
     */
    virtual ~AllocationStrategy(){}

    /**
     * pure virtual Allocation
     *
     * @param size to allocate
     * @return ptr on the pool
     */
    virtual void* myAllocate(size_t size) =0 ;

    /**
     * pure virtual Deallocation
     *
     * @param ptr to free
     */
    virtual void myFree(void *ptr) =0 ;

    /**
     * function for memory leak check
     */
    virtual void valgrind() =0;

protected:

    /**
     * my Heap
     */
    MemPool *pool;
};


#endif //CPPEX2_ALLOCATIONSTRATEGY_H
