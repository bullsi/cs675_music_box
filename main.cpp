#include<iostream>
#include<string>
#include<fstream>
#include<GL/glut.h>

#include "body.h"
#include "box.h"
#include "table.h"
#include "chair.h"
#include "fridge.h"
#include "television.h"
#include "lamp.h"
#include "room.h"
#include "light.h"
#include "file.h"
#include "bezier.h"

using namespace std;

int width = 600;
int height = 600;

Body* body;
Box* box;
Table* table;
Table* tvtable;
Chair* chair;
Chair* chair1;
Fridge* fridge;
Television* tv;
Room* room;
Lamp* lamp;
Bezier* bezier;
Light* wallLight;

GLuint tex2D;

enum sideEnum {LEFT, RIGHT};
enum directionEnum {PLUS, MINUS};
sideEnum side = LEFT;
directionEnum direction = PLUS;
int incr = 5;

float x = -15;
float yy = 0;

float lx=0, ly=10, lz=-100;
bool animateCamera = false;
float bezierU = 0;

vector< vector<float> > framesToInterpolate;
bool isAnimating = false;
int frameNumber;
int timeBetweenFrames = 60;	//Time in ms
int framesBetweenKeys = 10;


float interpolate(float currValue, float nextValue, float weightageToNextFrame)
{
	return currValue*(1-weightageToNextFrame) + nextValue*(weightageToNextFrame);
}
void assignNextFrameValues(int frameNumber)
{
	// KeyIndex is the index of the key to refer to
	int keyIndex = frameNumber / framesBetweenKeys;
	float weightageToNextFrame = (frameNumber % framesBetweenKeys) / (float)framesBetweenKeys;
	
	cout << keyIndex << "  " << weightageToNextFrame << endl;
	if(keyIndex+2>= framesToInterpolate.size())
	{
		cout << "***END***"<<endl;
		isAnimating = false;
		return;
	}
		
	// Assigning values to different things of the world
	body->torso1->rx = interpolate(framesToInterpolate[keyIndex][0], framesToInterpolate[keyIndex+1][0], weightageToNextFrame);
	body->torso1->ry = interpolate(framesToInterpolate[keyIndex][1], framesToInterpolate[keyIndex+1][1], weightageToNextFrame);
	body->torso1->rz = interpolate(framesToInterpolate[keyIndex][2], framesToInterpolate[keyIndex+1][2], weightageToNextFrame);
	body->torso2->rx = interpolate(framesToInterpolate[keyIndex][3], framesToInterpolate[keyIndex+1][3], weightageToNextFrame);
	body->torso2->ry = interpolate(framesToInterpolate[keyIndex][4], framesToInterpolate[keyIndex+1][4], weightageToNextFrame);
	body->torso2->rz = interpolate(framesToInterpolate[keyIndex][5], framesToInterpolate[keyIndex+1][5], weightageToNextFrame);
	body->torso3->rx = interpolate(framesToInterpolate[keyIndex][6], framesToInterpolate[keyIndex+1][6], weightageToNextFrame);
	body->torso3->ry = interpolate(framesToInterpolate[keyIndex][7], framesToInterpolate[keyIndex+1][7], weightageToNextFrame);
	body->torso3->rz = interpolate(framesToInterpolate[keyIndex][8], framesToInterpolate[keyIndex+1][8], weightageToNextFrame);
	
	body->neck->rx = interpolate(framesToInterpolate[keyIndex][9], framesToInterpolate[keyIndex+1][9], weightageToNextFrame);
	body->neck->ry = interpolate(framesToInterpolate[keyIndex][10], framesToInterpolate[keyIndex+1][10], weightageToNextFrame);
	body->neck->rz = interpolate(framesToInterpolate[keyIndex][11], framesToInterpolate[keyIndex+1][11], weightageToNextFrame);
	body->head->rx = interpolate(framesToInterpolate[keyIndex][12], framesToInterpolate[keyIndex+1][12], weightageToNextFrame);
	body->head->ry = interpolate(framesToInterpolate[keyIndex][13], framesToInterpolate[keyIndex+1][13], weightageToNextFrame);
	body->head->rz = interpolate(framesToInterpolate[keyIndex][14], framesToInterpolate[keyIndex+1][14], weightageToNextFrame);
	body->hipl->rx = interpolate(framesToInterpolate[keyIndex][15], framesToInterpolate[keyIndex+1][15], weightageToNextFrame);
	body->hipl->ry = interpolate(framesToInterpolate[keyIndex][16], framesToInterpolate[keyIndex+1][16], weightageToNextFrame);
	body->hipl->rz = interpolate(framesToInterpolate[keyIndex][17], framesToInterpolate[keyIndex+1][17], weightageToNextFrame);
	body->thighl->rx = interpolate(framesToInterpolate[keyIndex][18], framesToInterpolate[keyIndex+1][18], weightageToNextFrame);
	body->thighl->ry = interpolate(framesToInterpolate[keyIndex][19], framesToInterpolate[keyIndex+1][19], weightageToNextFrame);
	body->thighl->rz = interpolate(framesToInterpolate[keyIndex][20], framesToInterpolate[keyIndex+1][20], weightageToNextFrame);
	body->legl->rx = interpolate(framesToInterpolate[keyIndex][21], framesToInterpolate[keyIndex+1][21], weightageToNextFrame);
	body->legl->ry = interpolate(framesToInterpolate[keyIndex][22], framesToInterpolate[keyIndex+1][22], weightageToNextFrame);
	body->legl->rz = interpolate(framesToInterpolate[keyIndex][23], framesToInterpolate[keyIndex+1][23], weightageToNextFrame);
	body->anklel->rx = interpolate(framesToInterpolate[keyIndex][24], framesToInterpolate[keyIndex+1][24], weightageToNextFrame);
	body->anklel->ry = interpolate(framesToInterpolate[keyIndex][25], framesToInterpolate[keyIndex+1][25], weightageToNextFrame);
	body->anklel->rz = interpolate(framesToInterpolate[keyIndex][26], framesToInterpolate[keyIndex+1][26], weightageToNextFrame);
	body->hipr->rx = interpolate(framesToInterpolate[keyIndex][27], framesToInterpolate[keyIndex+1][27], weightageToNextFrame);
	body->hipr->ry = interpolate(framesToInterpolate[keyIndex][28], framesToInterpolate[keyIndex+1][28], weightageToNextFrame);
	body->hipr->rz = interpolate(framesToInterpolate[keyIndex][29], framesToInterpolate[keyIndex+1][29], weightageToNextFrame);
	body->footr->rx = interpolate(framesToInterpolate[keyIndex][30], framesToInterpolate[keyIndex+1][30], weightageToNextFrame);
	body->footr->ry = interpolate(framesToInterpolate[keyIndex][31], framesToInterpolate[keyIndex+1][31], weightageToNextFrame);
	body->footr->rz = interpolate(framesToInterpolate[keyIndex][32], framesToInterpolate[keyIndex+1][32], weightageToNextFrame);

	body->ankler->rx = interpolate(framesToInterpolate[keyIndex][33], framesToInterpolate[keyIndex+1][33], weightageToNextFrame);
	body->ankler->ry = interpolate(framesToInterpolate[keyIndex][34], framesToInterpolate[keyIndex+1][34], weightageToNextFrame);
	body->ankler->rz = interpolate(framesToInterpolate[keyIndex][35], framesToInterpolate[keyIndex+1][35], weightageToNextFrame);
	body->legr->rx = interpolate(framesToInterpolate[keyIndex][36], framesToInterpolate[keyIndex+1][36], weightageToNextFrame);
	body->legr->ry = interpolate(framesToInterpolate[keyIndex][37], framesToInterpolate[keyIndex+1][37], weightageToNextFrame);
	body->legr->rz = interpolate(framesToInterpolate[keyIndex][38], framesToInterpolate[keyIndex+1][38], weightageToNextFrame);
	body->kneer->rx = interpolate(framesToInterpolate[keyIndex][39], framesToInterpolate[keyIndex+1][39], weightageToNextFrame);
	body->kneer->ry = interpolate(framesToInterpolate[keyIndex][40], framesToInterpolate[keyIndex+1][40], weightageToNextFrame);
	body->kneer->rz = interpolate(framesToInterpolate[keyIndex][41], framesToInterpolate[keyIndex+1][41], weightageToNextFrame);
	body->thighr->rx = interpolate(framesToInterpolate[keyIndex][42], framesToInterpolate[keyIndex+1][42], weightageToNextFrame);
	body->thighr->ry = interpolate(framesToInterpolate[keyIndex][43], framesToInterpolate[keyIndex+1][43], weightageToNextFrame);
	body->thighr->rz = interpolate(framesToInterpolate[keyIndex][44], framesToInterpolate[keyIndex+1][44], weightageToNextFrame);
	body->shoulderl->rx = interpolate(framesToInterpolate[keyIndex][45], framesToInterpolate[keyIndex+1][45], weightageToNextFrame);
	body->shoulderl->ry = interpolate(framesToInterpolate[keyIndex][46], framesToInterpolate[keyIndex+1][46], weightageToNextFrame);
	body->shoulderl->rz = interpolate(framesToInterpolate[keyIndex][47], framesToInterpolate[keyIndex+1][47], weightageToNextFrame);
	body->uarml->rx = interpolate(framesToInterpolate[keyIndex][48], framesToInterpolate[keyIndex+1][48], weightageToNextFrame);
	body->uarml->ry = interpolate(framesToInterpolate[keyIndex][49], framesToInterpolate[keyIndex+1][49], weightageToNextFrame);
	body->uarml->rz = interpolate(framesToInterpolate[keyIndex][50], framesToInterpolate[keyIndex+1][50], weightageToNextFrame);
		
	body->elbowl->rx = interpolate(framesToInterpolate[keyIndex][51], framesToInterpolate[keyIndex+1][51], weightageToNextFrame);
	body->elbowl->ry = interpolate(framesToInterpolate[keyIndex][52], framesToInterpolate[keyIndex+1][52], weightageToNextFrame);
	body->elbowl->rz = interpolate(framesToInterpolate[keyIndex][53], framesToInterpolate[keyIndex+1][53], weightageToNextFrame);
	body->larml->rx = interpolate(framesToInterpolate[keyIndex][54], framesToInterpolate[keyIndex+1][54], weightageToNextFrame);
	body->larml->ry = interpolate(framesToInterpolate[keyIndex][55], framesToInterpolate[keyIndex+1][55], weightageToNextFrame);
	body->larml->rz = interpolate(framesToInterpolate[keyIndex][56], framesToInterpolate[keyIndex+1][56], weightageToNextFrame);
	body->handl->rx = interpolate(framesToInterpolate[keyIndex][57], framesToInterpolate[keyIndex+1][57], weightageToNextFrame);
	body->handl->ry = interpolate(framesToInterpolate[keyIndex][58], framesToInterpolate[keyIndex+1][58], weightageToNextFrame);
	body->handl->rz = interpolate(framesToInterpolate[keyIndex][59], framesToInterpolate[keyIndex+1][59], weightageToNextFrame);
	body->shoulderr->rx = interpolate(framesToInterpolate[keyIndex][60], framesToInterpolate[keyIndex+1][60], weightageToNextFrame);
	body->shoulderr->ry = interpolate(framesToInterpolate[keyIndex][61], framesToInterpolate[keyIndex+1][61], weightageToNextFrame);
	body->shoulderr->rz = interpolate(framesToInterpolate[keyIndex][62], framesToInterpolate[keyIndex+1][62], weightageToNextFrame);
	body->uarmr->rx = interpolate(framesToInterpolate[keyIndex][63], framesToInterpolate[keyIndex+1][63], weightageToNextFrame);
	body->uarmr->ry = interpolate(framesToInterpolate[keyIndex][64], framesToInterpolate[keyIndex+1][64], weightageToNextFrame);
	body->uarmr->rz = interpolate(framesToInterpolate[keyIndex][65], framesToInterpolate[keyIndex+1][65], weightageToNextFrame);
	body->elbowr->rx = interpolate(framesToInterpolate[keyIndex][66], framesToInterpolate[keyIndex+1][66], weightageToNextFrame);
	body->elbowr->ry = interpolate(framesToInterpolate[keyIndex][67], framesToInterpolate[keyIndex+1][67], weightageToNextFrame);
	body->elbowr->rz = interpolate(framesToInterpolate[keyIndex][68], framesToInterpolate[keyIndex+1][68], weightageToNextFrame);
	
	body->larmr->rx = interpolate(framesToInterpolate[keyIndex][69], framesToInterpolate[keyIndex+1][69], weightageToNextFrame);
	body->larmr->ry = interpolate(framesToInterpolate[keyIndex][70], framesToInterpolate[keyIndex+1][70], weightageToNextFrame);
	body->larmr->rz = interpolate(framesToInterpolate[keyIndex][71], framesToInterpolate[keyIndex+1][71], weightageToNextFrame);
	body->wristr->rx = interpolate(framesToInterpolate[keyIndex][72], framesToInterpolate[keyIndex+1][72], weightageToNextFrame);
	body->wristr->ry = interpolate(framesToInterpolate[keyIndex][73], framesToInterpolate[keyIndex+1][73], weightageToNextFrame);
	body->wristr->rz = interpolate(framesToInterpolate[keyIndex][74], framesToInterpolate[keyIndex+1][74], weightageToNextFrame);
	body->handr->rx = interpolate(framesToInterpolate[keyIndex][75], framesToInterpolate[keyIndex+1][75], weightageToNextFrame);
	body->handr->ry = interpolate(framesToInterpolate[keyIndex][76], framesToInterpolate[keyIndex+1][76], weightageToNextFrame);
	body->handr->rz = interpolate(framesToInterpolate[keyIndex][77], framesToInterpolate[keyIndex+1][77], weightageToNextFrame);
	
	body->tx = interpolate(framesToInterpolate[keyIndex][78], framesToInterpolate[keyIndex+1][78], weightageToNextFrame);
	body->ty = interpolate(framesToInterpolate[keyIndex][79], framesToInterpolate[keyIndex+1][79], weightageToNextFrame);
	body->tz = interpolate(framesToInterpolate[keyIndex][80], framesToInterpolate[keyIndex+1][80], weightageToNextFrame);
	
	box->angleOfCover = interpolate(framesToInterpolate[keyIndex][81], framesToInterpolate[keyIndex+1][81], weightageToNextFrame);
	room->doorAngle = interpolate(framesToInterpolate[keyIndex][82], framesToInterpolate[keyIndex+1][82], weightageToNextFrame);

	lamp->enable(framesToInterpolate[keyIndex][83] == 1? true: false);
	wallLight->enable(framesToInterpolate[keyIndex][84] == 1? true: false);
}


