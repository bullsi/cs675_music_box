#include<vector>
#include<math.h>
#include<iostream>
#include<GL/glut.h>

#ifndef _LIGHT_H_
#define _LIGHT_H_

class Light
{
	int lightIndex;
	
	public:
		GLfloat spot;
		GLfloat shininess;
		GLfloat const_att;
		GLfloat linear_att;
		GLfloat quad_att;
		GLfloat tx, ty, tz;
		bool isEnabled;
		
		Light(int index, GLfloat tx, GLfloat ty, GLfloat tz);
		void setLight();
		void enable(bool enable);
};

#endif
