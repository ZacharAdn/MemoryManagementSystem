#include <iostream>
#include <zconf.h>
#include <string>
#include "MemoryManager.h"
#include "MemPool.h"

#include "Operators.h"

using namespace std;

int main() {

//    MemoryManager mm(1000);

    int * g = new int[10];

    int * gt= new int[10];

    int *t = new int(5);

    delete[] g;

    return 0;
}