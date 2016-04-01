// CS3241Lab4.cpp : Defines the entry point for the console application.
//#include <cmath>
#include "math.h"
#include <iostream>
#include <fstream>

/* Include header files depending on platform */
#ifdef _WIN32
#include "glut.h"
#define M_PI 3.14159
#elif __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/GLUT.h>
#endif

#define MAXPTNO 1000
#define NLINESEGMENT 32.0
#define NOBJECTONCURVE 6

using namespace std;

// Global variables that you can use
struct Point {
	int x, y;
};

// Storage of control points
int nPt = 0;
Point ptList[MAXPTNO];
Point continuousPtList[MAXPTNO];

// Display options
bool displayControlPoints = true;
bool displayControlLines = true;
bool displayTangentVectors = false;
bool displayObjects = false;
bool C1Continuity = false;

void drawRightArrow()
{
	glColor3f(0, 1, 0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(0, 0);
	glVertex2f(100, 0);
	glVertex2f(95, 5);
	glVertex2f(100, 0);
	glVertex2f(95, -5);
	glEnd();
}

//refactored method for making continuous or discontinuous curves
void makingXY(Point pointType[MAXPTNO], int i, double t) {
	double x, y;
	//p00x,p01x,p02x,p03x symbolises the control points for x. this concept is the same for the y control points below
	double p00x = pointType[i].x;
	double p01x = pointType[i + 1].x;
	double p02x = pointType[i + 2].x;
	double p03x = pointType[i + 3].x;
	
	//equation for drawing the bezier curve
	x = pow(1 - t, 3) * p00x + 3 * pow(1 - t, 2) * t * p01x + 3 * (1 - t) * pow(t, 2) * p02x + pow(t, 3) * p03x;

	double p00y = pointType[i].y;
	double p01y = pointType[i + 1].y;
	double p02y = pointType[i + 2].y;
	double p03y = pointType[i + 3].y;

	y = pow(1 - t, 3) * p00y + 3 * pow(1 - t, 2) * t * p01y + 3 * (1 - t) * pow(t, 2) * p02y + pow(t, 3) * p03y;

	glVertex2f(x, y);
}

void drawNonContinuous() {
	glColor3f(0, 0, 1);
	for (int i = 0; i + 3 < nPt; i += 3) {
		glBegin(GL_LINE_STRIP);
		for (double t = 0; t <= 1; t += 1.0 / NLINESEGMENT) {
			makingXY(ptList, i, t);
		}
		glEnd();
	}
}

void drawContinuous() {
	glColor3f(0, 0, 1);
	for (int i = 0; i + 3 < nPt; i += 3) {
		glBegin(GL_LINE_STRIP);
		for (double t = 0; t <= 1; t += 1.0 / NLINESEGMENT) {
			makingXY(continuousPtList, i, t);
		}
		glEnd();
	}

}

void drawTangents() {
	for (int i = 0; i + 3 < nPt; i += 3){
		for (double t = 0; t < 1; t = t + 1.0 / NOBJECTONCURVE){
			double dx, dy, x, y, p00x, p01x, p02x, p03x, p00y, p01y, p02y, p03y;
			
			if (C1Continuity){
				p00x = continuousPtList[i].x;
				p01x = continuousPtList[i + 1].x;
				p02x = continuousPtList[i + 2].x;
				p03x = continuousPtList[i + 3].x;

				p00y = continuousPtList[i].y;
				p01y = continuousPtList[i + 1].y;
				p02y = continuousPtList[i + 2].y;
				p03y = continuousPtList[i + 3].y;			
			}
			else {
				p00x = ptList[i].x;
				p01x = ptList[i + 1].x;
				p02x = ptList[i + 2].x;
				p03x = ptList[i + 3].x;

				p00y = ptList[i].y;
				p01y = ptList[i + 1].y;
				p02y = ptList[i + 2].y;
				p03y = ptList[i + 3].y;
			}

			//differentiated equation for drawing the tangent of the bezier curve at a particular point t
			dx = -3 * pow(1 - t, 2)*p00x + (3 * pow(1 - t, 2) - 6 * (1 - t)*t)*p01x + (6 * (1 - t)*t - 3 * pow(t, 2))*p02x + 3 * pow(t, 2)*p03x;
			dy = -3 * pow(1 - t, 2)*p00y + (3 * pow(1 - t, 2) - 6 * (1 - t)*t)*p01y + (6 * (1 - t)*t - 3 * pow(t, 2))*p02y + 3 * pow(t, 2)*p03y;

			x = pow(1 - t, 3) * p00x + 3 * pow(1 - t, 2) * t * p01x + 3 * (1 - t) * pow(t, 2) * p02x + pow(t, 3) * p03x;
			y = pow(1 - t, 3) * p00y + 3 * pow(1 - t, 2) * t * p01y + 3 * (1 - t) * pow(t, 2) * p02y + pow(t, 3) * p03y;

			glPushMatrix();
			glTranslatef(x, y, 0);
			double result = atan(dy / dx) * 180 / M_PI;

			if (dx < 0) {
				glRotatef(result + 180, 0, 0, 1);
			}
			else {
				glRotatef(result, 0, 0, 1);
			}

			drawRightArrow();
			glPopMatrix();
		}
	}
}

void drawSemicircle() {
	double theta, nextTheta;
	double x1, y1;
	double x2, y2;

	glColor3f(0,0,0);
	glBegin(GL_LINE_STRIP);
	for (int i = 180; i < 360; i++) {	
		theta = (3.14259 / 180) * i;
		nextTheta = (3.14259 / 180) * (i + 1);
		x1 = sin(-theta); y1 = cos(-theta);
		x2 = sin(-nextTheta); y2 = cos(-nextTheta);

		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
	}
	glEnd();
}

void drawB() {

	glPushMatrix();
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(0, 0);
	glVertex2f(0, 100);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,25,0);
	glScalef(25,25,25);
	drawSemicircle();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 75, 0);
	glScalef(25, 25, 25);
	drawSemicircle();
	glPopMatrix();

}

