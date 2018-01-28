#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#ifdef __APPLE__
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <math.h>


GLfloat Tx,Ty,Tz;
GLfloat Rx,Ry,Rz;
GLfloat Sx,Sy,Sz;
GLfloat gg;

void DrawCircle(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_LINE_LOOP);
    for(int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle

        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component

        glVertex2f(x + cx, y + cy);//output vertex

    }
    glEnd();
}

void renderScene(void){
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glColor3f(0.2, 0.8, 0.5);

    // // changing in transformation matrix.
    glTranslatef(Tx, Ty, Tz);

    glScalef(Sx, Sy, Sz);

    // orbits
    DrawCircle(0.0, 0.0, 1, 5000);
    DrawCircle(0.0, 0.0, 1.5, 5000);
    DrawCircle(0.0, 0.0, 2, 5000);
    DrawCircle(0.0, 0.0, 2.5, 5000);
    DrawCircle(0.0, 0.0, 3, 5000);
    DrawCircle(0.0, 0.0, 3.5, 5000);
    DrawCircle(0.0, 0.0, 4, 5000);

    glFlush();
    glutSwapBuffers();

    // // Different default objects

    // // glutWireCone(1.0, 3.0, 100, 3);
    // // glutWireTorus(1.0, 2.0, 6, 4);
    // // glutWireDodecahedron();
    // // glutWireIcosahedron();
    // glutWireTeapot(1.0);

    // glFlush();
    // glutSwapBuffers();

    glMatrixMode(GL_MODELVIEW);
    // glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glColor3f(0.2, 0.8, 0.5);

    // changing in transformation matrix.
    glTranslatef(Tx, Ty, Tz);

    glRotatef(Rx, 1.0f, 0.0f, 0.0f);
    glRotatef(Ry, 0.0f, 1.0f, 0.0f);
    glRotatef(Rz, 1.0f, 0.0f, 1.0f);

    glScalef(Sx, Sy, Sz);

    // Different default objects

    // glutWireCone(1.0, 3.0, 100, 3);
    // glutWireTorus(1.0, 2.0, 6, 4);
    // glutWireDodecahedron();
    // glutWireIcosahedron();
    glutSolidSphere(0.75, 2000, 2000);
    glFlush();
    glutSwapBuffers();


}

void changeSize(int x, int y){
    if (y == 0 || x == 0) return;

    GLfloat aspect = (GLfloat)(x/y);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0, 1, 0);
    gluPerspective(45.0f,aspect,0.1f, 10000.0f);
    glViewport(0,0,x,y);
    glMatrixMode(GL_MODELVIEW);
}

void animate(void){
    Ry += 0.5;

    // if (Tx > 3.5) {
    //     gg = -1;
    // } else if (Tx <-3.5) {
    //     gg = 1;
    // }
    // Tx += gg*0.01;
    renderScene();
}

int main (int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000,1000);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Assignment1");

    glClearColor(0.0,0.0,0.0,0.0);

    Tx = 0.0; Ty = 0.0; Tz = -10.0;
    Rx = 40.0; Ry = 33.0; Rz = 23.0;
    Sx = 1.0; Sy = 1.0; Sz = 1.0;
    gg = 1;

    //Assign  the function used in events
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);

    // glutIdleFunc(animate);                  //for animation uncomment

    //Let start glut loop
    glutMainLoop();

    return 0;
}
