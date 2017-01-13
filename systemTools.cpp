////
//// Created by zahar on 11/01/17.
////
//
//#include "systemTools.h"
//#include "MemoryManager.h"
//
//systemTools::systemTools() {}
//
//systemTools::~systemTools() {
//
//}
//
//void* operator new(size_t size){
//    cout << "new\n";
//    return MemoryManager::getInstane()->myAllocate(size);
//}
//
//
//void* operator new[](size_t size){
//    cout << "new []\n";
//    return MemoryManager::getInstane()->myAllocate(size);
//}
//
//void operator delete(void* toDelete){
//    cout<<"delete\n";
//    MemoryManager::getInstane()->myFree(toDelete);
//}
//
//void operator delete[](void* toDelete){
//    cout<<"delete[]\n";
//    MemoryManager::getInstane()->myFree(toDelete);
//}
//
