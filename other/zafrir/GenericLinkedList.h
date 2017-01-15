
// Created by Zafrir.

#pragma once
#include <iostream>
#include"firstFitManager.h"

template <typename T>
class GNode {
public:
    GNode(T data) :data(data), next(nullptr) , prev(nullptr) {}
    T data;
    GNode<T>* next;
    GNode<T>* prev;

	void* operator new(size_t size) {
		return firstFitManager::getInstance(0)->allocate(size);
	}

	void* operator new[](size_t size) {
		//cout << "in new[]" << endl;
		return firstFitManager::getInstance(0)->allocate(size);
	}

		void operator delete(void* toDelete) {
		//cout << "delete" << endl;
		firstFitManager::getInstance(0)->myfree(toDelete);
	}

	void operator delete[](void* toDelete) {
		//cout << "delete[]"<<endl;
		firstFitManager::getInstance(0)->myfree(toDelete);
	}

};



template <typename T>
class GenericLinkedList {

public:
	GenericLinkedList() : head(nullptr), tail(nullptr), listSize(0) {}

	void deleteList() {
		if (this->head != nullptr) {
			GNode<T> *curr = head;
			for (size_t i = 0; i < listSize; i++)
			{
				GNode<T>* toDelete = curr;
				curr = curr->next;
				delete toDelete;
			}
			listSize = 0;
			head = nullptr;
			tail = nullptr;
		}
	}

	void add(T data) {
		GNode<T>  newNode(data); 
		if (head == nullptr) {
			head = tail = &newNode;
			head->prev = head;
			tail->next = head;
		}
		else {
			newNode.next = head;
			newNode.prev = tail;
			head->prev = &newNode;
			tail->next = &newNode;
			head = &newNode;
		}
		listSize++;
	}

	bool remove(T data) {
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
		for (size_t i = 0; i < listSize; i++) {
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

	void * operator new(size_t size)
	{
		return firstFitManager::getInstance(0)->allocate(size);
	}

	void * operator new[](size_t size)
	{
		return firstFitManager::getInstance(0)->allocate(size);
	}

	void operator delete(void * toDelete)
	{
		firstFitManager::getInstance(0)->myfree(toDelete);
	}

	void operator delete[](void * toDelete)
	{
		firstFitManager::getInstance(0)->myfree(toDelete);
	}


protected:
     GNode<T>* head;
	 GNode<T>* tail;
	 size_t listSize;
};
