
// Created by Zafrir.

using namespace std;
#include"firstFitManager.h"
#include<iostream>

firstFitManager::firstFitManager() {};


void * firstFitManager::operator new(size_t size)
{
	return malloc(size);
}

firstFitManager::firstFitManager(size_t heapsize):MemoryManager(heapsize){}



void* firstFitManager::allocate(size_t size) {
	if (freeList.empty()) {
		void* ptr = pool->getLocation(size);
		freeblock f(size, ptr);
		f.setAvailable(false);
		f.setNext(nullptr);
		if (blocksList.empty()) {
			//cout << "blockList is empty" << endl;
			blocksList.push_back(f);
		}
		else {
			blocksList.push_back(f);
			blocksList.at(blocksList.size() - 2).setNext(&blocksList.at(blocksList.size() - 1));
		}
		return f.getStartPtr();
	}
	else {
		for (size_t i = 0; i < freeList.size(); i++) {
			if (freeList.at(i).getSize() == size) {
				return freeList.at(i).getStartPtr();
			}
			  if (freeList.at(i).getSize() > size) {//found block bigger, allocate and make chunck
				size_t newSize = freeList.at(i).getSize() - size;
				void* newPtr = (char*)freeList.at(i).getStartPtr() + size;
				freeblock f1(newSize, newPtr);
				f1.setAvailable(true);
				f1.setNext(freeList.at(i).getNext());
				freeList.push_back(f1);
				size_t index = findBlock(freeList.at(i).getStartPtr());//update blockList
				blocksList[index].setSize(size);
				blocksList[index].setAvailable(false);
				blocksList.insert(blocksList.begin() + index, f1);
				blocksList[index].setNext(&blocksList[index + 1]);
				freeList.at(i).setSize(size);//update freeList
				freeList.at(i).setNext(&f1);
				freeblock tmp = freeList.at(i);
				freeList.erase(freeList.begin() + i);

				return tmp.getStartPtr();
			}
		}
		void* ptr = pool->getLocation(size);//allocate object on the heap
		if (ptr != nullptr) {
			freeblock f(size, ptr);
			f.setAvailable(false);
			f.setNext(nullptr);
			blocksList.push_back(f);
			blocksList.at(blocksList.size() - 2).setNext(&blocksList.at(blocksList.size() - 1));
			//freeblock f1 = blocksList.at(blocksList.size() - 1);
			//blocksList.pop_back();
			//f.setNext(&f1);
			//blocksList.push_back(f);
			//blocksList.push_back(f1);
			return f.getStartPtr();
		}
		else { //need to merge chunks
			for (size_t i = 0; i < freeList.size(); i++) {
				freeblock temp = freeList.at(i);
				size_t sumSize = size;
				size_t countIteration = 0;
				while (sumSize>0 && temp.getAvailable()) {//can merge with the next freeblock
					sumSize -= temp.getSize();
					if (temp.getNext() != nullptr)
						temp = *temp.getNext();
					countIteration++;
				}
				if (sumSize <= 0) {//found freeblock that fit in size and available
					size_t index = findBlock(freeList.at(i).getStartPtr());
					blocksList[index].setSize(size);
					blocksList[index].setAvailable(false);
					blocksList[index].setNext(blocksList.at(index + countIteration - 1).getNext());
					for (size_t j = 1; j<countIteration; j++) {
						blocksList.erase(blocksList.begin() + index + 1);
					}
					for (size_t j = 0; j<countIteration; j++) {
						freeList.erase(freeList.begin() + i);
					}
					return blocksList[index].getStartPtr();
				}
			}
		}
		cout << "No more Memory to Allocate" << endl;
		return nullptr;
	}
}

void firstFitManager::myfree(void* pointer) {
	size_t index = MemoryManager::findBlock(pointer);
	MemoryManager::blocksList.at(index).setAvailable(true);
	MemoryManager::freeList.push_back(blocksList.at(index));
}

