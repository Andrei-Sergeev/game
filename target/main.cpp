
#include <stdio.h>
#include <cstdlib>
#include "draw.h"
#include "repo.h"
#include <gl/glut.h>
#include <string.h>



int WindW, WindH;


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

	CheckAllMisselAndTarget();
	drawBack();
	if (isGameOn()) {		
		DrawAll();
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
}

void processKeyEvent(unsigned char key, int x, int y) {
	ObjectDescription* plain = getPlain();
	ObjectDescription* luncher = getLuncher();
	if (plain != NULL && plain->enable) {
		switch (key) {
		case 'w':
			plain->dy = 0.01f;
			break;
		case 's':
			plain->dy = -0.01f;
			break;
		case 'a':
			plain->dx = -0.01f;
			break;
		case 'd':
			plain->dx = 0.01f;
			break;
		case 'z':
			if (plain->shootEnable) {
				ObjectDescription* missle = CreateMisslePlain(plain);
				plain->lastShootTime = getGlobalTimerEventCount();
			}
			break;
		case 'n':
			if (luncher->alpha<170) {
					luncher->alpha += 10;
			}
			break;
		case 'm':
			if (luncher->alpha > 10) {
				luncher->alpha -= 10;
			}
			break;

		}
	}

}


void processSpecialKeyEvent(int key, int x, int y) {
	ObjectDescription* luncher = getLuncher();

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
			if (luncher->shootEnable) {
				ObjectDescription* missle = CreateMissleLuncher(luncher);
				luncher->lastShootTime = getGlobalTimerEventCount();
			}
			break;
		}
	}
}


int main(int argc, char* argv[])
{
	WindW = 800; WindH = 800;

	CreateLuncher();
	CreatePlain();

	CreateBarrier();

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



