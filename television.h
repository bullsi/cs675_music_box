#include<vector>
#include<math.h>
#include<iostream>
#include<GL/glut.h>


#include "rectangle.h"

using namespace std;

class Television
{
	public:
	GLfloat tx, ty, tz;
	GLfloat sx, sy, sz;
	GLfloat rx, ry, rz;	

	GLfloat backSize, frontSize;
	GLfloat length;
	
	Rectangle *rect;
	GLuint texture[1];
	
	Television();
	void draw();
};
