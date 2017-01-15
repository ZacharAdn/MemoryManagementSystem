#pragma once
#include <map>
#include "LinkedList.h"
#include "Allocator.h"
using namespace mystd;

class AbsStrategy{
public:
    AbsStrategy();
    virtual ~AbsStrategy();
    
    void operator delete(void* ptr) ;
    void* operator new(size_t size) ;
    virtual int searchFreeBlock(size_t bytes, map<size_t, LinkedList*, less<size_t>, MyAllocator<pair<size_t, LinkedList*> > >& freeLists)=0;

};