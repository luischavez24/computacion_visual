#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<GL/glut.h>
#define GL_PI 3.1416f

// Definicion de funciones

void init(void);
void display(void);
void reshape(int,int);
void ejes(GLfloat l);
int main(int argc, char** argv) {

    glutInit(&argc,argv);

    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);

    glutInitWindowSize(500,500);

    glutInitWindowPosition(100,100);

    glutCreateWindow(argv[0]);

    init();

    glutDisplayFunc(display);

    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}

void init(void) {

    glClearColor(1.0,1.0,1.0,0.0);

    glShadeModel(GL_FLAT);

    glLineWidth(1.5);

    glPointSize(3.0);



}

void display(void) {

    GLfloat ang, x, y, r = 0, l = 1.0f, aInit = 0.0f ,c1 = 0.0f, c2 = 0.0f;

    glClear(GL_COLOR_BUFFER_BIT);


    GLUquadricObj *pt;

    pt=gluNewQuadric();

    // Esta orden especifica como va a ser renderizado:
    gluQuadricDrawStyle(pt,GLU_LINE);

    glColor3f (1.0, 0.0, 0.0);
    // Dibuja Discos
    gluDisk(pt, 0, 9, 36, 6);

    // Color de la funcion
    glColor3f(0.0,0.0,0.5);

    glBegin(GL_LINE_STRIP);

    glPushMatrix();

    for(ang = 0.0f; ang  <= 2*GL_PI; ang += 2*GL_PI/100) {
        /* Curva 1
        x = 2*cos(ang) + 2*sin(2*ang);
        y = 2*sin(ang) + 4*pow(sin(ang),2);

        /* Curva 2
        x = (8*cos(2*ang))*cos(ang);
        y = (8*cos(2*ang))*sin(ang);

        /* Curva 3*/

       /* x = ang*cos(ang);
        y = ang*sin(ang);*/

        /*Curva 4*/

        x = 3*cos(ang) - 3*sin(ang)*cos(ang);
        y = 3*sin(ang) - 3*pow(sin(ang),2);

        glVertex2f(x,y);

    }

    glEnd();

    glFlush();

}

void reshape(int w, int h) {

    glViewport(0, 0, (GLsizei) w, (GLsizei) h);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    glOrtho(-10.0, 10.0, -10.0, 10, -10.0, 10.0);

    glMatrixMode

    (GL_MODELVIEW);

    glLoadIdentity();

}
