#include <stdlib.h>
#include<conio.h>
#include<stdio.h>
#include<math.h>
#include <gl/glut.h>

void ejes(int);

GLdouble angulo=0, incremento_angulo=0.1;
GLdouble const radio=0.5;
GLfloat px0=0,py0=0,pz0=5;
GLfloat px1=0,py1=0,pz1=4;
static GLfloat theta[] = {0.0,0.0,0.0};
static GLint axis = 2 ;

void iniciar(void)
{
    glClearColor (1.0, 1.0, 1.0, 0.0);
    glShadeModel (GL_FLAT);
}

void estructura1()
{
    for(GLfloat ang = 0.0f; ang <= 360; ang += 360/10) {
        glPushMatrix();
            glRotatef(ang,0.0,0.0,1.0);
            glTranslatef(2.0,0.0,0.0);

            glutWireCube(1);
        glPopMatrix();
    }
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glLoadIdentity();
// la camara se desplaza sobre el plano xz
    gluLookAt(px0,0.0,pz0,px1,0.0,pz1,0,1,0);
    glColor3f (1.0, 0.0, 0.0);
    ejes(2);
  //rota en los 3 ejes
    glRotatef(theta[0],1.0,0.0,0.0);
    glRotatef(theta[1],0.0,1.0,0.0);
    glRotatef(theta[2],0.0,0.0,1.0);

    glColor3f (0.0, 0.0, 1.0);
    //glutWireDodecahedron();
    estructura1();   //librer�a propia
    glFlush();
    glPopMatrix();
    glutSwapBuffers();
}
void CubeSpin()
{
    theta[axis] += 0.2;
    if(theta[axis]>360) theta[axis] -= 360.0;
    display();
}

void rotacamara()
{
    px1=px0+radio*sin(angulo);
    pz1=pz0-radio*cos(angulo);
}
void avanza()
{
    px0=px1;
    pz0=pz1;
    px1=px0+radio*sin(angulo);
    pz1=pz0-radio*cos(angulo);
}
void retro()
{
    px1=px0;
    pz1=pz0;
    px0=px0-radio*sin(angulo);
    pz0=pz0+radio*cos(angulo);
}
void teclado(unsigned char tecla,int x,int y)
{
    switch(tecla)
    {
    case 'a' :
        avanza();
        break;
    case 'r' :
        retro();
        break;
    case 'i' :
        angulo=angulo+incremento_angulo;
        rotacamara();
        break;
    case 'd' :
        angulo=angulo-incremento_angulo;
        rotacamara();
        break;
    case 'x' :
        axis = 0;
        break;
    case 'y' :
        axis = 1;
        break;
    case 'z' :
        axis = 2;
        break;
    case 'q' :
        exit(0);
        break;
    }
}
void ejes(int longitud)
{
    glBegin(GL_LINES);
    glVertex3d(0,0,longitud);
    glVertex3d(0,0,0);
    glEnd();
    glBegin(GL_LINES);
    glVertex3d(0,0,0);
    glVertex3d(0,longitud,0);
    glEnd();
    glBegin(GL_LINES);
    glVertex3d(0,0,0);
    glVertex3d(longitud,0,0);
    glEnd();
}
void myReshape(int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(60.0, (GLfloat) w/(GLfloat) h,0.1, 30.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500,500);
    glutCreateWindow("Estructura-labo3");
    iniciar();
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutIdleFunc(CubeSpin);
    glutKeyboardFunc(teclado);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}
