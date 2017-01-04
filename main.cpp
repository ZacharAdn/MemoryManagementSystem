#include <iostream>
#include <zconf.h>
#include <string>
#include "MemoryManager.h"
#include "MemPool.h"

#include "Operators.h"

using namespace std;

int main() {

//    void* m= sbrk(0);

    //int heapSize = 5;
//    MemPool& pool = MemPool::getInstane(5);
//
//    map<int, std::list<freeblock>> pooli = pool.getMemoryLists();

    MemoryManager mm(1000);

    int g [10]; // = new int[10];

    int * gt= new int[10];


    delete[] g;


    return 0;
}