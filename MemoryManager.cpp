//
// Created by zahar on 02/01/17.
//

#include <iostream>
#include "MemoryManager.h"
#include "FirstFitStrategy.h"




MemoryManager *MemoryManager::instance = nullptr;

MemoryManager::MemoryManager(size_t _heapSize, int strategyType)
        : heapSize(_heapSize) , pool(MemPool::getInstane(_heapSize)) , strategy(nullptr) {

    //set approach to memoryManager
    setStrategy(strategyType);
}

MemoryManager::MemoryManager() {}

MemoryManager::~MemoryManager() {
    delete pool;
    delete strategy;
}

MemoryManager *MemoryManager::getInstane(size_t heapSize,int strategyType) {
    if (!instance) {
        instance = new MemoryManager(heapSize,strategyType);
    }
    return instance;
}



void MemoryManager::setStrategy(int strategyType) {
    delete strategy;

    if(strategyType == FirstFit){
        strategy = new FirstFitStrategy(pool);
    }
    // if we want to add approach
}

void *MemoryManager::myAllocate(size_t size) {
    return strategy->myAllocate(size);
}

void MemoryManager::myFree(void *ptr) {
    strategy->myFree(ptr);
}

void MemoryManager::valgrind() {
    strategy->valgrind();
}

void *MemoryManager::operator new(size_t size){
    return malloc(size);
}

void MemoryManager::operator delete(void* ptr){
    free(ptr);
}
