#include <iostream>
#include "rat.h"

#define PI 3.141592653589

Rat::Rat(double x, double y, double d) :
	D(d),SpinConstant(0.1),MoveConstant(.0005)
{
	CollisionRadius = .25;
	X = MoveConstant*std::cos(D * PI / 180.0)+1.5;
	Y = MoveConstant*std::sin(D * PI / 180.0)+1;
	previousX = X;
	previousY = Y;
	dX = MoveConstant*std::cos(D*PI / 180.0);
	dY = MoveConstant*std::sin(D*PI / 180.0);
}
Rat::Rat() :
	X(0),Y(0),D(0),SpinConstant(0.0),MoveConstant(0) {
}
double Rat::getNextX(){
		return X + MoveConstant*std::cos(D * PI / 180.0);
}
double Rat::getNextY(){
		return Y + MoveConstant*std::sin(D * PI / 180.0);
}
double Rat::getdX(){
	return dX;
}
double Rat::getdY(){
	return dY;
}
void Rat::Scuttle(Maze & gMaze){
	bool x = gMaze.CheckCollision(getNextX()-1,Y-1,CollisionRadius);
	bool y = gMaze.CheckCollision(X-1,getNextY()-1,CollisionRadius);
	if ( x && y) {
		//std::cout<<" MOVE IN X DIRECTION "<<std::endl;
		X += MoveConstant*std::cos(D * PI / 180.0);
		Y += MoveConstant*std::sin(D * PI / 180.0);
	}
	if ( x && !y ) {
		//std::cout<<"Y"<<std::endl;
		X += MoveConstant*std::cos(D * PI / 180.0);
	}
	if ( !x && y ) {
		Y += MoveConstant*std::sin(D * PI / 180.0);
	}

}

void Rat::SpinLeft(){
	if (D > 360) {
		D -= 360;
	}
	D += SpinConstant;
}

void Rat::SpinRight(){
	if (D < -360) {
		D += 360;
	}
	D -= SpinConstant;
}
double Rat::getX(){
	return X;
}
double Rat::getY(){
	return Y;
}


void Rat::Draw(viewtype view){
	if (view == rat_view){
		return;
	}
	//draw collision circle
	if (false) {
		float x,y;
		glBegin(GL_LINES);
		glColor3f(0.0f,0.0f,0.0f);
		x = X +(float)CollisionRadius * cos(359 * PI/180.0f);
		y = Y +(float)CollisionRadius * sin(359 * PI/180.0f);
		for(int j = 0; j < 360; j++)
		{
			glVertex2f(x,y);
			x = X +(float)CollisionRadius * cos(j * PI/180.0f);
			y = Y +(float)CollisionRadius * sin(j * PI/180.0f);
			glVertex2f(x,y);
		}
		glEnd();
	}
	//draw mouse
	glColor3f(0.0f,0.0f,0.0f);
	glPushMatrix();
	//rotations have to happen at the origin, so translate it back after it's rotated
	glTranslated(X, Y, 0.0); // This happens first
	glRotated(D, 0, 0, 1);	   // This happens second
	glScaled(.5, .5, 1.0);

	DrawCircle( 0, 0, .4 ); //body
	DrawCircle( .4, 0, .1 ); //head

	glPopMatrix();
}