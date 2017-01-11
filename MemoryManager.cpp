//
// Created by zahar on 02/01/17.
//

#include <iostream>
#include "MemoryManager.h"
#include "math.h"
#include "MemPool.h"
#include "MyAllocator.h"

MemoryManager::MemoryManager(size_t heapSize) {
    pool = &MemPool::getInstane(heapSize); //TODO check where it save
}

MemoryManager::MemoryManager() {}

MemoryManager::~MemoryManager() {

}

void *MemoryManager::allocate(size_t size) {
    size_t fixSize = (size_t) pow(2,ceil(log2(size)));
    if(freeList.empty()){
        void* ptr = this->pool->getNextFreeLocationPtr(fixSize);
        freeblock f(ptr , fixSize);
        f.setAvailable(false);
        if(blocksList.empty()){
            cout<<"blockList is empty"<<endl;
            blocksList.push_back(f);
        }
        else{
//            freeblock f1 = blocksList.at(blocksList.size()-1);
//            blocksList.pop_back();
            blocksList.push_back(f);
            blocksList.at(blocksList.size()-2).setNext(&f);
//            blocksList.push_back(f1);

        }
        //findBlocks.insert(pair<void* , freeblock>(f.getStartPtr()));
        return f.getStartPtr();
    }
    else{
        for(size_t i = 0 ; i < freeList.size() ; i++){
            if(freeList.at(i).getSize() == fixSize){
                return freeList.at(i).getStartPtr();
            }
            if(freeList.at(i).getSize() > fixSize){
                ////here we need to disassemble chunks ///////
                size_t oldSize = freeList.at(i).getSize();
                size_t newSize = freeList.at(i).getSize() - fixSize;//TODO fix size for newSize
                void* newPtr = (char*)freeList.at(i).getStartPtr() + fixSize;
                freeblock f1(newPtr, newSize);
                f1.setAvailable(true);
                f1.setNext(freeList.at(i).getNext());
                /////// update blockList//////////
                size_t index = (size_t) findBlock(freeList.at(i).getStartPtr());
                blocksList.at(index).setSize(fixSize);
                blocksList.at(index).setAvailable(false);
                blocksList.at(index).setNext(&f1);
                blocksList.insert(blocksList.begin()+index , f1);
                ///////// update freeList///////////
                freeList.at(i).setSize(fixSize);
                freeList.at(i).setNext(&f1);
                freeList.push_back(f1);
                freeblock tmp = freeList.at(i);
                freeList.erase(freeList.begin()+i);
                return tmp.getStartPtr();
            }
        }
        void* ptr = this->pool->getNextFreeLocationPtr(fixSize);//allocate object on the heap
        if(ptr!=nullptr){
            freeblock f(ptr ,fixSize);
            f.setAvailable(false);
            freeblock f1 = blocksList.at(blocksList.size()-1);
            blocksList.pop_back();
            f.setNext(&f1);
            blocksList.push_back(f1);
            blocksList.push_back(f);
        }
        else{ /////// if we need, here we need to merge chunks////////
            for(size_t i = 0 ; i < freeList.size() ; i++){
                freeblock temp=freeList.at(i);
                size_t sumSize=fixSize;
                size_t countIteration=0;
                while(temp.getNext()->isAvailable() && sumSize>0){
                    temp=*temp.getNext();
                    sumSize-=temp.getSize();
                    countIteration++;
                }
                if(sumSize<=0){
                    int index=findBlock(freeList.at(i).getStartPtr());
                    blocksList[index].setSize(fixSize);
                    blocksList[index].setAvailable(false);
                    blocksList[index].setNext(blocksList.at(index+countIteration-1).getNext());
                    for(int j=1;j<countIteration;j++){
                        blocksList.erase(blocksList.begin()+index+j);
                    }
                    //blocksList.erase(blocksList.begin()+index+countIteration);
                    for(int j=0;j<countIteration;j++){
                        freeList.erase(freeList.begin()+i+j);
                    }
                    return blocksList[index].getStartPtr();
                }
            }
        }
    }
}

void MemoryManager::free(void* pointer) {
//   int size= associativeArray.at(pointer);
//   cout<< size;
//    cout<<"free"<<endl;
//    int size = associativeArray.at(pointer);
//    cout<< size;
//    freeblock f(size,pointer);
//    if(!freeLists->empty() && freeLists->find(pow(2,ceil(log2(size)))) != freeLists->end()){
//        freeLists->at(pow(2,ceil(log2(size)))).push_back(f);
//    }
//    else{
//        //list<freeblock,mystd::MyAllocator<freeblock>> listi;
//        list<freeblock,JVC::allocator<freeblock>> listi;
//        listi.push_back(f);
//        freeLists.insert(make_pair(size,listi));
//    }

    size_t index = (size_t) findBlock(pointer);
    blocksList[index].setAvailable(true);
    freeList.push_back(blocksList[index]);

}

int MemoryManager::findBlock(void* ptr) {
    for(int i = 0 ; blocksList.size() ; i++){
        if(blocksList.at(i).getStartPtr()== ptr){
            return i;
        }
    }
    return -1;
}

