#include "lamp.h"
#include "file.h"

Lamp :: Lamp(GLuint lightIndex)
{
	tx = 0;
	ty = 0;
	tz = 0;
	sx = 1;
	sy = 1;
	sz = 1;
	rx = 0;
	ry = 0;
	rz = 0;

	isEnabled = true;
	light = new Light(lightIndex, 0, 0.9, 0);
	LoadGLTextures("patterns/pattern5.bmp", texture[0]); //Top
	LoadGLTextures("patterns/pattern7.bmp", texture[1]); //Middle and Bottom
}

void Lamp :: draw()
{
	GLUquadric *quadric = gluNewQuadric();
	gluQuadricTexture(quadric, true);
	
	glPushMatrix();
		glTranslatef(tx, ty, tz);
		glRotatef(rx, 1, 0, 0);
		glRotatef(ry, 0, 1, 0);
		glRotatef(rz, 0, 0, 1);
		glScalef(sx, sy, sz);
		
		glPushMatrix();
			glTranslatef(0, 0.9, 0);
			glScalef(0.05, 0.05, 0.05);
			light->setLight();
		glPopMatrix();
		
		glColor3f(1,1,1);
		glBindTexture(GL_TEXTURE_2D, texture[1]);
		glRotatef(-90,1.0,0.0,0.0);
		gluCylinder(quadric, 0.6, 0.05, 0.1, 8, 8);	//Bottom
		glTranslatef(0,0,0.1);
		gluCylinder(quadric, 0.05, 0.05, 0.9, 8,8);	//Middle
		glTranslatef(0,0,0.5);
		//~ gluQuadricTexture(quadric, true);	
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);	//Temporary arrangement to light the light itself
		gluCylinder(quadric, 0.5, 0.25, 0.4, 8, 8);	//Upper
		glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Lamp :: enable(bool enable)
{
	this->isEnabled = enable;
	light->enable(enable);
}
