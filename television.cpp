#include "television.h"
#include "file.h"

Television :: Television()
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
	
	rect = new Rectangle(10,10,false);
	frontSize = 1; backSize = 0.5;
	length = 1;
	
	LoadGLTextures("patterns/pattern6.bmp", texture[0]); //Table Base
}

void Television :: draw()
{
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glColor3f(1,1,1);
	glPushMatrix();
		glTranslatef(tx, ty, tz);
		glRotatef(rx, 1, 0, 0);
		glRotatef(ry, 0, 1, 0);
		glRotatef(rz, 0, 0, 1);
		glScalef(sx, sy, sz);
		
		glTranslatef(0,0,-length/2);
		//Body
		glPushMatrix();
			glRotatef(45,0,0,1);
			GLUquadric *quadric = gluNewQuadric();
			gluQuadricTexture(quadric, true);
			gluCylinder(quadric, frontSize/1.414, backSize/1.414, length, 4, 4);
		glPopMatrix();
		//Back
		glPushMatrix();
			glTranslatef(0,0,1);
			glScalef(backSize,backSize,1);
			rect->draw();
		glPopMatrix();
		//Front
		glPushMatrix();
			//glTranslatef(0,0,0);
			glScalef(frontSize,frontSize,1);
			rect->draw();
		glPopMatrix();	
		glBindTexture(GL_TEXTURE_2D, 0);
		//Screen
		glPushMatrix();
			glColor3f(0,0,0);
			glTranslatef(0,0,-0.0001);
			glScalef(0.9*frontSize,0.9*frontSize,1);
			rect->draw();
		glPopMatrix();
		
	glPopMatrix();
	//~ glBindTexture(GL_TEXTURE_2D, 0);
}


