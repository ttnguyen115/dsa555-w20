//writing recursive functions:
//find base case first
//   for what values of n do you have an "easy"
//   solution for n!
//use function in recursive case, providing an 
//argument that gets you closer to the base case

/*this function returns n! = n * (n-1) * ... 3 * 2 * 1
	5! = 5 * (4 * 3 * 2 * 1)
	   = 5 * 4!

	n! = n * (n-1)!

*/
//let n represent number used for factorial function
//let T(n) represent number of ops needed to find
//n!
unsigned int factorial (unsigned int n){
	int rc=1;      //1
	if(n > 1){     //1

		//3 + # of ops needed to find n-1 factorial
		//using our factorial function
		//in other words: 3 + T(n-1)
		rc = n * factorial(n-1);   
	}
	return rc;     //1
}


int main(void){
	int x;
	x=factorial(4);
}

