//
// Created by zahar on 02/01/17.
//

#include <iostream>
#include "MemoryManager.h"
#include "math.h"
#include "MemPool.h"
#include "MyAllocator.h"

class freeblock;

MemoryManager::MemoryManager(size_t heapSize) {

//    std::map<int, std::list<freeblock>> listi ();
//            (std::map<int, std::list < freeblock>>*) listi;
    pool = &MemPool::getInstane(heapSize);
    MyAllocator<> m;
    void* ptr;
    void* t = m.allocate(5,ptr);
    associativeArray = m.allocate(1000,ptr);
//    associativeArray= (std::map<void*,int>*)malloc(1000);
//    associativeArray  = new std::map<void*,int> (1000);
//    freeLists = new std::map<int, std::list < freeblock>>();
    //TODO check where it save
}

MemoryManager::~MemoryManager() {

}

void *MemoryManager::allocate(size_t size) {
    /////////////////////////////////////////////////////////
    //here need to check if we have free block in the freeList//
    ////////////////////////////////////////////////////////
    void* ptr=this->pool->getNextFreeLocationPtr(size);
    associativeArray.insert(std::pair<void*,int>(ptr,size));
    return ptr;

}

MemoryManager::MemoryManager() {}

void MemoryManager::free(void* pointer) {
   int size= associativeArray.at(pointer);
   cout<< size;
}
