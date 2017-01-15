#pragma once
#include <iostream>


/*
Generic Node
*/
template <typename T>
class GNode 
{
public:
	GNode(T data) :data(data), next(nullptr) , prev(nullptr) {}

	T data;
	GNode<T>* next; 
	GNode<T>* prev; 
};




/*
Generic LinkedList
*/
template <typename T>
class GenericLinkedList {

public:

/*
Constractor
*/
GenericLinkedList() : head(nullptr) , tail(nullptr) , listSize(0) {

}
	
/*
Distractor
*/
~GenericLinkedList() {
	deleteList();
}
void deleteList() {
	GNode<T> *curr = head;

	for (size_t i = 0; i < listSize; i++)
	{
		GNode<T>* toDelete = curr;
		curr = curr->next;
		delete toDelete;
	}
	listSize=0;
	head = nullptr;
	tail=nullptr;
}

/*
Add element to front of list
*/
void addFirst(T data)
{
	GNode<T> * newNode = new GNode<T>(data);

	if (head == nullptr) {
		head = tail = newNode;
		head->prev = head;
		tail->next = head;
	}
	else {
		newNode->next = head;
		newNode->prev = tail;

		head->prev = newNode;
		tail->next = newNode;

		head = newNode;
	}
	listSize++;
};

/*
remove from list by data
*/
bool remove(T data)
{
	if (head == nullptr) {
		return false;
	}
	if (listSize == 1 && head->data == data) {
		delete head;
		head = tail = nullptr;
		listSize--;
		return true;
	}

	GNode<T>* curr = head;
	for (size_t i = 0; i < listSize; i++)
	{
		if (curr->data == data) {
			if (curr == tail) {
				tail = tail->prev;
				tail->next = head;
				head->prev = tail;
				delete curr;
			}
			else if (curr == head) {
				head = head->next;
				head->prev = tail;
				tail->next = head;
				delete curr;
			}
			else {
				GNode<T>* toDelete = curr;
				curr->next->prev = curr->prev;
				curr->prev->next = curr->next;
				delete toDelete;
			}
			listSize--;
			return true;
		}
		curr = curr->next;
	}
	return false;
}

private:
	GNode<T>* head;
	GNode<T>* tail;
	double listSize;
};