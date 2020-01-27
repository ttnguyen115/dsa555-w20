function Maze(){
	that={};
	var width_;
	var height_;
	var walls_;
	var initialized_=false;
	var cellWidth_;
	that.init = function(obj){
		mazeData=JSON.parse(obj);
		width_=mazeData.maxCol;
		height_=mazeData.maxRow;
		walls_=mazeData.walls;
		wallWidth_=5;
		initialized_=true;
		cellWidth_=min(int(1000/width_),20);
	}
	that.getRow=function(cell){
		return cell/height_;
	}
	that.getCol=function(cell){
		return cell%width_;
	}
	that.draw=function(){
		if(initialized_){
			strokeWeight(5);
			line(0,2.5,(width_*cellWidth_)+10,2.5);
			line(0,(height_*cellWidth_)+10,(width_*cellWidth_)+10,(height_*cellWidth_)+10);
			line(2.5,0,2.5,(height_*cellWidth_)+10);
			line((width_*cellWidth_)+10,0,(width_*cellWidth_)+10,(height_*cellWidth_)+10);

			strokeWeight(1);
			for(var i=0;i<walls_.length; i++){
				cell1=walls_[i][0];
				cell2=walls_[i][1];
				if(cell1 > cell2){
					var tmp=cell1;
					cell1=cell2;
					cell2=tmp;					
				}
				r1=int(cell1/width_);
				c1=cell1%width_;
				r2=int(cell2/width_);
				c2=cell2%width_;
				if(r1==r2){
					line(5+(c2*cellWidth_),5+(r1*cellWidth_), 5+(c2*cellWidth_),5+((r1+1)*cellWidth_));
				}
				else{
					line(5+(c2*cellWidth_),5+(r2*cellWidth_), 5+((c2+1)*cellWidth_),5+(r2*cellWidth_));					
				}
			}

		}
	}
	that.mazeWidth=function(){
		return width_;
	}
	that.mazeHeight=function(){
		return height_;
	}
	that.isInitialized=function(){
		return initialized_;
	}
	that.reset=function(){
		initialized_=false;
	}
	return that;
}

var theMaze;
var mazeFileInput;
var pathFile
var radio;
var thePath;
var theCanvas;
function Path(){
	var that = {}
	var initialized_=false;
	var thePath_;
	var curr_=0;
	var wallWidth_=5;
	that.init=function(pathArray){
		thePath_=JSON.parse(pathArray);
		initialized_=true;
	}
	that.draw=function(){
		if(initialized_){
			for(var i=0;i<curr_;i++){
				fill(0,0,255);
				stroke(0,0,255);
				rect(thePath_[i*2]*wallWidth_,thePath_[i*2+1]*wallWidth_,wallWidth_,wallWidth_);			
			}
			curr_+=5;;
		}
	}
	that.isInitialized=function(){
		return initialized_;
	}
	that.reset=function(){
		initialized_=false;
		curr_=0;
	}
	return that;
}
function loadPathFile(file){
	if(thePath.isInitialized()){
		thePath.reset();
	}
	thePath.init(file.data);
}
function loadMazeFile(file){
	if(thePath.isInitialized()){
		theMaze.reset();
	}
	theMaze.init(file.data);
}

function loadMaze(){
	switch(radio.value()){
		case '1': 
			theMaze.init(maze1,1,1,1,99); break;
		case '2':
			theMaze.init(maze1,75,69,99,85); break;
		case '3':
			theMaze.init(maze1,75,69,75,69); break;		
		case '4': 
			theMaze.init(maze1,99,85,75,69); break;			
		case '5': 
			theMaze.init(maze2,1,1,191,199); break;
		case '6':
			theMaze.init(maze3,1,1, 75,69); break;
		default:
			theMaze.init(maze1,1,1,1,99);		
	}
	thePath.reset();
}

function setup(){
	theMaze=Maze();
	thePath=Path();
	mazeFileInput=createFileInput(loadMazeFile);
	mazeFileInput.position(10,10);
	theCanvas=createCanvas(1200,1010);
	theCanvas.position(10,40);

}

function draw(){
	background(255,255,255);
	theMaze.draw();
//	thePath.draw();

}
