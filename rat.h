#include "glut.h"
#include <cmath>
#include "maze.h"

#ifndef RAT_H
#define RAT_H

void DrawCircle(double x1, double y1, double radius);
class Rat
{
public:
	Rat();
	Rat(double x, double y, double d);
	void Draw(viewtype view);
	void Scuttle(Maze & gMaze);
	void SpinLeft();
	void SpinRight();
	double getNextX();
	double getNextY();
	double getX();
	double getY();
	double getdX();
	double getdY();
	double getD() {return D;};

private:
	double MoveConstant;
	double SpinConstant;
	double CollisionRadius;
	double X;
	double Y;
	double dX;
	double dY;
	double D;
	double previousX;
	double previousY;
};

#endif // RAT