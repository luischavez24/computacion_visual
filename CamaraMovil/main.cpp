#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<GL/glut.h>
#define GL_PI 3.1416f
#define WIDTH 500
#define HEIGTH 500
// Definicion de funciones

void init(void);
void display(void);
void reshape(int,int);
void dibujarEjes();
void idleFunc();
void regionCircuferencia(GLfloat aInit,GLfloat aEnd, GLfloat cx, GLfloat cy, GLfloat r);
void espacio(GLfloat width, GLfloat heigth);
float convertirGrados(float degree);
void key_func(unsigned char, int, int);

// Variables globales
GLfloat x = 7, y = 2, z = 5, ang = 0;

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

    glutKeyboardFunc(key_func);

    glutReshapeFunc(reshape);

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

}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    gluLookAt(x,y,z,1,1,1,0,1,0);
    dibujarEjes();
    glColor3f(1,1,0);
    glutWireCube(2);
    //glutWireTeapot(2);
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


// Idle Func
void idleFunc(){
    z = sqrt(7*7 + 5*5) * cos(ang);
    x = sqrt(7*7 + 5*5)  * sin(ang);
    display();
}

// Primitivas graficas
void dibujarEjes()
{
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

    glBegin(GL_LINE_STRIP);
    glColor3f(0.0,1.0,0.0);
        glVertex3f(0.0,0.0,0.0);
        glVertex3f(0.0,0.0,20.0);
    glEnd();
}

void key_func(unsigned char tecla, int x, int y)
{
    switch(tecla)
    {
    case 'a':
        printf("Izquierda \n");
        ang += 0.1;
        break;
    case 'd':
        ang -= 0.1;
        printf("Derecha \n");
        break;
    }
}
float recta(float angulo_inclinacion, float x, float x0, float y0)
{
    return (tan(convertirGrados(angulo_inclinacion))) * (x - x0) + y0;
}

void regionCircuferencia(GLfloat aInit,GLfloat aEnd, GLfloat cx, GLfloat cy, GLfloat r)
{
    glBegin(GL_LINE_STRIP);
        //glColor3f(r,g,b);
        GLfloat ang, x, y;
        for(ang = aInit; ang  <= aEnd ; ang += 2*GL_PI/80) {
            x = r * cos(-ang) + cx;
            y = r * sin(-ang) + cy;
            glVertex2f(x,y);
        }
    glEnd();

    glBegin(GL_LINE_STRIP);
        glVertex3f(r*cos(aInit)+cx, r*sin(aInit)+cy,0);
        glVertex3f(cx, cy, 0);
    glEnd();

    glBegin(GL_LINE_STRIP);
        glVertex3f(r*cos(aEnd)+cx , r*sin(aEnd)+cy,0);
        glVertex3f(cx, cy, 0);
    glEnd();
}

void espacio(GLfloat width, GLfloat heigth)
{
    glBegin(GL_LINE_STRIP);
        glColor3f(1.0f,0.0f,0.0f);
        glVertex3f(-width/2, heigth/2, 0);
        glVertex3f(width/2, heigth/2, 0);
        glVertex3f(width/2, -heigth/2, 0);
        glVertex3f(-width/2, -heigth/2, 0);
        glVertex3f(-width/2, heigth/2, 0);
    glEnd();
}

float convertirGrados(float degree)
{
    return (GL_PI/180) * degree;
}
