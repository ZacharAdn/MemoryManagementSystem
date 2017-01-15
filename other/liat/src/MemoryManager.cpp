#include "MemoryManager.h"
#include "FirstFitStrategy.h"
#include <cmath>
#define FIRST_CELL 8
#define LAST_CELL 1024
#define TWO 2
#define EMPTY '.'
#define ALLOCATED_CELL '#'
#define START_V_FLAG 'x'

MemoryManager* MemoryManager::memoryManager = nullptr;



MemoryManager::MemoryManager(size_t heapSize) : firstFitAlgorithem(nullptr) ,test(nullptr) , sizeOfTestArr(0) ,heapPointerToEnd(0) {
	
	SumOfAllocatedBytes = 0;

	//init strategy object.
	firstFitAlgorithem = new FirstFitStrategy();

	//init singelton object.
	memoryPool = MemoryPool::getInstance(heapSize);

	for (size_t i = FIRST_CELL; i <= LAST_CELL; i *= TWO)
	{
		//LinkedList(i) -  all nodes in this linked list with size i.
		//map[i] - key to this list.
		freeLists[i] = new LinkedList(i);
	}

	//init test arr
	sizeOfTestArr = heapSize / FIRST_CELL;
	test = (char *)malloc(sizeOfTestArr);

	//empty heap test fill with EMPTYs
	for (size_t i = 0; i < sizeOfTestArr; i++)
	{
		test[i] = EMPTY;
	}
}

MemoryManager::~MemoryManager() {

	//delete from map all linked lists
	for (auto it = freeLists.begin(); it != freeLists.end(); it++)
	{
		delete it->second;
	}
	
	//***alocatedMemory map not need to delete , because in the end we delete all heap


	//delete object memort pool , mem pool delete allocated char heap
	delete memoryPool;

	//delete algorithem obejct
	delete firstFitAlgorithem;

	//free test array
	free (test);
}

void  MemoryManager::deallocate(void* addr) {
	
	if (!addr) {
		return; // Check for null pointer
	}


	//get pool return start of memory pool array	
	const char* startPool = memoryPool->getPool();

	//addr - start addr = index of pointer
	size_t pointerIndex = (size_t)addr - (size_t)startPool;

	void * key =(void *)(pointerIndex + startPool);
	
	//check if exist 
	auto it = alocatedMemory.find(key);
	if(it == alocatedMemory.end()){
		cout << "Function dealocate: this pointer already deleted" <<endl;
		return ;
	}


	//get from aloc map size of pointer
	size_t sizeOfPointer = alocatedMemory[key];
	
	//0 -> 0 , 8 -> 1 , 16 -> 2 ....
	pointerIndex /= FIRST_CELL;

	//add new node to free lists
	freeLists[sizeOfPointer]->add(pointerIndex);

	//update test array
	test[pointerIndex] = EMPTY;

	this->SumOfAllocatedBytes -= sizeOfPointer;
	
}

void* MemoryManager::allocate(size_t bytes) {

	void* ptr=nullptr;

	//not valide size of bytes
	if (bytes <= 0) {
		return nullptr;
	}

	//round to minimum 8
	if (bytes < FIRST_CELL) {
		bytes = FIRST_CELL;
	}

	//Rounding up to nearest power of 2
	bytes = (size_t)(pow(TWO, ceil(log(bytes) / log(TWO))));

	
	if(bytes > LAST_CELL){
		cout << "request more than 1024 bytes my heap cant contains this" <<endl;
		exit(1);
	}
	
	
	//Check may not have to go searching in free list
	if (memoryPool->getPoolSize() - this->heapPointerToEnd > bytes) {

		//mark this cell as allocated
		int index = this->heapPointerToEnd/FIRST_CELL;	
		test[index] = ALLOCATED_CELL;

		//move pointer to next allocated
		this->heapPointerToEnd += bytes;
		//remember the size of this allocated pointer
		void* ptr = (void *)(index*FIRST_CELL + memoryPool->getPool());
		alocatedMemory[ptr] = bytes;
		
		this->SumOfAllocatedBytes += bytes;
		return ptr;
	}
	

	//Search free block first fit algorithem
	int index = firstFitAlgorithem->searchFreeBlock(bytes, freeLists);

	//find free block
	if (index >= 0) {	
		//get ptr to block
		ptr = (void *)(index*FIRST_CELL + memoryPool->getPool());
		//save number of bytes
		alocatedMemory[ptr] = bytes;	
		//mark in test array
		test[index]=ALLOCATED_CELL;
		//add number of bytes to sum
		this->SumOfAllocatedBytes += bytes;
		
		return ptr;
	}

	cout << "No more memory on the HEAP" << endl;
	exit(1); 
}
 
 
void MemoryManager::operator delete(void* ptr) {
	free(ptr);
}
void* MemoryManager::operator new(size_t size) {
	return malloc(size);
}


MemoryManager* MemoryManager::getInstance(size_t size) {
	if (memoryManager == nullptr) {
		memoryManager = new MemoryManager(size);
	}
	return memoryManager;
}

void MemoryManager::printTest() {
	for (size_t i = 0; i < sizeOfTestArr; i++)
	{
		cout << test[i] << " ";
	}
	cout << "" << endl;
}

void MemoryManager::printVFlag(){
	cout << "---------------------------------------------------------------------------------  " << endl;
	cout << "Num of leaked Bytes " << this->SumOfAllocatedBytes << endl;
	cout << "---------------------------------------------------------------------------------  " << endl;
}