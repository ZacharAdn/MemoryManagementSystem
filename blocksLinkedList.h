//
// Created by zahar on 14/01/17.
//

#ifndef CPPEX2_LINKEDLIST_H
#define CPPEX2_LINKEDLIST_H


#include "freeblock.h"

class blocksLinkedList {
public:

    /**
     * Ctr - empty Linked List
     */
    blocksLinkedList();

    /**
     * Ctr - new Linked List with freeblock head
     * @param head
     */
    blocksLinkedList(freeblock *head);

    /**
     * Dctr delete all the list
     */
    virtual ~blocksLinkedList();

    /**
     * Add freeblock to the list and sort the list by the ptr place on the pool
     * @param block
     */
    void addBlock(freeblock *block);

    /**
     * Remove freeblock by he's ptr on the pool
     * @param ptr
     */
    void removeByPtr(void* ptr);

    /**
     *
     * @return true if listSize == 0
     */
    bool empty();

    /**
     *
     * @return head of the Linked List
     */
    freeblock *getHead() const;

    /**
     *
     * @return num of elements on the Linked List
     */
    size_t getListSize() const;

    /**
     * Override new
     * @param size
     * @return
     */
    void* operator new(size_t size);
    /**
     * Override delete
     * @param ptr
     */
    void operator delete(void* ptr);


private:

    freeblock *head;

    size_t listSize;

    void deleteList();
};


#endif //CPPEX2_LINKEDLIST_H
