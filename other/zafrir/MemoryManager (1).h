
// Created by Zafrir.

#pragma once
using namespace std;
#include "MemPool.h"
#include "myAllocator.h"
#include<vector>

//freeblock block that have 
//size 
//available 
//startPtr- his location
//next- the next freeblock he concted too
class freeblock {
public:
	freeblock(size_t size, void* ptr) { this->size = size, startPtr = ptr; this->next = nullptr; available = false; };
	void setAvailable(bool state) { this->available = state; };
	bool getAvailable() { return this->available; };
	size_t getSize() { return this->size; };
	freeblock* getNext() { return this->next; };
	void setNext(freeblock* block) { this->next = block; };
	void* getStartPtr() { return this->startPtr; };
	void setSize(size_t size) { this->size = size; };

private:
	void* startPtr;
	freeblock* next;
	size_t size;
	bool available;
};

//Memory Manger
//allocate and myFree are pure virtual
//each algo should inherit from MemoryManager and override 
class MemoryManager {

public:
	 ~MemoryManager();
	virtual  void* allocate(size_t)=0;
	virtual void myfree(void*)=0;
	size_t myValgringLicking();
	MemoryManager(size_t heapSize);

protected:
	MemoryManager();
	MemPool *pool;
	vector<freeblock, JVC::allocator<freeblock>> blocksList;//allocate by myAllocator
	vector<freeblock, JVC::allocator<freeblock>> freeList;//allocate by myAllocator
	size_t heapSize;
	size_t findBlock(void* ptr);//find the place of the block in blockList

};





