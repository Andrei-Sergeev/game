#include <gl/glut.h>
#include "draw.h"
#include "repo.h"
#include <corecrt_math.h>

#define LINE_WIDTH 3
#define LUNCHER_SIZE 0.05f
#define PLAIN_SIZE 0.05f

void drawMissleLuncher(ObjectDescription* model) {

	model->enable = (model->x >= -1.0 + model->dx) && (model->x <= 1.0 - model->dx) && (model->y+model->dy<0.95f);

	if (model->enable) {
		model->x += model->dx;
		model->y+= model->dy;
		model->alpha += 4;
		if (model->alpha > 360) model->alpha = 0;
		glLineWidth(3);
		glColor3f(0.0f, 0.6f, 0.9f);

		glPushMatrix();

		glBegin(GL_LINES);
		glVertex2f(model->x-0.01, model->y);
		glVertex2f(model->x+0.01, model->y);
		glEnd();
		glPopMatrix();
	}
};

void drawMisslePlain(ObjectDescription* model) {

	model->enable = (model->x >= -1.0 - model->dx) && (model->x <= 1.0 - model->dx) && (model->y>-1.0+LUNCHER_SIZE);

	if (model->enable) {
		model->x += model->dx;
		model->y -= 9.8f*(getGlobalTimerEventCount()-model->lastShootTime)*0.001;
		glLineWidth(3);
		glColor3f(0.7f, 0.0f, 0.0f);

		glPushMatrix();
		drawCircle(model->x, model->y, 0.01f, 8);		
		glPopMatrix();
		
	}
};


void drawLuncher(ObjectDescription* model)
{
	if (model->x+model->dx >-1.0+LUNCHER_SIZE && model->x+model->dx < 1.0f-LUNCHER_SIZE) model->x += model->dx;
	if (model->y+model->dy > -1.0f + LUNCHER_SIZE && model->y+model->dy <-LUNCHER_SIZE) model->y += model->dy;
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

	glPushMatrix();
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
	glEnd();

	// Пусковая установка

	glLineWidth(7);
	glColor3f(0.0f, 0.3f, 0.8f);
	glBegin(GL_LINES);
	glVertex2f(model->x, model->y);
	glVertex2f(model->x + 0.1 * cos(model->alpha / 180.0f * 3.1415f), model->y + 0.1 * sin(model->alpha / 180.0f * 3.1415f));
	glEnd();
	glPopMatrix();
	glLineWidth(3);


	//Колёса танка
	glPushMatrix();
	glColor3f(0.1, 0.1, 0.1); // Черный цвет

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



void drawPlain(ObjectDescription* model)
{
	
	model->dy = sin(model->alpha / 180.0f * 3.1415f)*2*PLAIN_SIZE;
	model->alpha += 6;
	if (model->x + model->dx <1.0 - PLAIN_SIZE && model->x + model->dx > -1.0f + PLAIN_SIZE) model->x += model->dx; else model->dx *= -1;
	model->y = 0.75 + model->dy;
	model->dx += randomFloat() * 0.002;
	
	model->shootEnable = (getGlobalTimerEventCount() - model->lastShootTime >= SHOOT_INTERVAL);
	if (model->shootEnable) {
		ObjectDescription* missle = CreateMisslePlain(getPlain());
	    getPlain()->lastShootTime = getGlobalTimerEventCount();
	}

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
	glVertex2f(model->x-LUNCHER_SIZE, model->y);
	glVertex2f(model->x+LUNCHER_SIZE, model->y);
	glEnd();
	glPopMatrix();

}


void drawCircle(float cx, float cy, float r, int num_segments)
{
	glBegin(GL_LINE_LOOP);
	for (int ii = 0; ii < num_segments; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle

		float x = r * cosf(theta);//calculate the x component
		float y = r * sinf(theta);//calculate the y component

		glVertex2f(x + cx, y + cy);//output vertex

	}
	glEnd();
}

