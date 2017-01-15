
// Created by Zafrir.

using namespace std;
#include<cstring>
#include <cstdlib>
#include <iostream>
#include "firstFitManager.h"
#include "GenericLinkedList.h"


void* operator new(size_t size) {
	//cout << "in new" << endl;
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



int main(int argc, char** argv) {
	firstFitManager* m=nullptr;
	/*if (argc < 1)
		exit(0);
	if (argv[1] == std::string("-S")) {
		 m= firstFitManager::getInstance(atoi(argv[2]));
		int* s = new int[8];
		delete[] s;
		char* s1 = new char[4];
		delete[] s1;
		char* linkListChar = new char[4];
		long* linkListLong = new long[5];
		GenericLinkedList<pair<char*, long*>*>* list = new GenericLinkedList<pair<char*, long*>*>();
		list->add(&make_pair(linkListChar, linkListLong));
		delete linkListChar;
		delete linkListLong;
		delete list;
	}
	if (argv[3]!=nullptr && argv[3] == std::string("-V")) {
		cout << "Bytes allocated and not released: " << m->myValgringLicking() << endl;
	}*/
	m = firstFitManager::getInstance(900);
	int* s = new int[8];
	delete[] s;
	char* s1 = new char[4];
	delete[] s1;
	char* linkListChar = new char[4];
	long* linkListLong = new long[5];
	GenericLinkedList<pair<char*, long*>*>* list = new GenericLinkedList<pair<char*, long*>*>();
	pair<char*, long*> p =  make_pair(linkListChar, linkListLong);
	list->add(&p);
	//list->add(&make_pair(linkListChar, linkListLong));
	//delete linkListChar;
	//delete linkListLong;
	delete list;

	//delete &p;
	cout << "Bytes allocated and not released: " << m->myValgringLicking() << endl;
	system("pause");
}


