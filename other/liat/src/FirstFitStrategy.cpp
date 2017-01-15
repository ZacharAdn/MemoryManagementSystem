#include "FirstFitStrategy.h"
#include "LinkedList.h"
#include "MemoryPool.h"

#define FIRST_MAP_CELL 8
#define LAST_MAP_CELL 1024
#define TWO 2

FirstFitStrategy::FirstFitStrategy() : AbsStrategy() {

}

int FirstFitStrategy::searchFreeBlock(size_t bytes, map<size_t, LinkedList*, less<size_t>, MyAllocator<pair<size_t, LinkedList*> > >& freeLists) {

	int tempIndex = 0;
	
	if(bytes > LAST_MAP_CELL){
		cout << "request more than 1024 bytes my heap cant contains this" <<endl;
		exit(1);
	}

	//The first list is most fir according to the size bits.
	LinkedList* matchedList = freeLists[bytes];
	//If the list is best for me by size is not empty we take a block of memory.
	if (matchedList->getSize() > 0) {
		tempIndex = matchedList->removeFirst();
		return  tempIndex;
	}

	//I'm starting to go down and look for the neighbor who has to give me the number of bytes that I want.
	size_t tempSize = bytes / TWO;
	while (tempSize >= FIRST_MAP_CELL) {
		//Looking for a suitable sequence.
		tempIndex = (freeLists[tempSize])->removeSequenceIfExist(bytes);
		//If the condition exists that means we've found the block.
		if (tempIndex >= 0) {
			return tempIndex;
		}
		tempSize /= TWO;
	}

	//I'm starting to go up and look for the neighbor who has to give me the number of bytes that I want.
	tempSize = bytes * TWO;
	while (tempSize <= LAST_MAP_CELL) {
		//
		LinkedList* tempList = freeLists[tempSize];
		if (tempList->getSize() > 0) {
			//remove from free list
			tempIndex = tempList->removeFirst();
			//add to my cell sequence of bytes
			matchedList->addSequenceIfExist(tempIndex, tempSize);
			//remove by index , becouse i want to allocate block 
			matchedList->removeByAddr((size_t)tempIndex);
			//return index to manager
			return tempIndex;
		}
		//
		tempSize *= TWO;
	}

	return -1;
}


void FirstFitStrategy::operator delete(void* ptr) {
	free(ptr);
}
void* FirstFitStrategy::operator new(size_t size) {
	return malloc(size);
}