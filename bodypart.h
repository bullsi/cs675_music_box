#include<vector>
#include<math.h>
#include<iostream>
#include<GL/glut.h>

#define PI 3.14159265

using namespace std;

enum BodyPartEnum
{
	HEAD,
	NECK,
	TORSO1,	TORSO2,	TORSO3,
	HIPL, HIPR,
	THIGHL, THIGHR,
	KNEEL, KNEER,
	LEGL, LEGR,
	ANKLEL, ANKLER,
	FOOTL, FOOTR,
	SHOULDERL, SHOULDERR,
	UARML, UARMR,
	ELBOWL, ELBOWR,
	LARML, LARMR,
	WRISTL,WRISTR,
	HANDL, HANDR	
};

class BodyPart
{
	public:
	GLuint displayList;
	GLdouble baseRadius;
	GLdouble topRadius;
	GLdouble height;
	GLint slices;
	GLint stacks;
	//Three degree of rotation with respect to the parent (1 degree in case of elbows and knee given by rx)
	GLfloat rx, ry, rz;
	GLfloat tx, ty, tz;
	GLfloat sx, sy, sz;
	GLint degreeOfFreedom;
	
	GLuint texture;
	
	//public:	
	//Vertices and indices that represent this body part
	//vector<GLfloat> vertices;
	//vector<GLubyte> indices;
	//vector<GLubyte> indexTop;
	//vector<GLubyte> indexBottom;
	
	BodyPart *parent;
	vector<BodyPart*> children;	//Just declaring it gives runtime error
	//BodyPartEnum part;
	
	// Initialize a particular part depending upon the value of part
	BodyPart(BodyPartEnum part, BodyPart *parent);
	void draw();
	
	static vector<GLfloat> getCylinder(GLfloat bottomRadius, GLfloat topRadius, GLfloat height, int slices, int stacks, vector<GLubyte> &indices);
};


