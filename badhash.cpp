#include <iostream>
#include <cstdlib>
#include <cstring>

unsigned int badHashFunction(const char* key){
	unsigned int rc=0;
	for(int i=0;key[i]!='\0';i++){
		rc+=key[i];
	}
	return rc;
}
int main(int argc, char* argv[]){

	if(argc != 3){
		std::cout << "a.out key capacity" << std::endl;
	}
	else{
		unsigned int capacity=atoi(argv[2]);
		unsigned int hashvalue = badHashFunction(argv[1]);
		std::cout << "hash(" << argv[1] << ") = " << hashvalue << std::endl;
		std::cout << "hashindex = " << hashvalue << " % " << capacity << " = " << hashvalue%capacity << std::endl;

	}
	return 0;
}