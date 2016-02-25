// CS3241Lab1.cpp : Defines the entry point for the console application.
#include <cmath>
#include <iostream>

/* Include header files depending on platform */
#ifdef _WIN32
	#include "glut.h"
	#define M_PI 3.14159
#elif __APPLE__
	#include <OpenGL/gl.h>
	#include <GLUT/GLUT.h>
#endif

using namespace std;

float alpha = 0.0, k=1;
float tx = 0.0, ty=0.0;

float animateFire = 0;
float animateTreeTop = 159;
float animateTrunk = 347.5;
float animateMarinaBuilding = 0;
float animateMarinaHoriBuilding = -2;
float animateMarinaTop = 360;
float animateFlyerWheel = 360;
float animateFlyerStick = 0;
float animateLine = 62;
float timeLine = 0;
float turningXOne = 0;

float counter = 0.05;

void makeCircle(int i, char type) {

	int x = 0, y = 0;
	double theta, nextTheta;
	double x1, y1;
	double x2, y2;

	if (type == GL_LINE_STRIP) {
	glBegin(type);
		theta = (3.14259 / 180) * i;
		nextTheta = (3.14259 / 180) * (i + 1);
		x1 = sin(theta); y1 = cos(theta);
		x2 = sin(nextTheta); y2 = cos(nextTheta);

		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
	glEnd();
	}
	else if (type == GL_TRIANGLE_STRIP) {
		glBegin(type);
		glVertex2f(0,0);
		theta = (3.14259 / 180) * i;
		nextTheta = (3.14259 / 180) * (i + 1);
		x1 = sin(theta); y1 = cos(theta);
		x2 = sin(nextTheta); y2 = cos(nextTheta);

		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
		glEnd();
	}
}

void drawSuperTreeCurve()
{
	//Draw Tree Top
	glPushMatrix();
		glTranslatef(0,10.72,0);
		glScalef(5, 1, 1);
	
	for (int i = 0; i <= 159-animateTreeTop; i++)   {
			makeCircle(i, GL_LINE_STRIP);
	}
	glPopMatrix();
	
	//Draw Tree Trunk
	glPushMatrix();
		glTranslatef(2, 0, 0);
		glScalef(1.5,10,1);
			 
		for (int i = 270; i <= 347.5-animateTrunk; i++)   {
			makeCircle(i, GL_LINE_STRIP);
		}		
	glPopMatrix();
	
	if (animateTreeTop >= 0) {
		animateTreeTop -= counter/2;
		
	}
	 
	if (animateTrunk >= 0) {
		animateTrunk -= counter;
	}
}

void drawMarina()
{
	glColor3f(1, 0, 0);
	glBegin(GL_LINE_STRIP);
		glVertex2f(0, 0);
		glVertex2f(0,animateMarinaBuilding);
	glEnd();

	glBegin(GL_LINE_STRIP);
		glVertex2f(4, 15);
		glVertex2f(4,15 - animateMarinaBuilding);
	glEnd();

	for (int i = 0; i <= 14; i += 2) {
		glColor3f(0.9, 0.0, 0.1);
		glRectf(0, i, 4, i+1);
	}

	glBegin(GL_LINE_STRIP);
		glVertex2f(6,0);
		glVertex2f(6,animateMarinaBuilding);
	glEnd();

	glBegin(GL_LINE_STRIP);
		glVertex2f(10,15);
		glVertex2f(10, 15 - animateMarinaBuilding);
	glEnd();

	for (int i = 0; i <= 14; i += 2) {
		glColor3f(0.9, 0.0, 0.1);
		glRectf(6, i, 10, i + 1);
	}

	glBegin(GL_LINE_STRIP);
		glVertex2f(12,0);
		glVertex2f(12,animateMarinaBuilding);
	glEnd();

	glBegin(GL_LINE_STRIP);
		glVertex2f(16,15);
		glVertex2f(16, 15 - animateMarinaBuilding);
	glEnd();

	for (int i = 0; i <= 14; i += 2) {
		glColor3f(0.9, 0.0, 0.1);
		glRectf(12, i, 16, i + 1);
	}

	if (animateMarinaBuilding <= 15) {
		animateMarinaBuilding += 0.01;
	}
	
	glBegin(GL_LINE_STRIP);
		glVertex2f(-2, 15);
		glVertex2f(animateMarinaHoriBuilding,15);
	glEnd();

	glBegin(GL_LINE_STRIP);
		glVertex2f(17,16);
		glVertex2f(17,15);
	glEnd();

	glBegin(GL_LINE_STRIP);
		glVertex2f(17,16);
		glVertex2f(15 - animateMarinaHoriBuilding,16);
	glEnd();
	
	if (animateMarinaHoriBuilding <= 17) {
		animateMarinaHoriBuilding += 0.01;
	}

	glPushMatrix();
		glTranslatef(-2, 15.5,0);
		glScalef(0.5,0.5,0.5);
		if (animateMarinaTop >= 0) {
			animateMarinaTop -= counter*3;
		}
		 
		for (int i = 180; i <= 360 -animateMarinaTop; i++)   {
			makeCircle(i, GL_LINE_STRIP);
		}
	glPopMatrix();
}

