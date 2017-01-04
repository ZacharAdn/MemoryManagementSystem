//
// Created by zahar on 04/01/17.
//

#ifndef CPPEX2_OPERATORS_H
#define CPPEX2_OPERATORS_H

#include "MemoryManager.h"

//class MemoryManager;

MemoryManager manager(10000);

void* operator new(size_t size){
    return manager.allocate(size);
}


void* operator new[](size_t size){
    return manager.allocate(size);
}

void operator delete(void* toDelete){
    cout<<"delete";

    manager.free(toDelete);
}

void operator delete[](void* toDelete){
    cout<<"delete[]";
    manager.free(toDelete);
}


#endif //CPPEX2_OPERATORS_H

