#include <iostream>
#include "MemoryManager.h"
#include "systemTools.h"


using namespace std;



int main() {

    MemoryManager *memoryManager = MemoryManager::getInstane(1000, MemoryManager::AllocationType::FirstFit);
    MemoryManager *memoryManager2= MemoryManager::getInstane(10, MemoryManager::AllocationType::FirstFit);

    int *g = new int[10];
    delete[] g;

    int *t = new int(5);
    delete t;

    char *a = new char('&');

    int *gt= new int[10];


    delete [] gt;

    return 0;
}
