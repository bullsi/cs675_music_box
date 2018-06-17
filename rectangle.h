#include<vector>
#include<math.h>
#include<iostream>
#include<GL/glut.h>

#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_

using namespace std;

// Creates a rectangle from (-0.5, -0.5, 0) to (0.5, 0.5, 0) whose normal is towards negative z-axis
class Rectangle
{
	int xDivs;
	int yDivs;
	vector<GLfloat> vertices;
	vector<GLfloat> textureCoords;
	vector<GLubyte> indices;
	bool repeat;
	
	public:
		Rectangle(GLuint xDivs, GLuint yDivs, bool repeat);
		void draw();
		static void drawCube(Rectangle* xRect, Rectangle* yRect, Rectangle* zRect);
};

#endif
