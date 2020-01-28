/*************************************************************************************/
/*                                                                                   */
/*   A1 part2 tester file                                                            */
/*                                                                                   */
/*   To compile: g++ disjointset.cpp a1q2tester.cpp a1q2.cpp timer.cpp -std=c++0x    */
/*                                                                                   */
/*                                                                                   */
/*************************************************************************************/

#include "wall.h"
#include "timer.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
int generateMaze(int row, int col, Wall walls[]);
bool test1(std::string& error);	
bool test2(std::string& error);	
bool test3(std::string& error);	
bool test4(std::string& error);	

const int numTests=4;
typedef bool (*TestPtr)(std::string&);
void getRowCol(int cell,int maxRow, int maxCol, int& cellRow, int& cellCol);
bool checkWalls(int maxRow,int maxCol,Wall walls[],int numWalls);
void printMaze(const std::string& fname, int maxRow, int maxCol, Wall walls[], int numWalls);

int main(void){
	TestPtr runTest[numTests]={test1, test2, test3, test4};
	std::string msg;
	bool result=true;
	int numPassed=0;
	Timer t;
	for(int i=0;result && i<numTests;i++){
		t.start();
		result = runTest[i](msg);
		t.stop();
		if(!result){
			std::cout << msg << std::endl;
		}
		else{
			numPassed++;
			std::cout << "Test " << i+1 << " passed!" << std::endl;
		}
	}
	if(numPassed == numTests){
		std::cout << std::endl;
		std::cout << "Congratulations! You have passed testing for A1 part 2" <<  std::endl;
		std::cout << "Total Time: " << t.currtime() << std::endl << std::endl;
		std::cout << "Some mazes generated by your function have been written to your folder"<< std::endl;
		std::cout << "The files are named maze<height>x<width>.txt" << std::endl;
		std::cout << "To see what they look like, go to: " << std::endl;
		std::cout << "    https://seneca-dsa555w20.github.io/dsa555-w20/a1q2.html" << std::endl;
		std::cout << "To see your maze, load the file using the button" << std::endl;
		std::cout << "at top of web page then browse to your files" << std::endl;
	}
	else{
		std::cout << "Looks like you still have some work left to do" << std::endl;
	}
}

/* Given cell, size of maze, calculate the cell's row/col position*/
void getRowCol(int cell,int maxRow, int maxCol, int& cellRow, int& cellCol){
	cellRow=cell/maxCol;
	cellCol=cell%maxCol;
}

/* test1: ensure that the number of walls is correct.  The number of walls depends
   number of rows/cols and number of cells.  So the same number of cells with 
   different number of rows/cols will have different number of walls in solution
   For example suppose your maze had 6 cells with  1 row, 6 cols, the number of walls in solution is
   0 in the solution set.  But if it was 2 rows, 3 cols, the number of walls is 2
*/
bool test1(std::string& error){
	int rc=true;
	Wall walls[50000];
	int result;
	int mazeSizes[10][2]={{1,6},{6,1},{2,3},{20,20},{1,100},{100,1},{50,50},{100,100},{30,60},{40,30}};
	for(int i=0;rc && i<10;i++){
		int row=mazeSizes[i][0];
		int col=mazeSizes[i][1];
		int numCells=row*col;
		int maxWalls=row*(col-1) + col*(row-1);
		int correctWalls=maxWalls-(numCells-1);
		result=generateMaze(row,col,walls);
		if(result != correctWalls){
			rc=false;
			error="Error 1";
			error+= ": function returned ";
			error += std::to_string(result);
			error += ".  It should have returned ";
			error += std::to_string(correctWalls); 		
		}	
	}
	return rc;
}

