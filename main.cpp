#include <iostream>
#include "MemoryManager.h"
#include "CyclicGenericList.h"


using namespace std;

void LinkedListCheck() ;



int main(int argc, char* argv[]) {

    if (argc < 1) {
        exit(0);
    } else {
        MemoryManager *memoryManager =
                MemoryManager::getInstane((size_t)atoi(argv[2]), MemoryManager::AllocationType::FirstFit);

        LinkedListCheck();

        if(argc == 4 && argv[3][0] == '-' && argv[3][1] == 'v'){
            memoryManager->valgrind();
        }
    }
    return 0;
}

/**
 * override the global new
 * @param size
 * @return
 */
void* operator new(size_t size){
    return MemoryManager::getInstane()->myAllocate(size);
}

/**
 * override the global new[]
 * @param size
 * @return
 */
void* operator new[](size_t size){
    return MemoryManager::getInstane()->myAllocate(size);
}

/**
 * override the global delete
 * @param toDelete
 */
void operator delete(void* toDelete){
    MemoryManager::getInstane()->myFree(toDelete);
}

/**
 * override the global delete[]
 * @param toDelete
 */
void operator delete[](void* toDelete){
    MemoryManager::getInstane()->myFree(toDelete);
}

/**
 * check for the geeric Linked List
 */
void LinkedListCheck() {
    CyclicGenericList <pair<char* , long*>*>* LinkedList = new CyclicGenericList <pair<char*, long*>*>();

    char* c1 = new char[10];
    c1[0] = '&';
    c1[1] = '*';
    c1[2] = '@';
    long* l1 = new long(33);
    pair<char*, long*>* pair1 = new pair<char*, long*>(c1,l1);

    char* c2 = new char[3];
    c2[0] = '!';
    c2[1] = '#';
    long* l2 = new long(32193021);
    pair<char*, long*>* pair2 = new pair<char*, long*>(c2, l2);

    char* c3 = new char[20];
    c3[0] = '0';
    c3[1] = '^';
    c3[2] = '^';
    c3[3] = '^';
    c3[4] = '^';
    c3[5] = '^';
    long* l3 = new long(1290139);
    pair<char*, long*>* pair3 = new pair<char*, long*>(c3, l3);

    LinkedList->add(pair1);
    LinkedList->add(pair2);
    LinkedList->add(pair3);
    LinkedList->remove(pair1);
    LinkedList->remove(pair2);
    LinkedList->remove(pair3);

    delete pair1->first;
    delete pair1->second;
    delete pair1;

    delete pair2->first;
    delete pair2->second;
    delete pair2;

    delete pair3->first;
    delete pair3->second;
    delete pair3;

    delete LinkedList;
}