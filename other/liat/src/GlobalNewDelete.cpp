#include <iostream>
#include <cmath>
#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "MemoryPool.h"
#include "MemoryManager.h"
#include "Valgrind.h"

#define REG_DELETE '&'
#define ARR_DELETE '%'
#define REG_ALLOCATE '#'
#define ARR_ALLOCATE '$'
#define MAX_FUNCTION_NAME_SIZE 50
#define FIRST_CELL 8
#define TWO 2
#define END_OF_STRING '\0'
#define OPEN_SCOPE '('
#define PLUS '+'
#define BACK_TRACE 4
#define BACK_TRACE_SYMBOL (BACK_TRACE -1)

void getPerentFanctionName (char* name, int name_size);
void deleteMemoryPrint(void*ptr , char symbol);
void allocateMemoryPrint(void * ptr ,  char symbol);
void valgrind(void * ptr , size_t size);


void operator delete(void* ptr) {

	////////////////////////FREE MEMORY///////////////////////////////////////////////
    MemoryManager::getInstance()->deallocate(ptr);

	////////////////////////PRINT TEST ARRAY//////////////////////////////////////////
	deleteMemoryPrint(ptr,REG_DELETE);
	
	////////////////////////VALGRIND/////////////////////////////////////////////////
	Valgrind::getInstance()->deallocate(ptr);
	
}


void operator delete[](void* ptr) {

	////////////////////////FREE MEMORY///////////////////////////////////////////////
	MemoryManager::getInstance()->deallocate(ptr);


	////////////////////////PRINT TEST ARRAY/////////////////////////////////////////
	deleteMemoryPrint(ptr,ARR_DELETE);
	
	
	////////////////////////VALGRIND/////////////////////////////////////////////////
	Valgrind::getInstance()->deallocate( ptr);
	
}


void* operator new(size_t size) {
	void* ans = nullptr;
	
	////////////////////////ALLOCATE MEMORY///////////////////////////////////////////////
	ans = MemoryManager::getInstance()->allocate(size);
	
	////////////////////////PRINT TEST ARRAY///////////////////////////////////////////////
	allocateMemoryPrint(ans , REG_ALLOCATE );
	
	////////////////////////VALGRIND/////////////////////////////////////////////////
	valgrind(ans , size);

	return ans;
}
void* operator new[](size_t size) {
	void * ans = nullptr;
	
	////////////////////////ALLOCATE MEMORY///////////////////////////////////////////////
	ans = MemoryManager::getInstance()->allocate(size);
	
	////////////////////////PRINT TEST ARRAY///////////////////////////////////////////////
	allocateMemoryPrint(ans , ARR_ALLOCATE );
	
	////////////////////////VALGRIND/////////////////////////////////////////////////
	valgrind(ans , size);

	return ans;
}


void deleteMemoryPrint(void * ptr , char symbol ){
	size_t sizeOfPointer =0;
	size_t pointerIndex =0;
	const char* startPool=nullptr;
	

	////////////size of pointer//////////////////////////////////////
	startPool = MemoryPool::getInstance()->getPool();
	//start pool
	pointerIndex = (size_t)ptr - (size_t)startPool;
	//size of pointer
	sizeOfPointer = MemoryManager::getInstance()->alocatedMemory[(void *)(pointerIndex + startPool)];
	/////////////////////////////////////////////////////////////////

	if(symbol == REG_DELETE){
		cout << "delete " << sizeOfPointer << " bytes index " << pointerIndex/FIRST_CELL << endl;
	}else{
		cout << "delete[] " << sizeOfPointer << " bytes index " << pointerIndex/FIRST_CELL << endl;
	}
	MemoryManager::getInstance()->printTest();
}

void allocateMemoryPrint(void * ptr , char symbol){
	
	size_t sizeOfPointer = 0;
	size_t pointerIndex =0;
	
	//index on original heap
	pointerIndex = (size_t)ptr - (size_t)MemoryPool::getInstance()->getPool();
	//round to pow 2
	sizeOfPointer = (size_t)(pow(TWO, ceil(log(sizeOfPointer) / log(TWO))));
	
	if (sizeOfPointer < FIRST_CELL) {
		sizeOfPointer = FIRST_CELL;
	}
	
	if(symbol == REG_ALLOCATE){
		cout << "allocate " << sizeOfPointer << " bytes index " << pointerIndex/FIRST_CELL << endl;
	}else{
		cout << "allocate[] " << sizeOfPointer << " bytes index " << pointerIndex/FIRST_CELL << endl;
	}
	MemoryManager::getInstance()->printTest();
}

void valgrind(void * ptr , size_t size){
	size_t pointerSize=0;
	//round to pow 2
	pointerSize = (size_t)(pow(TWO, ceil(log(size) / log(TWO))));
	if (pointerSize < FIRST_CELL) {
		pointerSize = FIRST_CELL;
	}
	
	char name[MAX_FUNCTION_NAME_SIZE];
	getPerentFanctionName (name ,MAX_FUNCTION_NAME_SIZE);
	Valgrind::getInstance()->allocate(pointerSize , ptr , name );
}


/* Obtain a backtrace and print it to stdout. */
void getPerentFanctionName(char* name, int name_size)
{
  void *array[2];
  size_t size;
  char **strings;

  //size of stack , and index that i want
  size = backtrace (array, BACK_TRACE); //3
  //put names function to array 
  strings = backtrace_symbols (array, size);
  
  //copy to name the fanction name
  strncpy(name , strings[BACK_TRACE_SYMBOL] , name_size); //2
  
  //name to return without garbage
  char short_name[MAX_FUNCTION_NAME_SIZE];
  bool startCopy = false;
  int k=0;
  
  for (int i = 0; i < MAX_FUNCTION_NAME_SIZE; i++) {
      if(startCopy){
         if(name[i]== PLUS) 
        	break;
         short_name[k++] = name[i];
      }  
      if(name[i]==OPEN_SCOPE) 
    	startCopy = true;
  }
  //add end of name
  short_name[k]=END_OF_STRING;
  
  //copy to my pointer
  strncpy(name , short_name , name_size);
  free (strings);
}
