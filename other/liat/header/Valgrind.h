#pragma once
#include "Allocator.h"
#include <map>
#define MAX_FUNCTION_NAME 50
using namespace mystd;
using namespace std;

class VNode {
public:

	/*
	hold size of block
	*/
	size_t size;
	
	/*
	hold function name 
	*/
	char  functionName[MAX_FUNCTION_NAME];


	/*
	Constractor
	*/
	VNode(size_t size , char* func);
	
	
	/*
	overrided new and delete operators
	*/
	void operator delete(void* ptr);
	void* operator new(size_t size);
};


/*
Singelton Class Valgrind
*/
class Valgrind {
public:

	/*
	Distractor
	*/
	~Valgrind();

	/*
	histogram map
	*/
	map<size_t, size_t, less<size_t>, MyAllocator<pair<size_t, size_t> > > histogram;
	
	/*
	map  key pointer , value VNode hold size of pointer and function name
	*/
	map<void*, VNode*, less<void*>, MyAllocator<pair<void*, VNode*> > > allocMap;

	/*
	return Instance of Singelton
	*/
	static Valgrind* getInstance();

	/*
	if any one allocate memory we register when and where allocated bytes
	*/
	void allocate(size_t size , void* ptr , char * functionName);
	
	/*
	If released memory erased the record
	*/
	void deallocate(void* ptr);

	/*
	overrided new and delete operators
	*/
	void operator delete(void* ptr);
	void* operator new(size_t size);
	
	/*
	print conclusion of valgrind
	*/
	void print();
	

private:
	/*
	Constractor
	*/
	Valgrind();
	
	/*
	variables 
	*/
	int  numOfBlockes;
	int numOfBytes;
	size_t sumOfBlockes;
	size_t sumOfBytes;
	
	/*
	valgrind static instance
	*/
	static Valgrind*  valgrind;
};