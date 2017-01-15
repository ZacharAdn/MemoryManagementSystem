//
// Created by zahar on 14/01/17.
//

#ifndef CPPEX2_LINKEDLIST_H
#define CPPEX2_LINKEDLIST_H


#include "freeblock.h"

class blocksLinkedList {
public:

    blocksLinkedList();

    blocksLinkedList(freeblock *head);

    void addBlock(freeblock *block);

    void removeByPtr(void* ptr);

    bool empty();

    freeblock *getHead() const;

    void setHead(freeblock *head);

    size_t getListSize() const;

    void setListSize(size_t listSize);

    void* operator new(size_t size);

    void operator delete(void* ptr);

    virtual ~blocksLinkedList();


private:

    freeblock *head;

    size_t listSize;

};


#endif //CPPEX2_LINKEDLIST_H
