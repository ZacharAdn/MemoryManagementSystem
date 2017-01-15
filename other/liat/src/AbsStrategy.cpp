#include "AbsStrategy.h"

AbsStrategy::AbsStrategy(){
	
}
AbsStrategy::~AbsStrategy(){
	
}
void AbsStrategy::operator delete(void* ptr) {
	free(ptr); 
}
void* AbsStrategy::operator new(size_t size) {
	return malloc(size);
}