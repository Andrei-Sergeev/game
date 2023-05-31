﻿
#include <stdio.h>
#include <cstdlib>
#include "draw.h"
#include "repo.h"
#include <gl/glut.h>
#include <string.h>

#define SHOOT_INTERVAL 40


int WindW, WindH;


ObjectDescription* repo = NULL;
ObjectDescription* luncher = NULL;
ObjectDescription* cannon = NULL;
long globalTimerEventCount = 0;


void Reshape(int width, int height) // Reshape function 
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1, 1, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	WindW = width;
	WindH = height;
}

void DrawText(char* string) {
	glColor3f(0.5f, 0.0f, 0.0f);
	glRasterPos2f(-0.2, 0.0);
	int len = (int)strlen(string);
	for (int i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}

}

void Draw(void) // Window redraw function 
{
	glClear(GL_COLOR_BUFFER_BIT);

	CheckAllMisselAndTarget(repo);
	if (luncher->enable && cannon->enable) {
		DrawAll(repo);
	}
	else {
		char string[] = "This is end of the game";
		DrawText(string);
	}

	glFlush();
	glutSwapBuffers();
}

void Visibility(int state) // Visibility function 
{
	if (state == GLUT_NOT_VISIBLE) printf("Window not visible!\n");
	if (state == GLUT_VISIBLE) printf("Window visible!\n");
}

void timf(int value) // Timer function 
{
	glutPostRedisplay();
	// Redraw windows 
	glutTimerFunc(40, timf, 0);
	// Setup next timer 
	globalTimerEventCount++;
	luncher->shootLuncher = (globalTimerEventCount - luncher->lastShootTimeLuncher >= SHOOT_INTERVAL);
	cannon->shootCannon = (globalTimerEventCount - cannon->lastShootTimeCannon >= SHOOT_INTERVAL);
}

void processKeyEvent(unsigned char key, int x, int y) {
	if (cannon != NULL && cannon->enable) {
		switch (key) {
		case 'w':
			cannon->dy = 0.01f;
			break;
		case 's':
			cannon->dy = -0.01f;
			break;
		case 'a':
			cannon->dx = -0.01f;
			break;
		case 'd':
			cannon->dx = 0.01f;
			break;
		case 'z':
			if (cannon->shootCannon) {
				ObjectDescription* missle = CreateMissleCannon(repo, cannon);
				cannon->lastShootTimeCannon = globalTimerEventCount;
				repo = missle;
			}
			break;
		}
	}

}


void processSpecialKeyEvent(int key, int x, int y) {

	if (luncher != NULL && luncher->enable) {
		switch (key) {
		case GLUT_KEY_UP:
			luncher->dy = 0.01f;
			break;
		case GLUT_KEY_DOWN:
			luncher->dy = -0.01f;
			break;
		case GLUT_KEY_LEFT:
			luncher->dx = -0.01f;
			break;
		case GLUT_KEY_RIGHT:
			luncher->dx = 0.01f;
			break;
		case GLUT_KEY_INSERT:			
			if (luncher->shootLuncher) {
				ObjectDescription* missle = CreateMissleLuncher(repo, luncher);
				luncher->lastShootTimeLuncher = globalTimerEventCount;
				repo = missle;
			}
			break;
		}
	}
}


int main(int argc, char* argv[])
{
	WindW = 800; WindH = 800;
	
	luncher = CreateLuncher(repo);
	repo = luncher;

	cannon = CreateCannon(repo);
	repo = cannon;

	repo = CreateBarrier(repo, -1);
	repo = CreateBarrier(repo, 1);

	glutInit(&argc, argv);
	glutInitWindowSize(WindW, WindH);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	(void)glutCreateWindow("Andrew Play");
	glutReshapeFunc(Reshape);
	// Set up reshape function 
	glutDisplayFunc(Draw); // Set up redisplay function 
	glutTimerFunc(40, timf, 0); // Set up timer for 40ms, about 25 fps 
	glutKeyboardFunc(processKeyEvent);
	glutSpecialFunc(processSpecialKeyEvent);
	glutVisibilityFunc(Visibility); // Set up visibility funtion 
	glClearColor(0, 0, 0, 0);
	glutMainLoop();
	return 0;
}



