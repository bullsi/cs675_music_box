#include<vector>
#include<math.h>
#include<iostream>
#include<GL/glut.h>


#include "rectangle.h"

using namespace std;

class Fridge
{
	public:
	GLfloat tx, ty, tz;
	GLfloat sx, sy, sz;
	GLfloat rx, ry, rz;	

	GLuint displayList;
	Rectangle *rect;
	GLuint texture[1];
	
	Fridge();
	void draw();
};