class MyDisjointSet{
	int* sets_;
	int max_;
public:
	MyDisjointSet(int max){
		max_=max;
		sets_=new int[max];
		for(int i=0;i<max;i++){
			sets_[i]=-1;
		}
	}
	int findSet(int obj) const{
		if(sets_[obj]==-1){
			return obj;
		}
		else{
			return findSet(sets_[obj]);
		}
	}
	void unionSet(int rep1,int rep2){
		sets_[rep2]=rep1;
	}
	int numSets() const{
		int total=0;
		for(int i=0;i<max_;i++){
			if(sets_[i]==-1){
				total++;
			}
		}
		return total;
	}
	~MyDisjointSet(){
		delete [] sets_;
	}
};
void getAdjacentCells(int maxRow,int maxCol,Wall walls[],int numWalls,
							int** adjacent,int* numAdjacent,int numCells){
	int j=0;
	int k=0;
	for(int i=0;i<numCells;i++){
		adjacent[i]=new int[2];
		if(k<maxRow-1){
			if(j<maxCol-1){
				adjacent[i][0]= i+1;
				adjacent[i][1]= i+maxCol;
				j++;
				numAdjacent[i]=2;
			}
			else{
				adjacent[i][0]=i+maxCol;
				j=0;
				numAdjacent[i]=1;
				k++;
			}
		}
		else{
			if(j<maxCol-1){
				adjacent[i][0]= i+1;
				numAdjacent[i]=1;
				j++;
			}
			else{
				numAdjacent[i]=0;
			}			
		}
	}

	for(int i=0;i<numWalls;i++){
		int c1=walls[i].cell1();
		int c2=walls[i].cell2();
		if(c1 > c2){
			int tmp=c1;
			c1=c2;
			c2=tmp;
		}
		if(adjacent[c1][0]==c2){
			adjacent[c1][0]=adjacent[c1][1];
			numAdjacent[c1]--;
		}
	}
}
bool checkWalls(int maxRow,int maxCol,Wall walls[],int numWalls){
	int numCells=maxRow*maxCol;
	MyDisjointSet checkConnected(numCells);
	int** adjacent=new int*[numCells];
	int* numAdjacent=new int[numCells];
	bool rc=true;
	getAdjacentCells(maxRow,maxCol,walls,numWalls,adjacent,numAdjacent,numCells);
	for(int i=0;i<numCells;i++){
		for(int j=0;j<numAdjacent[i];j++){
			int r1=checkConnected.findSet(i);
			int r2=checkConnected.findSet(adjacent[i][j]);
			if(r1!=r2){
				checkConnected.unionSet(r1,r2);
			}
		}
	}
	if(checkConnected.numSets()!=1){
		rc=false;
	}
	return rc;
}
bool sameMaze(int** adjacent1,int* numAdjacent1, int** adjacent2,int* numAdjacent2, int numCells){
	int rc=true;
	for(int i=0;rc && i<numCells;i++){
		if(numAdjacent1[i]!=numAdjacent2[i]){
			rc=false;
		}
		else{
			for(int j=0;rc && j<numAdjacent1[i];j++){
				if(adjacent1[i][j] != adjacent2[i][j]){
					rc=false;
				}
			}
		}
	}
	return rc;
}
void printMaze(const std::string& fname, int maxRow, int maxCol, Wall walls[], int numWalls){
	std::ofstream fs(fname);
	fs << "{ \"maxRow\": " << maxRow << ",";
	fs  << "\"maxCol\": " << maxCol << ",";
	fs << "\"walls\": [";
	for(int i=0;i<numWalls - 1;i++){
		fs <<"[" <<  walls[i].cell1() << ", " << walls[i].cell2() <<"], " ;
	}
	fs <<"[" << walls[numWalls-1].cell1() << ", " << walls[numWalls-1].cell2() <<"]]}" << std::endl;
	fs.close();
}
/*test2: check to make sure every cell is reacheable.  
This is done by seeing whether or not all cells are connected*/
bool test2(std::string& error){
	int rc=true;
	Wall walls[50000];
	bool result;
	int mazeSizes[10][2]={{1,6},{6,1},{2,3},{3,2},{20,20},
							{70,100},{50,50},{100,70},{30,60},{40,30}};
	for(int i=0;rc && i<10;i++){
		int row=mazeSizes[i][0];
		int col=mazeSizes[i][1];
		int numCells=row*col;
		int maxWalls=row*(col-1) + col*(row-1);
		int correctWalls=maxWalls-(numCells-1);
		int numWalls=generateMaze(row,col,walls);
		result = checkWalls(row,col,walls,numWalls);
		if(!result){
			rc=false;
			error="Error 2";
			error+= ": at least one cell does is not reacheable.\n";
			error+= "To view the maze generated go to:\n  https://seneca-dsa555w20.github.io/dsa555-w20/a1q2.html\n";
			error+= "and load the file error2.txt(found in your directory)";
			printMaze("error2.txt",row,col,walls,numWalls);
		}
	}
	return rc;
}

/*test3: create 100 items, merge together into pairs, check
  that their representatives are consistent*/
bool test3(std::string& error){
	int rc=true;
	Wall walls1[50000];
	Wall walls2[50000];
	bool result;
	int mazeSizes[5][2]={{20,20},{50,50},{70,100},{30,60},{40,30}};
	for(int i=0;rc && i<5;i++){
		int row=mazeSizes[i][0];
		int col=mazeSizes[i][1];
		int numCells=row*col;

		int numWalls1=generateMaze(row,col,walls1);
		int** adjacent1=new int*[numCells];
		int* numAdjacent1=new int[numCells];		
		getAdjacentCells(row,col,walls1,numWalls1,adjacent1,numAdjacent1,numCells);


		int numWalls2=generateMaze(row,col,walls2);
		int** adjacent2=new int*[numCells];
		int* numAdjacent2=new int[numCells];		
		getAdjacentCells(row,col,walls2,numWalls2,adjacent2,numAdjacent2,numCells);

		if(sameMaze(adjacent1,numAdjacent1, adjacent2,numAdjacent2,numCells)){
			rc=false;
			error="Error 3: Your generateMaze() function appears to be generating the same maze each time.\nIt should generate a different maze with each call\n";
			error+= "To view the maze generated go to:\n   https://seneca-dsa555w20.github.io/dsa555-w20/a1q2.html\n";
			error+= "and load the file error3.txt(found in your directory)";
			printMaze("error3.txt",row,col,walls1,numWalls1);
		}
	}
	return rc;
}
bool test4(std::string& error){
	Wall walls[50000];

	bool result;
	int mazeSizes[8][2]={{10,20},{20,10},{50,50},{6,1},{1,6},{30,60},{40,30},{70,100}};
	for(int i=0;i<8;i++){
		int row=mazeSizes[i][0];
		int col=mazeSizes[i][1];
		int numWalls=generateMaze(row,col,walls);
		std::string fname="maze";
		fname+=std::to_string(row);
		fname+="x";
		fname+=std::to_string(col);
		fname+=".txt";
		printMaze(fname,row,col,walls,numWalls);
	}
	return true;
}

