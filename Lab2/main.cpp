// CS3241Lab2.cpp : Defines the entry point for the console application.
#include <cmath>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <Windows.h>
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

#define numStars 100
#define numPlanets 9

float alpha = 0.0, k = 1;
float tx = 0.0, ty = 0.0;
float PI = 3.14;

float ellipticPinkRotate, ellipticPurpleRotate = 0;
float circleRed, circleBlue, circleViolet, circleForest = 0;
float circleSateViolet = 0;
float jumping = 0;
float transparency = 0;
float prevJumping = -1;
float turningSatellite = 0;
float secPlanet, minPlanet, hourPlanet = 0;

GLfloat ellipticColPink[] = { 255.0 / 255.0, 228.0 / 255.0, 225.0 / 255.0, 1 };
GLfloat ellipticColPurple[] = { 104.0 / 255.0, 34.0 / 255.0, 139.0 / 255.0, 1 };
GLfloat ellipticColYellow[] = { 1, 1, 0 };

GLfloat centerColBlue[] = { 100.0 / 255.0, 149.0 / 255.5, 237.0 / 255.0, 1 };
GLfloat centerColRedOrange[] = { 255.0 / 255.0, 30.0 / 255.0, 0, 1 };
GLfloat centerColViolet[] = { 176.0 / 255.0, 48.0 / 255.0, 96.0 / 255.0, 1 };
GLfloat centerColForest[] = { 0, 80.0 / 255.0, 0, 1 };

GLfloat circleSateColViolet[] = { 131.0 / 255.0, 139.0 / 255.0, 139.0 / 255.0, 1 };
GLfloat circleSateJumpCol[] = { 1, 1, 1, 1 };
GLboolean clockActivate = false;
GLfloat color[4];

void drawDisk(float size, GLfloat color[4]) {
	int x = 0, y = 0;
	double theta, nextTheta;
	double x1, y1;
	double x2, y2;

	glColor4f(color[0], color[1], color[2], color[3]);
	glScalef(size, size, 0);
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i <= 360; i++) {
		glVertex2f(0, 0);
		theta = (3.14259 / 180) * i;
		nextTheta = (3.14259 / 180) * (i + 1);
		x1 = sin(theta); y1 = cos(theta);
		x2 = sin(nextTheta); y2 = cos(nextTheta);

		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
	}
	glEnd();
}

class planet
{
public:
	float distFromRefX;
	float angularSpeed;
	GLfloat color[3];
	float size;
	float angle;

	planet()
	{
		distFromRefX = 0;
		angularSpeed = 0;
		color[0] = color[1] = color[2] = 0;
		size = 0;
		angle = 0;
	}

	void setDistance(float, float);
	void setEllipticDistance(float, float);
	void setSize(float);
	void setAngle(float);
	void setAngularSpeed(float);
	void drawCircle(float, float, float, float, GLfloat[]);
	void drawCircleSatellite(float, float, float, GLfloat[], float, float, float, GLfloat[]);
	void drawCircleSatelliteJump(float, float, float, GLfloat[], float, float, float, GLfloat[]);
	void drawElliptical(float, float, float, GLfloat[], float, float);
	void drawEllipticalSatellite(float, float, float, GLfloat[], float, float, float, GLfloat[]);

};

void planet::setDistance(float x, float y) {
	distFromRefX = x;
	glTranslatef(x, y, 0);
}

void planet::setEllipticDistance(float x, float y) {
	distFromRefX = x;
	float angularSpeedRad = angularSpeed*(PI / 180);
	glTranslatef(cos(angularSpeedRad)*x, sin(angularSpeedRad)*y, 0);
}

void planet::setSize(float x) {
	size = PI*x*x;
	glScalef(x, x, 0);
}

void planet::setAngle(float x) {
	angle = x;
	glRotatef(x, 0, 0, 1);
}

void planet::setAngularSpeed(float x) {
	angularSpeed = x;
}

