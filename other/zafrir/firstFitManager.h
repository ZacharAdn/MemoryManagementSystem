
// Created by Zafrir.

#pragma once
#include"MemoryManager.h"


//firstFitManager - inherit from memorymanger and override allocate and myfree.
//firstFitManager is singeltone for override global new in main and take every time the same firsfitmanager

class firstFitManager : public MemoryManager {

public:
	static firstFitManager* getInstance(size_t heapSize) {
		static firstFitManager* instance = new firstFitManager(heapSize);
		return instance;
	}
	void* allocate(size_t) ;
	void myfree(void*);

private:
	firstFitManager();
	firstFitManager(size_t heapsize);
	void* operator new(size_t size);
	static firstFitManager* instance;
};
