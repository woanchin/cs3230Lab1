// CS3241Lab3.cpp : Defines the entry point for the console application.
//#include <cmath>
#include "math.h"
#include <iostream>
#include <fstream>

#ifdef _WIN32
#include <Windows.h>
#include "glut.h"
#define M_PI 3.141592654
#elif __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/GLUT.h>
#endif

// global variable

bool m_Smooth = false;
bool m_Highlight = false;
GLfloat angle = 0;   /* in degrees */
GLfloat angle2 = 0;   /* in degrees */
GLfloat zoom = 1.0;
int mouseButton = 0;
int moving, startx, starty;

#define NO_OBJECT 4;
int current_object = 0;

using namespace std;

void setupLighting()
{
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);

	// Lights, material properties
	GLfloat	ambientProperties[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat	diffuseProperties[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat	specularProperties[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat lightPosition[] = { -100.0f, 100.0f, 100.0f, 1.0f };

	glClearDepth(1.0);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientProperties);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseProperties);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularProperties);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);

	// Default : lighting
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

}


void drawSphere(double r, int polygonNumX, int polygonNumY,
	GLfloat mat_ambient[4], GLfloat mat_diffuse[4], GLfloat mat_emission[4], GLfloat mat_specular[4])
{

	float no_mat[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float no_shininess = 0.0f;
	float shininess = 100.0f;

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

	if (m_Highlight)
	{
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	}
	else {
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
		glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
	}


	int i, j;
	for (i = 0; i<polygonNumX; i++)
	for (j = 0; j<polygonNumY; j++)
	if (m_Smooth)
	{
		glBegin(GL_POLYGON);

		// the normal of each vertex is actaully its own coordinates normalized for x sphere

		glNormal3d(sin(i*M_PI / polygonNumX)*cos(j*M_PI / polygonNumX),
				 cos(i*M_PI / polygonNumX)*cos(j*M_PI / polygonNumX),
				 sin(j*M_PI / polygonNumX));

		glVertex3d(r*sin(i*M_PI / polygonNumX)*cos(j*M_PI / polygonNumX),
				 r*cos(i*M_PI / polygonNumX)*cos(j*M_PI / polygonNumX),
				 r*sin(j*M_PI / polygonNumX));

		glNormal3d(sin((i + 1)*M_PI / polygonNumX)*cos(j*M_PI / polygonNumX),
				 cos((i + 1)*M_PI / polygonNumX)*cos(j*M_PI / polygonNumX),
				 sin(j*M_PI / polygonNumX));

		glVertex3d(r*sin((i + 1)*M_PI / polygonNumX)*cos(j*M_PI / polygonNumX),
				 r*cos((i + 1)*M_PI / polygonNumX)*cos(j*M_PI / polygonNumX),
				 r*sin(j*M_PI / polygonNumX));

		glNormal3d(sin((i + 1)*M_PI / polygonNumX)*cos((j + 1)*M_PI / polygonNumX),
				 cos((i + 1)*M_PI / polygonNumX)*cos((j + 1)*M_PI / polygonNumX),
				 sin((j + 1)*M_PI / polygonNumX));

		glVertex3d(r*sin((i + 1)*M_PI / polygonNumX)*cos((j + 1)*M_PI / polygonNumX),
				 r*cos((i + 1)*M_PI / polygonNumX)*cos((j + 1)*M_PI / polygonNumX),
				 r*sin((j + 1)*M_PI / polygonNumX));

		// your normal here
		glNormal3d(sin(i*M_PI / polygonNumX)*cos((j + 1)*M_PI / polygonNumX),
				 cos(i*M_PI / polygonNumX)*cos((j + 1)*M_PI / polygonNumX),
				 sin((j + 1)*M_PI / polygonNumX));

		glVertex3d(r*sin(i*M_PI / polygonNumX)*cos((j + 1)*M_PI / polygonNumX),
				 r*cos(i*M_PI / polygonNumX)*cos((j + 1)*M_PI / polygonNumX),
				 r*sin((j + 1)*M_PI / polygonNumX));

		glEnd();
	}
	else	{
		glBegin(GL_POLYGON);
		// Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for x sphere
		glNormal3d(sin((i + 0.5)*M_PI / polygonNumX)*cos((j + 0.5)*M_PI / polygonNumX),
				 cos((i + 0.5)*M_PI / polygonNumX)*cos((j + 0.5)*M_PI / polygonNumX),
				 sin((j + 0.5)*M_PI / polygonNumX));

		glVertex3d(r*sin(i*M_PI / polygonNumX)*cos(j*M_PI / polygonNumX),
				 r*cos(i*M_PI / polygonNumX)*cos(j*M_PI / polygonNumX),
				 r*sin(j*M_PI / polygonNumX));

		glVertex3d(r*sin((i + 1)*M_PI / polygonNumX)*cos(j*M_PI / polygonNumX),
				 r*cos((i + 1)*M_PI / polygonNumX)*cos(j*M_PI / polygonNumX),
				 r*sin(j*M_PI / polygonNumX));

		glVertex3d(r*sin((i + 1)*M_PI / polygonNumX)*cos((j + 1)*M_PI / polygonNumX),
				 r*cos((i + 1)*M_PI / polygonNumX)*cos((j + 1)*M_PI / polygonNumX),
				 r*sin((j + 1)*M_PI / polygonNumX));

		glVertex3d(r*sin(i*M_PI / polygonNumX)*cos((j + 1)*M_PI / polygonNumX),
				 r*cos(i*M_PI / polygonNumX)*cos((j + 1)*M_PI / polygonNumX),
				 r*sin((j + 1)*M_PI / polygonNumX));

		glEnd();
	}

}

void drawCylinder(double radius, double height, int polygonNumX,
	GLfloat cmat_ambient[4], GLfloat cmat_diffuse[4], GLfloat cmat_emission[4], GLfloat cmat_specular[4])
{
	float cno_mat[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float cno_shininess = 0.0f;
	float cshininess = 100.0;


	glMaterialfv(GL_FRONT, GL_AMBIENT, cmat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, cmat_diffuse);
	glMaterialfv(GL_FRONT, GL_EMISSION, cno_mat);

	if (m_Highlight)
	{
		glMaterialfv(GL_FRONT, GL_SPECULAR, cmat_specular);
		glMaterialf(GL_FRONT, GL_SHININESS, cshininess);
	}
	else {
		glMaterialfv(GL_FRONT, GL_SPECULAR, cno_mat);
		glMaterialf(GL_FRONT, GL_SHININESS, cno_shininess);
	}

	if (m_Smooth)
	{
		for (int i = 0; i <= polygonNumX; i++) {

			int x = 2 * i;
			
			glBegin(GL_POLYGON);


			glNormal3d(sin(M_PI*x /polygonNumX),
					 cos(M_PI*x /polygonNumX),
					 0.5*height);

			glVertex3d(radius*sin(M_PI*x /polygonNumX),
					 radius*cos(M_PI*x /polygonNumX),
					 0.5*height);

			glNormal3d(sin(M_PI*x /polygonNumX),
					 cos(M_PI*x /polygonNumX),
					 -0.5*height);

			glVertex3d(radius*sin(M_PI*x /polygonNumX),
					 radius*cos(M_PI*x /polygonNumX),
					 -0.5*height);

			glNormal3d(sin(M_PI*(x + 2) /polygonNumX),
					 cos(M_PI*(x + 2) /polygonNumX),
					 -0.5*height);

			glVertex3d(radius*sin(M_PI*(x + 2) /polygonNumX),
					 radius*cos(M_PI*(x + 2) /polygonNumX),
					 -0.5*height);

			glNormal3d(sin(M_PI*(x + 2) /polygonNumX),
					 cos(M_PI*(x + 2) /polygonNumX),
					 0.5*height);

			glVertex3d(radius*sin(M_PI*(x + 2) /polygonNumX),
					 radius*cos(M_PI*(x + 2) /polygonNumX),
					 0.5*height);

			glEnd();
		}
	}
	else	{
		for (int i = 0; i <= polygonNumX; i++) {
			int x = 2 * i;

			glBegin(GL_POLYGON);

			glNormal3d(radius*sin(M_PI*(x + 2) /polygonNumX),
					 radius*cos(M_PI*(x + 2) /polygonNumX),
					 0);

			glVertex3d(radius*sin(M_PI*x /polygonNumX),
					 radius*cos(M_PI*x /polygonNumX),
					 0.5*height);

			glVertex3d(radius*sin(M_PI*x /polygonNumX),
					 radius*cos(M_PI*x /polygonNumX),
					 -0.5*height);

			glVertex3d(radius*sin(M_PI*(x + 2) /polygonNumX),
					 radius*cos(M_PI*(x + 2) /polygonNumX),
					 -0.5*height);

			glVertex3d(radius*sin(M_PI*(x + 2) /polygonNumX),
					 radius*cos(M_PI*(x + 2) /polygonNumX),
					 0.5*height);

			glEnd();
		}
	}
}
float mat_ambient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
float mat_diffuse[] = { 0.1f, 0.5f, 0.8f, 1.0f };
float mat_emission[] = { 0.3f, 0.2f, 0.2f, 1.0f };
float mat_specular[] = { 0.075f, 0.5f, 1, 1.0f };

float wine_ambient[] = { 0.7, 0, 0, 1.0f };
float wine_diffuse[] = { 0.1f, 0, 0.3f, 0.2f };
float wine_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
float wine_specular[] = { 0.5f, 0.5f, 1, 1.0f };

float white_ambient[] = { 0.9, 0.9, 0.9, 1.0f };
float white_diffuse[] = { 0.9, 0.8, 0, 1 };
float white_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
float white_specular[] = { 0.075f, 0.5f, 1, 1.0f };

float black_ambient[] = { 0, 0, 0, 1.0f };
float black_diffuse[] = { 0, 0, 0, 1.0f };
float black_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
float black_specular[] = { 0.075f, 0.5f, 1, 1.0f };

float lightBlue_ambient[] = { 0.9, 0.9, 0.9, 0 };
float lightBlue_diffuse[] = { 0.1, 0.5, 0.8, 0 };
float lightBlue_emission[] = { 0.0f, 0.0f, 0.0f, 0 };
float lightBlue_specular[] = { 0.075f, 0.5f, 1, 1.0f };

void drawBottle() {
	glPushMatrix();
		glTranslatef(0, 0, 1.4);
		glScalef(1, 1, 0.05);
		drawSphere(0.075, 90, 180, white_ambient, white_diffuse, white_emission, white_specular);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0, 0, -.75);
		glScalef(1, 1, 0.05);
		drawSphere(0.25, 90, 180, black_ambient, black_diffuse, black_emission, black_specular);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0, 0, 0.75);
		drawSphere(0.25, 90, 90, black_ambient, black_diffuse, black_emission, black_specular);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0, 0, 0.025);
		drawCylinder(0.251, 1.2, 90.0, white_ambient, white_diffuse, white_emission, white_specular);
	glPopMatrix();
	glPushMatrix();
		drawCylinder(0.25, 1.5, 90.0, black_ambient, black_diffuse, black_emission, black_specular);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0, 0, 1.15);
		drawCylinder(0.075, 0.45, 90.0, black_ambient, black_diffuse, black_emission, black_specular);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0, 0, 1.25);
		drawCylinder(0.076, 0.3, 90.0, white_ambient, white_diffuse, white_emission, white_specular);
	glPopMatrix();
}

