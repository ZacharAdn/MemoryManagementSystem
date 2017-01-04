//
// Created by zahar on 02/01/17.
//

#include <iostream>
#include "MemoryManager.h"
#include "math.h"
#include "MemPool.h"

class freeblock;

MemoryManager::MemoryManager(size_t heapSize) {

//    std::map<int, std::list<freeblock>> listi ();
//            (std::map<int, std::list < freeblock>>*) listi;
    pool = &MemPool::getInstane(heapSize);
    freeLists = new std::map<int, std::list < freeblock>>();


}

MemoryManager::~MemoryManager() {

}

void *MemoryManager::allocate(size_t size) {
    /////////////////////////////////////////////////////////
    //here need to check if we have free block in the freeList//
    ////////////////////////////////////////////////////////
    return this->pool->getNextFreeLocationPtr(size);

}

MemoryManager::MemoryManager() {}

void MemoryManager::free(void *) {

   cout<< sizeof(void *);
}
