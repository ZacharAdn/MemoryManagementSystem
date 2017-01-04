//
// Created by zahar on 02/01/17.
//

#ifndef CPPEX2_MEMORYMANAGER_H
#define CPPEX2_MEMORYMANAGER_H


#include <cstddef>
#include "MemPool.h"
//#include "Operators.h"

struct freeblock{
    struct freeblock *next;
    size_t size;
};

class MemoryManager {
public:
    MemoryManager();

    size_t getHeapSize() const;

    MemoryManager(size_t heapSize);

    virtual ~MemoryManager();


    void* allocate(size_t);
    void   free(void*);




private:
    std::map<int, std::list<freeblock>> *freeLists;
    static std::map<void*,int> associativeArray;
    MemPool *pool ;
    size_t heapSize;

};


#endif //CPPEX2_MEMORYMANAGER_H