void planet::drawCircle(float size, float x, float y, float orbit, GLfloat color[4]) {
	setAngle(orbit);

	glPushMatrix();
	setDistance(x, y);
	drawDisk(size, color);
	glPopMatrix();
}

void planet::drawCircleSatellite(float size, float x, float orbit, GLfloat color[4],
						    float sateSize, float sateX, float sateOrbit, GLfloat sateColor[4]) {
	setAngle(orbit);

	glPushMatrix();
		setDistance(x, x);
		drawDisk(size, color);
		setAngle(sateOrbit);
		glPushMatrix();
			setDistance(sateX, sateX);

			drawDisk(sateSize, sateColor);
		glPopMatrix();
	glPopMatrix();
}

void planet::drawCircleSatelliteJump(float size, float x, float orbit, GLfloat color[4],
	float sateSize, float sateX, float jumping, GLfloat sateColor[4]) {
	setAngle(orbit);

	glPushMatrix();
		setDistance(x, x);
		drawDisk(size, color);
		glPushMatrix();
			setDistance(sateX, sateX + 2 + sin(jumping)*2);

			drawDisk(sateSize, sateColor);
		glPopMatrix();
	glPopMatrix();
}

void planet::drawElliptical(float size, float dx, float dy, GLfloat color[4], float inclination, float orbit) {
	glPushMatrix();
		setEllipticDistance(dx, dy);
		
		setAngularSpeed(orbit);

		drawDisk(size, color);
	glPopMatrix();
}

planet planetList[numPlanets];

void drawStars(float transparency) {
	glPushMatrix();
		glScalef(1, 1, 0);
		glColor4f(1, 1, 1, sin(transparency));
	
		glBegin(GL_POLYGON);
			glVertex2f(0,0);
			glVertex2f(0,0.2);
			glVertex2f(0.2, 0.2);
			glVertex2f(0.2,0);
		glEnd();

		glBegin(GL_POLYGON);
			glVertex2f(4, 4);
			glVertex2f(4, 4.2);
			glVertex2f(4.2, 4.2);
			glVertex2f(4.2, 4);
		glEnd();
	
		glBegin(GL_POLYGON);
			glVertex2f(-10.8, -11);
			glVertex2f(-10.8, -11.2);
			glVertex2f(-11, -11.2);
			glVertex2f(-11, -11);
		glEnd();

		glBegin(GL_POLYGON);
			glVertex2f(7.5, 7.7);
			glVertex2f(7.5, 7.9);
			glVertex2f(7.7, 7.9);
			glVertex2f(7.7, 7.7);
		glEnd();

		glBegin(GL_POLYGON);
			glVertex2f(0, 5);
			glVertex2f(0, 5.2);
			glVertex2f(0.2, 5.2);
			glVertex2f(0.2, 5);
		glEnd();
	glPopMatrix();

}
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-20, 20, -20, 20, -20, 20);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.3, 1.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


