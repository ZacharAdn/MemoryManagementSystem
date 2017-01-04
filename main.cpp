#include <iostream>
#include <zconf.h>
#include <string>
#include "MemoryManager.h"
#include "MemPool.h"

#include "Operators.h"

using namespace std;

int main() {

    MemoryManager mm(1000);

    int g [20]; // = new int[10];

    int * gt= new int[10];


    int t = 5;

    delete[] g;

//
//    static std::map<void*,int> associativeArray ; //=  (std::map<void*,int> *) malloc(10000);//new std::map<void*,int> ();
//
//    void* ptr ;
//
//
//    associativeArray.insert(std::pair<void*,int>(ptr,6));
//
//    cout << associativeArray.at(ptr);

    return 0;
}