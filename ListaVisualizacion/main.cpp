#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<GL/glut.h>

#define GL_PI 3.1415926535897932384626433832795f
#define WIDTH 500
#define HEIGTH 500
#define EJES_CORD 1
#define TORUS 2

// Definicion de funciones

void init(void);
void display(void);
void reshape(int,int);
void dibujarEjes();
void dibujarPendulo(GLfloat, GLfloat, GLfloat, GLfloat);
void idleFunc();
void keyboardFunc(unsigned char tecla,int x,int y);
void revolTorus(int stacks, int slices);

// Variables globales

static float theta[3] = {0.0, 0.0, 0.0};
int axis = 2;
int main(int argc, char** argv)
{

    glutInit(&argc,argv);

    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB |GLUT_DEPTH);

    glutInitWindowSize(WIDTH,HEIGTH);

    glutInitWindowPosition(100,100);

    glutCreateWindow(argv[0]);

    init();

    glutDisplayFunc(display);

    glutIdleFunc(idleFunc);

    glutReshapeFunc(reshape);

    glutKeyboardFunc(keyboardFunc);

    glEnable(GL_DEPTH_TEST);

    glutMainLoop();

    return 0;
}

void init(void)
{

    glClearColor(0.0,0.0,0.0,0.0);

    glShadeModel(GL_FLAT);

    glLineWidth(1.5);

    glPointSize(3.0);

    glColor3f(1.0,0.0,0.0);

    revolTorus(50, 16);

    dibujarEjes();


}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    gluLookAt(1, 1, 1, 0, 0 ,0, 0, 1, 0);

    glCallList(EJES_CORD);

    glRotated(theta[0], 1, 0, 0);
    glRotated(theta[1], 0, 1, 0);
    glRotated(theta[2], 0, 0, 1);

    //glutWireSphere(5, 16, 16);
    glCallList(TORUS);

    glutSwapBuffers();
}

void reshape(int w, int h)
{

    glViewport(0, 0, (GLsizei) w, (GLsizei) h);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    glOrtho(-10.0, 10.0, -10.0, 10, -10.0, 10.0);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

}

void dibujarEjes()
{

    glNewList(EJES_CORD, GL_COMPILE);
        glColor3f(1.0,0.0,0.0);
        glBegin(GL_LINE_STRIP);
            glVertex3f(0.0,0.0,0.0);
            glVertex3f(20.0,0.0,0.0);
        glEnd();
        glColor3f(0.0,0.0,1.0);
        glBegin(GL_LINE_STRIP);
            glVertex3f(0.0,0.0,0.0);
            glVertex3f(0.0,20.0,0.0);
        glEnd();
        glColor3f(0.0,1.0,0.0);
        glBegin(GL_LINE_STRIP);
            glVertex3f(0.0,0.0,0.0);
            glVertex3f(0.0,0.0,20.0);
        glEnd();
    glEndList();
}

// Idle Func
void idleFunc(){

    theta[axis] += 0.1;

    if(theta[axis] >= 360.0) {
        theta[axis] -= 360.0;
    }

    display();
}

// KeyBoard Function

void keyboardFunc(unsigned char tecla,int x,int y)
{

    switch(tecla)
    {
        case 'z':
            axis = 0;
            break;
        case 'x':
            axis = 1;
            break;
        case 'c':
            axis = 2;
            break;
    }
}

void circulo(float x, float y, float radio) {

    glBegin(GL_LINE_STRIP);
        for(float ang = 0.0 ; ang <= 2 * GL_PI; ang += 2 * GL_PI / 36) {
            glVertex3f(x + radio * cos(ang), y + radio * sin(ang), 0);
        }
    glEnd();

}
void revolTorus(int stacks, int slices)
{
    glNewList(TORUS, GL_COMPILE);
    for(float ang = 0; ang <= 360; ang += 360 / stacks) {
        glPushMatrix();
            glRotatef(ang, 0, 1, 0);
            circulo(4, 0, 1);
        glPopMatrix();
    }
    glEndList();
}




