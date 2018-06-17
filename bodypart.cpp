#include "bodypart.h"
#include "file.h"


BodyPart :: BodyPart(BodyPartEnum part, BodyPart *parent)
{
	vector<int> a;
	this->parent = parent;
	GLUquadric *quadric = gluNewQuadric();
	gluQuadricTexture(quadric, true);
	
	texture = 0;
	//this->part = part;
	GLfloat skr = 1, skg=1, skb=1;	//Skin Color
	GLfloat topr = 0, topg = 0, topb = 1;	//Top Color
	GLfloat skirtr = 1, skirtg = 1, skirtb = 1;	//Skirt Color
	const char* skirt = "patterns/pattern11.bmp";	//Skirt texture
	const char* top = "patterns/pattern11.bmp";	//Top texture
	const char* skin = "patterns/pattern14.bmp";	//Skin texture
	
	if(part == TORSO3)
	{
		degreeOfFreedom = 3;
		
		baseRadius = 4.0;
		topRadius = 5.0;
		height = 2.0;
		slices = 80;
		stacks = 100;
		rx=0; ry=0; rz=0;
		tx=0; ty=-this->height/2-parent->baseRadius; tz=0;
		sx=1; sy=1; sz=1;
		LoadGLTextures(skirt, texture);
		
		displayList = glGenLists(1);
		glNewList(displayList, GL_COMPILE);
			glColor3f(skirtr,skirtg,skirtb);
			glTranslatef(0, height/2, 0);
			glRotatef(90,1.0,0.0,0.0);
			//glTranslatef(0, 0, -height/2);
			gluCylinder(quadric, baseRadius, topRadius, height, slices, stacks);
			gluCylinder(quadric, baseRadius, topRadius+2, height+2, slices, stacks);
		glEndList();
	}
	if(part == TORSO1)
	{
		degreeOfFreedom = 0;
		
		baseRadius = 4.5;
		topRadius = 4.0;
		height = 7.0;
		slices = 80;
		stacks = 100;
		
		rx=0; ry=0; rz=0;
		tx=0; ty=this->height/2+parent->baseRadius; tz=0;
		sx=1; sy=1; sz=1;
		LoadGLTextures(top, texture);
		
		displayList = glGenLists(1);
		glNewList(displayList, GL_COMPILE);
			glColor3f(topr,topg,topb);
			glTranslatef(0, height/2, 0);
			glRotatef(90,1.0,0.0,0.0);
			gluCylinder(quadric, baseRadius, topRadius, height, slices, stacks);
		glEndList();
	}
	if(part == TORSO2)
	{
		degreeOfFreedom = 0;
		
		baseRadius = 0.5;
		height = 5.0;
		slices = 100;
		stacks = 100;
		rx=0; ry=0; rz=0;
		tx=0; ty=0; tz=0;
		sx=9; sy=1; sz=9;
		//rx=0; ry=0; rz=0;
		//tx=0; ty=parent->height/2+this->baseRadius; tz=0;
		//sx=1+parent->baseRadius/this->baseRadius; sy=1; sz=1+parent->baseRadius/this->baseRadius;
		LoadGLTextures(top, texture);
		
		displayList = glGenLists(1);
		glNewList(displayList, GL_COMPILE);
			glColor3f(topr,topg,topb);
			//glRotatef(90,1.0,0.0,0.0);
			//glTranslatef(0, 0, -2);
			gluSphere(quadric, baseRadius, slices, stacks);
		glEndList();
	}

	if(part == THIGHL || part == THIGHR)
	{
		degreeOfFreedom = 3;
		
		baseRadius = 2.0;
		topRadius = 1.5;
		height = 5.0;
		slices = 80;
		stacks = 200;
		rz = 15;
		rx=0; ry=0; rz=0;
		tx=0; ty=-(this->height/2 + parent->baseRadius); tz=0;
		sx=1; sy=1; sz=1;
		displayList = glGenLists(1);
		LoadGLTextures(skin, texture);
		
		glNewList(displayList, GL_COMPILE);
			glColor3f(skr, skg, skb);
			glRotatef(90,1.0,0.0,0.0);
			glTranslatef(0, 0, -height/2);
			gluCylinder(quadric, baseRadius, topRadius, height, slices, stacks);
		glEndList();
	}
	if(part == LEGL || part == LEGR)
	{
		degreeOfFreedom = 1;
		
		baseRadius = 1.5;
		topRadius = 1.0;
		height = 6.0;
		slices = 80;
		stacks = 200;
		rx=0; ry=0; rz=0;
		tx=0; ty=-(this->height/2+parent->baseRadius); tz=0;
		sx=1; sy=1; sz=1;
		displayList = glGenLists(1);
		LoadGLTextures(skin, texture);
		
		glNewList(displayList, GL_COMPILE);
			glColor3f(skr, skg, skb);
			glRotatef(90,1.0,0.0,0.0);
			glTranslatef(0, 0, -height/2);
			gluCylinder(quadric, baseRadius, topRadius, height, slices, stacks);
		glEndList();
	}
	if(part == FOOTR)
	{
		degreeOfFreedom = 3;
		baseRadius = 1;
		topRadius = 0.2;
		height = 2.0;
		slices = 80;
		stacks = 200;
		rx=70; ry=0; rz=20;
		tx=0; ty=-(this->baseRadius+parent->baseRadius); tz=0;
		sx=1; sy=2; sz=1;
		displayList = glGenLists(1);
//		LoadGLTextures(skin, texture);
		
		glNewList(displayList, GL_COMPILE);
			glColor3f(0,0,0);
			//glRotatef(90,1.0,0.0,0.0);
			//glTranslatef(0, 0, -height/2);
			gluSphere(quadric,baseRadius, slices, stacks);
		glEndList();
	}
	if(part == FOOTL)
	{
		degreeOfFreedom = 3;

		baseRadius = 1;
		topRadius = 0.2;
		height = 2.0;
		slices = 80;
		stacks = 200;
		rx=50; ry=0; rz=-10;
		tx=0; ty=-(this->baseRadius+parent->baseRadius); tz=0;
		sx=1; sy=2; sz=1;
		displayList = glGenLists(1);
//		LoadGLTextures(skin, texture);
		
		glNewList(displayList, GL_COMPILE);
			glColor3f(0,0,0);
			//glRotatef(90,1.0,0.0,0.0);
			//glTranslatef(0, 0, -height/2);
			gluSphere(quadric,baseRadius, slices, stacks);
		glEndList();
	}

	if(part == KNEEL || part == KNEER)
	{
		degreeOfFreedom = 0;
		
		baseRadius = 0.25;
		topRadius = 1.5;
		height = 5.0;
		slices = 80;
		stacks = 200;
		rx=0; ry=0; rz=0;
		tx=0; ty=-(parent->height/2 + this->baseRadius); tz=0;
		sx=parent->topRadius/this->baseRadius; sy=1; sz= parent->topRadius/this->baseRadius;
		displayList = glGenLists(1);
		LoadGLTextures(skin, texture);
		
		glNewList(displayList, GL_COMPILE);
			glColor3f(skr, skg, skb);
			//glRotatef(90,1.0,0.0,0.0);
			//glTranslatef(0, 0, -height/2);
			gluSphere(quadric,baseRadius, slices, stacks);
		glEndList();
	}
	if(part == ANKLEL || part == ANKLER)
	{
		degreeOfFreedom = 0;
		
		baseRadius = 0.25;
		topRadius = 1.5;
		height = 5.0;
		slices = 80;
		stacks = 200;
		rx=0; ry=0; rz=0;
		tx=0; ty= -(parent->height/2 + this->baseRadius); tz=0;
		sx=parent->topRadius/this->baseRadius; sy=1; sz=parent->topRadius/this->baseRadius;
		displayList = glGenLists(1);
		LoadGLTextures(skin, texture);
		
		glNewList(displayList, GL_COMPILE);
			glColor3f(skr, skg, skb);
			//glRotatef(90,1.0,0.0,0.0);
			//glTranslatef(0, 0, -height/2);
			gluSphere(quadric,baseRadius, slices, stacks);
		glEndList();
	}
	if(part == HIPL)
	{
		degreeOfFreedom = 0;
		
		baseRadius = 0.5;
		topRadius = 1.0;
		height = 5.0;
		slices = 80;
		stacks = 200;
		rx=0; ry=0; rz=0;
		tx=-parent->topRadius/2; ty=-(parent->height/2 + this->baseRadius); tz=0;
		sx=-0.5+parent->topRadius; sy=1; sz=-0.5+parent->topRadius;
		displayList = glGenLists(1);
		LoadGLTextures(skin, texture);
		
		glNewList(displayList, GL_COMPILE);
			glColor3f(skr, skg, skb);	
			//glRotatef(90,1.0,0.0,0.0);
			//glTranslatef(0, 0, -height/2);
			//glScalef(xRadius, yRadius, zRadius);
			gluSphere(quadric, baseRadius, slices, stacks);
		glEndList();
	}
	if(part == HIPR)
	{
		degreeOfFreedom = 0;
		
		baseRadius = 0.5;
		topRadius = 1.0;
		height = 5.0;
		slices = 80;
		stacks = 200;
		rx=0; ry=0; rz=0;
		tx=parent->topRadius/2; ty=-(parent->height/2 + this->baseRadius); tz=0;
		sx=-0.5+parent->topRadius; sy=1; sz=-0.5+parent->topRadius;
		displayList = glGenLists(1);
		LoadGLTextures(skin, texture);		
			
		glNewList(displayList, GL_COMPILE);
			glColor3f(skr, skg, skb);
			//glRotatef(90,1.0,0.0,0.0);
			//glTranslatef(0, 0, -height/2);
			gluSphere(quadric, baseRadius, slices, stacks);
		glEndList();
	}

	if(part == SHOULDERL)
	{
		degreeOfFreedom = 0;
		
		baseRadius = 1;
		topRadius = 1.5;
		height = 5.0;
		slices = 80;
		stacks = 200;
		rx=0; ry=0; rz=0;
		tx=-parent->baseRadius/2-this->baseRadius-1; ty=parent->height/2; tz=-0.25;
		sx=1; sy=1; sz=1;
		displayList = glGenLists(1);
		LoadGLTextures(top, texture);
		glNewList(displayList, GL_COMPILE);			
			glColor3f(topr,topg,topb);
			//glRotatef(90,1.0,0.0,0.0);
			//glTranslatef(0, 0, -height/2);
			gluSphere(quadric,baseRadius, slices, stacks);
		glEndList();
	}

	if(part == SHOULDERR)
	{
		degreeOfFreedom = 0;
		
		baseRadius = 1;
		topRadius = 1.5;
		height = 5.0;
		slices = 80;
		stacks = 200;
		rx=0; ry=0; rz=0;
		tx=parent->baseRadius/2+this->baseRadius+1; ty=parent->height/2; tz=-0.25;
		sx=1; sy=1; sz=1;
		displayList = glGenLists(1);
		LoadGLTextures(top, texture);
		
		glNewList(displayList, GL_COMPILE);
			glColor3f(topr,topg,topb);
			//glRotatef(90,1.0,0.0,0.0);
			//glTranslatef(0, 0, -height/2);
			gluSphere(quadric,baseRadius, slices, stacks);
		glEndList();
	}

	if(part == UARML)
	{
		degreeOfFreedom = 3;
		
		baseRadius = 1.0;
		topRadius = 1.0;
		height = 4;
		slices = 80;
		stacks = 200;
		rx=0; ry=0; rz=-15;
		tx=0; ty=-(this->height/2 + parent->baseRadius); tz=0;
		sx=1; sy=1; sz=1;
		displayList = glGenLists(1);
		LoadGLTextures(top, texture);
		glNewList(displayList, GL_COMPILE);
			glColor3f(topr,topg,topb);
			glRotatef(90,1.0,0.0,0.0);
			glTranslatef(0, 0, -height/2);
			gluCylinder(quadric, baseRadius, topRadius, height, slices, stacks);
		glEndList();
	}

	if(part == UARMR)
	{
		degreeOfFreedom = 3;
		
		baseRadius = 1.0;
		topRadius = 1.0;
		height = 4;
		slices = 80;
		stacks = 200;
		rx=0; ry=0; rz=15;
		tx=0; ty=-(this->height/2 + parent->baseRadius); tz=0;
		sx=1; sy=1; sz=1;
		displayList = glGenLists(1);
		LoadGLTextures(top, texture);
		glNewList(displayList, GL_COMPILE);
			glColor3f(topr,topg,topb);
			glRotatef(90,1.0,0.0,0.0);
			glTranslatef(0, 0, -height/2);
			gluCylinder(quadric, baseRadius, topRadius, height, slices, stacks);
		glEndList();
	}
	if(part == LARML || part == LARMR)
	{
		degreeOfFreedom = 1;
		
		baseRadius = 1;
		topRadius = 1;
		height = 4.5;
		slices = 80;
		stacks = 200;
		rx=30; ry=0; rz=0;
		tx=0; ty=-(this->height/2+parent->baseRadius); tz=0;
		sx=1; sy=1; sz=1;
		displayList = glGenLists(1);
		LoadGLTextures(skin, texture);
		glNewList(displayList, GL_COMPILE);
			glColor3f(skr, skg, skb);
			glRotatef(90,1.0,0.0,0.0);
			glTranslatef(0, 0, -height/2);
			gluCylinder(quadric, baseRadius, topRadius, height, slices, stacks);
		glEndList();
	}
	if(part == HANDL || part == HANDR)
	{
		degreeOfFreedom = 3;
		
		baseRadius = 1;
		topRadius = 0.2;
		height = 1.5;
		slices = 80;
		stacks = 200;
		rx=0; ry=0; rz=0;
		tx=0; ty=-(this->height/2+parent->baseRadius); tz=0;
		sx=1; sy=1; sz=1;
		displayList = glGenLists(1);
		LoadGLTextures(skin, texture);
		glNewList(displayList, GL_COMPILE);
			glColor3f(skr, skg, skb);
			glRotatef(90,1.0,0.0,0.0);
			glTranslatef(0, 0, -height/2);
			gluCylinder(quadric, baseRadius, topRadius, height, slices, stacks);
		glEndList();
	}

	if(part == ELBOWL || part == ELBOWR)
	{
		degreeOfFreedom = 0;
		
		baseRadius = 0.25;
		topRadius = 1.5;
		height = 5.0;
		slices = 80;
		stacks = 200;
		rx=0; ry=0; rz=0;
		tx=0; ty=-(parent->height/2 + this->baseRadius); tz=0;
		sx=parent->topRadius/this->baseRadius; sy=1; sz= parent->topRadius/this->baseRadius;
		displayList = glGenLists(1);
		LoadGLTextures(skin, texture);
		
		glNewList(displayList, GL_COMPILE);
			glColor3f(skr, skg, skb);
			//glRotatef(90,1.0,0.0,0.0);
			//glTranslatef(0, 0, -height/2);
			gluSphere(quadric,baseRadius, slices, stacks);
		glEndList();
	}
	if(part == WRISTL || part == WRISTR)
	{
		degreeOfFreedom = 0;
		
		baseRadius = 0.25;
		topRadius = 1.5;
		height = 5.0;
		slices = 80;
		stacks = 200;
		rx=0; ry=0; rz=0;
		tx=0; ty= -(parent->height/2 + this->baseRadius); tz=0;
		sx=parent->topRadius/this->baseRadius; sy=1; sz=parent->topRadius/this->baseRadius;
		displayList = glGenLists(1);
		LoadGLTextures(skin, texture);
		glNewList(displayList, GL_COMPILE);
			glColor3f(skr, skg, skb);
			//glRotatef(90,1.0,0.0,0.0);
			//glTranslatef(0, 0, -height/2);
			gluSphere(quadric,baseRadius, slices, stacks);
		glEndList();
	}
	if(part == NECK)
	{
		degreeOfFreedom = 0;
		
		baseRadius = 1;
		topRadius = 1.5;
		height = 1.5;
		slices = 80;
		stacks = 200;
		rx=0; ry=0; rz=0;
		tx=0; ty= (parent->height/2 + this->baseRadius); tz=0;
		sx=1; sy=1; sz=1;
		displayList = glGenLists(1);
		LoadGLTextures(skin, texture);
		glNewList(displayList, GL_COMPILE);
			glColor3f(skr, skg, skb);
			glRotatef(90,1.0,0.0,0.0);
			glTranslatef(0, 0, -height/2);
			gluCylinder(quadric, baseRadius, topRadius, height, slices, stacks);
		glEndList();
	}
	if(part == HEAD)
	{
		degreeOfFreedom = 3;
		
		baseRadius = 2.2;
		topRadius = 2;
		height = 3.0;
		slices = 80;
		stacks = 200;
		rx=0; ry=0; rz=0;
		tx=0; ty= (parent->height/2 + this->height/2); tz=0;
		sx=1; sy=1; sz=1;
		displayList = glGenLists(1);
		LoadGLTextures(skin, texture);
		glNewList(displayList, GL_COMPILE);
			glColor3f(0,0,0);
			glTranslatef(0,this->height/2,0);
			gluSphere(quadric,baseRadius, slices, stacks);
			glColor3f(skr, skg, skb);
			glTranslatef(0,-this->height/2,0);
			glRotatef(90,1.0,0.0,0.0);
			glTranslatef(0, 0, -height/2);
			gluCylinder(quadric, baseRadius, topRadius, height, slices, stacks);	
		glEndList();
	}


}
void BodyPart :: draw()
{
	glBindTexture(GL_TEXTURE_2D, texture);
	//glColor3f(1,0,0);
	glRotatef(rx,1,0,0);
	glRotatef(ry,0,1,0);
	glRotatef(rz,0,0,1);
	glTranslatef(tx,ty,tz);
	glPushMatrix();
		glScalef(sx,sy,sz);
		glCallList(displayList);
	glPopMatrix();

	//cout<<"as"<<tx<<","<<ty<<","<<tz<<","<<sx<<","<<sy<<endl;
	for (int i=0; i<children.size();i++)
	{
//		cout<<"hi "<<i<<endl;
		glPushMatrix();
			children[i]->draw();
		glPopMatrix();
	}
	//glCallList(displayList);
	glBindTexture(GL_TEXTURE_2D, 0);
}


