//
// Created by zahar on 11/01/17.
//

#include "FirstFitStrategy.h"

FirstFitStrategy::FirstFitStrategy(MemPool *pool) : AllocationStrategy(pool), freeList(new blocksLinkedList()) {}

FirstFitStrategy::~FirstFitStrategy() {

    //free all the freeblocks on the map
    for (auto it = associativeArray.begin(); it != associativeArray.end() ; it++){
        delete it->second;
    }

    delete freeList;
}

void *FirstFitStrategy::myAllocate(size_t size) {

    //normalization the size to powers of 2
    size_t fixedSize = (size_t) pow(2,ceil(log2(size)));
    freeblock *newBlock = nullptr;
    void* ptr = nullptr;

    // the minimum size to allocate - 4
    if(fixedSize < MIN_CELL_SIZE){
        fixedSize = MIN_CELL_SIZE;
    }

    if(freeList->empty()){
        //its no blocks in free list - allocation from the pool
        ptr = pool->getNextFreeLocationPtr(fixedSize);

        // its no space on the pool
        if(ptr== nullptr){
            std::cout << "NO MORE SPACE ON THE HEAP";
            exit(1);
        }

        newBlock = new freeblock(ptr , fixedSize);
        associativeArray[newBlock->getStartPtr()] = newBlock;
        return newBlock->getStartPtr();

    }else{
        //loock for block in custom size
        newBlock = findCustomBlock(fixedSize);

        //its no blocks with enough space
        if(!newBlock){
            //allocate object on the heap
            ptr = pool->getNextFreeLocationPtr(fixedSize);

            // its no space on the pool
            if(ptr== nullptr){
                std::cout << "NO MORE SPACE ON THE HEAP";
                exit(1);
            }
            newBlock = new freeblock(ptr,fixedSize);
            associativeArray[ptr] = newBlock;
        }
        return newBlock->getStartPtr();
    }
}

void FirstFitStrategy::myFree(void *ptr) {
    //find the block by ptr on the associativeArray and add hem to freList
    freeList->addBlock(associativeArray[ptr]);
}


freeblock *FirstFitStrategy::findCustomBlock(size_t size) {
    freeblock *current = freeList->getHead(), *firstToMerge= nullptr,*result= nullptr, *cutedBlock = nullptr;
    size_t mergedSize = 0, mergeCount = 0;

    //saves blocks thed need to merged
    std::vector<freeblock*, mystd::allocator<freeblock*>> blocksToDelete;

    while(current!= nullptr){
        size_t currSize = current->getSize();


        if(currSize == size){//it is block with same size
            freeList->removeByPtr(current->getStartPtr());
            result = new freeblock(current->getStartPtr(), size);
            return result;

        }else if(currSize  > size) {// need to cut from the current
            size_t cutedSize = currSize /2;

            void* ptrAns = current->getStartPtr();;

            //delete the block from the map and the list - need to change he's size
            associativeArray.erase(current->getStartPtr());
            freeList->removeByPtr(current->getStartPtr());

            //recursive func to cut the blocks
            while (cutedSize > size){
                cutedBlock = new freeblock((char*)ptrAns+cutedSize , cutedSize);
                freeList->addBlock(cutedBlock);
                associativeArray[cutedBlock->getStartPtr()] = cutedBlock ;
                cutedSize /= 2;
            }
            //the last block that cuted
            cutedBlock = new freeblock((char*)ptrAns+cutedSize , cutedSize);
            freeList->addBlock(cutedBlock);
            associativeArray[cutedBlock->getStartPtr()] = cutedBlock ;


            result = new freeblock(ptrAns,cutedSize);
            associativeArray[result->getStartPtr()] = result;

            return result;

        }else if(currSize < size){//need to merge blocks
            if(mergedSize == 0) {
                firstToMerge = current;//saves the first to merge
            }
            mergedSize += currSize;
            mergeCount++;

            //save in the vector
            blocksToDelete.push_back(current);
        }


        //if its enough blocks for merge
        if(mergedSize >= size){
            //delete from the Map and the List all the blocks gonna to merge
            for (size_t j = 0; j < mergeCount; ++j) {
                associativeArray.erase(blocksToDelete.at(j)->getStartPtr());
                freeList->removeByPtr(blocksToDelete.at(j)->getStartPtr());
            }

            //if its block with remain
            if(mergedSize > size) {
                size_t overSize = mergedSize - size;
                cutedBlock = new freeblock(blocksToDelete.at(mergeCount - 1) + size, overSize);
                freeList->addBlock(cutedBlock);
                mergedSize = size;
            }

            //the merged block
            result = new freeblock(firstToMerge->getStartPtr(),mergedSize);
            associativeArray[result->getStartPtr()] = result ;

            delete firstToMerge;
            delete cutedBlock;

            return result;
        }

        current=current->getNext();
    }

    return nullptr;
}


void FirstFitStrategy::valgrind() {
    size_t allocatedMemory = 0 ;

    freeblock *current= freeList->getHead();

    //sum of the all the allocated blocks
    for (auto it=associativeArray.begin(); it!=associativeArray.end(); ++it){
        allocatedMemory += it->second->getSize();
    }

    //sum of all the free blocks
    while(current != nullptr){
        allocatedMemory -= current->getSize();
        current = current->getNext();
    }

    std::cout << "\nBytes Allocated And Not Released : " << allocatedMemory << "\n";

}

void* FirstFitStrategy::operator new(size_t size){
    return malloc(size);
}

void FirstFitStrategy::operator delete(void* ptr){
    free(ptr);
}
