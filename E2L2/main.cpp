#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<GL/glut.h>
#define GL_PI 3.1416f

// Definicion de funciones

void init(void);
void display(void);
void reshape(int,int);
void dibujarCuadrado(GLfloat);

int main(int argc, char** argv)
{

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
    //declaracion de variables
    GLfloat ang = 0, da = 3, scal = 1;

    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);   //para hacer mas de una transformación
    glLoadIdentity();

    for(ang = -20; ang <= 0; ang += da)
    {
        glPushMatrix();
            printf("Rotando %2.1f\n", da);
            glRotatef(ang,0,0,1);      //rotará en el eje z, significa rotar en el plano xy
            glScalef(scal,scal,0);
            dibujarCuadrado(13);
        glPopMatrix();

        scal *= 0.98*0.9;
     }


    glFlush();
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

void dibujarCuadrado(GLfloat l)
{
    //dibujando cuadrado, uniendo los 4 vertices
    glBegin(GL_LINE_STRIP);
        glVertex3f(l/2,l/2,0);
        glVertex3f(l/2,-l/2,0);
        glVertex3f(-l/2,-l/2,0);
        glVertex3f(-l/2,l/2,0);
        glVertex3f(l/2,l/2,0);
    glEnd();
}
