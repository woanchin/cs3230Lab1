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

#define HALF 'H'
#define FULL 'F'
#define PI 3.142
#define TWICE_PI 2.0*3.142

void drawSuperTreeCurve()
{
	int x = 0,y = 0;
	double theta, nextTheta;
	double x1, y1;
	double x2, y2;

	//Draw Tree Top
	glLineWidth(2.0);
	glPushMatrix();
	glTranslatef(0,10.72,0);
	glScalef(5, 1, 1);
		glBegin(GL_LINE_STRIP); //begin circle
		for (int i = 0; i <= 159; i++)   {
			theta = (3.14259/180) * i;
			nextTheta = (3.14259 / 180) * (i+1);
			x1 = sin(theta); y1 = cos(theta);
			x2 = sin(nextTheta); y2 = cos(nextTheta);

			glVertex2f(x1, y1);
			glVertex2f(x2, y2);
			//	glVertex2f((i/360.0)*x1, (i/360.0)*y1);
			//	glVertex2f(((i + 1) / 360.0)*x2, ((i+1)/360.0)*y2);
		
		}
		glEnd();
	glPopMatrix();
	
	//Draw Tree Trunk
	glPushMatrix();
	glTranslatef(2, 0, 0);
	glScalef(1.5,10,1);
		glBegin(GL_LINE_STRIP); //begin circle
		for (int i = 270; i <= 347.5; i++)   {
			theta = (3.14259 / 180) * i;
			nextTheta = (3.14259 / 180) * (i + 1);
			x1 = sin(theta); y1 = cos(theta);
			x2 = sin(nextTheta); y2 = cos(nextTheta);

			glVertex2f(x1, y1);
			glVertex2f(x2, y2);
		}
		glEnd();
	glPopMatrix();
	
}

void drawMarina()
{

	int x = 0, y = 0;
	double theta, nextTheta;
	double x1, y1;
	double x2, y2;

	glRectd(0,0,4,15);

	glRectd(6,0, 10,15);

	glRectd(12,0, 16,15);

	glRectd(-2, 15, 17, 17);

	glPushMatrix();
	glLineWidth(1);
	glTranslatef(-2, 16,0);
	glBegin(GL_TRIANGLE_FAN); //begin circle
	for (int i = 180; i <= 360; i++)   {
		theta = (3.14259 / 180) * i;
		nextTheta = (3.14259 / 180) * (i + 1);
		x1 = sin(theta); y1 = cos(theta);
		x2 = sin(nextTheta); y2 = cos(nextTheta);

		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
	}
	glEnd();

	glPopMatrix();
}

void drawFlyer()
{

	
	int x = 0, y = 0;
	double theta, nextTheta;
	double x1, y1;
	double x2, y2;

	glLineWidth(1);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-0.5,0);
	glVertex2f(-0.5,13);
	glVertex2f(0.5,13);
	glVertex2f(0.5,0);
	glEnd();

	glPushMatrix();
	glTranslatef(0, 13, 0);
	glScalef(0.5, 0.5, 0.5);

	glBegin(GL_LINE_STRIP); //begin circle
	for (int i = 0; i <= 360; i++)   {
		theta = (3.14259 / 180) * i;
		nextTheta = (3.14259 / 180) * (i + 1);
		x1 = sin(theta); y1 = cos(theta);
		x2 = sin(nextTheta); y2 = cos(nextTheta);

		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 13, 0);
	glScalef(10,10,10);
	
	glBegin(GL_LINE_STRIP); //begin circle
	for (int i = 0; i <= 360; i++)   {
		theta = (3.14259 / 180) * i;
		nextTheta = (3.14259 / 180) * (i + 1);
		x1 = sin(theta); y1 = cos(theta);
		x2 = sin(nextTheta); y2 = cos(nextTheta);

		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0, 13, 0);
	glScalef(10.5, 10.5, 10.5);
	
	glBegin(GL_LINE_STRIP); //begin circle
	for (int i = 0; i <= 360; i++)   {
		theta = (3.14259 / 180) * i;
		nextTheta = (3.14259 / 180) * (i + 1);
		x1 = sin(theta); y1 = cos(theta);
		x2 = sin(nextTheta); y2 = cos(nextTheta);

		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();

	glColor3f(1,0,0);
	glPushMatrix();
	glTranslatef(0,13,0);
	for (int j = 0; j <= 360; j+=40)   {
		
		theta = (3.14259 / 180) * j;
		nextTheta = (3.14259 / 180) * (j + 1);
		x1 = sin(theta); y1 = cos(theta);
		x2 = sin(nextTheta); y2 = cos(nextTheta);
		
		glPushMatrix();
		glScalef(0.5,0.5,0.5);
		glTranslatef(22*x1, 22*y1,0);
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i <= 360; i++)   {
			theta = (3.14259 / 180) * i;
			nextTheta = (3.14259 / 180) * (i + 1);
			x1 = sin(theta); y1 = cos(theta);
			x2 = sin(nextTheta); y2 = cos(nextTheta);
			
			glVertex2f(x1, y1);
			glVertex2f(x2, y2);
		}
		glEnd();
		glPopMatrix();
	
		
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
	/*
	glPushMatrix();
		glTranslatef(-0.5,0,0);
		drawFork(2, 65, 1, 3.75);
	glPopMatrix();
	
	glPushMatrix();
		drawFork(1, 45, 2, 4);
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(0.5, 0, 0);
		glScalef(-1, 1, 1);
		drawFork(2, 65, 1, 3.75);
	glPopMatrix();
	*/
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
	glTranslatef(-10, 0, 0);
	glRotatef(-90,0,0,1);
	
	drawLine(60);
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
