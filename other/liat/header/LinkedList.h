#pragma once
#include <iostream>
using namespace std;


/*
free list NODE
*/
class Node
{
public:
	Node* next;
	size_t addr;
	Node(size_t addr);
	void operator delete(void* ptr);
	void* operator new(size_t size);
};


/*
free list
*/
class LinkedList {

public:
	/*
	Contractor Distractor.
	*/
	LinkedList(size_t memoryBlock);
	~LinkedList();

	/*
	Add new node with this addr to linked list.
	*/
	void add(size_t addr);

	/*
	Return size of lisr
	*/
	const size_t& getSize() const;

	/*
	Remove first element from linked list
	*/
	int removeFirst();

	/*
	Function accepts a parameter if it finds sequence of addresses of length x ,
	it deletes the sequence and returns the first address.
	*/
	int removeSequenceIfExist(size_t LengthOfTheSequence);

	/*
	Function accepts a index start of secuence and numeber of bits and add sequence of nodes
	*/
	void addSequenceIfExist(size_t index, size_t bits);

	/*
	getters
	*/
	const size_t& getMemoryBlock() const;
	
	/*
	return head of list
	*/
	Node*  getHead() const;


	bool removeByAddr(size_t addr);

	/*
	ovverided operator new and delete
	*/
	void operator delete(void* ptr);
	void* operator new(size_t size);

private:
	Node* head;
	size_t listSize;
	size_t memoryBlock;
	void deleteList();
};