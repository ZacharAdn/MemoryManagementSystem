//
// Created by zahar on 11/01/17.
//

#ifndef CPPEX2_FREEBLOCK_H
#define CPPEX2_FREEBLOCK_H

#include <string>
using namespace std;

class freeblock {

public:

    /**
     * Ctr
     * @param startPtr
     * @param size
     */
    freeblock(void *startPtr, size_t size);

    /**
     * Dctr
     */
    virtual ~freeblock();

    /**
     * @return the ptr to the block
     */
    void *getStartPtr() const;

    /**
     * override to the operaotr new
     * @param size
     * @return
     */
    void* operator new(size_t size);

    /**
     * override to operatot delete
     * @param ptr
     */
    void operator delete(void* ptr);

    /**
     *
     * @return next block
     */
    freeblock *getNext() const;

    /**
     *
     * @param next
     */
    void setNext(freeblock *next);

    /**
     *
     * @return size of the block
     */
    size_t getSize() const;

    /**
     *
     * @param size
     */
    void setSize(size_t size);

private:

    void* startPtr;

    freeblock* next;

    size_t size;
};


#endif //CPPEX2_FREEBLOCK_H
