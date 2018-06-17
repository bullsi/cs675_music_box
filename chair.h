#include<vector>
#include<math.h>
#include<iostream>
#include<GL/glut.h>


#include "rectangle.h"

using namespace std;

class Chair
{
	public:
	GLfloat tx, ty, tz;
	GLfloat sx, sy, sz;
	GLfloat rx, ry, rz;	

	GLuint displayList;
	Rectangle *rectSides, *rectTop;
	GLuint texture[1];
	
	Chair();
	void draw();
};
