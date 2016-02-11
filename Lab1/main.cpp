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

float animateTreeTop = 159;
float animateTrunk = 347.5;
float animateMarinaBuilding = 0;
float animateMarinaHoriBuilding = -2;
float animateMarinaTop = 360;
float animateFlyerWheel = 360;
float animateFlyerWheelTwo = 360;
float animateFlyerCarriage = 360;
float animateFlyerStick = 0;
float animateLine = 60;
float timeLine = 0;

float counter = 0.05;

void makeCircle(int i) {

	int x = 0, y = 0;
	double theta, nextTheta;
	double x1, y1;
	double x2, y2;

	glBegin(GL_LINE_STRIP);
	theta = (3.14259 / 180) * i;
	nextTheta = (3.14259 / 180) * (i + 1);
	x1 = sin(theta); y1 = cos(theta);
	x2 = sin(nextTheta); y2 = cos(nextTheta);

	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
}

void drawSuperTreeCurve()
{
	//Draw Tree Top
	glLineWidth(2.0);
	glPushMatrix();
		glTranslatef(0,10.72,0);
		glScalef(5, 1, 1);
	
	for (int i = 0; i <= 159-animateTreeTop; i++)   {
			makeCircle(i);
		}
	glPopMatrix();
	
	//Draw Tree Trunk
	glPushMatrix();
		glTranslatef(2, 0, 0);
		glScalef(1.5,10,1);
			 
		for (int i = 270; i <= 347.5-animateTrunk; i++)   {
			makeCircle(i);
		}		
	glPopMatrix();
	
	if (animateTreeTop >= 0 || animateTrunk >=0) {
		animateTreeTop -= counter;
	}
}

void drawMarina()
{

	glColor3f(1,0,0);
	
	glBegin(GL_LINE_STRIP);
		glVertex2f(0, 0);
		glVertex2f(0,animateMarinaBuilding);
	glEnd();

	glBegin(GL_LINE_STRIP);
		glVertex2f(4, 15);
		glVertex2f(4,15 - animateMarinaBuilding);
	glEnd();

	glBegin(GL_LINE_STRIP);
		glVertex2f(6,0);
		glVertex2f(6,animateMarinaBuilding);
	glEnd();

	glBegin(GL_LINE_STRIP);
		glVertex2f(10,15);
		glVertex2f(10, 15 - animateMarinaBuilding);
	glEnd();

	glBegin(GL_LINE_STRIP);
		glVertex2f(12,0);
		glVertex2f(12,animateMarinaBuilding);
	glEnd();

	glBegin(GL_LINE_STRIP);
		glVertex2f(16,15);
		glVertex2f(16, 15 - animateMarinaBuilding);
	glEnd();

	if (animateMarinaBuilding <= 15) {
		animateMarinaBuilding += 0.005;
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
		animateMarinaHoriBuilding += 0.005;
	}

	glPushMatrix();
		glLineWidth(2);
		glTranslatef(-2, 15.5,0);
		glScalef(0.5,0.5,0.5);
		if (animateMarinaTop >= 0) {
			animateMarinaTop -= counter*2;
		}
		 
		for (int i = 180; i <= 360 -animateMarinaTop; i++)   {
			makeCircle(i);
		}
	glPopMatrix();
}

void drawFlyer()
{
	glLineWidth(1);
	
	glBegin(GL_LINE_STRIP);
		glVertex2f(-0.5,0);
		glVertex2f(-0.5,animateFlyerStick);
	glEnd();

	glBegin(GL_LINE_STRIP);
		glVertex2f(0.5,0);
		glVertex2f(0.5,animateFlyerStick);
	glEnd();

	if (animateFlyerStick <= 13) {
		animateFlyerStick += 0.005;
	}

	glPushMatrix();
		glTranslatef(0, 13, 0);
		glScalef(0.5, 0.5, 0.5);
	
		//making small circle in the middle
		for (int i = 0; i <= 360; i++)   {
			makeCircle(i);
		}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 13, 0);
	glScalef(10,10,10);

	//make flyer wheel
	for (int i = 0; i <= 360 - animateFlyerWheel; i++)   {
		makeCircle(i); 
	}

	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0, 13, 0);
	glScalef(10.5, 10.5, 10.5);
	
	//make flyer wheel
	for (int i = 0; i <= 360 - animateFlyerWheel; i++)   {
		makeCircle(i);
	}
	glPopMatrix();

	int x = 0, y = 0;
	double theta, nextTheta;
	double x1, y1;
	double x2, y2;

	glColor3f(1,0,0);
	glPushMatrix();
	glTranslatef(0,13,0);

	for (int j = 0; j <= 360 - animateFlyerWheel; j+=40)   {
		
		theta = (3.14259 / 180) * j;
		nextTheta = (3.14259 / 180) * (j + 1);
		x1 = sin(theta); y1 = cos(theta);
		x2 = sin(nextTheta); y2 = cos(nextTheta);
		
		glPushMatrix();
		
		glTranslatef(11*x1, 11*y1,0);
		glScalef(0.5, 0.5, 0.5);
		for (int i = 0; i <= 360; i++)   {
			makeCircle(i);
		}

		glPopMatrix();
	
		
	}

	if (animateFlyerWheel >= 0) {
		animateFlyerWheel -= counter * 2;
	}

	glPopMatrix();
	

}
void drawLine(double length)
{

	glBegin(GL_LINE_STRIP);
	glColor3f(1.0, 0, 0);
	glVertex2f(0, 0);
	glVertex2f(0, length);
	glEnd();

}

void drawFork(int n, int degree, int toFork, double lengthOfLine)
{

	drawLine(lengthOfLine);
	if (n==0) return;
	
	glPushMatrix();
		glTranslatef(0,lengthOfLine,0);
		glPushMatrix();
			glRotatef(degree, 0, 0, 1);
			glScalef(0.55, 0.55, 0.55);
			drawFork(n-1, degree-10, toFork-1, lengthOfLine-0.25);
		glPopMatrix();
		
		if (toFork%2==0) { //if we want a fork to occur
			glPushMatrix();
				glRotatef(-degree, 0, 0, 1);
				glScalef(0.55, 0.55, 0.55);
				drawFork(n - 1, degree - 10, toFork-1, lengthOfLine - 0.25);
			glPopMatrix();
		}
	
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

	//controls transformation
	glScalef(k, k, k);	
	glTranslatef(tx, ty, 0);	
	glRotatef(alpha, 0, 0, 1);
	
	//draw your stuff here
	glPushMatrix();
	if (animateLine >= 0) {
		animateLine -= counter/3;
	}
	glTranslatef(-10, 0, 0);
	glRotatef(-90,0,0,1);
	drawLine(60-animateLine);
	glPopMatrix();

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

	glPushMatrix();
	glTranslatef(10,0,0);
	drawMarina();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(40, 0, 0);
	drawFlyer();
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
	glClearColor (1.0, 1.0, 1.0, 1.0);
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
