#include "table.h"
#include "file.h"

Table :: Table()
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
	GLfloat vertices[] = 
	{
		-0.5f, -0.5f, -0.5f,	//0
		0.5f, -0.5f, -0.5f,		//1
		-0.5f, 0.5f, -0.5f,		//2
		0.5f, 0.5f, -0.5f,		//3	
		-0.5f, -0.5f, 0.5f,		//4
		0.5f, -0.5f, 0.5f,		//5
		-0.5f, 0.5f, 0.5f,		//6
		0.5f, 0.5f, 0.5f,		//7
	};
	GLfloat textCoords[] = {
		0,0,
		0,1,
		1,1,
		1,0
	};
	GLubyte indices[] = {0,2,3,1, 1,3,7,5, 5,7,6,4, 4,6,2,0, 0,1,5,4, 2,3,7,6};
	
	const GLfloat size_x = 1, size_y = 0.05, size_z = 0.5;
	const GLfloat leg_length = 0.5;
	displayList = glGenLists(1);
	
	rectSides = new Rectangle(10,2,false);
	rectTop = new Rectangle(10,10,false);
	
	GLUquadric *quadric = gluNewQuadric();
	gluQuadricTexture(quadric, true);
	
	glNewList(displayList, GL_COMPILE);
		//~ glPushMatrix();
			//~ glScalef(size_x, size_y, size_z);
			//~ glBegin(GL_QUADS);
			//~ for(int i=0; i<24; i++) {
				//~ //** glNormal3f(--)
				//~ glTexCoord2f(textCoords[(2*i)%8], textCoords[(2*i+1)%8]);
				//~ glVertex3f( vertices[3*indices[i]], vertices[3*indices[i]+1], vertices[3*indices[i]+2] );
			//~ }
			//~ glEnd();
		//~ glPopMatrix();
		
		glPushMatrix();
			glTranslatef(-0.8*size_x/2, 0, -0.8*size_z/2);
			glRotatef(90,1.0,0.0,0.0);
			glScalef(leg_length,leg_length,leg_length);
			gluCylinder(quadric, 0.04, 0.025, 1, 8, 20);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-0.8*size_x/2, 0, 0.8*size_z/2);
			glRotatef(90,1.0,0.0,0.0);
			glScalef(leg_length,leg_length,leg_length);
			gluCylinder(quadric, 0.04, 0.025, 1, 8, 20);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.8*size_x/2, 0, -0.8*size_z/2);
			glRotatef(90,1.0,0.0,0.0);
			glScalef(leg_length,leg_length,leg_length);
			gluCylinder(quadric, 0.04, 0.025, 1, 8, 20);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.8*size_x/2, 0, 0.8*size_z/2);
			glRotatef(90,1.0,0.0,0.0);
			glScalef(leg_length,leg_length,leg_length);
			gluCylinder(quadric, 0.04, 0.025, 1, 8, 20);
		glPopMatrix();
	glEndList();
	LoadGLTextures("patterns/pattern3.bmp", texture[0]); //Table Base
}

void Table :: draw()
{
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glColor3f(1,1,1);
	glPushMatrix();
		glTranslatef(tx, ty, tz);
		glRotatef(rx, 1, 0, 0);
		glRotatef(ry, 0, 1, 0);
		glRotatef(rz, 0, 0, 1);
		glScalef(sx, sy, sz);
		
		glTranslatef(0, 0.5+0.05, 0);
		glPushMatrix();
			glScalef(1,0.05,0.5);
			//Front
			glPushMatrix();
				glTranslatef(0,0,-0.5);
				rectSides->draw();
			glPopMatrix();
			//Right
			glPushMatrix();
				glRotatef(90,0,1,0);
				glTranslatef(0,0,-0.5);
				rectSides->draw();
			glPopMatrix();
			//~ //Left
			glPushMatrix();
				glRotatef(-90,0,1,0);
				glTranslatef(0,0,-0.5);
				rectSides->draw();
			glPopMatrix();
			//Back
			glPushMatrix();
				glRotatef(180,0,1,0);
				glTranslatef(0,0,-0.5);
				rectSides->draw();
			glPopMatrix();
			//Bottom
			glPushMatrix();
				glRotatef(-90,1,0,0);
				glTranslatef(0,0,-0.5);
				rectTop->draw();
			glPopMatrix();
			glColor3f(1,1,1);
			//Top
			glPushMatrix();
				glRotatef(90,1,0,0);
				glTranslatef(0,0,-0.5);
				rectTop->draw();
			glPopMatrix();
		glPopMatrix();
		
		glCallList(displayList);
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
	//glDeleteTextures(1, texture);
}
