#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "shaderMethods.h"

void drawCuboid (float x, float y, float z, float l, float w, float nh, float cr, float cg, float cb) {
    glPushMatrix();

    glTranslatef (x, y, z);
    glColor3f(cr, cg, cb);

    const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
    const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
    const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat high_shininess[] = { 100.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glScalef(1.0, nh/l, w/l);
    glutSolidCube(2*l);
    glPopMatrix();
}

void drawChair (float x, float y, float z) {
	float h = 0.025f, l = 0.35f, w = 0.25f;
	float hl = 0.25f, ll = 0.025f, wl = 0.025f;

	// 4 legs
	drawCuboid(x - l + ll, y - h - hl, z + w - wl, ll, wl, hl, 204.0f/255.0f, 153.0f/255.0f, 102.0f/255.0f);
	drawCuboid(x + l - ll, y - h - hl, z + w - wl, ll, wl, hl, 204.0f/255.0f, 153.0f/255.0f, 102.0f/255.0f);
	drawCuboid(x + l - ll, y - h - hl, z - w + wl, ll, wl, hl, 204.0f/255.0f, 153.0f/255.0f, 102.0f/255.0f);
	drawCuboid(x - l + ll, y - h - hl, z - w + wl, ll, wl, hl, 204.0f/255.0f, 153.0f/255.0f, 102.0f/255.0f);

	// base
	drawCuboid(x, y, z, l, w, h, 0.5f, 0.35f, 0.0f);

	// back
	hl = 0.32f; ll = 0.35f; wl = 0.025f;
	drawCuboid(x, y + h + hl, z + w - wl, ll, wl, hl, 0.5f, 0.2f, 0.0f);
}

void renderChairs () {
	GLuint p = setShaders((char *) "shaders/vert_chair.glsl", (char *) "shaders/frag_chair.glsl");
    float z = -25.0, x = 1.7, y = -3.0;
    while (z < -8.1) {
        x = 1.7;
        while (x < 16.0) {
            drawChair(x, y, z);
            x += 1.7;
        }
        z += 4.0;
    }
    glDeleteProgram(p);
}

void renderFloor () {
	GLuint p = setShaders((char *) "shaders/vert_floor.glsl", (char *) "shaders/frag_common.glsl");
	setTextures(p, (char *) "texture", 0, (char *) "textures/floor.tga");
    drawCuboid(8.5f, -3.5f, -24.0f, 12.0f, 22.0f, 0.1f, 0.4f, 0.4f, 0.4f);
    glDeleteProgram(p);
}

void renderCeiling () {
	GLuint p = setShaders((char *) "shaders/vert_ceiling.glsl", (char *) "shaders/frag_common.glsl");
	setTextures(p, (char *) "texture", 0, (char *) "textures/ceiling.tga");
	drawCuboid(8.5f, 6.5f, -24.0f, 12.0f, 22.0f, 0.1f, 0.4f, 0.4f, 0.4f);
	glDeleteProgram(p);
}

void renderWall (GLfloat x, GLfloat y, GLfloat z, GLfloat l, GLfloat w, GLfloat h) {
	drawCuboid(x, y, z, l, w, h, 0.4f, 0.4f, 0.4f);
}

void renderSideWalls () {
	GLuint p = setShaders((char *) "shaders/vert_side_wall.glsl", (char *) "shaders/frag_common.glsl");
	setTextures(p, (char *) "texture", 0, (char *) "textures/bricks_white.tga");

	// left, right wall in order
	renderWall(-3.0f, 1.5f, -24.0f, 0.5f, 22.0f, 5.0f);
	renderWall(20.0f, 1.5f, -24.0f, 0.5f, 22.0f, 5.0f);

	glDeleteProgram(p);
}

void renderMidWall () {
	GLuint p = setShaders((char *) "shaders/vert_mid_wall.glsl", (char *) "shaders/frag_common.glsl");
	setTextures(p, (char *) "texture", 0, (char *) "textures/Birch_bark_tile.tga");

	renderWall(8.5f, 1.5f, -45.0f, 11.0f, 0.5f, 5.0f);
	renderWall(10.5f, 1.5f, -3.0f, 9.0f, 0.5f, 5.0f);

	glDeleteProgram(p);
}

void renderAllWalls () {
	renderSideWalls();
	renderMidWall();
}

void renderBoard () {
	GLuint p = setShaders((char *) "shaders/vert_mid_wall.glsl", (char *) "shaders/frag_common.glsl");
	setTextures(p, (char *) "texture", 0, (char *) "textures/Green-Chalkboard-Texture.tga");

	drawCuboid(9.0f, 1.5f, -44.0f, 6.0f, 0.1f, 2.5f, 0.4f, 0.4f, 0.4f);

	glDeleteProgram(p);
}

void renderTable () {
	float x = -1.25f, y = -1.6f, z = -40.0f;
	float h = 0.15f, l = 0.9f, w = 1.7f;
	float hl = 0.75f, ll = 0.1f, wl = 0.075f;

	// 4 legs
	drawCuboid(x - l + ll, y - h - hl, z + w - wl, ll, wl, hl, 0.3f, 0.3f, 0.0f);
	drawCuboid(x + l - ll, y - h - hl, z + w - wl, ll, wl, hl, 0.3f, 0.3f, 0.0f);
	drawCuboid(x + l - ll, y - h - hl, z - w + wl, ll, wl, hl, 0.3f, 0.3f, 0.0f);
	drawCuboid(x - l + ll, y - h - hl, z - w + wl, ll, wl, hl, 0.3f, 0.3f, 0.0f);

	// base
	drawCuboid(x, y, z, l, w, h, 0.5f, 0.35f, 0.0f);
}

void renderDoorAndTable() {
	GLuint p = setShaders((char *) "shaders/vert_door.glsl", (char *) "shaders/frag_common.glsl");
	setTextures(p, (char *) "texture", 0, (char *) "textures/door.tga");

	renderWall(-0.5f, 1.5f, -3.0f, 2.0f, 0.5f, 5.0f);
	renderTable();

	glDeleteProgram(p);
}
