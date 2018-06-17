#include "room.h"
#include "file.h"

Room :: Room()
{
	tx = 0;
	ty = 0;
	tz = -100;
	sx = 200;
	sy = 60;
	sz = 400;
	rx = 0;
	ry = 0;
	rz = 0;
	doorAngle = 40;
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
	GLfloat colors[] = //Not sure to use it
	{
		0,0,0, 
		0,0,1,
		0,1,0,
		0,1,1,
		1,0,0, 
		1,0,1,
		1,1,0,
		1,1,1
	};
	GLfloat textCoords[] = {
		0,0,
		0,1,
		1,1,
		1,0
	};
	
	GLubyte indices[] = {0,2,3,1, 1,3,7,5, 5,7,6,4, 4,6,2,0, 0,1,5,4, 2,3,7,6}; //{wall,wall,wall,wall,floor,ceiling}
	for(int i=0; i<36; i++)
		this->vertices[i] = vertices[i];
	for(int i=0; i<36; i++)
		this->colors[i] = colors[i];
	for(int i=0; i<24; i++)
		this->indices[i] = indices[i];
	for(int i=0; i<8; i++)
		this->textCoords[i] = textCoords[i];
	rect = new Rectangle(15, 5, true);
	//Loading textures
	LoadGLTextures("patterns/pattern9.bmp", texture[0]); //Wall
	LoadGLTextures("patterns/pattern9.bmp", texture[1]); //Floor
	LoadGLTextures("patterns/pattern9.bmp", texture[2]); //Ceiling
}

void Room :: draw()
{	
	glPushMatrix();
		glTranslatef(tx, ty, tz);
		glRotatef(rx, 1, 0, 0);
		glRotatef(ry, 0, 1, 0);
		glRotatef(rz, 0, 0, 1);
		glScalef(sx, sy, sz);
		glTranslatef(0,0.5,0);
		
		glColor3f(1,1,1);
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		//Back
		glPushMatrix();
			glTranslatef(0,0,0.5);
			rect->draw();
		glPopMatrix();
		//Left
		glPushMatrix();
			glRotatef(90,0,1,0);
			glTranslatef(0,0,0.5);
			rect->draw();
		glPopMatrix();
		//Right
		glPushMatrix();
			glRotatef(-90,0,1,0);
			glTranslatef(0,0,0.5);
			rect->draw();
		glPopMatrix();
		//Front
			//Left part
		glPushMatrix();
			glRotatef(180,0,1,0);
			glTranslatef(-0.27,0,0.5);
			glScalef(0.46, 1, 1);
			rect->draw();
		glPopMatrix();
			//Right part
		glPushMatrix();
			glRotatef(180,0,1,0);
			glTranslatef(0.27,0,0.5);
			glScalef(0.46, 1, 1);
			rect->draw();
		glPopMatrix();
			//Center top part
		glPushMatrix();
			glRotatef(180,0,1,0);
			glTranslatef(0,0.2,0.5);
			glScalef(0.08,0.6,1);
			rect->draw();
		glPopMatrix();
			//Door
		glPushMatrix();
			glColor3f(0,0,0);
			glRotatef(180,0,1,0);
			glTranslatef(-0.04,-0.3,0.5);
			glRotatef(doorAngle, 0,1,0);
			glTranslatef(0.04,0,0);
			glScalef(0.08,0.4,1);
			rect->draw();
		glPopMatrix();
		//Top
		glColor3f(1,1,1);
		glBindTexture(GL_TEXTURE_2D, texture[1]);
		glPushMatrix();
			glRotatef(90,1,0,0);
			glTranslatef(0,0,0.5);
			rect->draw();
		glPopMatrix();
		//Bottom
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glPushMatrix();
			glRotatef(-90,1,0,0);
			glTranslatef(0,0,0.5);
			rect->draw();
		glPopMatrix();
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
}
