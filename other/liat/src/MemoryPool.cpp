#include "MemoryPool.h"
#include <stdio.h>
#include <iostream>
#define MEMORY_BLOCK 8

MemoryPool* MemoryPool::memoryPool = nullptr;

MemoryPool::MemoryPool(size_t size) : pool(nullptr),poolSize(size) {
	pool = (char*)malloc(poolSize*sizeof(char));
}

MemoryPool::~MemoryPool() {
	free (pool);
}

char* MemoryPool::getPool() const {
	return this->pool;
}

MemoryPool* MemoryPool::getInstance(size_t size) {
	if (memoryPool == nullptr) {
		memoryPool = new MemoryPool(size);
	}
	return memoryPool;
}

const size_t& MemoryPool::getPoolSize() const {
	return this->poolSize;
}

void MemoryPool::operator delete(void* ptr) {
	free(ptr);
}
void* MemoryPool::operator new(size_t size) {
	return malloc(size);
}