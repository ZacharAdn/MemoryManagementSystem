//
// Created by zahar on 02/01/17.
//

#ifndef CPPEX2_MEMPOOL_H
#define CPPEX2_MEMPOOL_H


#include <cstdio>
#include <zconf.h>
#include <map>
#include <list>

using namespace std;



class MemPool {
public:
    static MemPool& getInstane(size_t heapSize) {
        static MemPool instance(heapSize);
        return instance;
    }

    //the class are singleton - the copy ctr and operator=, not need to be used
    MemPool(MemPool const&) = delete;
    void operator=(MemPool const&) = delete;

    void* getNextFreeLocationPtr(size_t size){
        this->currentFreeLocation_ptr = this->nextFreeLocation_ptr;
        this->nextFreeLocation_ptr = nextFreeLocation_ptr  + size;
        return this->currentFreeLocation_ptr;
    }


private:
    MemPool() {}
    void* nextFreeLocation_ptr;
    void* currentFreeLocation_ptr;
    MemPool(size_t heapSize) {
        char* myHeap;
        myHeap = (char*)malloc(heapSize);
        nextFreeLocation_ptr = myHeap;
    }

};


#endif //CPPEX2_MEMPOOL_H
