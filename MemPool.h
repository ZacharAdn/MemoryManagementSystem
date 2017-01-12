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
    static MemPool* getInstane(size_t heapSize) {
        static MemPool* instance = new MemPool(heapSize);
        return instance;
    }

    //the class are singleton - the copy ctr and operator=, not need to be used
    MemPool(MemPool const&) = delete;
    void operator=(MemPool const&) = delete;

    void* getNextFreeLocationPtr(size_t size){
        if(this->availableSize < size){
            return nullptr;
        }
        availableSize = availableSize - size;
        this->currentFreeLocation_ptr = this->currentFreeLocation_ptr +size;//this->nextFreeLocation_ptr;
//        this->nextFreeLocation_ptr = nextFreeLocation_ptr  + size;
        return (void*)(&myHeap[this->currentFreeLocation_ptr-size]);
    }


private:
    MemPool() {}
//    void* nextFreeLocation_ptr;
    size_t currentFreeLocation_ptr;
    size_t availableSize ;
    char* myHeap;

    MemPool(size_t heapSize) {
        availableSize =heapSize;
        myHeap = (char*)malloc(heapSize);
        this->currentFreeLocation_ptr = 0;
//        nextFreeLocation_ptr = myHeap;
    }


    void* operator new(size_t size){
        return malloc(size);
    }

    void operator delete(void* ptr){
        free(ptr);
    }

};


#endif //CPPEX2_MEMPOOL_H
