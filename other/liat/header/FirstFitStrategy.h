#pragma once
#include "AbsStrategy.h"

class FirstFitStrategy : public AbsStrategy {

public:

	FirstFitStrategy();
	
	/*
	get free lists and size and searching for free memory 
	*/
	int searchFreeBlock(size_t bytes, map<size_t, LinkedList*, less<size_t>, MyAllocator<pair<size_t, LinkedList*>>>& freeLists);
	
	/*
	override new delete 
	*/
	void operator delete(void* ptr);
	void* operator new(size_t size);

};