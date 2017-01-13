//
// Created by zahar on 11/01/17.
//

#ifndef CPPEX2_SYSTEMTOOLS_H
#define CPPEX2_SYSTEMTOOLS_H

#include <iostream>
#include "MemoryManager.h"

using namespace std;
//
//class systemTools {
//
//public:
//    systemTools();
//
//    virtual ~systemTools();
//
//    void* operator new(size_t size);
//
//    void* operator new[](size_t size){
//
//        private:
//
//};


void* operator new(size_t size){
    cout << "new\n";
    return MemoryManager::getInstane()->myAllocate(size);
}


void* operator new[](size_t size){
    cout << "new []\n";
    return MemoryManager::getInstane()->myAllocate(size);
}

void operator delete(void* toDelete){
    cout<<"delete\n";
    MemoryManager::getInstane()->myFree(toDelete);
}

void operator delete[](void* toDelete){
    cout<<"delete[]\n";
    MemoryManager::getInstane()->myFree(toDelete);
}


#endif //CPPEX2_SYSTEMTOOLS_H
