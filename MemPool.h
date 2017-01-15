//
// Created by zahar on 02/01/17.
//

#ifndef CPPEX2_MEMPOOL_H
#define CPPEX2_MEMPOOL_H


#include <cstdio>
#include <zconf.h>
#include <map>
#include <list>
#include <iostream>
#include "freeblock.h"


using namespace std;



class MemPool {
public:
    static MemPool* getInstane(size_t heapSize) {
        static MemPool* instance = new MemPool(heapSize);
        return instance;
    }

    //the class are singleton - the copy ctr and operator=, not need to be used
    MemPool(MemPool const&) = delete;
    void operator=(MemPool const&) = delete;

    void* operator new(size_t size){
        return malloc(size);
    }

    void operator delete(void* ptr){
        free(ptr);
    }

    void* getNextFreeLocationPtr(size_t size){
        if(size > availableSizeOnHeap){
            return nullptr;
        }
        availableSizeOnHeap -= size;
        addressLocation = &myHeap[indexLocation];
        indexLocation += size;

        cout << "\nallocated: " << to_string(availableSizeOnHeap) << "\n";

        return addressLocation;
    }


private:
    MemPool() {}
    void* addressLocation;
    size_t indexLocation;
    size_t availableSizeOnHeap ;
    char* myHeap;

    MemPool(size_t heapSize) {
        availableSizeOnHeap =heapSize;
        myHeap = (char*)malloc(heapSize);
        indexLocation = 0;
    }

};

#endif //CPPEX2_MEMPOOL_H
