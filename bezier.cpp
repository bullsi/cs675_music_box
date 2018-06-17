#include "bezier.h"

point_3 :: point_3(){ }
point_3 :: point_3(GLfloat x, GLfloat y, GLfloat z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
	
//This method plots the the given point on the screen. This is the most elementary method in this where all lines and polygons are drawn using point class' draw method.
void point_3 :: draw()
{
	//glBegin(GL_POINT);
		glVertex3f(x, y, z);
	//glEnd();
}
void point_3 :: setPoint(float x,float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}


Bezier :: Bezier(){ }
void Bezier :: bezierPoints()
{
	controlPoints.clear();
	//controlPoints.push_back(new point_3(0,30,-65));
	//controlPoints.push_back(new point_3(0,20,-60));
	//controlPoints.push_back(new point_3(0,10,-70));
	//controlPoints.push_back(new point_3(30,40,0));
	//controlPoints.push_back(new point_3(30,20,0));
	//controlPoints.push_back(new point_3(-30,0,0));
}
void Bezier :: drawControlSpheres()
{
	for (int i=0; i<controlPoints.size(); i++)
	{
		glPushMatrix();
			glTranslatef(controlPoints[i]->x , controlPoints[i]->y, controlPoints[i]->z);
			gluSphere(gluNewQuadric(), 0.5, 20, 20);
		glPopMatrix();
	}
}
void Bezier :: addPoint(float x, float y, float z)
{
	controlPoints.push_back(new point_3(x,y,z));
}
point_3* Bezier :: nextPoint(float u)
{
	tempPoints.clear();
	for (int i=0; i<controlPoints.size(); i++)
	{
		tempPoints.push_back(new point_3(controlPoints[i]->x, controlPoints[i]->y, controlPoints[i]->z));
		//cout << "11" <<endl;
	}
	int numPoints = controlPoints.size();
	for (int k=1; k<numPoints; k++)
	{
		for(int i=0; i<(numPoints - k); i++)
		{
			//cout<<"a" <<endl;
			tempPoints[i]->x = tempPoints[i]->x * (1-u) + tempPoints[i+1]->x * u ;
			tempPoints[i]->y = tempPoints[i]->y * (1-u) + tempPoints[i+1]->y * u ;
			tempPoints[i]->z = tempPoints[i]->z * (1-u) + tempPoints[i+1]->z * u ;
		}
	}
	//cout << "in nextpoint" << tempPoints[0] ->x <<endl;
	return tempPoints[0];
}
