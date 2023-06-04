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

	// Тело танка
	glBegin(GL_QUADS);
	glVertex2f(model->x - 0.08, model->y - 0.05);
	glVertex2f(model->x + 0.05, model->y - 0.05);
	glVertex2f(model->x + 0.05, model->y + 0.02);
	glVertex2f(model->x - 0.075, model->y + 0.02);
	glEnd();

	// Башня танка
	glBegin(GL_QUADS);
	glVertex2f(model->x - 0.05, model->y - 0.05);
	glVertex2f(model->x + 0.03, model->y - 0.05);
	glVertex2f(model->x + 0.03, model->y + 0.09);
	glVertex2f(model->x - 0.05, model->y + 0.09);
	glPopMatrix();
	glEnd();

	// Дуло танка
	glBegin(GL_QUADS);
	glVertex2f(model->x - 0.08, model->y + 0.04);
	glVertex2f(model->x - 0.05, model->y + 0.04);
	glVertex2f(model->x - 0.05, model->y + 0.06);
	glVertex2f(model->x - 0.08, model->y + 0.06);
	glPopMatrix();
	glEnd();

	//Колёса танка
	glColor3f(0.1, 0.1, 0.1); // Черный цвет

	glPushMatrix();
	glTranslatef(model->x - 0.06, model->y - 0.05, 0); // Первое колесо
	glutSolidTorus(0.01, 0.01, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(model->x + 0.03, model->y - 0.05, 0); // Второе колесо
	glutSolidTorus(0.01, 0.01, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(model->x + 0.005, model->y - 0.05, 0); // Третье колесо
	glutSolidTorus(0.01, 0.01, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(model->x - 0.03, model->y - 0.05, 0); // Четвертое колесо
	glutSolidTorus(0.01, 0.01, 10, 10);
	glPopMatrix();

	glFlush();


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

	//Тело самолёта
	glBegin(GL_QUADS);
	glVertex2f(model->x + 0.063, model->y + 0.02);   // Верхняя правая точка
	glVertex2f(model->x - 0.06, model->y + 0.02);   // Верхняя левая точка
	glVertex2f(model->x - 0.06, model->y - 0.02);   // Нижняя левая точка
	glVertex2f(model->x + 0.07, model->y - 0.02);   // Нижняя правая точка
	glEnd();

	//Крыло нижнее 
	glBegin(GL_TRIANGLES);
	glVertex2f(model->x + 0.028,  model->y - 0.02);   //
	glVertex2f(model->x - 0.028, model->y - 0.08);   //
	glVertex2f(model->x - 0.015, model->y - 0.02);    //
	glEnd();

	//Крыло верхнее
	glBegin(GL_TRIANGLES);
	glVertex2f(model->x + 0.028, model->y + 0.02);   //
	glVertex2f(model->x - 0.028, model->y + 0.08);   //
	glVertex2f(model->x - 0.015, model->y + 0.02);     //
	glEnd();

	//Хвост
	glBegin(GL_TRIANGLES);
	glVertex2f(model->x - 0.045,  model->y + 0.02);   //
	glVertex2f(model->x - 0.07, model->y + 0.05);   //
	glVertex2f(model->x - 0.06,  model->y + 0.02);     //
	glEnd();
	
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

