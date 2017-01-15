
// Created by Zafrir.

#pragma once
using namespace std;
#include <cstdio>
#include <stdlib.h>

class MemPool {

public:

	//getInstance - return mempool create him only once
	static MemPool& getInstance(size_t heapSize) {
		static MemPool instance(heapSize);
		return instance;
	}

	//getLocation- return ptr to free location on myHeap
	void* getLocation(size_t size);


	//This class is singeltone - canot create another MemPool.
	MemPool(MemPool const&) = delete;
	void operator=(MemPool const&) = delete;


private:
	MemPool() {}
	
	int curLocationPtr;
	size_t availableSize;
	size_t heapSize;
	char* myHeap;
	
	MemPool(size_t heapSize) {
		this->myHeap = (char*)malloc(heapSize);
		this->heapSize = heapSize;
		this->availableSize = heapSize;
		this->curLocationPtr = 0;
	}

};
