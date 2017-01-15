#include "Valgrind.h"
#include "MemoryManager.h"
#include "Tests.h"

#define NEED_VFLAG 'v'
#define NOT_NEED_VFLAG 'x'

#define NEED_VALGRIND 'V'
#define NOT_NEED_VALGRIND 'X'

using namespace std;


int main(int argc, char* argv[]) {
	Tests t;
	//var represent if need v flag
	char ifVFlag = NOT_NEED_VFLAG;
	//var check if need valgrind flag
	char ifValgrid = NOT_NEED_VALGRIND;
	
	
	if(argc == 3){
		MemoryManager::getInstance((size_t)atoi(argv[2]));
	}
	else if (argc == 4){
		
		MemoryManager::getInstance((size_t)atoi(argv[2]));
		
		//check if need v flag
		if(argv[3][0] == '-' &&  argv[3][1] == 'v'){
			ifVFlag = NEED_VFLAG;
		}else{
			ifVFlag = NOT_NEED_VFLAG;
		}
		
		//check if need valgrind
		if(argv[3][0] == '-' &&  argv[3][1] == 'm'){
			ifValgrid = NEED_VALGRIND;
		}else{
			ifValgrid = NOT_NEED_VALGRIND;
		}

	}else{
		cout << "Regular executen example : ./run_game.o -S 1000 " << endl;
		cout << "with memory leak or Valgrind executen example : ./run_game.o -S 1000 -v/-m (-v sum memory leak , -m valgrind)" << endl;
		
		return 1;
	}
	t.PremitiveLinkedList();//no leaks
	t.PremitiveLinkedList1();//no leaks
	t.LinkedListPairs(); //no leaks
	t.LeakTest();//need to leak 8 bytes;
	t.LinkedListPairsWithLeaks(); // 3 blocks 56 bytes leak
	
	if(ifVFlag == NEED_VFLAG){
		MemoryManager::getInstance()->printVFlag();
	}
	
	if(ifValgrid == NEED_VALGRIND){
		Valgrind::getInstance()->print();
	}
	
	delete Valgrind::getInstance();//->~Valgrind();
	//free (Valgrind::getInstance());
	
	delete MemoryManager::getInstance();//->~MemoryManager();
	//free (MemoryManager::getInstance());
	
	return 1;
}