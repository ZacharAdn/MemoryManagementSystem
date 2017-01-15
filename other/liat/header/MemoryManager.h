#pragma once
#include <map>
#include "LinkedList.h"
#include "AbsStrategy.h"
#include "MemoryPool.h"
#include "Allocator.h"
using namespace std;


/*
Singelton Class
Manager responsible to manage heap
*/
class MemoryManager {
	
public:
	
	/*
	Distractor
	*/
	virtual ~MemoryManager();

	/*
	All clases that will hold an object from MemoryManager , Will override the operator new and delete ,
	And when they want to allocate memory they turn this function.
	*/
	void* allocate(size_t);

	/*
	All clases that will hold an object from MemoryManager , Will override the operator new and delete ,
	And when they want to release the memory they turn this function.
	*/
	void  deallocate(void*);

	/*
	key - pointer , value - size of bytes.
	*/
	map<void* , size_t, less<void*>, MyAllocator<pair<void*, size_t> > > alocatedMemory;

	/*
	map of free lists . every cell hold list of his size. 8 ,16 ,32 ,64
	*/
	map<size_t, LinkedList*,less<size_t>, MyAllocator<pair<size_t, LinkedList*> > > freeLists;

	/*
	Objecy memory pool is singelton init him by getInstance()
	*/
	MemoryPool* memoryPool;

	/*
	Strategy design pattern .
	Object knows how to run a certain algorithm.
	If tomorrow we want to change the algorithm simply change the implemantation of AbsStrategy in another class.
	*/
	AbsStrategy* firstFitAlgorithem;

	/*
	I ovveride new and delete operators to not get to go globals.
	*/
	void operator delete(void* ptr);
	void* operator new(size_t size);

	/*
	Singelton function get instance.
	*/
	static MemoryManager* getInstance(size_t size = 0);

	/*
	My test array 
	*/
	char * test;
	

	/*
	print test array
	*/
	void printTest();


	/*
	print sum of allocated bytes
	*/
	void printVFlag();


private:

	/*
	sum of test array 
	*/
	size_t sizeOfTestArr;
	
	/*
	pointer to the begin of empty memory
	*/
	size_t heapPointerToEnd ;
	
	/*
	My Singelton object.
	*/
	static MemoryManager* memoryManager;
	
	/*
	private Constractor get heam size and init memory pool singelton.
	*/
	MemoryManager(size_t heapSize);

	/*
	sum of bytes , help to detect leaks
	*/
	size_t SumOfAllocatedBytes;
	
};