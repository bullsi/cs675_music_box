#include "rectangle.h"

Rectangle :: Rectangle(GLuint xDivs, GLuint yDivs, bool repeat)
{
	this->xDivs = xDivs;
	this->yDivs = yDivs;
	this->repeat = repeat;
	
	float xInterval = 1.0/xDivs;
	float yInterval = 1.0/yDivs;
	
	int index = 0;
	for(GLfloat y=-0.5; y<=0.5; y += yInterval)
	{
		for(GLfloat x=-0.5; x<=0.5; x += xInterval)
		{
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(0);
			textureCoords.push_back(x+0.5);
			textureCoords.push_back(y+0.5);
			
			if(y != -0.5 && x != -0.5)
			{
				/*
					6 7 8
					3 4 5
					0 1 2
					
					2 3 ....
					1 4 ....
				*/
				indices.push_back(index-(xDivs+1)-1);	//1
				indices.push_back(index-1);				//2
				indices.push_back(index);				//3				
				indices.push_back(index-(xDivs+1));		//4
			}
			index++;
		}
	}
}
void Rectangle :: draw()
{
	glVertexPointer (3, GL_FLOAT, 0, &vertices[0]);
	glTexCoordPointer(2, GL_FLOAT, 0, &textureCoords[0]);
	glNormal3f(0,0,-1);

	//~ glDrawElements(GL_QUADS, (xDivs)*(yDivs)*4, GL_UNSIGNED_BYTE, &indices[0]);
	glBegin(GL_QUADS);
	for(int j=0; j<indices.size(); j++)
	{
		int i = indices[j];
		if(repeat)
			glTexCoord2f( xDivs*textureCoords[2*i], yDivs*textureCoords[2*i+1] );
		else
			glTexCoord2f( textureCoords[2*i], textureCoords[2*i+1] );
		glVertex3f( vertices[3*i], vertices[3*i+1], vertices[3*i+2] );
	}
	glEnd();
	//cout << "END" << endl;
}

// Draws a cube from (-0.5,-0.5,-0.5) to (0.5,0.5,0.5)
void Rectangle :: drawCube(Rectangle* xRect, Rectangle* yRect, Rectangle* zRect)
{
	//Right
	glPushMatrix();
		glRotatef(90,0,1,0);
		glTranslatef(0,0,-0.5);
		xRect->draw();
	glPopMatrix();
	//Left
	glPushMatrix();
		glRotatef(-90,0,1,0);
		glTranslatef(0,0,-0.5);
		xRect->draw();
	glPopMatrix();
	
	//Bottom
	glPushMatrix();
		glRotatef(-90,1,0,0);
		glTranslatef(0,0,-0.5);
		yRect->draw();
	glPopMatrix();
	glColor3f(1,1,1);
	//Top
	glPushMatrix();
		glRotatef(90,1,0,0);
		glTranslatef(0,0,-0.5);
		yRect->draw();
	glPopMatrix();
	
	//Front
	glPushMatrix();
		glTranslatef(0,0,-0.5);
		zRect->draw();
	glPopMatrix();
	//Back
	glPushMatrix();
		glRotatef(180,0,1,0);
		glTranslatef(0,0,-0.5);
		zRect->draw();
	glPopMatrix();
}

