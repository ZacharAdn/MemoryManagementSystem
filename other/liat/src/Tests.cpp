#include <iostream>
#include <map>
#include "LinkedList.h"
#include "MemoryManager.h"
#include "GenericLinkedList.h"
#include "Valgrind.h"
#include "Tests.h"

int Tests::PremitiveLinkedList() {
	
	std::cout << "PremitiveLinkedList test :" << std::endl;

	int * a = new int(5); 

	int * a1 = new int(5); 

	int * a2 = new int(5); 

	double *d = new double[5]; 

	double *d1 = new double[5];

	int *d2 = new int[150]; 

	double *d3 = new double(100); 
	
	GenericLinkedList <double>* list = new GenericLinkedList<double>();
	list->addFirst(5); 
	list->addFirst(6);
	list->addFirst(7);
	list->addFirst(8);

	std::cout <<  "delete linked list :" << std::endl;
	delete list;
	delete a;	
	delete a1;	

	delete a2;	
	delete d;	
	delete d1;	
	delete[] d2;	
	delete[] d3;
	
	return 1;
}


int Tests::PremitiveLinkedList1() {
	std::cout << "PremitiveLinkedList1 test :" << std::endl;

	double * d = new double[8]; 
	double * d1 = new double[16]; 
	double * d2 = new double[32]; 
	double * d3 = new double[64]; 

	delete d; 
	delete d1; 
	delete []d2; 
	delete []d3; 

	
	d = new double[8]; 
	d1 = new double[16]; 
	d2 = new double[32]; 
	d3 = new double[64]; 
	delete d; 
	delete d1; 
	delete[]d2; 
	delete[]d3; 

	d = new double[8]; 
	d1 = new double[16]; 
	d2 = new double[32]; 
	d3 = new double[64]; 

	delete d; 
	delete d1; 
	delete[]d2; 
	delete[]d3; 


	d = new double[8]; 
	d1 = new double[16]; 
	d2 = new double[32]; 
	d3 = new double[64]; 
	delete d; 
	delete d1; 
	delete[]d2; 
	delete[]d3; 

	d = new double[8]; 
	d1 = new double[16]; 
	d2 = new double[32]; 
	d3 = new double[64]; 
	double* d4 = new double[16];  
	double* d5 = new double[16];  
	double* d6 = new double[16];  
	double* d7 = new double[16];  
	double* d8 = new double[16];  
	double* d9 = new double[16];  
	double* d10 = new double[16];  

	delete d; 
	delete d1; 
	delete d2; 
	delete d3; 
	delete d4; 
	delete d5; 
	delete d6; 
	delete d7; 
	delete d8; 
	delete d9; 
	delete d10; 


	d = new double[8]; 
	d1 = new double[16]; 
	d2 = new double[32]; 
	d3 = new double[64]; 

	delete d; 
	delete d1; 
	delete[]d2; 
	delete[]d3; 


	d = new double[8]; 
	d1 = new double[16]; 
	d2 = new double[32]; 
	d3 = new double[64]; 

	delete d; 
	delete d1; 
	delete[]d2; 
	delete[]d3; 

	d = new double[8]; 
	d1 = new double[16]; 
	d2 = new double[32]; 
	d3 = new double[64]; 

	delete d; 
	delete d1; 
	delete[]d2; 
	delete[]d3; 

	return 1;
}

