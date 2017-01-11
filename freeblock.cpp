//
// Created by zahar on 11/01/17.
//

#include <cstdio>
#include "freeblock.h"



freeblock::freeblock(void *startPtr, size_t size) : startPtr(startPtr), next(nullptr),
                                                    size(size), available(false) {}

void *freeblock::getStartPtr() const {
    return startPtr;
}

void freeblock::setStartPtr(void *startPtr) {
    freeblock::startPtr = startPtr;
}

freeblock *freeblock::getNext() const {
    return next;
}

void freeblock::setNext(freeblock *next) {
    freeblock::next = next;
}

size_t freeblock::getSize() const {
    return size;
}

void freeblock::setSize(size_t size) {
    freeblock::size = size;
}

bool freeblock::isAvailable() const {
    return available;
}

void freeblock::setAvailable(bool available) {
    freeblock::available = available;
}

freeblock::~freeblock() {

}
