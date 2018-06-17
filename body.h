#include "bodypart.h"

class Body
{
	public:
	GLfloat tx, ty, tz;
	GLfloat rx, ry, rz;
	GLfloat sx, sy, sz;
	
	BodyPart *torso1,*torso2,*torso3, *neck, *head,
		 *hipl, *thighl, *kneel, *legl, *anklel, *footl, 
		 *hipr, *footr, *ankler, *legr, *kneer, *thighr,
		 *shoulderl, *uarml, *elbowl, *larml, *wristl, *handl,
		 *shoulderr, *uarmr, *elbowr, *larmr, *wristr, *handr;
	Body();
	void createBodyTranslations();
	void draw();
};
