
// Created by Zafrir.

#include"MemPool.h"

void* MemPool::getLocation(size_t size) {
	if (this->availableSize < size) {
		return nullptr;
	}
	availableSize = availableSize - size;
	this->curLocationPtr = this->curLocationPtr + size;
	return (void*)(&myHeap[this->curLocationPtr - size]);
}
