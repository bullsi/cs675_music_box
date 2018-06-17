#include "body.h"

Body :: Body()
{
	tx = 0; ty = 23;tz = 0;
	rx = 90; ry = 0; rz = -90;
	sx = 0.5f; sy = 0.5f; sz = 0.5f;
	
	torso2 	= new BodyPart (TORSO2, NULL);
	torso3 	= new BodyPart(TORSO3,torso2);
	torso1 	= new BodyPart (TORSO1,torso2);

	hipl	= new BodyPart (HIPL, torso3);
	thighl	= new BodyPart (THIGHL, hipl);
	kneel	= new BodyPart (KNEEL, thighl);
	legl	= new BodyPart (LEGL, kneel);
	anklel	= new BodyPart (ANKLEL, legl);
	footl	= new BodyPart (FOOTL, anklel);

	hipr	= new BodyPart (HIPR, torso3);
	thighr	= new BodyPart (THIGHR, hipr);
	kneer	= new BodyPart (KNEER, thighr);
	legr	= new BodyPart (LEGR, kneer);
	ankler	= new BodyPart (ANKLER, legr);
	footr	= new BodyPart (FOOTR, ankler);

	shoulderl = new BodyPart (SHOULDERL, torso1);
	uarml	= new BodyPart (UARML, shoulderl);
	elbowl	= new BodyPart (ELBOWL, uarml);
	larml	= new BodyPart (LARML, elbowl);
	wristl	= new BodyPart (WRISTL, larml);
	handl	= new BodyPart (HANDL, wristl);

	shoulderr = new BodyPart (SHOULDERR, torso1);
	uarmr	= new BodyPart (UARMR, shoulderr);
	elbowr	= new BodyPart (ELBOWR, uarmr);
	larmr	= new BodyPart (LARMR, elbowr);
	wristr	= new BodyPart (WRISTR, larmr);
	handr	= new BodyPart (HANDR, wristr);

	neck	= new BodyPart(NECK, torso1);
	head	= new BodyPart(HEAD, neck);

	torso2->children.push_back(torso3);
	torso3->children.push_back(hipl);
	torso3->children.push_back(hipr);
	torso2->children.push_back(torso1);

	hipl->children.push_back(thighl);	
	thighl->children.push_back(kneel);
	kneel->children.push_back(legl);
	legl->children.push_back(anklel);
	anklel->children.push_back(footl);

	hipr->children.push_back(thighr);	
	thighr->children.push_back(kneer);
	kneer->children.push_back(legr);
	legr->children.push_back(ankler);
	ankler->children.push_back(footr);

	torso1->children.push_back(shoulderl);
	shoulderl->children.push_back(uarml);
	uarml->children.push_back(elbowl);
	elbowl->children.push_back(larml);
	larml->children.push_back(wristl);
	wristl->children.push_back(handl);

	torso1->children.push_back(shoulderr);
	shoulderr->children.push_back(uarmr);
	uarmr->children.push_back(elbowr);
	elbowr->children.push_back(larmr);
	larmr->children.push_back(wristr);
	wristr->children.push_back(handr);

	torso1->children.push_back(neck);
	neck->children.push_back(head);

	cout<<"tp"<<endl;

}

void Body :: draw()
{
	//~ glBegin(GL_LINES);
	  //~ glVertex3f(-2,0,0);
	  //~ glVertex3f(10,0,0);
	//~ glEnd();
	//glRotatef(-30,1,0,0);
	glPushMatrix();
		glTranslatef(tx,ty,tz);
		glRotatef(rx,1,0,0);
		glRotatef(ry,0,1,0);
		glRotatef(rz,0,0,1);
		glPushMatrix();
			glScalef(sx,sy,sz);
			torso2->draw();
		glPopMatrix();
	glPopMatrix();
}



