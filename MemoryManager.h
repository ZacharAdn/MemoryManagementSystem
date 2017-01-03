//
// Created by zahar on 02/01/17.
//

#ifndef CPPEX2_MEMORYMANAGER_H
#define CPPEX2_MEMORYMANAGER_H


#include <cstddef>
class MemoryManager {
public:
    MemoryManager();

    virtual ~MemoryManager();

private:

    void* allocate(size_t);
    void   free(void*);



};


#endif //CPPEX2_MEMORYMANAGER_H