void clockOn() {
	time_t seconds = time(NULL);
	struct tm * timeinfo = localtime(&seconds);

	minPlanet = (float)timeinfo->tm_min * 6;
	glPushMatrix();
	if (timeinfo->tm_hour > 12)
		hourPlanet = ((float)timeinfo->tm_hour - 12) * 30;
	else
		hourPlanet = (float)timeinfo->tm_hour * 30;

	secPlanet = (float)timeinfo->tm_sec * 6;
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

		//controls transformation
		glScalef(k, k, k);
		glTranslatef(tx, ty, 0);
		glRotatef(alpha, 0, 0, 1);

		//draw stuff here!
		//drawing Stars
		glPushMatrix();
			drawStars(transparency);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(5, 0, 0);
			drawStars(transparency);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-5, -2, 0);
			drawStars(transparency);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(3, 6, 0);
			drawStars(transparency);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-2, 10, 0);
			drawStars(transparency);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-9, 3, 0);
			drawStars(transparency);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(10, -10, 0);
			drawStars(transparency);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(10, 10, 0);
			drawStars(transparency);
		glPopMatrix();
		//end of draw Stars;

		if (clockActivate) {
			clockOn();
			glPushMatrix();
				planetList[5].drawCircle(0.6, 0, 10, -secPlanet, centerColBlue);
			glPopMatrix();
			glPushMatrix();
				planetList[6].drawCircle(0.7, 0, 8, -minPlanet, ellipticColPurple);
			glPopMatrix();
			glPushMatrix();
				planetList[7].drawCircle(0.5, 0, 5, -hourPlanet, ellipticColPink);
			glPopMatrix();
			glPushMatrix();
				planetList[0].drawCircle(2, 0, 0, circleRed, centerColRedOrange);
			glPopMatrix();
		} else {
			glPushMatrix();
				planetList[1].drawElliptical(0.5, 5, 10, ellipticColPink, 135, ellipticPinkRotate);
			glPopMatrix();
			glPushMatrix();
				planetList[2].drawElliptical(0.7, -10, -15, ellipticColPurple, 100, ellipticPurpleRotate);
			glPopMatrix();
		
			glPushMatrix();
				planetList[3].drawCircle(0.6, 4, 4, circleBlue, centerColBlue);
			glPopMatrix();
			glPushMatrix();
				planetList[8].drawCircleSatellite(0.8, 8, circleViolet, centerColViolet, 0.2, 1, circleSateViolet, circleSateColViolet);
			glPopMatrix();
			glPushMatrix();
				planetList[8].drawCircleSatelliteJump(0.8, 8, circleForest, centerColForest, 0.2, 1, jumping, circleSateJumpCol);
			glPopMatrix();
			glPushMatrix();
				planetList[0].drawCircle(2, 0, 0, circleRed, centerColRedOrange);
			glPopMatrix();
		}

	glPopMatrix();

	glFlush();
}

void idle()
{
	//update animation here
	if (clockActivate) {
		transparency += 0.001;
		secPlanet += 6;

		if (secPlanet == 360) {
			secPlanet = 0;
			minPlanet += 6;
			if (minPlanet == 360) {
				minPlanet = 0;
				hourPlanet += 1;
			}
			if (hourPlanet == 12) {
				hourPlanet = 0;
			}
		}
	}
	else {
		ellipticPinkRotate += 0.075;
		ellipticPurpleRotate += 0.01;
		circleRed += 0.04;
		circleForest += 0.05;
		circleBlue += 0.05;
		circleViolet += 0.02;
		circleSateViolet -= 0.1;
		jumping += 0.005;
		transparency += 0.001;
	}	

	glutPostRedisplay();	//after updating, draw the screen again
}

void keyboard(unsigned char key, int x, int y)
{
	//keys to control scaling - k
	//keys to control rotation - alpha
	//keys to control translation - tx, ty
	switch (key) {

	case 'a':
		alpha += 10;
		glutPostRedisplay();
		break;

	case 'd':
		alpha -= 10;
		glutPostRedisplay();
		break;

	case 'q':
		k += 0.1;
		glutPostRedisplay();
		break;

	case 'e':
		if (k>0.1)
			k -= 0.1;
		glutPostRedisplay();
		break;

	case 'z':
		tx -= 0.1;
		glutPostRedisplay();
		break;

	case 'c':
		tx += 0.1;
		glutPostRedisplay();
		break;

	case 's':
		ty -= 0.1;
		glutPostRedisplay();
		break;

	case 'w':
		ty += 0.1;
		glutPostRedisplay();
		break;

	case 't':
		clockActivate = !clockActivate;
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
	cout << "CS3241 Lab 2\n\n";
	cout << "+++++CONTROL BUTTONS+++++++\n\n";
	cout << "Scale Up/Down: Q/E\n";
	cout << "Rotate Clockwise/Counter-clockwise: A/D\n";
	cout << "Move Up/Down: W/S\n";
	cout << "Move Left/Right: Z/C\n";
	cout << "ESC: Quit\n";

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(50, 50);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	//glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 0;
}
