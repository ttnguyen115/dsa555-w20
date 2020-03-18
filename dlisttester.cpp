#include "lab3.h"

int main(void){
	DList<int> regular;
	for(int i=0;i<3;i++){
		regular.push_front(i);
	}
	regular.print();
	regular.reversePrint();
	for(int i=0;i<4;i++){
		regular.pop_front();
	}
	regular.print();
	regular.reversePrint();
}