void drawFlyer()
{
	glPushMatrix();
		glTranslatef(0, 13, 0);
		glScalef(10.5, 10.5, 10.5);
		glColor3f(0.9, 0.0, 0.1);

		//make flyer wheel
		for (int i = 0; i <= 360 - animateFlyerWheel; i++)   {
			makeCircle(i, GL_TRIANGLE_STRIP);
		}
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0, 13, 0);
		glScalef(10, 10, 10);

		//make flyer wheel
		glColor3f(1, 1, 1);
		for (int i = 0; i <= 360 - animateFlyerWheel; i++)   {
			makeCircle(i, GL_TRIANGLE_STRIP);
		}
	glPopMatrix();

	int x = 0, y = 0;
	double theta, nextTheta;
	double x1, y1;
	double x2, y2;
	
	glColor3f(1,0,0);
	glPushMatrix();
		glTranslatef(0,13,0);
		turningXOne += 0.1;
		
		if (animateFlyerWheel >= 0) {
			animateFlyerWheel -= counter * 5;
		} else {
			for (int j = 0; j <= 360; j += 30)   {
				theta = (3.14259 / 180) * j;
				nextTheta = (3.14259 / 180) * (j + turningXOne);
				x1 = sin(theta); y1 = cos(theta);
				x2 = sin(nextTheta); y2 = cos(nextTheta);

				glPushMatrix();
					glLineWidth(2);
					glTranslatef(11*x2, 11*y2, 0);

					glScalef(0.5, 0.5, 0.5);
					for (int i = 0; i <= 360; i++)   {
						makeCircle(i, GL_LINE_STRIP);
					}
				glPopMatrix();
			}

			
		}
	glPopMatrix();
	
	glLineWidth(1);
	glBegin(GL_LINE_STRIP);
		glVertex2f(-0.5, 0);
		glVertex2f(-0.5, animateFlyerStick);
	glEnd();

	glBegin(GL_LINE_STRIP);
		glVertex2f(0.5, 0);
		glVertex2f(0.5, animateFlyerStick);
	glEnd();

	if (animateFlyerStick <= 13) {
		animateFlyerStick += 0.01;
	}

	glPushMatrix();
		glTranslatef(0, 13, 0);
		glScalef(0.5, 0.5, 0.5);

		//making small circle in the middle
		for (int i = 0; i <= 360; i++)   {
			makeCircle(i, GL_LINE_STRIP);
		}
	glPopMatrix();
}

void drawLine(double length)
{
	glBegin(GL_LINE_STRIP);
		glVertex2f(0, 0);
		glVertex2f(0, length);
	glEnd();
}

void drawFireWorks() 
{
	if (animateFire <= 10) {
		animateFire += counter / 3;
	}
	else if (animateFire > 10) {
		animateFire = 0;
	}
	
	glPushMatrix();
		glRotatef(-45, 0, 0, 1);
		glTranslatef(0, animateFire, 0);
		drawLine(3);
	glPopMatrix();

	glPushMatrix();
		glRotatef(0, 0, 0, 1);
		glTranslatef(0, animateFire, 0);
		drawLine(3);
	glPopMatrix();

	glPushMatrix();
		glRotatef(45, 0, 0, 1);
		glTranslatef(0, animateFire, 0);
		drawLine(3);
	glPopMatrix();

	glPushMatrix();
		glRotatef(90, 0, 0, 1);
		glTranslatef(0, animateFire, 0);
		drawLine(3);
	glPopMatrix();

	glPushMatrix();
		glRotatef(135, 0, 0, 1);
		glTranslatef(0, animateFire, 0);
		drawLine(3);
	glPopMatrix();

	glPushMatrix();
		glRotatef(180,0,0,1);
		glTranslatef(0, animateFire, 0);
		drawLine(3);
	glPopMatrix();

	glPushMatrix();
		glRotatef(225, 0, 0, 1);
		glTranslatef(0, animateFire, 0);
		drawLine(3);
	glPopMatrix();

	glPushMatrix();
		glRotatef(270, 0, 0, 1);
		glTranslatef(0, animateFire, 0);
		drawLine(3);
	glPopMatrix();
}

