#include "Valgrind.h"
#include <iostream>
#include "MemoryPool.h"
#include "MemoryManager.h"
#define END_OF_STRING '\0'
#define FIRST_CELL 8
#define LAST_CELL 1024
#define TWO 2

using namespace std;
Valgrind* Valgrind::valgrind=nullptr;

VNode::VNode(size_t size , char* func) : size(size) {
	int i = 0;
	
	//deep copy function name
	while (func[i] != END_OF_STRING ) {
		this->functionName[i] = func[i];
		i++;
	}
	this->functionName[i] = func[i];
}

Valgrind::Valgrind() : numOfBlockes(0) , numOfBytes(0) , sumOfBlockes(0) , sumOfBytes(0){

	//init histogram all values 0
	for (size_t i = FIRST_CELL; i <= LAST_CELL; i *= TWO)
	{
		histogram[i] = 0;
	}
}

Valgrind::~Valgrind() {
	

	//delete from map all linked lists
	for (auto it = allocMap.begin(); it != allocMap.end(); it++)
	{
		delete it->second;
	}
	
}

void  Valgrind::allocate(size_t size, void* ptr , char * functionName) {
	
	//add one in histogram line
	this->histogram[size]++;
	//save ptr -> VNode
	this->allocMap[ptr] = new VNode(size , functionName);
	//update parametes
	this->numOfBlockes++;
	this->numOfBytes += size;	
	this->sumOfBlockes++;
	this->sumOfBytes+=size;
	
}

void  Valgrind::deallocate(void* ptr) {

	////////////size of pointer//////////////////////////////////////
	const char* startPool = MemoryPool::getInstance()->getPool();
	//start pool
	size_t pointerIndex = (size_t)ptr - (size_t)startPool;
	//size of pointer
	size_t sizeOfPointer = MemoryManager::getInstance()->alocatedMemory[(void *)(pointerIndex + startPool)];
	/////////////////////////////////////////////////////////////////
	
	//update parametes
	this->numOfBlockes--;
	this->numOfBytes -= sizeOfPointer;

	//dave node to delete
	VNode * toDelete =  this->allocMap[ptr];

	//remove from map
	auto it = allocMap.find(ptr);
	this->allocMap.erase(it);

	delete toDelete;
}

Valgrind* Valgrind::getInstance() {
	if (valgrind == nullptr) {
		Valgrind::valgrind =  new Valgrind();
	}
	return valgrind;
}

void Valgrind::operator delete(void* ptr) {
	free (ptr);
}

void* Valgrind::operator new(size_t size) {
	return malloc(size);
}

void VNode::operator delete(void* ptr) {
	free(ptr);
}
void* VNode::operator new(size_t size) {
	return malloc(size);
}


void Valgrind::print() {
	cout << "---------------------------------------------------------------------------------  "<< endl;
	cout << "----------------------------Valgrind---------------------------------------------  "<< endl;
	cout << "---------------------------------------------------------------------------------  "<< endl;
	cout << "Sum of allocated Blockes " << this->sumOfBlockes << endl;
	cout << "Sum of allocated Bytes " << this->sumOfBytes << endl;
	cout << "Blockes allocated and not released " << this->numOfBlockes << endl;
	cout << "Bytes allocated and not released " << this->numOfBytes << endl;
	cout << "---------------------------------------------------------------------------------  "<< endl;
	cout << "----------------------------Histogram--------------------------------------------  " << endl;
	cout << "---------------------------------------------------------------------------------  " << endl;
	for (size_t i = FIRST_CELL; i <= LAST_CELL; i *= TWO)
	{
		cout << i << " bytes allocMap : " << this->histogram[i] << " times : " ;
		size_t loop = this->histogram[i];
		for (size_t i = 0; i < loop; i++)
		{
			cout << "+";
		}
		cout << "" << endl;
	}
	cout << "---------------------------------------------------------------------------------  " << endl;
	cout << "---------------------------Leak Memory-------------------------------------------  " << endl;
	cout << "---------------------------------------------------------------------------------  " << endl;
	//Prints the places where the memory was allocated and not released
	for (auto it = allocMap.begin(); it != allocMap.end(); it++)
	{	
		int i = 0;
		cout << it->second->size << " bytes allocated in ";
		while (it->second->functionName[i] !=  END_OF_STRING) {
			cout << it->second->functionName[i];
			i++;
		}
		cout <<" and not released" <<endl;
	}
	cout << "---------------------------------------------------------------------------------  " << endl;
	cout << "----------------------------End Valgrind-----------------------------------------  " << endl;
	cout << "---------------------------------------------------------------------------------  " << endl;
}
