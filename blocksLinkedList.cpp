//
// Created by zahar on 14/01/17.
//

#include "blocksLinkedList.h"

blocksLinkedList::blocksLinkedList():head(nullptr) , listSize(0) {}

blocksLinkedList::~blocksLinkedList() {
    deleteList();
}

blocksLinkedList::blocksLinkedList(freeblock *head) : head(head) , listSize(1) {}

void blocksLinkedList::addBlock(freeblock *block) {
    freeblock *prev = nullptr;
    freeblock *current = head;

    bool done= false;

    if(listSize == 0 ){
        head = block;
        head->setNext(nullptr);
    }else{//its freeblocks on the freeList

        //find where to add
        while(current!= nullptr  && !done){

            //sorted by the ptr
            if((char*)block->getStartPtr() < (char*)current->getStartPtr()){
                if(current != head) {
                    prev->setNext(block);
                    block->setNext(current);
                }else{
                    head = block;
                    head->setNext(current);
                }

                done = true;
            } else{
                prev = current;
                current = current->getNext();
            }
        }

        //the sorted place is on the tail
        if(!done){
            prev->setNext(block);
            block->setNext(nullptr);
        }
    }
    listSize++;
}

void blocksLinkedList::removeByPtr(void* ptr) {
    freeblock *prev = nullptr;
    freeblock *current = head;

    while(current != nullptr){
        if(ptr == current->getStartPtr()){

            if(current != head) {
                prev->setNext(current->getNext());
            }else {
                head = current->getNext();
            }

            listSize--;
            delete current;
            current = nullptr;
        } else{
            prev = current;
            current = current->getNext();
        }
    }
}

freeblock *blocksLinkedList::getHead() const {
    return head;
}
void* blocksLinkedList::operator new(size_t size){
    return malloc(size);
}

void blocksLinkedList::operator delete(void* ptr){
    free(ptr);
}

bool blocksLinkedList::empty() {
    return listSize==0;
}

size_t blocksLinkedList::getListSize() const {
    return listSize;
}

void blocksLinkedList::deleteList() {
    freeblock *current = head;

    //save the prev and delete the next
    for (size_t i = 0; i < listSize; i++){
        freeblock* toDelete = current;
        current = current->getNext();
        delete toDelete;
    }
    listSize=0;
    head = nullptr;
}

