#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <stdio.h>
#include <stdlib.h>

#include "shaderMethods.h"
#include "renderObjects.h"

const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };
GLfloat Ry = 0, k = 1;

void renderScene () {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glPushMatrix();
	glRotatef(Ry, 0.0f, 1.0f, 0.0f);

	renderFloor();
	renderCeiling();

	renderChairs();

	renderAllWalls();
	renderBoard();

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

void animate () {
	if (Ry > 40) {
		k = -1;
	} else if (Ry < 0) {
		k = 1;
	}
	Ry += k*0.5;
	renderScene();
}

// Initialize lighting, depth func, etc
void initializeRoom () {
	glClearColor(0,0,0,1);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(900, 700);
	glutCreateWindow("Assignment 2: 14292");

	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(animate);

	initializeRoom();
	initializeGlew();

	glutMainLoop();
	return 0;
}
