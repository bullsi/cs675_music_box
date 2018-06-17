#include<vector>
#include<math.h>
#include<iostream>
#include<GL/glut.h>

#include "rectangle.h"

using namespace std;

class Room
{
	public:
	GLfloat tx, ty, tz;
	GLfloat sx, sy, sz;
	GLfloat rx, ry, rz;	

	GLuint displayList;
	
	GLfloat vertices[36];
	GLfloat colors[36];	//Not sure to use it
	GLfloat textCoords[8];
	GLubyte indices[24];
	
	Rectangle* rect;
	GLfloat doorAngle;
	GLuint texture[3];	//0: walls;	1: floor;	2: ceiling
	
	Room();
	void draw();
};
