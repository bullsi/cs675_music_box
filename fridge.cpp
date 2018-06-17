#include "fridge.h"
#include "file.h"

Fridge :: Fridge()
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
	
	const GLfloat size_x = 1, size_y = 2.5, size_z = 1;
	const GLfloat leg_length = 0.3;
	
	rect = new Rectangle(10,10,false);
	
	displayList = glGenLists(1);
	GLUquadric *quadric = gluNewQuadric();
	//No texture required
	//~ gluQuadricTexture(quadric, true);
	glNewList(displayList, GL_COMPILE);
		glColor3f(0.2,0.2,0.2);
		glPushMatrix();
			glTranslatef(-0.7*size_x/2, 0, -0.7*size_z/2);
			glRotatef(90,1.0,0.0,0.0);
			glScalef(leg_length,leg_length,leg_length);
			gluCylinder(quadric, 0.4, 0.15, 1, 8, 20);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-0.7*size_x/2, 0, 0.7*size_z/2);
			glRotatef(90,1.0,0.0,0.0);
			glScalef(leg_length,leg_length,leg_length);
			gluCylinder(quadric, 0.4, 0.15, 1, 8, 20);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.7*size_x/2, 0, -0.7*size_z/2);
			glRotatef(90,1.0,0.0,0.0);
			glScalef(leg_length,leg_length,leg_length);
			gluCylinder(quadric, 0.4, 0.15, 1, 8, 20);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.7*size_x/2, 0, 0.7*size_z/2);
			glRotatef(90,1.0,0.0,0.0);
			glScalef(leg_length,leg_length,leg_length);
			gluCylinder(quadric, 0.4, 0.15, 1, 8, 20);
		glPopMatrix();
	glEndList();
	LoadGLTextures("patterns/pattern14.bmp", texture[0]); //Table Base
}

void Fridge :: draw()
{
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glColor3f(1,1,1);
	glPushMatrix();
		glTranslatef(tx, ty, tz);
		glRotatef(rx, 1, 0, 0);
		glRotatef(ry, 0, 1, 0);
		glRotatef(rz, 0, 0, 1);
		glScalef(sx, sy, sz);
		
		// Body
		glTranslatef(0, 0.3, 0);	//Leg length
		glPushMatrix();
			glTranslatef(0, 2.5/2, 0);	//Half the height of the fridge
			glScalef(1,2.5,1);
			Rectangle :: drawCube(rect, rect, rect);
		glPopMatrix();
		// Between Body and Door
		glPushMatrix();
			glColor3f(0,0,0);
			glTranslatef(0, 2.5/2, -1.1/2);	//Half the height of the fridge
			glScalef(0.8,2.0,0.1);
			Rectangle :: drawCube(rect, rect, rect);
		glPopMatrix();
		// Door
		glPushMatrix();
			glColor3f(0.5,0.5,0.5);
			glTranslatef(0, 2.5/2, -(0.1 + 1.1/2));	//Half the height of the fridge
			glScalef(1,2.5,0.1);
			Rectangle :: drawCube(rect, rect, rect);
		glPopMatrix();
		// For legs
		glCallList(displayList);
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
}

