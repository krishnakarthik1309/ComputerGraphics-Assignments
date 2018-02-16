#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

float Tx,Ty,Tz;
float Sx,Sy,Sz;
float Rx,Ry,Rz;

void drawCuboid (float x, float y, float z, float l, float w, float nh, float cr, float cg, float cb) {
    float h = -nh;
    glPushMatrix();
    glTranslatef (x, y, z);
    glColor3f(cr, cg, cb);

    glBegin(GL_QUADS);
    // top
    glNormal3f(x + 0.0f, y + 1.0f, z + 0.0f);
    glVertex3f(-l, h, w);
    glVertex3f(l, h, w);
    glVertex3f(l, h, -w);
    glVertex3f(-l, h, -w);

    glEnd();

    glBegin(GL_QUADS);
    // front
    glNormal3f(x + 0.0f, y + 0.0f, z + 1.0f);
    glVertex3f(l, -h, w);
    glVertex3f(l, h, w);
    glVertex3f(-l, h, w);
    glVertex3f(-l, -h, w);

    glEnd();

    glBegin(GL_QUADS);
    // right
    glNormal3f(x + 1.0f, y + 0.0f, z + 0.0f);
    glVertex3f(l, h, -w);
    glVertex3f(l, h, w);
    glVertex3f(l, -h, w);
    glVertex3f(l, -h, -w);

    glEnd();

    glBegin(GL_QUADS);
    // left
    glNormal3f(x - 1.0f, y + 0.0f, z + 0.0f);
    glVertex3f(-l, -h, w);
    glVertex3f(-l, h, w);
    glVertex3f(-l, h, -w);
    glVertex3f(-l, -h, -w);

    glEnd();

    glBegin(GL_QUADS);
    // bottom
    glNormal3f(x + 0.0f, y -1.0f, z + 0.0f);
    glVertex3f(l, -h, w);
    glVertex3f(-l, -h, w);
    glVertex3f(-l, -h, -w);
    glVertex3f(l, -h, -w);

    glEnd();

    glBegin(GL_QUADS);
    // back
    glNormal3f(x + 0.0f, y + 0.0f, z - 1.0f);
    glVertex3f(l, h, -w);
    glVertex3f(l, -h, -w);
    glVertex3f(-l, -h, -w);
    glVertex3f(-l, h, -w);

    glEnd();
    glPopMatrix();
}

void drawChair (float x, float y, float z) {
    float h = 0.025f, l = 0.25f, w = 0.25f;
    float hl = 0.25f, ll = 0.025f, wl = 0.025f;

    // 4 legs
    drawCuboid(x - l + ll, y - h - hl, z + w - wl, ll, wl, hl, 1.0f, 0.5f, 0.0f);
    drawCuboid(x + l - ll, y - h - hl, z + w - wl, ll, wl, hl, 1.0f, 0.5f, 0.0f);
    drawCuboid(x + l - ll, y - h - hl, z - w + wl, ll, wl, hl, 1.0f, 0.5f, 0.0f);
    drawCuboid(x - l + ll, y - h - hl, z - w + wl, ll, wl, hl, 1.0f, 0.5f, 0.0f);

    // base
    drawCuboid(x, y, z, l, w, h, 1.0f, 0.0f, 0.0f);

    // back
    hl = 0.32f; ll = 0.25f; wl = 0.025f;
    drawCuboid(x, y + h + hl, z + w - wl, ll, wl, hl, 0.0f, 0.0f, 1.0f);

}

void drawChairs () {
    float z_delta = -12.0;
    drawChair(-3.4, -3.0, z_delta);
    drawChair(-1.7, -3.0, z_delta);
    drawChair(0.0, -3.0, z_delta);
    drawChair(1.7, -3.0, z_delta);
    drawChair(3.4, -3.0, z_delta);

    z_delta = -8.0;
    drawChair(-3.4, -3.0, z_delta);
    drawChair(-1.7, -3.0, z_delta);
    drawChair(0.0, -3.0, z_delta);
    drawChair(1.7, -3.0, z_delta);
    drawChair(3.4, -3.0, z_delta);

    z_delta = -4.0;
    drawChair(-3.4, -3.0, z_delta);
    drawChair(-1.7, -3.0, z_delta);
    drawChair(0.0, -3.0, z_delta);
    drawChair(1.7, -3.0, z_delta);
    drawChair(3.4, -3.0, z_delta);

    z_delta = -0.0;
    drawChair(-3.4, -3.0, z_delta);
    drawChair(-1.7, -3.0, z_delta);
    drawChair(0.0, -3.0, z_delta);
    drawChair(1.7, -3.0, z_delta);
    drawChair(3.4, -3.0, z_delta);


}

void drawBoard () {
    drawCuboid(-4.8f, 1.5f, -14.0f, 1.5f, 0.01f, 2.0f, 0.5f, 0.5f, 0.5f);
    drawCuboid(0.0f, 1.5f, -14.0f, 3.0f, 0.01f, 2.0f, 0.0f, 0.3f, 0.0f);
    drawCuboid(4.8f, 1.5f, -14.0f, 1.5f, 0.01f, 2.0f, 0.5f, 0.5f, 0.5f);
}

void renderScene (void) {
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glPushMatrix();

    glTranslatef(Tx, Ty, Tz);
    glScalef(Sx, Sy, Sz);

    drawBoard();

    drawChairs();
    glutSwapBuffers();
}

void changeSize (int x, int y) {
    if (y == 0 || x == 0) return;

    GLfloat aspect = (GLfloat)(x/y);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0, 1, 0);
    gluPerspective(45.0f,aspect,0.1f, 10000.0f);
    glViewport(0,0,x,y);
    glMatrixMode(GL_MODELVIEW);
}

void initializeRoom () {
    glClearColor(0.0,0.0,0.0,0.0);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
}

int main (int argc, char **argv) {
    glutInit (&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(900, 700);
    glutCreateWindow("Classroom");

    Tx = 0.0; Ty = 0.0; Tz = -10.0;
    Sx = 1.0; Sy = 1.0; Sz = 1.0;
    Rx = 40.0; Ry = 33.0; Rz = 23.0;

    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);

    glutMainLoop();

    return 0;
}