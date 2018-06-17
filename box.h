#include<vector>
#include<math.h>
#include<iostream>
#include<GL/glut.h>

#include "rectangle.h"

using namespace std;

class Box
{
	public:
	GLfloat tx, ty, tz;
	GLfloat sx, sy, sz;
	GLfloat rx, ry, rz;
	
	GLfloat angleOfCover;
	
	GLfloat vertices[36];
	GLfloat colors[36];	//Not sure to use it
	GLfloat textCoords[8];
	GLubyte indices[24];
	
	GLuint displayList;
	Rectangle* rect;
	GLuint texture[1];
	
	Box();
	void draw();
};
