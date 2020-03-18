#include <cstdlib>
#include <iostream>
using namespace std;

int main(void){
//	srand(someconstant)
	for(int i=0;i<5;i++){
		cout << rand() << endl;
	}
	cout << "***" << endl;
	for(int i=0;i<5;i++){
		cout << rand() << endl;
	}
	return 0;
}