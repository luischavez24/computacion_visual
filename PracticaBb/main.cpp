#include <stdlib.h>
#include<conio.h>
#include<stdio.h>
#include<math.h>
#include <gl/glut.h>

void ejes(int);
static GLfloat theta[] = {0.0,0.0,0.0};
static GLint axis = 1 ;
float incremento_velo = 0.03;


void iniciar(void)
{
    glClearColor (1.0, 1.0, 1.0, 0.0);
    glShadeModel (GL_FLAT);
    glLineWidth(1.5);
}

void dibujarTriangulo1()
{
    glColor3f(0,0,1);
    glBegin(GL_POLYGON);
    glVertex3f(0.5,0,-0.5);
    glVertex3f(-0.5,0,0.5);
    glVertex3f(-0.5,0,-0.5);
    glVertex3f(0.5,0,-0.5);
    glEnd();

    glColor3f(0,0,0);
    glBegin(GL_POLYGON);
    glVertex3f(0.5,0,-0.5);
    glVertex3f(0.5,-1,-0.5);
    glVertex3f(-0.5,-1,-0.5);
    glVertex3f(-0.5,0,-0.5);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(0,0,0);
    glVertex3f(-0.5,0,-0.5);
    glVertex3f(-0.5,-1,-0.5);
    glVertex3f(-0.5,-1,0.5);
    glVertex3f(-0.5,0,0.5);
    glEnd();

}

void dibujarTriangulo2()
{
    glColor3f(0,1,0);
    glBegin(GL_POLYGON);
    glVertex3f(0.5,0,-0.5);
    glVertex3f(-0.5,0,0.5);
    glVertex3f(0.5,0,0.5);
    glVertex3f(0.5,0,-0.5);
    glEnd();

    glColor3f(0,0,0);
    glBegin(GL_POLYGON);
    glVertex3f(0.5,0,-0.5);
    glVertex3f(0.5,-1,-0.5);
    glVertex3f(0.5,-1,0.5);
    glVertex3f(0.5,0,0.5);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(0,0,0);
    glVertex3f(0.5,0,0.5);
    glVertex3f(0.5,-1,0.5);
    glVertex3f(-0.5,-1,0.5);
    glVertex3f(-0.5,0,0.5);
    glEnd();
}

void cuadrito() {
    glPushMatrix();
        glScalef(1,0.45,1);
        dibujarTriangulo1();
        dibujarTriangulo2();
    glPopMatrix();
}
void generarTablero()
{
    for (float i = -3.5; i <= 3.5; i++)
    {
        for (float j = -3.5; j <= 3.5; j++)
        {
            glPushMatrix();
                glTranslatef(i, 0, j);
                cuadrito();
            glPopMatrix();
        }
    }
}
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glLoadIdentity();

    gluLookAt(0.5,0.3,0.5,0,0,0,0,1,0);
    ejes(3);

    glRotatef(theta[0],1.0,0.0,0.0);
    glRotatef(theta[1],0.0,1.0,0.0);
    glRotatef(theta[2],0.0,0.0,1.0);

    generarTablero();
    //cuadrito();

    glFlush();
    glPopMatrix();
    glutSwapBuffers();
}
void CubeSpin()
{
    theta[axis] += incremento_velo;
    if(theta[axis]>360) theta[axis] -= 360.0;
    display();
}


void teclado(unsigned char tecla,int x,int y)
{
    switch(tecla)
    {

   /* case 'x' :
        axis = 0;
        break;
    case 'y' :
        axis = 1;
        break;
    case 'z' :
        axis = 2;
        break;
        */
    case '+' :
        incremento_velo *= 1.35;
        break;
    case '-' :
        incremento_velo /= 1.35;
        break;
    case 'q' :
        exit(0);
        break;
    }
}
void ejes(int longitud)
{
    glBegin(GL_LINES);
    glColor3f(0,1,0);
    glVertex3d(0,0,longitud);
    glVertex3d(0,0,0);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1,0,0);
    glVertex3d(0,0,0);
    glVertex3d(0,longitud,0);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0,0,1);
    glVertex3d(0,0,0);
    glVertex3d(longitud,0,0);
    glEnd();
}
void myReshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    glOrtho(-6.0, 6.0, -6.0, 6, -6.0, 6.0);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500,500);
    glutCreateWindow("camara movil");
    iniciar();
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutIdleFunc(CubeSpin);
    glutKeyboardFunc(teclado);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}
