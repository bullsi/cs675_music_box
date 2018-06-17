#include "chair.h"
#include "file.h"

Chair :: Chair()
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
	
	const GLfloat size_x = 1, size_y = 0.05, size_z = 1;
	const GLfloat leg_length = 1;
	
	rectSides = new Rectangle(15,2,false);
	rectTop = new Rectangle(15,10,false);
	
	displayList = glGenLists(1);
	GLUquadric *quadric = gluNewQuadric();
	gluQuadricTexture(quadric, true);
	glNewList(displayList, GL_COMPILE);
		glPushMatrix();
			glTranslatef(-0.9*size_x/2, 0, -0.9*size_z/2);
			glRotatef(90,1.0,0.0,0.0);
			glScalef(leg_length,leg_length,leg_length);
			gluCylinder(quadric, 0.04, 0.025, 1, 8, 20);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-0.9*size_x/2, 0, 0.9*size_z/2);
			glRotatef(90,1.0,0.0,0.0);
			glScalef(leg_length,leg_length,leg_length);
			gluCylinder(quadric, 0.04, 0.025, 1, 8, 20);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.9*size_x/2, 0, -0.9*size_z/2);
			glRotatef(90,1.0,0.0,0.0);
			glScalef(leg_length,leg_length,leg_length);
			gluCylinder(quadric, 0.04, 0.025, 1, 8, 20);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.9*size_x/2, 0, 0.9*size_z/2);
			glRotatef(90,1.0,0.0,0.0);
			glScalef(leg_length,leg_length,leg_length);
			gluCylinder(quadric, 0.04, 0.025, 1, 8, 20);
		glPopMatrix();
	glEndList();
	LoadGLTextures("patterns/pattern3.bmp", texture[0]); //Table Base
}

void Chair :: draw()
{
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glColor3f(1,1,1);
	glPushMatrix();
		glTranslatef(tx, ty, tz);
		glRotatef(rx, 1, 0, 0);
		glRotatef(ry, 0, 1, 0);
		glRotatef(rz, 0, 0, 1);
		glScalef(sx, sy, sz);
		
		// Seat
		glTranslatef(0, 1, 0);	//Leg length
		glPushMatrix();
			glTranslatef(0, 0.05/2, 0);
			glScalef(1,0.05,1);
			Rectangle :: drawCube(rectSides, rectTop, rectSides);
		glPopMatrix();
		// Back
		glPushMatrix();
			glTranslatef(0, 0.5 + 0.05/2, 0.5);
			glScalef(1,1,0.05);
			Rectangle :: drawCube(rectSides, rectSides, rectTop);
		glPopMatrix();
		// For legs
		glCallList(displayList);
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
}
