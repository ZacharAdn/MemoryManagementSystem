
// Created by Zafrir.

#include <iostream>
#include "MemoryManager.h"

//constructor - make singeltone mempool
MemoryManager::MemoryManager(size_t heapSize) {
	pool = &MemPool::getInstance(heapSize);
}

MemoryManager::~MemoryManager() {
}

MemoryManager::MemoryManager() {}

size_t MemoryManager::findBlock(void* ptr) {
	for (int i = 0; blocksList.size(); i++) {
		if (blocksList.at(i).getStartPtr() == ptr) {
			return i;
		}
	}
	return -1;
}

size_t MemoryManager::myValgringLicking()
{
	size_t sum = 0;
	for (size_t i = 0; i < this->blocksList.size(); i++)
	{
		if (!blocksList[i].getAvailable()) {
			sum += blocksList[i].getSize();
		}
	}
	return sum;
}
