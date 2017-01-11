//
// Created by zahar on 11/01/17.
//

#ifndef CPPEX2_FREEBLOCK_H
#define CPPEX2_FREEBLOCK_H


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


private:
    void* startPtr;

    freeblock* next;

    size_t size;

    bool available;
};


#endif //CPPEX2_FREEBLOCK_H