vector<string> keyFrames;

vector<float> worldToFrames()
{
	// 85 values
	
	vector<float> a;
	a.push_back(body->torso1->rx);
	a.push_back(body->torso1->ry);
	a.push_back(body->torso1->rz);
	a.push_back(body->torso2->rx);
	a.push_back(body->torso2->ry);
	a.push_back(body->torso2->rz);
	a.push_back(body->torso3->rx);
	a.push_back(body->torso3->ry);
	a.push_back(body->torso3->rz);
	a.push_back(body->neck->rx);
	a.push_back(body->neck->ry);
	a.push_back(body->neck->rz);
	
	a.push_back(body->head->rx);
	a.push_back(body->head->ry);
	a.push_back(body->head->rz);
	a.push_back(body->hipl->rx);
	a.push_back(body->hipl->ry);
	a.push_back(body->hipl->rz);
	a.push_back(body->thighl->rx);
	a.push_back(body->thighl->ry);
	a.push_back(body->thighl->rz);
	a.push_back(body->legl->rx);
	a.push_back(body->legl->ry);
	a.push_back(body->legl->rz);
	a.push_back(body->anklel->rx);
	a.push_back(body->anklel->ry);
	a.push_back(body->anklel->rz);
	a.push_back(body->hipr->rx);
	a.push_back(body->hipr->ry);
	a.push_back(body->hipr->rz);
	
	a.push_back(body->footr->rx);
	a.push_back(body->footr->ry);
	a.push_back(body->footr->rz);
	a.push_back(body->ankler->rx);
	a.push_back(body->ankler->ry);
	a.push_back(body->ankler->rz);
	a.push_back(body->legr->rx);
	a.push_back(body->legr->ry);
	a.push_back(body->legr->rz);
	a.push_back(body->kneer->rx);
	a.push_back(body->kneer->ry);
	a.push_back(body->kneer->rz);
	a.push_back(body->thighr->rx);
	a.push_back(body->thighr->ry);
	a.push_back(body->thighr->rz);
	a.push_back(body->shoulderl->rx);
	a.push_back(body->shoulderl->ry);
	a.push_back(body->shoulderl->rz);
	
	a.push_back(body->uarml->rx);
	a.push_back(body->uarml->ry);
	a.push_back(body->uarml->rz);
	a.push_back(body->elbowl->rx);
	a.push_back(body->elbowl->ry);
	a.push_back(body->elbowl->rz);
	a.push_back(body->larml->rx);
	a.push_back(body->larml->ry);
	a.push_back(body->larml->rz);
	a.push_back(body->handl->rx);
	a.push_back(body->handl->ry);
	a.push_back(body->handl->rz);
	a.push_back(body->shoulderr->rx);
	a.push_back(body->shoulderr->ry);
	a.push_back(body->shoulderr->rz);
	a.push_back(body->uarmr->rx);
	a.push_back(body->uarmr->ry);
	a.push_back(body->uarmr->rz);
	
	a.push_back(body->elbowr->rx);
	a.push_back(body->elbowr->ry);
	a.push_back(body->elbowr->rz);
	a.push_back(body->larmr->rx);
	a.push_back(body->larmr->ry);
	a.push_back(body->larmr->rz);
	a.push_back(body->wristr->rx);
	a.push_back(body->wristr->ry);
	a.push_back(body->wristr->rz);
	a.push_back(body->handr->rx);
	a.push_back(body->handr->ry);
	a.push_back(body->handr->rz);
	a.push_back(body->tx);
	a.push_back(body->ty);
	a.push_back(body->tz);
	
	a.push_back(box->angleOfCover);
	a.push_back(room->doorAngle);
	a.push_back(lamp->isEnabled?1:0);
	a.push_back(wallLight->isEnabled?1:0);

	return a;
}


