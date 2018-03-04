#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <stdio.h>
#include <stdlib.h>

#include "shaderMethods.h"
#include "renderObjects.h"

const GLfloat globalAmb[] = {.2, .2, .2, 1};
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };
GLfloat Ry = 15.0, Tx = 0.0, Ty = 0.0, Tz = 2.0;

void renderScene () {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glPushMatrix();
	glRotatef(Ry, 0.0f, 1.0f, 0.0f);
	glTranslatef(Tx, Ty, Tz);
	glEnable (GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	renderFloor();
	renderCeiling();

	renderChairs();

	renderAllWalls();
	renderBoard();
	renderDoorAndTable();

	glPopMatrix();
	glutSwapBuffers();
}

void changeSize (int width, int height) {
	const float aspectRatio = (float) width / (float) height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, aspectRatio, 2.0, 100.0);
	gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0, 1, 0);	// default -z axis

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity() ;
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'r':
		Ry = 0;
		Tx = 0;
		Ty = 0;
		Tz = 2;
		renderScene();
		break;
	case 'l':
		Ry += 5;
		renderScene();
		break;
	case 'h':
		Ry -= 5;
		renderScene();
		break;
	case 'w':
		Tz += 2;
		renderScene();
		break;
	case 's':
		Tz -= 2;
		renderScene();
		break;
	case 'a':
		Tx += 2;
		renderScene();
		break;
	case 'd':
		Tx -= 2;
		renderScene();
		break;
	case 'j':
		Ty -= 2;
		renderScene();
		break;
	case 'k':
		Ty += 2;
		renderScene();
		break;
	}
}

// Initialize lighting, depth func, etc
void initializeRoom () {
	glClearColor(0,0,0,1);

	glShadeModel(GL_SMOOTH);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	//set the global ambient light
	glLightModelfv (GL_LIGHT_MODEL_AMBIENT, globalAmb) ;
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(900, 700);
	glutCreateWindow("Assignment 2: 14292");

	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutKeyboardFunc(keyboard);

	initializeRoom();
	initializeGlew();

	glutMainLoop();
	return 0;
}
