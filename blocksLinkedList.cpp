//
// Created by zahar on 14/01/17.
//

#include <vector>
#include <map>
#include "blocksLinkedList.h"
#include "MyAllocator.h"


blocksLinkedList::blocksLinkedList():listSize(0) {}

blocksLinkedList::~blocksLinkedList() {

}

blocksLinkedList::blocksLinkedList(freeblock *head) : head(head) , listSize(1) {}

void blocksLinkedList::addBlock(freeblock *block) {
    freeblock *prev = nullptr;
    freeblock *current = head;

    if(listSize == 0){
        head = block;
        head->setNext(nullptr);
    }else{
        while(current!= nullptr){
            if((char*)block->getStartPtr() < (char*)current->getStartPtr()){
                if(current != head) {
                    prev->setNext(block);
                }

                block->setNext(current);
            } else{
                prev = current;
                current = current->getNext();
            }
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
            } else{
                head = current->getNext();
            }
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

void blocksLinkedList::setHead(freeblock *head) {
    blocksLinkedList::head = head;
}

void* blocksLinkedList::operator new(size_t size){
    return malloc(size);
}

void blocksLinkedList::operator delete(void* ptr){
    free(ptr);
}

bool blocksLinkedList::empty() {
    if(listSize == 0){
        return true;
    }else{
        return false;
    }
}

size_t blocksLinkedList::getListSize() const {
    return listSize;
}

void blocksLinkedList::setListSize(size_t listSize) {
    blocksLinkedList::listSize = listSize;
}

