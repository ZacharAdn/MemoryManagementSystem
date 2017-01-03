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
    static MemPool& getInstane(int heapSize) {
        static MemPool instance(heapSize);
        return instance;
    }

    //the class are singleton - the copy ctr and operator=, not need to be used
    MemPool(MemPool const&) = delete;
    void operator=(MemPool const&) = delete;

private:

    std::map<int, std::list<freeblock>> memoryLists;

    struct freeblock{
        struct freeblock *next;
        size_t size;
    };

    MemPool() {}

    MemPool(int heapSize) {
        char* HEAP = new char[heapSize];
        memoryLists = map<int, std::list<freeblock>>();
    }
};


#endif //CPPEX2_MEMPOOL_H
