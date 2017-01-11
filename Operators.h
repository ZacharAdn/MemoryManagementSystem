//
// Created by zahar on 04/01/17.
//

#ifndef CPPEX2_OPERATORS_H
#define CPPEX2_OPERATORS_H

#include "MemoryManager.h"


MemoryManager manager(10000);//TODO find the right way to allocate
//mystd::allocator MemoryManager manager;



void* operator new(size_t size){
    cout << "new\n";
    return manager.allocate(size);
}


void* operator new[](size_t size){
    cout << "new []\n";
    return manager.allocate(size);
}

void operator delete(void* toDelete){
    cout<<"delete\n";

    manager.free(toDelete);
}

void operator delete[](void* toDelete){
    cout<<"delete[]\n";
    manager.free(toDelete);
}


#endif //CPPEX2_OPERATORS_H

