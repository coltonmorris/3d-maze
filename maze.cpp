#include "maze.h"
#include <time.h>

Maze::Maze()
	: cellArray(0),
	  M(0),
	  N(0)
{
	//do nothing
}

Maze::Maze(int m, int n)
	:
	  M(m),
	  N(n)
{
	padding_x = 1;
	padding_y = 1;
	screen_x = 10;
	screen_y = 10;
	cellWidth = (screen_x-padding_x*2)/M;
	cellHeight = (screen_y-padding_y*2)/N;
	cellArray = new Cell[M*N];
	srand (time(NULL));
	RemoveWalls(0);
	RemoveStartandEnd();

}

Maze::~Maze(){
	//delete the cell array
}

//std::string Maze::CheckCollision(double x, double y, double radius) {
bool Maze::CheckCollision(double x, double y, double radius) {
	//let mouse roam outside maze
	if (x < 0 || y <0 || y >GetM() || x > GetN() ) {
		return true;
	}

	//find decimal value of rats location in cell
	double ox = x -int(x);
	double oy = y -int(y);

	//find the cell index
	int index = int(y)*M + int(x);

	//check each side
	if ( ox - radius < 0 && cellArray[index].l){
		//std::cout<<"touching left-side"<<std::endl;
		return false;
	}
	if ( ox + radius > 1 && cellArray[index].r){
		//std::cout<<"touching right-side"<<std::endl;
		return false;
	}
	if ( oy - radius < 0 && cellArray[index].b){
		//std::cout<<"touching bot-side"<<std::endl;
		return false;
	}
	if ( oy + radius > 1 && cellArray[index].t){
		//std::cout<<"touching top-side"<<std::endl;
		return false;
	}
	//check corners
	//if (
	return true;
}

double Maze::GetM(){
	return M;
}
double Maze::GetN(){
	return N;
}
void Maze::Draw(viewtype view){
	for (int i = 0; i < M*N ; i++){
		int x1 = ( padding_x + cellWidth * (i%M) );
		int y1 = ( padding_y + cellHeight * (i/M) );
		//glColor3d(  double(x1)/M , double(y1)/N , double(i)/M*N);
		cellArray[i].Draw( x1, y1, x1+cellWidth, y1+cellHeight, M, N, view);
	}
}

void Maze::Cell::Draw(double x1, double y1, double x2, double y2, int M, int N,viewtype view) {

	if (view == top_view){
		glBegin(GL_LINES);
		if (l) {
			glColor3d( double(x1)/M -.2 , double(y1)/N , double(y2)/N -.2 );
			glVertex2d(x1,y1);
			glVertex2d(x1,y2);
		}
		if (r) {
			glColor3d( double(x2)/M -.2 , double(y1)/N , double(y2)/N -.2 );
			glVertex2d(x2,y1);
			glVertex2d(x2,y2);
		}
		if (t) {
			glColor3d( double(x1)/M -.2 , double(y2)/N , double(x2)/M -.2 );
			glVertex2d(x1,y2);
			glVertex2d(x2,y2);
		}
		if (b) {
			glColor3d( double(x1)/M-.2  , double(y1)/N , double(x2)/M -.2 );
			glVertex2d(x1,y1);
			glVertex2d(x2,y1);
		}
		glEnd();
	}
	else {
		//quads
		double height = .5;
		glBegin(GL_QUADS);
		if (l) {
			glColor3d( double(x1)/M -.2 , double(y1)/N , double(y2)/N -.2 );
			glVertex3d(x1,y2,height); //top right
			glVertex3d(x1,y1,height); //top left
			glVertex3d(x1,y1,0);      //bottom left
			glVertex3d(x1,y2,0);      //bottom right
		}
		if (r) {
			glColor3d( double(x2)/M -.2 , double(y1)/N , double(y2)/N -.2 );
			glVertex3d(x2,y2,height); //top right
			glVertex3d(x2,y1,height); //top left
			glVertex3d(x2,y1,0);      //bottom left
			glVertex3d(x2,y2,0);      //bottom right
		}
		if (t) {
			glColor3d( double(x1)/M -.2 , double(y2)/N , double(x2)/M -.2 );
			glVertex3d(x2,y2,height); //top right
			glVertex3d(x1,y2,height); //top left
			glVertex3d(x1,y2,0);      //bottom left
			glVertex3d(x2,y2,0);      //bottom right
		}
		if (b) {
			glColor3d( double(x1)/M -.2, double(y1)/N , double(x2)/M -.2 );
			glVertex3d(x2,y1,height); //top right
			glVertex3d(x1,y1,height); //top left
			glVertex3d(x1,y1,0);      //bottom left
			glVertex3d(x2,y1,0);      //bottom right
		}
		//glFlush();
		glEnd();
	}
}

void Maze::RemoveWalls(int index)
{
	cellArray[index].visited = true;
	while( true) {
		//pick next cell returns -1 if it couldnt find a neighbor
		int nextIndex = PickNextCell(index);
		if(nextIndex == -1){
			break;
		}
		RemoveWallBetween(index,nextIndex);
		RemoveWalls(nextIndex);
	}
}
void Maze::RemoveWallBetween(int cell1, int cell2){
	int tester = cell1 - cell2;
	if (tester == M){
		//remove cell1 bot, cell2 top
		cellArray[cell1].b = false;
		cellArray[cell2].t = false;
	}
	if (tester == -M) {
		//remove cell1 top, cell2 bot
		cellArray[cell1].t = false;
		cellArray[cell2].b = false;
	}
	if (tester == 1) {
		//remove cell1 left, cell2 right
		if ( cell1/M != cell2/M ) {
			//do not remove walls
		}
		else {
			cellArray[cell1].l = false;
			cellArray[cell2].r = false;
		}
	}
	if (tester == -1) {
		//remove cell1 right, cell2 left
		if ( cell1/M != cell2/M ) {
			//do not remove walls
		}
		else {
		cellArray[cell1].r = false;
		cellArray[cell2].l = false;
		}
	}

}

int Maze::PickNextCell(int index){
	int i = index%M;
	int j = index/M;
	int nextIndex =-1;

	int legalChoices = 0;
	if(j>0 && cellArray[index-M].visited == false){ //downward?
		legalChoices++;
	}
	if(j<N -1 && cellArray[index+M].visited == false){//upward?
		legalChoices++;
	}
	if(i>0 && cellArray[index-1].visited == false) {//left?
		legalChoices++;
	}
	if(i< M-1 && cellArray[index+1].visited == false) {//right?
		legalChoices++;
	}
	if(legalChoices==0)
		return -1;
	int choice = rand()%legalChoices+1;
	legalChoices=0;
	if(j>0 && cellArray[index-M].visited == false){ //downward?
		legalChoices++;
		if(legalChoices==choice)
			return index-M;
	}
	if(j<N -1 && cellArray[index+M].visited == false){//upward?
		legalChoices++;
		if(legalChoices==choice)
			return index+M;
	}
	if(i>0 && cellArray[index-1].visited == false) {//left?
		legalChoices++;
		if(legalChoices==choice)
			return index-1;
	}
	if(i< M-1 && cellArray[index+1].visited == false) {//right?
		legalChoices++;
		if(legalChoices==choice)
			return index+1;
	}
	return -1;
}

void Maze::RemoveStartandEnd(){
	int choice = rand()%M;
	cellArray[M*N-1-choice].t = false;
	cellArray[0].b=false;
}
