//
// Created by zahar on 16/01/17.
//

#include "MemPool.h"

MemPool *MemPool::instance = nullptr;

MemPool *MemPool::getInstane(size_t heapSize) {
    if(!instance) {
        instance = new MemPool(heapSize);
    }
    return instance;
}

void *MemPool::operator new(size_t size) {
    return malloc(size);
}

void MemPool::operator delete(void *ptr) {
    free(ptr);
}

void *MemPool::getNextFreeLocationPtr(size_t size) {
    // if its no space anymore
    if(size > availableSizeOnHeap){
        return nullptr;
    }
    availableSizeOnHeap -= size;
    void* addressLocation = &myHeap[indexLocation];
    indexLocation += size;

    return addressLocation;
}

MemPool::MemPool(size_t heapSize) {
    myHeap = (char*)malloc(heapSize);
    availableSizeOnHeap = heapSize;
    indexLocation = 0;
}