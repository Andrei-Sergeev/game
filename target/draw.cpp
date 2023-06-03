#include <gl/glut.h>
#include "draw.h"
#include "repo.h"

#define LINE_WIDTH 3
#define LUNCHER_SIZE 0.05f
#define CANNON_SIZE1 -0.05f

void drawMissleLuncher(ObjectDescription* model) {

	model->enable = model->x >= -1.0 + model->dx;

	if (model->enable) {
		model->x += model->dx;
		model->alpha += 4;
		if (model->alpha > 360) model->alpha = 0;
		glLineWidth(3);
		glColor3f(0.0f, 0.6f, 0.9f);

		glPushMatrix();
//		glRotatef(model->alpha, 0.0f, 0.0f, 1.0f);

		glBegin(GL_LINES);
		glVertex2f(model->x-0.05, model->y);
		glVertex2f(model->x+0.05, model->y);
		glEnd();
		glPopMatrix();
	}
};

void drawMissleCannon(ObjectDescription* model) {

	model->enable = model->x >= -1.0 + model->dx;

	if (model->enable) {
		model->x += model->dx;
		model->alpha += 4;
		if (model->alpha > 360) model->alpha = 0;
		glLineWidth(3);
		glColor3f(0.7f, 0.0f, 0.0f);

		glPushMatrix();
		//		glRotatef(model->alpha, 0.0f, 0.0f, 1.0f);

		glBegin(GL_LINES);
		glVertex2f(model->x - 0.05, model->y);
		glVertex2f(model->x + 0.05, model->y);
		glEnd();
		glPopMatrix();
	}
};

void drawLuncher(ObjectDescription* model)
{
	if (model->x+model->dx > LUNCHER_SIZE && model->x+model->dx < 1.0f-LUNCHER_SIZE) model->x += model->dx;
	if (model->y+model->dy > -1.0f + LUNCHER_SIZE && model->y+model->dy <1-LUNCHER_SIZE) model->y += model->dy;
	model->shootEnable = (getGlobalTimerEventCount() - model->lastShootTime >= SHOOT_INTERVAL);

	model->dx = 0;
	model->dy = 0;


	glPushMatrix();
	//glRotatef(model->alpha, 0.0f, 0.0f, 1.0f);

	glLineWidth(3);
	if (model->shootEnable) {
		glColor3f(0.0f, 0.0f, 0.8f);		
	}
	else {
		glColor3f(0.0f, 0.0f, 0.4f);
	}

	glBegin(GL_QUADS);
	glVertex2f(model->x - LUNCHER_SIZE, model->y-LUNCHER_SIZE);
	glVertex2f(model->x + LUNCHER_SIZE, model->y-LUNCHER_SIZE);
	glVertex2f(model->x + LUNCHER_SIZE, model->y + LUNCHER_SIZE);
	glVertex2f(model->x - LUNCHER_SIZE, model->y + LUNCHER_SIZE);
	glEnd();
	glPopMatrix();
};



void drawCannon(ObjectDescription* model)
{
	/*   2 игрока
	if (model->x + model->dx < CANNON_SIZE1 && model->x + model->dx > -1.0f - CANNON_SIZE1) model->x += model->dx;
	if (model->y + model->dy > -1.0f + LUNCHER_SIZE && model->y + model->dy < 1 - LUNCHER_SIZE) model->y += model->dy;
	model->dx = 0;
	model->dy = 0;
	*/

	if (model->x + model->dx < CANNON_SIZE1 && model->x + model->dx > -1.0f - CANNON_SIZE1) model->x += model->dx; else model->dx *= -1;
	if (model->y + model->dy > -1.0f + LUNCHER_SIZE && model->y + model->dy < 1 - LUNCHER_SIZE) model->y += model->dy; else model->dy *= -1;
	
	model->shootEnable = (getGlobalTimerEventCount() - model->lastShootTime >= SHOOT_INTERVAL);
	if (model->shootEnable) {
		ObjectDescription* missle = CreateMissleCannon(getCannon());
	    getCannon()->lastShootTime = getGlobalTimerEventCount();
	}


//  2 игрока
//	model->dx = 0;
//	model->dy = 0;


	glPushMatrix();

	glLineWidth(3);
	if (model->shootEnable) {
		glColor3f(0.0f, 0.8f, 0.0f);
	}
	else {
		glColor3f(0.0f, 0.4f, 0.0f);
	}

	glBegin(GL_QUADS);
	glVertex2f(model->x - LUNCHER_SIZE, model->y - LUNCHER_SIZE);
	glVertex2f(model->x + LUNCHER_SIZE, model->y - LUNCHER_SIZE);
	glVertex2f(model->x + LUNCHER_SIZE, model->y + LUNCHER_SIZE);
	glVertex2f(model->x - LUNCHER_SIZE, model->y + LUNCHER_SIZE);
	glEnd();
	glPopMatrix();
}

void drawBarrier(ObjectDescription* model)
{
	glPushMatrix();

	glLineWidth(4);
	glColor3f(0.4f, 0.4f, 0.4f);

	glBegin(GL_LINES);
	glVertex2f(model->x, model->y - LUNCHER_SIZE);
	glVertex2f(model->x, model->y + LUNCHER_SIZE);
	glEnd();
	glPopMatrix();

}
;

