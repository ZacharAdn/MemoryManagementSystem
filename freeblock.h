//
// Created by zahar on 11/01/17.
//

#ifndef CPPEX2_FREEBLOCK_H
#define CPPEX2_FREEBLOCK_H

#include <string>
using namespace std;

class freeblock {

public:

    freeblock(void *startPtr, size_t size);

    virtual ~freeblock();

    void *getStartPtr() const;

    void setStartPtr(void *startPtr);

    freeblock *getNext() const;

    void setNext(freeblock *next);

    size_t getSize() const;

    void setSize(size_t size);

    bool isAvailable() const;

    void setAvailable(bool available);

//    string toString();
//
    string toString();

private:
    void* startPtr;

    freeblock* next;

    size_t size;

    bool available;
};


#endif //CPPEX2_FREEBLOCK_H