void drawE() {
	glColor3f(0, 0, 0);
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	glVertex2f(0, 0);
	glVertex2f(0, 100);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 100, 0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(0, 0);
	glVertex2f(30, 0);
	glEnd();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0, 50, 0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(0, 0);
	glVertex2f(25, 0);
	glEnd();
	glPopMatrix();
	
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	glVertex2f(0, 0);
	glVertex2f(30, 0);
	glEnd();
	glPopMatrix();
}

void drawL() {
	glColor3f(0, 0, 0);
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	glVertex2f(0, 0);
	glVertex2f(0, 100);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 100, 0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(0, 0);
	glVertex2f(30, 0);
	glEnd();
	glPopMatrix();
}

void drawBELL() {
	for (int i = 0; i + 3 < nPt; i += 3){
		for (double t = 0; t < 1; t = t + 1.0 / NOBJECTONCURVE){
			double dx, dy, x, y, p00x, p01x, p02x, p03x, p00y, p01y, p02y, p03y;

			if (C1Continuity){
				p00x = continuousPtList[i].x;
				p01x = continuousPtList[i + 1].x;
				p02x = continuousPtList[i + 2].x;
				p03x = continuousPtList[i + 3].x;

				p00y = continuousPtList[i].y;
				p01y = continuousPtList[i + 1].y;
				p02y = continuousPtList[i + 2].y;
				p03y = continuousPtList[i + 3].y;
			}
			else {
				p00x = ptList[i].x;
				p01x = ptList[i + 1].x;
				p02x = ptList[i + 2].x;
				p03x = ptList[i + 3].x;

				p00y = ptList[i].y;
				p01y = ptList[i + 1].y;
				p02y = ptList[i + 2].y;
				p03y = ptList[i + 3].y;
			}

			dx = -3 * pow(1 - t, 2)*p00x + (3 * pow(1 - t, 2) - 6 * (1 - t)*t)*p01x + (6 * (1 - t)*t - 3 * pow(t, 2))*p02x + 3 * pow(t, 2)*p03x;
			dy = -3 * pow(1 - t, 2)*p00y + (3 * pow(1 - t, 2) - 6 * (1 - t)*t)*p01y + (6 * (1 - t)*t - 3 * pow(t, 2))*p02y + 3 * pow(t, 2)*p03y;

			x = pow(1 - t, 3) * p00x + 3 * pow(1 - t, 2) * t * p01x + 3 * (1 - t) * pow(t, 2) * p02x + pow(t, 3) * p03x;
			y = pow(1 - t, 3) * p00y + 3 * pow(1 - t, 2) * t * p01y + 3 * (1 - t) * pow(t, 2) * p02y + pow(t, 3) * p03y;

			glPushMatrix();

			glTranslatef(x, y, 0);
			double result = atan(dy / dx) * 180 / M_PI;
			if (dx < 0) {
				glRotatef(result + 180, 0, 0, 1);
			}
			else {
				glRotatef(result, 0, 0, 1);
			}

			glPushMatrix();
			glScalef(0.35, 0.35, 0.35);
			drawB();

			glPushMatrix();
			glTranslatef(30, 0, 0);
			drawE();
			glPopMatrix();

			glPushMatrix();
			glTranslatef(60, 0, 0);
			drawL();
			glPopMatrix();

			glPushMatrix();
			glTranslatef(90, 0, 0);
			drawL();
			glPopMatrix();
			glPopMatrix();
			glPopMatrix();
		}
	}
}

			
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	if (displayControlPoints)
	{
		glPointSize(5);
		glBegin(GL_POINTS);
		for (int i = 0; i<nPt; i++)
		{
			if (C1Continuity && i > 1 && i % 3 == 1) {
				glColor3f(0.8, 0.8, 0.8);
				glVertex2d(ptList[i].x, ptList[i].y);

				glColor3f(1, 0, 0);
				glVertex2d(continuousPtList[i].x, continuousPtList[i].y);
			}
			else {
				glColor3f(0, 0, 0);
				glVertex2d(ptList[i].x, ptList[i].y);
			}
		}
		glEnd();
		glPointSize(1);

	}

	if (displayControlLines)
	{
		for (int i = 0; i < nPt - 1; i++) {
			glColor3f(0, 1, 0);
			glBegin(GL_LINE_STRIP);
			if (C1Continuity) {
				glVertex2d(continuousPtList[i].x, continuousPtList[i].y);
				glVertex2d(continuousPtList[i + 1].x, continuousPtList[i + 1].y);
			}
			else {
				glVertex2d(ptList[i].x, ptList[i].y);
				glVertex2d(ptList[i + 1].x, ptList[i + 1].y);
			}
			glEnd();
		}
	}

	if (C1Continuity) {
		drawContinuous();
	}
	else {
		drawNonContinuous();
	}

	if (displayTangentVectors) {
		drawTangents();
	}

	if (displayObjects){
		drawBELL();
	}
	glPopMatrix();
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, h, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
}

