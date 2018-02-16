#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

float Tx,Ty,Tz;
float Sx,Sy,Sz;
float Rx,Ry,Rz;

void drawCuboid (float x, float y, float z, float l, float w, float nh, float cr, float cg, float cb) {
    glPushMatrix();

    glTranslatef (x, y, z);
    glColor3f(cr, cg, cb);

    float diffuse[] = {cr, cg, cb, 1};
    float emmision[] = {0, 0, 0, 1};
    float specular[] = {1, 1, 1, 1};

    glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, diffuse) ;
    glMaterialfv (GL_FRONT, GL_SPECULAR, diffuse) ;
    glMaterialfv (GL_FRONT, GL_EMISSION, emmision);

    glScalef(1.0, nh/l, w/l);
    glutSolidCube(2*l);
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

    z_delta = 4.0;
    drawChair(-3.4, -3.0, z_delta);
    drawChair(-1.7, -3.0, z_delta);
    drawChair(0.0, -3.0, z_delta);
    drawChair(1.7, -3.0, z_delta);
    drawChair(3.4, -3.0, z_delta);

    z_delta = 8.0;
    drawChair(-3.4, -3.0, z_delta);
    drawChair(-1.7, -3.0, z_delta);
    drawChair(0.0, -3.0, z_delta);
    drawChair(1.7, -3.0, z_delta);
    drawChair(3.4, -3.0, z_delta);

    z_delta = 12.0;
    drawChair(-3.4, -3.0, z_delta);
    drawChair(-1.7, -3.0, z_delta);
    drawChair(0.0, -3.0, z_delta);
    drawChair(1.7, -3.0, z_delta);
    drawChair(3.4, -3.0, z_delta);

    z_delta = 16.0;
    drawChair(-3.4, -3.0, z_delta);
    drawChair(-1.7, -3.0, z_delta);
    drawChair(0.0, -3.0, z_delta);
    drawChair(1.7, -3.0, z_delta);
    drawChair(3.4, -3.0, z_delta);


}

void drawBoard () {
    drawCuboid(0.0f, 1.5f, -14.0f, 4.0f, 0.01f, 2.4f, 0.0f, 0.3f, 0.0f);
}

void initializeRoom () {
    glEnable(GL_CULL_FACE);

    glShadeModel(GL_SMOOTH) ;
    glEnable (GL_NORMALIZE) ;
    glEnable (GL_LIGHTING) ;

    //set the global ambient light
    float globalAmb[] = {.2, .2, .2, 1};
    glLightModelfv (GL_LIGHT_MODEL_AMBIENT, globalAmb) ;

    //set up a light and enable it
    float diffuse[] = {0.7, 0.7, 0.7, 1};
    float ambient[] = {0, 0, 0, 1};
    float specular[] = {0.7, 0.7, 0.7, 1};

    glLightfv (GL_LIGHT0, GL_DIFFUSE, diffuse) ;
    glLightfv (GL_LIGHT0, GL_AMBIENT, ambient) ;
    glLightfv (GL_LIGHT0, GL_SPECULAR, specular) ;
    glEnable (GL_LIGHT0) ; //enable the light

    //set light position
    // set last term to 0 for a spotlight
    float lightpos[] = {0.0f, 4.0f, -13.0f, 1};
    glLightfv (GL_LIGHT0, GL_POSITION, lightpos) ;
}

void renderScene (void) {
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glPushMatrix();
    glTranslatef(Tx, Ty, Tz);
    glScalef(Sx, Sy, Sz);
    glRotatef(Rx, 1.0f, 0.0f, 0.0f);
    glRotatef(Ry, 0.0f, 1.0f, 0.0f);
    glRotatef(Rz, 1.0f, 0.0f, 1.0f);

    initializeRoom();

    // floor
    drawCuboid(0.0f, -3.1f, 0.0f, 9.0f, 18.0f, 0.1f, 0.6f, 0.6f, 0.6f);

    drawBoard();

    // light bulb
    drawCuboid(0.0f, 4.0f, -14.0f, 1.5f, 0.01f, 0.09f, 1.0f, 1.0f, 1.0f);

    drawChairs();

    glPopMatrix();
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

void animate (void) {
    Ry += 0.2;
    renderScene();
}

int main (int argc, char **argv) {
    glutInit (&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(900, 700);
    glutCreateWindow("Classroom");

    Tx = 0.0; Ty = -2.0; Tz = -10.0;
    Sx = 1.0; Sy = 1.0; Sz = 1.0;
    Rx = 25.0; Ry = 00.0; Rz = 00.0;

    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);

    glutIdleFunc(animate);

    glutMainLoop();

    return 0;
}