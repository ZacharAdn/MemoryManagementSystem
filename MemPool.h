//
// Created by zahar on 02/01/17.
//

#ifndef CPPEX2_MEMPOOL_H
#define CPPEX2_MEMPOOL_H


#include <cstdio>
#include <map>
#include <list>
#include "freeblock.h"


using namespace std;



class MemPool {
public:

    /**
     * the access to the singleton object
     * @param heapSize
     * @return
     */
    static MemPool* getInstane(size_t heapSize);

    /**
     * the class is singleton - the copy ctr and operator=, not need to be used
     */
    MemPool(MemPool const&) = delete;
    void operator=(MemPool const&) = delete;

    /**
     * override to operator new
     * @param size
     * @return
     */
    void* operator new(size_t size);

    /**
     * override to operator delete
     * @param ptr
     */
    void operator delete(void* ptr);

    /**
     *
     * @param size
     * @return the next free location on the pool
     */
    void* getNextFreeLocationPtr(size_t size);

    /**
     * the singleton object
     */
    static MemPool* instance;

private:

    /**
     * the pool
     */
    char* myHeap;

    /**
     * index of the last location that allocated
     */
    size_t indexLocation;

    /**
     * available size on the heap
     */
    size_t availableSizeOnHeap;

    /**
     * ctr
     */
    MemPool() {}

    /**
     * ctr - called from the instance
     * @param heapSize
     */
    MemPool(size_t heapSize);
};

#endif //CPPEX2_MEMPOOL_H