void readFile()
{

	std::ifstream file;
	file.open("savefile.txt");
	file >> nPt;

	if (nPt>MAXPTNO)
	{
		cout << "Error: File contains more than the maximum number of points." << endl;
		nPt = MAXPTNO;
	}

	for (int i = 0; i<nPt; i++)
	{
		file >> ptList[i].x;
		file >> ptList[i].y;

		if (i > 1 && i % 3 == 1) {
			continuousPtList[i].x = 2 * ptList[i - 1].x - ptList[i - 2].x;
			continuousPtList[i].y = 2 * ptList[i - 1].y - ptList[i - 2].y;
		}
		else {
			continuousPtList[i].x = ptList[i].x;
			continuousPtList[i].y = ptList[i].y;
		}
	}
	file.close();// is not necessary because the destructor closes the open file by default
}

void writeFile()
{
	std::ofstream file;
	file.open("savefile.txt");
	file << nPt << endl;

	for (int i = 0; i<nPt; i++)
	{
		file << ptList[i].x << " ";
		file << ptList[i].y << endl;
	}
	file.close();// is not necessary because the destructor closes the open file by default
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {

	case 'r':
	case 'R':
		readFile();
		break;

	case 'w':
	case 'W':
		writeFile();
		break;

	case 'T':
	case 't':
		displayTangentVectors = !displayTangentVectors;
		break;

	case 'o':
	case 'O':
		displayObjects = !displayObjects;
		break;

	case 'p':
	case 'P':
		displayControlPoints = !displayControlPoints;
		break;

	case 'L':
	case 'l':
		displayControlLines = !displayControlLines;
		break;

	case 'C':
	case 'c':
		C1Continuity = !C1Continuity;
		break;

	case 'e':
	case 'E':
		nPt = 0;
		break;

	case 27:
		exit(0);
		break;

	default:
		break;
	}

	glutPostRedisplay();
}



void mouse(int button, int state, int x, int y)
{
	/*button: GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, or GLUT_RIGHT_BUTTON */
	/*state: GLUT_UP or GLUT_DOWN */
	enum
	{
		MOUSE_LEFT_BUTTON = 0,
		MOUSE_MIDDLE_BUTTON = 1,
		MOUSE_RIGHT_BUTTON = 2,
		MOUSE_SCROLL_UP = 3,
		MOUSE_SCROLL_DOWN = 4
	};
	if ((button == MOUSE_LEFT_BUTTON) && (state == GLUT_UP))
	{
		if (nPt == MAXPTNO)
		{
			cout << "Error: Exceeded the maximum number of points." << endl;
			return;
		}
		
		ptList[nPt].x = x;
		ptList[nPt].y = y;

		if (nPt > 1 && nPt % 3 == 1) {
			continuousPtList[nPt].x = 2* ptList[nPt - 1].x - ptList[nPt - 2].x;
			continuousPtList[nPt].y = 2* ptList[nPt - 1].y - ptList[nPt - 2].y;
		}
		else {
			continuousPtList[nPt].x = x;
			continuousPtList[nPt].y = y;
		}
		nPt++;
	}
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	cout << "CS3241 Lab 4" << endl << endl;
	cout << "Left mouse click: Add a control point" << endl;
	cout << "ESC: Quit" << endl;
	cout << "P: Toggle displaying control points" << endl;
	cout << "L: Toggle displaying control lines" << endl;
	cout << "E: Erase all points (Clear)" << endl;
	cout << "C: Toggle C1 continuity" << endl;
	cout << "T: Toggle displaying tangent vectors" << endl;
	cout << "O: Toggle displaying objects" << endl;
	cout << "R: Read in control points from \"savefile.txt\"" << endl;
	cout << "W: Write control points to \"savefile.txt\"" << endl;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("CS3241 Assignment 4");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 0;
}
