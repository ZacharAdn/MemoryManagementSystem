//
// Created by zahar on 11/01/17.
//

#include "FirstFitStrategy.h"

FirstFitStrategy::FirstFitStrategy(MemPool *pool) : AllocationStrategy(pool) {}

FirstFitStrategy::~FirstFitStrategy() {

}

void *FirstFitStrategy::myAllocate(size_t size) {
    size_t fixedSize = (size_t) pow(2,ceil(log2(size)));

    if(freeList.empty()){//TODO why freeList?
        void* ptrAddress = pool->getNextFreeLocationPtr(fixedSize);
        freeblock *newBlock = new freeblock(ptrAddress , fixedSize);
        newBlock->setAvailable(false);

        blocksList.push_back(newBlock);

        if(!blocksList.empty()){
            blocksList.at(blocksList.size()-1)->setNext(newBlock);
        }

        return newBlock->getStartPtr();

    }else{

        for(size_t i = 0 ; i < freeList.size() ; i++){
            if(freeList.at(i)->getSize() == fixedSize){
                return freeList.at(i)->getStartPtr();
            }

            if(freeList.at(i)->getSize() > fixedSize){
                //here we need to cut block
                size_t oldSize = freeList.at(i)->getSize();
                size_t newSize = freeList.at(i)->getSize() - fixedSize;//TODO fix size for newSize

                void* newPtr = freeList.at(i)->getStartPtr() + fixedSize;
                freeblock *f1 = new freeblock(newPtr, newSize);
                f1->setAvailable(true);
                f1->setNext(freeList.at(i)->getNext());

                /////// update blockList//////////
                size_t index = (size_t) findBlock(freeList.at(i)->getStartPtr());
                blocksList.at(index)->setSize(fixedSize);
                blocksList.at(index)->setAvailable(false);
                blocksList.at(index)->setNext(f1);
                blocksList.insert(blocksList.begin()+index , f1);
                ///////// update freeList///////////
                freeList.at(i)->setSize(fixedSize);
                freeList.at(i)->setNext(f1);
                freeList.push_back(f1);
                freeblock *tmp = freeList.at(i);
                freeList.erase(freeList.begin()+i);
                return tmp->getStartPtr();
            }
        }
//
//        cout << "lalala";
//
//        for (std::vector<freeblock,mystd::allocator<freeblock>>::iterator i = blocksList.begin(); i != blocksList.end(); ++i)
//            std::cout << i->toString() << ' ';


        void* ptr = this->pool->getNextFreeLocationPtr(fixedSize);//myAllocate object on the heap
        if(ptr!=nullptr){
            freeblock *f= new freeblock(ptr ,fixedSize);
            f->setAvailable(false);
            freeblock *f1 = blocksList.at(blocksList.size()-1);
            blocksList.pop_back();
            f->setNext(f1);
            blocksList.push_back(f1);
            blocksList.push_back(f);
        }
        else{ /////// if we need, here we need to merge chunks////////
            for(size_t i = 0 ; i < freeList.size() ; i++){
                freeblock *temp=freeList.at(i);
                size_t sumSize=fixedSize;
                size_t countIteration=0;
                while(temp->getNext()->isAvailable() && sumSize>0){
                    temp=temp->getNext();
                    sumSize-=temp->getSize();
                    countIteration++;
                }
                if(sumSize<=0){
                    int index=findBlock(freeList.at(i)->getStartPtr());
                    blocksList[index]->setSize(fixedSize);
                    blocksList[index]->setAvailable(false);
                    blocksList[index]->setNext(blocksList.at(index+countIteration-1)->getNext());
                    for(int j=1;j<countIteration;j++){
                        blocksList.erase(blocksList.begin()+index+j);
                    }
                    //blocksList.erase(blocksList.begin()+index+countIteration);
                    for(int j=0;j<countIteration;j++){
                        freeList.erase(freeList.begin()+i+j);
                    }
                    return blocksList[index]->getStartPtr();
                }
            }
        }
    }
}

void FirstFitStrategy::myFree(void *pointer) {
    size_t index = (size_t) findBlock(pointer);
    blocksList[index]->setAvailable(true);
    pool->updateHeap(blocksList[index]->getSize());
    freeList.push_back(blocksList[index]);
}

int FirstFitStrategy::findBlock(void* ptr) {
    for(int i = 0 ; blocksList.size() ; i++){
        if(blocksList.at((size_t)i)->getStartPtr()== ptr){
            return i;
        }
    }
    return -1;
}


void* FirstFitStrategy::operator new(size_t size){
    std::cout << "first new";
    return malloc(size);
}

void FirstFitStrategy::operator delete(void* ptr){
    free(ptr);
}