void writeFramesToFile()
{
	ofstream out("keyframes.txt");
	if(out.is_open())
	{
		for(int i=0; i<framesToInterpolate.size(); i++)
		{
			vector<float> a = framesToInterpolate[i];
			for(int j=0; j<a.size(); j++)
			{
				out << a[j] << " ";
			}
			out << endl;
		}
		out.close();
	}
	else
		cout << "File Error" << endl;
}

void readingFramesFromFile()
{
	framesToInterpolate.clear();
	ifstream in("keyframes.txt");
	string str ="";
	if( in.is_open() )
	{
		int lines = 0;
		int counter = 0;
		vector<float> a;
		framesToInterpolate.push_back(*(new vector<float>));
		while(in)
		{
			GLfloat value;
			in >> value;
			framesToInterpolate[lines].push_back(value);
			counter++;
			if(counter == 85)
			{
				lines++;
				framesToInterpolate.push_back(*(new vector<float>));
				counter = 0;
			}
		}
		//framesToInterpolate.pop_back();
		
		//~ for(int i=0; i<framesToInterpolate.size(); i++)
		//~ {
			//~ vector<float> a = framesToInterpolate[i];
			//~ for(int j=0; j<a.size(); j++)
			//~ {
				//~ cout << a[j] << " ";
			//~ }
			//~ cout << endl;
		//~ }
		
		in.close();
	}
	else
		cout << "File Error" << endl;
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,-(GLfloat)width/(GLfloat)height, 5, 10000);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//cout << lx << ly << lz << "ll" << endl;
	gluLookAt(lx,ly,lz, 0,0,1, 0,1,0);
	
	// ***** TO VARY CAMERA POSITION ****
	//glRotatef(-15,1.0,0.0,0.0);
	//glRotatef(yy,0.0,1.0,0.0);
	//glTranslatef(3,-30,0);
	
	// LIGHTING (not needed now)
	//~ GLfloat ambient[] = { 1,0,0, 1 };
	//~ GLfloat diffuse[] = { 0,1,0, 1 };
	//~ GLfloat spot[] = {100};
	//~ GLfloat shininess[] = {1};
	//~ GLfloat const_att[] = {0.05};
	//~ GLfloat linear_att[] = {0.05};
	//~ GLfloat quad_att[] = {0};
	//~ glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	//~ glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	//~ glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess );
	//~ glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);	
	//~ glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	//~ glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	//~ glLightfv(GL_LIGHT0, GL_SPOT_EXPONENT, spot);
	//~ glLightfv(GL_LIGHT0, GL_CONSTANT_ATTENUATION, const_att);
	//~ glLightfv(GL_LIGHT0, GL_LINEAR_ATTENUATION, linear_att);
	//~ glLightfv(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, quad_att);
	//~ glPushMatrix();
		//~ glTranslatef(x, 14, -7);
		//~ GLfloat light_position[] = { 0,0,0,1 };
		//~ glLightfv(GL_LIGHT0, GL_POSITION, light_position);	
		//~ gluSphere(gluNewQuadric(), 1, 8, 8);
	//~ glPopMatrix();
	
	wallLight->setLight();
	//~ wallLight->enable(false);
	//~ wallLight->tx = x;
	
	glBindTexture(GL_TEXTURE_2D, tex2D);
	glColor3f(1,1,1);	
	glPushMatrix();
		glBegin(GL_QUADS);
			// Not specified Normal (Lighting still working with color and textures)
			//~ glNormal3f(0, 0, -1);
			//~ glTexCoord2f(0,0); glVertex3f(0,0,-6);
			//~ glTexCoord2f(0,1); glVertex3f(0,15,-6);
			//~ glTexCoord2f(1,1); glVertex3f(15,15,-6);
			//~ glTexCoord2f(1,0); glVertex3f(15,0,-6);
		glEnd();
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
	
	//~ GLuint texture;
	//~ LoadGLTextures("patterns/pattern9.bmp", texture);
	//~ glBindTexture(GL_TEXTURE_2D, texture);
	//~ GLUquadric *q = gluNewQuadric();
	//~ gluQuadricTexture(q, 1);
	//~ gluCylinder(q, 9,9,9,10,20);
	//~ gluSphere(q, 5, 20, 20);
	
	body->draw();
	table->draw();
	chair->draw();
	chair1->draw();
	fridge->draw();
	tv->draw();
	tvtable->draw();
	room->draw();
	box->draw();
	lamp->draw();
	bezier->drawControlSpheres();
	
	if (animateCamera == true)
	{
		point_3* tmp = bezier->nextPoint(bezierU);
		lx = tmp->x; ly = tmp->y; lz = tmp->z;
		cout << tmp->x << tmp->y << tmp->z << endl;
		
		//glBegin(GL_POINTS);
		//for (float u = 0.005; u<1.0; u+=0.005)
		//{
			//point_3* tmp = bezier->nextPoint(u);
			////cout << "hi" <<endl;
			//cout<< tmp->x << tmp->y << tmp->z<< endl;
			////glVertex3f(tmp->x, tmp->y, tmp->z);
			//tmp->draw();
		//}
		//glEnd();
	}

	
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0) h = 1;

	GLfloat ratio = 1.0f * w / h;
	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the clipping volume
	gluPerspective(45, -ratio, 1, 150);
}

void mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)	
	{
		if (button == GLUT_LEFT_BUTTON)
		{
			bezier->addPoint(lx, ly, lz);
			cout << lx << ly << lz << endl;
		}
		if (button == GLUT_RIGHT_BUTTON)
			animateCamera = true;
	}
	glutPostRedisplay();
}
void motion(int x, int y)
{
	
}
void p_motion(int x, int y)
{
	
}

void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
		case '=':
		case '+':
			direction = PLUS;
			incr = 5;
			break;
		case '_':
		case '-':
			direction = MINUS;
			incr = -5;
			break;
		case '[':
		case '{':
			side = LEFT;
			break;
		case ']':
		case '}':
			side = RIGHT;
			break;
		case 'k':
			body->torso2->rx+= incr;
			break;
		case 'l':
			body->torso2->ry+= incr;
			break;
		case ';':
			body->torso2->rz+= incr;
			break;
		case ',':
			body->tx += incr/5; break;
		case '.':
			body->ty += incr/5; break;
		case '/':
			body->tz += incr/5; break;

		case 'q':
			body->head->rx+=incr;
			//body->head->rx = (body->head->rx > 360? body->head->rx-360: body->head->rx);
			break;
		case 'w':
			body->head->ry+=incr;
			//body->head->ry = (body->head->ry > 360? body->head->ry-360: body->head->ry);
			
			break;
		case 'e':
			body->head->rz+=incr;
			//body->head->rz %= 360;
			break;
		case 'r':
			body->torso1->rx+=incr;
			//body->torso1->rx %= 360;
			break;
		case 't':
			body->torso1->ry+=incr;
			//body->torso1->ry %= 360;
			break;
		case 'y':
			body->torso1->rz+=incr;
			//body->torso1->rz %= 360;
			break;
		case 'u':
			body->torso3->rx+=incr;
			//body->torso3->rx %= 360;
			break;
		case 'i':
			body->torso3->ry+=incr;
			//body->torso3->ry %= 360;
			break;
		case 'o':
			body->torso3->rz+=incr;
			//body->torso3->rz %= 360;
			break;

		case 'a':
			if(side == LEFT)
				body->uarml->rx+=incr;
			//	body->uarml->rx %= 360;
			else
				body->uarmr->rx+=incr;
			//	body->uarmr->rx %= 360;
			break;
		case 's':
			if(side == LEFT)
				body->uarml->ry+=incr;
			//	body->uarml->ry %= 360;
			else
				body->uarmr->ry+=incr;
				//body->uarmr->ry %= 360;
			break;
		case 'd':
			if(side == LEFT)
				body->uarml->rz+=incr;
			//	body->uarml->rz %= 360;
			else
				body->uarmr->rz+=incr;
				//body->uarmr->rz %= 360;
			break;
		case 'f':
			if(side == LEFT)
				body->larml->rx+=incr;
				//body->larml->rx %= 360;
			else
				body->larmr->rx+=incr;
				//body->larmr->rx %= 360;
			break;
		case 'g':
			if(side == LEFT)
				body->handl->rx+=incr;
				//body->larml->ry %= 360;
			else
				body->handr->rx+=incr;
			//	body->larmr->ry %= 360;
			break;
		case 'h':
			if(side == LEFT)
				body->handl->ry+=incr;
			//	body->larml->rz %= 360;
			else
				body->handr->ry+=incr;
			//	body->larmr->rz %= 360;
			break;
		case 'j':
			if(side == LEFT)
				body->handl->rz+=incr;
			//	body->larml->rz %= 360;
			else
				body->handr->rz+=incr;
			//	body->larmr->rz %= 360;
			break;

		case 'z':
			if(side == LEFT)
				body->thighl->rx+=incr;
			//	body->thighl->rx %= 360;
			else
				body->thighr->rx+=incr;
			//	body->thighr->rx %= 360;
			break;
		case 'x':
			if(side == LEFT)
				body->thighl->ry+=incr;
			//	body->thighl->ry %= 360;
			else
				body->thighr->ry+=incr;
			//	body->thighr->ry %= 360;
			break;
		case 'c':
			if(side == LEFT)
				body->thighl->rz+=incr;
			//	body->thighl->rz %= 360;
			else
				body->thighr->rz+=incr;
			//	body->thighr->rz %= 360;
			break;

		case 'v':
			if(side == LEFT)
				body->legl->rx+=incr;
			//	body->legl->rx %= 360;
			else
				body->legr->rx+=incr;
			//	body->legr->rx %= 360;
			break;
		case 'b':
			if(side == LEFT)
				body->footl->rx+=incr;
			//	body->legl->ry %= 360;
			else
				body->footr->rx+=incr;
			//	body->legr->ry %= 360;
			break;
		case 'n':
			if(side == LEFT)
				body->footl->ry+=incr;
			//	body->legl->rz %= 360;
			else
				body->footr->ry+=incr;
			//	body->legr->rz %= 360;
			break;
		case 'm':
			if(side == LEFT)
				body->footl->rz+=incr;
			//	body->legl->rz %= 360;
			else
				body->footr->rz+=incr;
			//	body->legr->rz %= 360;
			break;

		case 'p':
			if(side == LEFT)
			{
				box->angleOfCover += incr;
			}
			else
			{
				box->angleOfCover -= incr;
			}
			break;
		case '1':
			lamp->enable( lamp->isEnabled? false: true );
			break;
		case '2':
			wallLight->enable( wallLight->isEnabled? false: true );
			break;
		case '3':
			//Adding a KeyFrame
			framesToInterpolate.push_back(worldToFrames());
			cout << "Key Frame Set" << endl;
			break;
		case '4':
			//Writing all the key frames to file
			writeFramesToFile();
			cout << "Frames written to file successfully" << endl;
			break;
		case '5':
			//Reading the key frames from the file
			readingFramesFromFile();
			isAnimating = true;
			frameNumber = 0;
			cout << "Read from file" << endl;
			break;
		case 27:
			exit(0);	
		default:
			break;
	}
	glutPostRedisplay();
}

