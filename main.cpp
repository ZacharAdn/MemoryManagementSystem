#include <iostream>
#include "MemoryManager.h"


using namespace std;



int main() {

    MemoryManager *memoryManager = MemoryManager::getInstane(1000, MemoryManager::AllocationType::FirstFit);
    MemoryManager *memoryManager2= MemoryManager::getInstane(10, MemoryManager::AllocationType::FirstFit);

    int *t = new int(5);

    char *a = new char('&');

    int * g = new int[10];

    int * gt= new int[10];


    delete (t);

    delete [] gt;

    return 0;
}


void* operator new(size_t size){
    cout << "new\n";
    return MemoryManager::getInstane()->myAllocate(size);
}


void* operator new[](size_t size){
    cout << "new []\n";
    return MemoryManager::getInstane()->myAllocate(size);
}

void operator delete(void* toDelete){
    cout<<"delete\n";
    MemoryManager::getInstane()->myFree(toDelete);
}

void operator delete[](void* toDelete){
    cout<<"delete[]\n";
    MemoryManager::getInstane()->myFree(toDelete);
}

