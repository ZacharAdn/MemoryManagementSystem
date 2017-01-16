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

    /**
     * enum for the approaches can used the memory manager
     * if we want to add new approach
     */
    enum AllocationType{
        FirstFit
    };

    /**
     *  the access to the singleton object - default type approach: FirsFit
     */
    static MemoryManager* getInstane(size_t heapSize=0, int type = FirstFit);

    /**
     * the class is singleton - the copy ctr and operator=, not need to be used
     */
    MemoryManager(MemoryManager const&) = delete;
    void operator=(MemoryManager const&) = delete;

    /**
     * override to operator new
     * @param size
     * @return
     */
    void* operator new (size_t size);

    /**
     * override to operator delete
     * @param ptr
     */
    void operator delete(void* ptr);

    /**
     * allocation on memoryManager by approach (default - first fit)
     * @param size
     * @return
     */
    void* myAllocate(size_t size);

    /**
     * deallocation by approach(default - first fit)
     * @param ptr
     */
    void myFree(void *ptr);

    /**
     * memory leak check
     */
    void valgrind();

    /**
     * Dctr
     */
    ~MemoryManager();

    /**
     * the allocation type object
     */
    AllocationStrategy *strategy;

private:

    /**
     * Ctr
     */
    MemoryManager();

    /**
     * Ctr - called by the instance func
     * @param heapSize
     * @param strategyType
     */
    MemoryManager(size_t heapSize,int strategyType);

    /**
     * the singleton object
     */
    static MemoryManager *instance;

    /**
     * the pool
     */
    MemPool *pool;

    /**
     *
     */
    size_t heapSize;

    /**
     * set approach to memoryManager
     * @param pStrategy
     */
    void setStrategy(int pStrategy);
};


#endif //CPPEX2_MEMORYMANAGER_H
