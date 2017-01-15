#pragma once
#include <string>
#include <iostream>
using namespace std;

/*
Singelton Class
memory pool hold array of chars our heap
*/
class MemoryPool {

public:

	/*
	return instance of singelton
	*/
	static MemoryPool* getInstance(size_t size=0);

	/*
	return start of pool
	*/
	char* getPool() const;
	
	/*
	return pool size
	*/
	const size_t& getPoolSize() const;

	/*
	Distractor
	*/
	~MemoryPool();

	/*
	overrided new and delete operators
	*/
	void operator delete(void* ptr);
	void* operator new(size_t size);

private:
	/*
	private Constractor
	*/
	MemoryPool(size_t size);
	
	/*
	pool -> our heap
	*/
	char* pool;

	/*
	pool static instance
	*/
	static MemoryPool*  memoryPool;
	
	/*
	pool size
	*/
	size_t poolSize;
};
