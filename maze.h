#ifndef MAZE
#define MAZE

#include <iostream>
#include "glut.h"

enum viewtype{top_view,perspective_view,rat_view};
class Maze
{
public:
	Maze();
	Maze(int m, int n);
	~Maze();
	void Draw(viewtype view);
	int GetSize(){ return M*N; };
	double GetM();
	double GetN();
	//std::string CheckCollision(double x, double y, double radius);
	bool CheckCollision(double x, double y, double radius);

	double padding_x;
	double padding_y;
	double screen_x;
	double screen_y;
	int cellWidth;
	int cellHeight;
private:
	struct Cell {
		Cell()
		{
			l=b=r=t=true;
			visited = false;
		}
		void Draw (double x1, double y1, double x2, double y2, int M, int N,viewtype view);
		bool l,b,r,t; //true if cell walls exist
		bool visited;
	};
	Cell * cellArray;
	void RemoveStartandEnd();
	void RemoveWalls(int index);
	void MarkAllNotVisited();
	int PickNextCell(int index);
	void RemoveWallBetween(int cell1, int cell2);
	int M,N; //columns,rows

};

#endif