void recursiveWineStalk(double radius) {
	if (radius > 0.009) {
		glPushMatrix();
			drawCylinder(radius, 0.05, 90.0, lightBlue_ambient, lightBlue_diffuse, lightBlue_emission, lightBlue_specular);
			glTranslatef(0, 0, radius);
			recursiveWineStalk(radius - 0.002);
		glPopMatrix();
	}
}

void drawWineGlass() {
	glPushMatrix();
		glScalef(1, 1, 0.05);
		drawSphere(0.15, 90, 180, lightBlue_ambient, lightBlue_diffuse, lightBlue_emission, lightBlue_specular);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0,0, 0.02);
		recursiveWineStalk(0.04);
	glPopMatrix();

	glPushMatrix(); 
		glRotatef(180,1,0,0);
		glRotatef(-180, 0, 0, 1);
		glTranslatef(0, 0, -0.93);
		glScalef(1, 1, 2);
		drawSphere(0.25, 90, 90, lightBlue_ambient, lightBlue_diffuse, lightBlue_emission, lightBlue_specular);
	glPopMatrix();

	glPushMatrix();
		glRotatef(180, 1, 0, 0);
		glRotatef(-180, 0, 0, 1);
		glTranslatef(0, 0, -0.9);
		glScalef(1, 1, 1);
		drawSphere(0.249, 90, 90, wine_ambient, wine_diffuse, wine_emission, wine_specular);
	glPopMatrix();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
		glTranslatef(0, 0, -6);

		glRotatef(angle2, 1.0, 0.0, 0.0);
		glRotatef(angle, 0.0, 1.0, 0.0);

		glScalef(zoom, zoom, zoom);

		switch (current_object) {
		case 0:
			drawSphere(1, 20, 40, mat_ambient, mat_diffuse, mat_emission, mat_specular);
			break;
		case 1:
			drawCylinder(0.5, 3, 90.0, mat_ambient, mat_diffuse, mat_emission, mat_specular);
			break;
		case 2:
			drawBottle();
			break;
		case 3:
			glPushMatrix();
				glTranslatef(-0.5,0,0.25);
				drawBottle();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.15, 0, -0.5);
				drawWineGlass();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.75,0,-0.5);
				drawWineGlass();
			glPopMatrix();
			break;
		default:
			break;
		};
	glPopMatrix();
	glutSwapBuffers();
}