/*void (BodyPart *left, BodyPart *right, int axis, sideEnum side)
{
	if(axis == 0)
	{
		if(side == LEFT)
			left->rx += incr;
		else
			right->rx += incr;
	}
	if(axis == 1)
	{
		if(side == LEFT)
			left->ry += incr;
		else
			right->ry += incr;
	}
	if(axis == 2)
	{
		if(side == LEFT)
			left->rz += incr;
		else
			right->rz += incr;
	}
}*/

void inputKey(int key, int x, int y) 
{
	switch (key) 
	{
  		case GLUT_KEY_LEFT : lx-=5; break;
  		case GLUT_KEY_RIGHT : lx+=5; break;
  		case GLUT_KEY_UP : lz+=5; break;
  		case GLUT_KEY_DOWN : lz-=5; break;
  		case GLUT_KEY_PAGE_UP : ly+=5; break;
		case GLUT_KEY_PAGE_DOWN : ly-=5; break;
	}
 	glutPostRedisplay();
}

void keyboard_up(unsigned char key, int x, int y)
{
	
}
void processAnimationTimer(int value)
{
	//x += 0.5;
	//yy = ((int)yy+1)%360;
	//yy = -60;
	//if ( yy==90 )
		//wallLight->enable(false);
	//if ( yy==180 )
		//wallLight->enable(true);

	if (animateCamera == true)
		bezierU+= 0.005;
	if (bezierU>1)
		animateCamera = false;
	
	if(isAnimating)
	{
		assignNextFrameValues(frameNumber);
		frameNumber++;
	}
	
	glutPostRedisplay();
	glutTimerFunc(timeBetweenFrames, processAnimationTimer, 50);
}

