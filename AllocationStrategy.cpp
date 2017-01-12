//
// Created by zahar on 12/01/17.
//

#include <iostream>
#include "AllocationStrategy.h"

AllocationStrategy::AllocationStrategy(MemPool *pool) : pool(pool) {}

AllocationStrategy::~AllocationStrategy() {

}

void *AllocationStrategy::operator new(size_t size) {
    return malloc(size);
}

void AllocationStrategy::operator delete(void *ptr) {
    free(ptr);
}
