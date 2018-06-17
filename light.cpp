#include "light.h"

Light :: Light(int index, GLfloat tx, GLfloat ty, GLfloat tz)
{
	this->lightIndex = index;
	this->tx = tx;
	this->ty = ty;
	this->tz = tz;
	isEnabled = true;
	glEnable(index);
}

void Light :: setLight()
{
	spot = 100.0;
	shininess = 1;
	const_att = 0.01;
	linear_att = 0.02;
	quad_att = 0;
	
	glLightfv(lightIndex, GL_SPOT_EXPONENT, &spot);	//Effect not visible
	glLightfv(lightIndex, GL_CONSTANT_ATTENUATION, &const_att);
	glLightfv(lightIndex, GL_LINEAR_ATTENUATION, &linear_att);
	glLightfv(lightIndex, GL_QUADRATIC_ATTENUATION, &quad_att);
	

	GLfloat color[]   = {   1,1,1, 1.0 };
	//~ GLfloat light_diffuse[]   = {   1.0,   1.0,   1.0, 1.0 };
	//~ GLfloat light_specular[]  = {   1.0,   1.0,   1.0, 1.0 };
	glLightfv(lightIndex, GL_AMBIENT,  color);
    glLightfv(lightIndex, GL_DIFFUSE,  color);
    glLightfv(lightIndex, GL_SPECULAR, color);
	
	glPushMatrix();
		glTranslatef(tx, ty, tz);
		GLfloat light_position[] = { 0,0,0,1 };
		glLightfv(lightIndex, GL_POSITION, light_position);	
		glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);	//Temporary arrangement to light the light itself
		glColor3f(0.5,0.5,0);
		//~ glColor3f(1,1,1);
		gluSphere(gluNewQuadric(), 1, 8, 8);
		glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	glPopMatrix();
}

void Light :: enable(bool enable)
{
	this->isEnabled = enable;
	switch(enable)
	{
		case true: glEnable(lightIndex); break;
		case false: glDisable(lightIndex); break;
	}
}
