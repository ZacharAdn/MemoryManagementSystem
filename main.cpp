#include <iostream>
#include <zconf.h>
#include <string>
#include "MemoryManager.h"
#include "MemPool.h"

using namespace std;

int main() {

//    void* m= sbrk(0);

    MemPool& pool = MemPool::getInstane();

    return 0;
}