void drawSuperTree() {
	glPushMatrix();
		drawSuperTreeCurve(); //draw one half of the tree
		glScalef(-1, 1, 1);
		drawSuperTreeCurve(); //draw the other half of the tree
	glPopMatrix();
	
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	glPushMatrix();

	glTranslatef(0, -25, 0);

		//controls transformation
		glScalef(k, k, k);	
		glTranslatef(tx, ty, 0);	
		glRotatef(alpha, 0, 0, 1);
	
		glTranslatef(-20, 0, 0);
		//draw your stuff here
		glPushMatrix();
			glColor3f(1,0,0);
			if (animateLine >= 0) {
				animateLine -= counter/2;
			}

			glTranslatef(-10, 0, 0);
			glRotatef(-90,0,0,1);
			drawLine(62-animateLine);
		glPopMatrix();

		glLineWidth(2.0);
		glPushMatrix();
			glColor3f(1.0, 0, 0);
			glTranslatef(-5,0,0);
			drawSuperTree();
		glPopMatrix();

		glPushMatrix();
			glColor3f(1.0,0,0);
			glTranslatef(-1,0,0);
			glScalef(0.5, 0.5, 0.5);
			drawSuperTree();
		glPopMatrix();

		glPushMatrix();
			glColor3f(1.0, 0, 0);
			glTranslatef(5, 0, 0);
			glScalef(0.7, 0.7, 0.7);
			drawSuperTree();
		glPopMatrix();

		glLineWidth(1.0);
		glPushMatrix();
			glTranslatef(10,0,0);
			drawMarina();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(40, 0, 0);
			drawFlyer();
		glPopMatrix();

		glPushMatrix();
		glColor3f(0.439, 0.858, 0.576);
			glTranslatef(0, 35, 0);
			drawFireWorks();
		glPopMatrix();

		glPushMatrix();
			glColor3f(1, 0.8, 0.5);
			glTranslatef(43, 45, 0);
			glScalef(0.5,0.5,0.5);
			drawFireWorks();
		glPopMatrix();

		glPushMatrix();
			glColor3f(1, 0.8, 0.5);
			glTranslatef(30, 40, 0);
			glScalef(0.7, 0.7, 0.7);
			drawFireWorks();
		glPopMatrix();

		glPushMatrix();
			glColor3f(0.439, 0.576, 0.858);
			glTranslatef(20, 30, 0);
			glScalef(0.7, 0.7, 0.7);
			drawFireWorks();
		glPopMatrix();

		glPushMatrix();
			glColor3f(0.1372, 0.5568, 0.419);
			glTranslatef(50, 30, 0);
			glScalef(0.4, 0.4, 0.4);
			drawFireWorks();
		glPopMatrix();

	glPopMatrix();

	glutPostRedisplay();
	glFlush();
}

void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-50, 50,-50,50,-50,50);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void init(void)
{
	glClearColor(1,1,1,1);
	glShadeModel (GL_SMOOTH);
}



void keyboard (unsigned char key, int x, int y)
{
	//keys to control scaling - k
	//keys to control rotation - alpha
	//keys to control translation - tx, ty
	switch (key) {

		case 'a':
			alpha+=10;
			glutPostRedisplay();
		break;

		case 'd':
			alpha-=10;
			glutPostRedisplay();
		break;

		case 'q':
			k+=0.1;
			glutPostRedisplay();
		break;

		case 'e':
			if(k>0.1)
				k-=0.1;
			glutPostRedisplay();
		break;

		case 'z':
			tx-=0.1;
			glutPostRedisplay();
		break;

		case 'c':
			tx+=0.1;
			glutPostRedisplay();
		break;

		case 's':
			ty-=0.1;
			glutPostRedisplay();
		break;

		case 'w':
			ty+=0.1;
			glutPostRedisplay();
		break;
			
		case 27:
			exit(0);
		break;

		default:
		break;
	}
}

int main(int argc, char **argv)
{
	cout<<"CS3241 Lab 1\n\n";
	cout<<"+++++CONTROL BUTTONS+++++++\n\n";
	cout<<"Scale Up/Down: Q/E\n";
	cout<<"Rotate Clockwise/Counter-clockwise: A/D\n";
	cout<<"Move Up/Down: W/S\n";
	cout<<"Move Left/Right: Z/C\n";
	cout <<"ESC: Quit\n";

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (600, 600);
	glutInitWindowPosition (50, 50);
	glutCreateWindow (argv[0]);
	init ();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	//glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 0;
}
