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

    /**
     * Allocation Type - First Fit
     * override the pure virtual of the abstract class AllocationStrategy
     * @param pool
     */
    FirstFitStrategy(MemPool *pool);

    /**
     * Dctr - iterate the Map and delete all the free block and the LinkedList
     */
    virtual ~FirstFitStrategy();

    /**
     * override operator new
     * @param size
     * @return
     */
    void* operator new(size_t size);

    /**
     * override operator delete
     * @param ptr
     */
    void operator delete(void* ptr);

    /**
     * find block to allocate on the freeList
     * allocate on the pool if its no such block
     * @param size
     * @return ptr to the allocated place
     */
    void* myAllocate(size_t size);

    /**
     * add block to the freeList
     * @param ptr
     */
    void myFree(void *ptr);

    /**
     * check for memory leak
     */
    void valgrind();

private:

    /**
     * LinkedList of freeBlocks - store all the free blocks
     */
    blocksLinkedList *freeList;

    /**
     * map of all the allocated blocks - mapped by the ptr of the blovk
     */
    std::map<void*,freeblock*, less<void*>, mystd::allocator<pair<void* ,freeblock*>>> associativeArray;

    /**
     * finds block on the freeList
     * @param size
     * @return freeblock to allocate on
     */
    freeblock *findCustomBlock(size_t size);
};


#endif //CPPEX2_FIRSTFITSTRATEGY_H
