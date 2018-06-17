#include<vector>
#include<math.h>
#include<iostream>
#include<GL/glut.h>

#include "rectangle.h"
#include "light.h"

using namespace std;

class Lamp
{
	public:
	GLfloat tx, ty, tz;
	GLfloat sx, sy, sz;
	GLfloat rx, ry, rz;
	GLuint texture[2];
	Light* light;
	bool isEnabled;
	
	Lamp(GLuint lightIndex);
	void draw();
	void enable(bool enable);
};
