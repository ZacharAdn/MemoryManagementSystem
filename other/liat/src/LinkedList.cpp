#include <iostream>
#include "LinkedList.h"
#define FIRST_CELL 8


Node::Node(size_t data)
	:  next(nullptr),addr(data) {}

void Node::operator delete(void* ptr) {
	free(ptr);
}
void* Node::operator new(size_t size) {
	return malloc(size);
}

LinkedList::LinkedList(size_t memory)
	: head(nullptr), listSize(0) , memoryBlock(memory) {
}


LinkedList::~LinkedList() {
	deleteList();
}
void LinkedList::deleteList() {
	Node * curr = nullptr;
	while (head)
	{
		listSize--;
		curr = head;
		head = head->next;
		delete curr;
	}
	head = nullptr;
}


int LinkedList::removeFirst() {

	//empty list
	if (head == nullptr) {
		return -1;
	}

	size_t ans  =-1;

	//only head/tail
	if (head->next == nullptr) {
		ans = head->addr;
		delete head;
		head = nullptr;
	}
	else {
		ans = head->addr;
		Node* curr = head;
		head = head->next;
		delete curr;
		curr = nullptr;
	}
	listSize--;

	return ans;
}

void LinkedList::add(size_t addr)
{
	Node *newNode = new Node(addr);

	Node *prev = nullptr;
	Node *curr = head;

	if (head == nullptr) {
		head = newNode;
	}
	else if (head->addr >= addr) {
		newNode->next = head;
		head = newNode;
	}
	else {
		while (curr!= nullptr && curr->addr < addr) {
			prev = curr;
			curr = curr->next;
		}
		if (curr == nullptr) {
			prev->next = newNode;
		}
		else {
			newNode->next = curr;
			prev->next = newNode;
		}
	}
	listSize++;
}

/*
if have secuence of x bits
*/
int LinkedList::removeSequenceIfExist(size_t bits) {

	if (head == nullptr)
		return -1;
	if (head->next == nullptr) {
		return -1;
	}

	size_t counter = 1;
	size_t sequence = bits / memoryBlock;
	Node* curr = head;
	Node* previous = nullptr;
	Node* toDelete = nullptr;
	int ans = -1;
	size_t difference = this->memoryBlock / 8;

	while (curr != nullptr && curr->next != nullptr) {

		if (curr->next->addr - curr->addr  != difference) {
			counter = 1;
			previous = curr;
			curr = curr->next;
		}
		else {
			counter++;
			curr = curr->next;
		}

		if (counter == sequence) {

			//sequence is whole list
			if (previous == nullptr && curr->next == nullptr) {
				ans = head->addr;
				deleteList();
				break;
			}
			//sequence in the begining
			else if (previous == nullptr) {
				ans = head->addr;
				curr = curr->next;
				previous = head;
				while (previous->addr !=curr->addr) {
					toDelete = previous;
					previous = previous->next;
					delete toDelete;
					toDelete = nullptr;
				}
				head = curr;
				break;
			}
			//sequence from middle to end
			else if(curr->next == nullptr) {
				Node* last = previous;
				previous = previous->next;	
				ans = previous->addr;

				last->next = nullptr;
				while (previous!=nullptr) {
					toDelete = previous;
					previous = previous->next;
					delete toDelete;
					toDelete = nullptr;

				}
				break;
			}
			//sequence in the middle
			else {
				Node* last = previous;
				previous = previous->next;	
				ans = previous->addr;

				curr = curr->next;
				while (previous->addr != curr->addr) {
					toDelete = previous;
					previous = previous->next;
					delete toDelete;
					toDelete = nullptr;

				}
				last->next = curr;
				break;
			}
		}
	}
	if (ans != -1) {
		this->listSize -= sequence;
	}
	return ans;
}

void LinkedList::addSequenceIfExist(size_t index, size_t bits) {

	size_t jumpsIndex = this->memoryBlock / FIRST_CELL;

	size_t loop = (size_t)bits / this->memoryBlock;

	for (size_t i = 0; i < loop; i++) {
		add(index + (i*jumpsIndex));
	}
}

const size_t& LinkedList::getMemoryBlock() const {
	return memoryBlock;
}

Node*  LinkedList::getHead() const {
	return this->head;
}


const size_t& LinkedList::getSize() const {
	return listSize;
}

bool LinkedList::removeByAddr(size_t addr) {

	if (head == nullptr) {
		return false;
	}

	Node* curr = head;
	Node* prev = nullptr;

	while (curr != nullptr && curr->addr != addr) {
		prev = curr;
		curr = curr->next;
	}

	if (curr == nullptr) {
		return false;
	}
	if (prev == nullptr) {
		removeFirst();
		return true;
	}
	prev->next = curr->next;
	delete curr;
	curr = nullptr;

	return true;
}

void LinkedList::operator delete(void* ptr) {
	free(ptr);
}
void* LinkedList::operator new(size_t size) {
	return malloc(size);
}