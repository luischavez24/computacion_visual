#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<GL/glut.h>
#define PI 3.1416f

// Definicion de funciones

void init(void);
void display(void);
void reshape(int,int);
void dibujarEjes();
void dibujarPendulo(GLfloat, GLfloat, GLfloat, GLfloat);
void oscilacion();

// Declaración de variables globales

GLfloat theta = 15, ang = 0, aumento = 0.01, z=0 ,y=0;

int main(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB |GLUT_DEPTH);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutIdleFunc(oscilacion);    ///va a estar oscilando siempre
    glutReshapeFunc(reshape);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();

    return 0;
}

void init(void)
{
    glClearColor(1.0,1.0,1.0,0.0);
    glShadeModel(GL_FLAT);
    glLineWidth(1.5);
    glPointSize(3.0);
    glColor3f(1.0,0.0,0.0);
}

void display(void)
{
    GLfloat cam_x=1.5, cam_y = 1, cam_z = 1, lejos=3;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cam_x*lejos,cam_y*lejos,cam_z*lejos,0,0,0,0,1,0);
    dibujarEjes();
    GLfloat l = 15, angulo = 15;
    // Sistema del pendulo
    glPushMatrix();
        glTranslated(0,l,0);
        glRotated(ang,1, 0, 0);
        dibujarPendulo(l, 0, 0, angulo);
    glPopMatrix();
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

void dibujarPendulo(GLfloat longitud, GLfloat x_init, GLfloat y_init, GLfloat ang)
{
    GLfloat a = x_init + longitud * sin(ang*PI/180);
    GLfloat b = y_init - longitud * cos(ang*PI/180);

    //printf("(%.2f, %.2f)\n", a, b);

    glColor3f(1,0,1);
    glBegin(GL_LINE_STRIP);
        glVertex3f(0, y_init,x_init);
        glVertex3f(0, b,a);
    glEnd();
    glColor3f(1,1,0);
    glPushMatrix();
        glTranslated(0, b, a);
        glutWireSphere(0.5,10,10);
    glPopMatrix();

}
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

void oscilacion(){   ///variables globale del Idle
    //printf("(0, %.2f, % .2f)\n", y, z);
    z = 20*cos(ang * (PI/180));
    y = 20*sin(ang * (PI/180)) + 20;

    ang += aumento;

    if(ang <= 0 || ang >= 30){
        aumento *= -1;
    }

    display();
}

