#include "box.h"
#include "file.h"

Box :: Box()
{
	angleOfCover = 0;
	tx = 0;
	ty = 0;
	tz = 0;
	sx = 20;
	sy = 5;
	sz = 10;
	rx = 0;
	ry = 0;
	rz = 0;
	GLfloat vertices_ [] = 
	{
		-0.5f, -0.5f, -0.5f,	//0
		0.5f, -0.5f, -0.5f,		//1
		-0.5f, 0.5f, -0.5f,		//2
		0.5f, 0.5f, -0.5f,		//3	
		-0.5f, -0.5f, 0.5f,		//4
		0.5f, -0.5f, 0.5f,		//5
		-0.5f, 0.5f, 0.5f,		//6
		0.5f, 0.5f, 0.5f,		//7
		//Repeating the vertices at the top to open it
		-0.5f, 0.5f, -0.5f,		//8
		0.5f, 0.5f, -0.5f,		//9
		-0.5f, 0.5f, 0.5f,		//10
		0.5f, 0.5f, 0.5f,		//11
	};
	GLubyte indices_[] = {0,2,3,1, 1,3,7,5, 5,7,6,4, 4,6,2,0, 0,1,5,4, 8,9,11,10};
	GLfloat textCoords_[] = {
		0,0,
		0,1,
		1,1,
		1,0
	};
	for(int i=0; i<36; i++)
		vertices[i] = vertices_[i];
	for(int i=0; i<24; i++)
		indices[i] = indices_[i];
	for(int i=0; i<8; i++)
		textCoords[i] = textCoords_[i];

	rect = new Rectangle(10,10, false);
	glNewList(displayList, GL_COMPILE);
		glPushMatrix();
			//Front
			glTranslatef(0,0,-0.5);
			//rect->draw();
			//Right
			//~ glRotatef(90,0,1,0);
			//~ rect->draw();
			//~ //Back
			//~ glRotatef(90,0,1,0);
			//~ rect->draw();
			//~ //Left
			//~ glRotatef(90,0,1,0);
			//~ rect->draw();
			//~ //Bottom
			//~ glRotatef(-90,0,0,1);
			//~ rect->draw();
		glPopMatrix();
	glEndList();
	
	LoadGLTextures("patterns/pattern4.bmp", texture[0]);
}
void Box :: draw()
{
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glPushMatrix();
		glTranslatef(tx, ty, tz);
		glRotatef(rx, 1, 0, 0);
		glRotatef(ry, 0, 1, 0);
		glRotatef(rz, 0, 0, 1);
		glScalef(sx, sy, sz);
		glTranslatef(0,0.5,0);
		glColor3f(1,0,0);
		// Base and Walls
		//~ glCallList(displayList);
		//Front
		glPushMatrix();
			glTranslatef(0,0,-0.5);
			rect->draw();
		glPopMatrix();
		//Right
		glPushMatrix();
			glRotatef(90,0,1,0);
			glTranslatef(0,0,-0.5);
			rect->draw();
		glPopMatrix();
		//Left
		glPushMatrix();
			glRotatef(-90,0,1,0);
			glTranslatef(0,0,-0.5);
			rect->draw();
		glPopMatrix();
		//Back
		glPushMatrix();
			glRotatef(180,0,1,0);
			glTranslatef(0,0,-0.5);
			rect->draw();
		glPopMatrix();
		//Bottom
		glPushMatrix();
			glRotatef(-90,1,0,0);
			glTranslatef(0,0,-0.5);
			rect->draw();
		glPopMatrix();
			
		glColor3f(1,0,0);
		//Top
		glPushMatrix();
			glTranslatef(0.0f,0.5f,0.5f);
			glRotatef(angleOfCover, 1,0,0);
			glTranslatef(0.0f,-0.5f,-0.5f);
			
			glRotatef(90,1,0,0);
			glTranslatef(0,0,-0.5);
			rect->draw();
		glPopMatrix();
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);	//Unbind
}


