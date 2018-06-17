#include <GL/glut.h>
#include <vector>

using namespace std;

class point_3
{
	public:
	GLfloat x,y,z;

	point_3();
	point_3(GLfloat x, GLfloat y, GLfloat z);
	
	void draw();
	void setPoint(float x,float y, float z);
};


class Bezier
{
	public:
	vector<point_3*> controlPoints, tempPoints;

	Bezier();
	void bezierPoints();
	void drawControlSpheres();
	void addPoint(float x, float y, float z);
	point_3* nextPoint(float u);
};