void idle(void)
{
	GLfloat seconds = glutGet(GLUT_ELAPSED_TIME)/1000.0;
}

int main(int argc, char *argv[])
{
	glutInit( &argc, argv );
	glutInitWindowPosition( 150, 50 );
	//glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA);
	glutInitWindowSize(width, height);
	glutCreateWindow( "Program 1" );
	
	room = new Room();
	body = new Body();
	bezier = new Bezier();
	bezier-> bezierPoints();
	//Table size 25 along x axis (the largest length)
	table = new Table(); table->sx = table->sy = table->sz = 35;
	tvtable = new Table(); tvtable->sx = tvtable->sy = tvtable->sz = 25;
	tvtable->tx = -50; tvtable->tz = 50;
	chair = new Chair(); chair->sx = chair->sy = chair->sz = 12;
	chair->tx = 30;	chair->ry = 90;
	chair1 = new Chair(); chair1->sx = chair1->sy = chair1->sz = 12;
	chair1->tx = -30;	chair1->ry = -90;
	box = new Box();
	box->ty = table->sy * (0.55) + 1;
	fridge = new Fridge(); fridge->sx = fridge->sy = fridge->sz = 15;
	fridge->tx = 40; fridge->tz = 45;
	fridge->ry = 0;
	
	tv = new Television(); tv->sx = tv->sy = tv->sz = 10;
	tv->tx = tvtable->tx-2;
	tv->ty = 19.5;
	tv->tz = tvtable->tz;
	
	LoadGLTextures("pattern4.bmp", tex2D);
	//glutIgnoreKeyRepeat(1);
	//glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	
	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
	glClearDepth(1);	//By default 1
	//Enabling Z-buffering
	glEnable(GL_DEPTH_TEST);
	
	glShadeModel (GL_SMOOTH);
	
	//Lighting
	glEnable(GL_LIGHTING);
	//~ glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);	//Suppose to light both sides but lighting only back side
	wallLight = new Light(GL_LIGHT0, room->sx/2, room->sy-5, 0);
	lamp = new Lamp(GL_LIGHT1);
	lamp->sx = lamp->sy = lamp->sz = 8;
	lamp->tx = tv->tx + 10;
	lamp->ty = tv->ty - tv->sy/2;
	lamp->tz = tv->tz;
	
	glEnable(GL_COLOR_MATERIAL);
	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	
	//~ glDisable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_NORMALIZE);
	
	glEnableClientState (GL_COLOR_ARRAY);
	glEnableClientState (GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY); 
	
	glutDisplayFunc( display );
	glutReshapeFunc( reshape );
	glutMotionFunc( motion );
	glutPassiveMotionFunc( p_motion );
	glutMouseFunc( mouse );
	
	glutKeyboardFunc( keyboard );
	glutKeyboardUpFunc( keyboard_up );
	glutSpecialFunc(inputKey);

	glutTimerFunc(10, processAnimationTimer, 25);
	
	glutMainLoop();
	
	return 0;
}
