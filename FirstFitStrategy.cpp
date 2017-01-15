//
// Created by zahar on 11/01/17.
//

#include "FirstFitStrategy.h"

FirstFitStrategy::FirstFitStrategy(MemPool *pool) : AllocationStrategy(pool), freeList(new blocksLinkedList()) {}

FirstFitStrategy::~FirstFitStrategy() {

}

void *FirstFitStrategy::myAllocate(size_t size) {
    size_t fixedSize = (size_t) pow(2,ceil(log2(size)));
    freeblock *newBlock;
    void* ptr = nullptr;

    if(fixedSize < MIN_CELL_SIZE){
        fixedSize = MIN_CELL_SIZE;
    }

    if(freeList->empty()){

        ptr = pool->getNextFreeLocationPtr(fixedSize);
        if(ptr== nullptr){
            std::cout << "NO MORE SPACE ON THE HEAP";
            exit(1);
        }

        newBlock = new freeblock(ptr , fixedSize);

        associativeArray[newBlock->getStartPtr()] = newBlock;
        return newBlock->getStartPtr();

    }else{
        newBlock = findCustomBlock(fixedSize);

        if(!newBlock){//its no blocks with enough space
            ptr = pool->getNextFreeLocationPtr(fixedSize);//allocate object on the heap
            if(ptr== nullptr){
                std::cout << "NO MORE SPACE ON THE HEAP";
                exit(1);
            }
            newBlock = new freeblock(ptr,fixedSize);
            associativeArray.emplace(ptr,newBlock);
        }
        return newBlock;
    }
    exit(1);
}

void FirstFitStrategy::myFree(void *ptr) {
    freeList->addBlock(associativeArray[ptr]);
}


freeblock *FirstFitStrategy::findCustomBlock(size_t size) {
    freeblock *current = freeList->getHead(), *firstToMerge= nullptr,*result= nullptr, *cutedBlock = nullptr;
    size_t mergedSize = 0, mergeCount = 0;

    std::vector<freeblock*, mystd::allocator<freeblock*>> *blocksToDelete;



    while(current!= nullptr){

        if(current->getSize() == size){// block with same size
            freeList->removeByPtr(current->getStartPtr());
            return current;
        }else if(current->getSize() > size) {// need to cut from the current

            size_t cutedSize = current->getSize()/2;

            void* ptrAns = current->getStartPtr();;
            associativeArray.erase(current->getStartPtr());
            freeList->removeByPtr(current->getStartPtr());

            while (cutedSize >= size){
                cutedBlock = new freeblock((char*)ptrAns+cutedSize , cutedSize);
                freeList->addBlock(cutedBlock);
                associativeArray.emplace(cutedBlock->getStartPtr(),cutedBlock);
                cutedSize /= 2;
            }

            result = new freeblock(ptrAns,cutedSize);
            associativeArray.emplace(result->getStartPtr(),result);


            return result;
        }else if(current->getSize() < size){//need to merge blocks
            if(mergedSize == 0) {
                firstToMerge = current;
            }
            mergedSize += current->getSize();
            mergeCount++;
            blocksToDelete->push_back(current);
        }


        if(mergedSize == size){
            for (size_t j = 0; j < mergeCount; ++j) {
                associativeArray.erase(blocksToDelete->at(j)->getStartPtr());
                freeList->removeByPtr(blocksToDelete->at(j)->getStartPtr());
            }

            result = new freeblock(firstToMerge->getStartPtr(),mergedSize);
            associativeArray.emplace(result->getStartPtr(),result);
            return result;
        }else if(mergedSize > size){
            size_t overSize = mergedSize-size;
            for (size_t j = 0; j < mergeCount; ++j) {
                associativeArray.erase(blocksToDelete->at(j));
                freeList->removeByPtr(blocksToDelete->at(j));
            }

            freeblock *cuted = new freeblock(blocksToDelete->at(mergeCount-1)+size, overSize);
            freeList->addBlock(cuted);

            result = new freeblock(firstToMerge->getStartPtr(),size);
            associativeArray.emplace(result->getStartPtr(),result);

            return result;
        }
        current=current->getNext();
    }

    return nullptr;
}

void* FirstFitStrategy::operator new(size_t size){
    std::cout << "first new";
    return malloc(size);
}

void FirstFitStrategy::operator delete(void* ptr){
    free(ptr);
}

size_t FirstFitStrategy::howMuchToCut(size_t currentBlockSize, size_t size) {
    size_t sourceSize = currentBlockSize;

    while (sourceSize/2 > size){

        sourceSize /= 2;
    }

    return 0;
}