void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'p':
	case 'P':
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	case 'w':
	case 'W':
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case 'v':
	case 'V':
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		break;
	case 's':
	case 'S':
		m_Smooth = !m_Smooth;
		break;
	case 'h':
	case 'H':
		m_Highlight = !m_Highlight;
		break;

	case '1':
	case '2':
	case '3':
	case '4':
		current_object = key - '1';
		break;

	case 27:
		exit(0);
		break;

	default:
		break;
	}

	glutPostRedisplay();
}



void
mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN) {
		mouseButton = button;
		moving = 1;
		startx = x;
		starty = y;
	}
	if (state == GLUT_UP) {
		mouseButton = button;
		moving = 0;
	}
}

void motion(int x, int y)
{
	if (moving) {
		if (mouseButton == GLUT_LEFT_BUTTON)
		{
			angle = angle + (x - startx);
			angle2 = angle2 + (y - starty);
		}
		else zoom += ((y - starty)*0.001);
		startx = x;
		starty = y;
		glutPostRedisplay();
	}

}

int main(int argc, char **argv)
{
	cout << "CS3241 Lab 3" << endl << endl;

	cout << "1-4: Draw different objects" << endl;
	cout << "S: Toggle Smooth Shading" << endl;
	cout << "H: Toggle Highlight" << endl;
	cout << "W: Draw Wireframe" << endl;
	cout << "P: Draw Polygon" << endl;
	cout << "V: Draw Vertices" << endl;
	cout << "ESC: Quit" << endl << endl;

	cout << "Left mouse click and drag: rotate the object" << endl;
	cout << "Right mouse click and drag: zooming" << endl;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("CS3241 Assignment 3");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutKeyboardFunc(keyboard);
	setupLighting();
	glDisable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);

	glMatrixMode(GL_PROJECTION);
	gluPerspective( /* field of view in degree */ 40.0,
		/* aspect ratio */ 1.0,
		/* Z near */ 1.0, /* Z far */ 80.0);
	glMatrixMode(GL_MODELVIEW);
	glutMainLoop();

	return 0;
}