int Tests::LinkedListPairs() {
	std::cout << "LinkedListPairs test :" << std::endl;

	GenericLinkedList <pair<char* , long*>*>* list = new GenericLinkedList<pair<char*, long*>*>(); 
	delete list; 

	char* c = new char[10]; 
	c[0] = 'o';	c[1] = 'l';	c[2] = 'e';	c[3] = 'g';
	long* l = new long(12345); 
	pair<char*, long*>* p = new pair<char*, long*>(c,l); 
	
	delete p->first; 
	delete p->second; 
	delete p; 
	
	char* c1 = new char[20]; 
	c1[0] = 'o';	c1[1] = 'l';	c1[2] = 'e';	c1[3] = 'g';
	long* l1 = new long(123456); 
	pair<char*, long*>* p1 = new pair<char*, long*>(c1, l1); 

	char* c2 = new char[20]; 
	c2[0] = 'o';	c2[1] = 'l';	c2[2] = 'e';	c2[3] = 'g';
	long* l2 = new long(123456); 
	pair<char*, long*>* p2 = new pair<char*, long*>(c2, l2); 

	char* c3 = new char[20]; 
	c3[0] = 'o';	c3[1] = 'l';	c3[2] = 'e';	c3[3] = 'g';
	long* l3 = new long(123456); 
	pair<char*, long*>* p3 = new pair<char*, long*>(c3, l3); 

	GenericLinkedList <pair<char*, long*>*>* list1 = new GenericLinkedList<pair<char*, long*>*>(); 
	list1->addFirst(p1); 
	list1->addFirst(p2); 
	list1->addFirst(p3); 

	list1->remove(p1); 
	list1->remove(p2); 
	list1->remove(p3); 

	delete p1->first; 
	delete p1->second; 
	delete p1; 

	delete p2->first; 
	delete p2->second; 
	delete p2; 

	delete p3->first; 
	delete p3->second; 
	delete p3; 
	
	delete list1; 


	return 1;
}

int Tests::LeakTest(){
	std::cout << "LeakTest test :" << std::endl;

    //need to leak 8 bytes;
    short * s = new short(1);
    short * s1 = new short(1);
    short * s2 = new short(1);
    short * s3 = new short(1);
    short * s4 = new short(1);
    short * s5 = new short(1);
    *s5 = 7; //used
    delete s;
    delete s1;
    delete s2;
    delete s3;
    delete s4;
    //delete s5;
    return 1;
}

int Tests::LinkedListPairsWithLeaks(){
    std::cout << "LinkedListPairsWithLeaks test :" << std::endl;

	GenericLinkedList <pair<char* , long*>*>* list = new GenericLinkedList<pair<char*, long*>*>(); 
	delete list; 

	char* c = new char[10]; 
	c[0] = 'o';	c[1] = 'l';	c[2] = 'e';	c[3] = 'g';
	long* l = new long(12345); 
	pair<char*, long*>* p = new pair<char*, long*>(c,l); 
	
	delete p->first; 
	delete p->second; 
	delete p; 
	
	char* c1 = new char[20]; 
	c1[0] = 'o';	c1[1] = 'l';	c1[2] = 'e';	c1[3] = 'g';
	long* l1 = new long(123456); 
	pair<char*, long*>* p1 = new pair<char*, long*>(c1, l1); 

	char* c2 = new char[20]; 
	c2[0] = 'o';	c2[1] = 'l';	c2[2] = 'e';	c2[3] = 'g';
	long* l2 = new long(123456); 
	pair<char*, long*>* p2 = new pair<char*, long*>(c2, l2); 

	char* c3 = new char[20]; 
	c3[0] = 'o';	c3[1] = 'l';	c3[2] = 'e';	c3[3] = 'g';
	long* l3 = new long(123456); 
	pair<char*, long*>* p3 = new pair<char*, long*>(c3, l3); 


	GenericLinkedList <pair<char*, long*>*>* list1 = new GenericLinkedList<pair<char*, long*>*>(); 
	list1->addFirst(p1); 
	list1->addFirst(p2); 
	list1->addFirst(p3); 

	list1->remove(p1); 
	list1->remove(p2); 
	list1->remove(p3); 

	delete p1->first; 
	delete p1->second; 
	delete p1; 

	delete p2->first; 
	delete p2->second; 
	delete p2; 

	delete p3->first; 
	delete p3->second; 
	delete p3; 
	
	char* d1 = new char[20]; 
	long* e1 = new long(1); 
	pair<char*, long*>* pp1 = new pair<char*, long*>(d1, e1); 
	
	char* d2 = new char[20]; 
	long* e2 = new long(1); 
	pair<char*, long*>* pp2 = new pair<char*, long*>(d2, e2); 
	
	char* d3 = new char[20]; 
	long* e3 = new long(1); 
	pair<char*, long*>* pp3 = new pair<char*, long*>(d3, e3); 
	
	list1->remove(pp1); 
	list1->remove(pp2); 
	delete pp1->first; 
	delete pp1->second; 
	delete pp1; 

	delete pp2->first; 
	delete pp2->second; 
	delete pp2; 
	
	
	long x =7 ;
    pp3->second = &x;
	delete list1; 
	return 1;
}
