#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <GL/glut.h>
#define PI 3.1416f

GLUquadricObj *pt;
int Control=1;

void Cardiode(){
glBegin(GL_LINE_LOOP);
    for(float ang=0;ang<=2*PI;ang+=PI/24){
            float Radio=3-3*sin(ang);
            float x=Radio*cos(ang);
            float y=Radio*sin(ang);
            glVertex2f(x,y);
    }
    glEnd();
}

void Rosal(){
    glBegin(GL_LINE_LOOP);
    for(float ang=0;ang<=2*PI;ang+=PI/24){
            float Radio=3*cos(2*ang);
            float x=Radio*cos(ang);
            float y=Radio*sin(ang);
            glVertex2f(x,y);
    }
    glEnd();
}

void Caracol(){
    glBegin(GL_LINE_LOOP);
    for(float ang=0;ang<=2*PI;ang+=PI/24){
            float Radio=2+ 3*sin(ang);
            float x=Radio*cos(ang);
            float y=Radio*sin(ang);
            glVertex2f(x,y);
    }
    glEnd();
}

void Espiral(){
    glBegin(GL_LINE_STRIP);
    for(float ang=0;ang<=2*PI;ang+=PI/24){
            float Radio=ang;
            float x=Radio*cos(ang);
            float y=Radio*sin(ang);
            glVertex2f(x,y);
    }
    glEnd();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	pt=gluNewQuadric();
	gluQuadricDrawStyle(pt,GLU_LINE);
    glColor3f (1.0, 0.0, 0.0);
    gluDisk(pt, 0, 5, 24, 6);
    glColor3f (0.0, 0.0, 1.0);
    if(Control==1){
        Caracol();
    }else if(Control==2){
        Rosal();
    }else if(Control==3){
        Cardiode();
    }else if(Control==4){
        Espiral();
    }
	glFlush();
    glutSwapBuffers();

}

void reshape(int w, int h)
{
    glViewport(0,0,(GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-7.0,7.0,-7.0,7,-7.0,7.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void init(void)
{
    glClearColor(1.0,1.0,1.0,0.0);
    glShadeModel(GL_FLAT);

}

void teclado(unsigned char tecla,int x,int y)
{
    switch(tecla){
    case '1': Control=1;break;
    case '2': Control=2;break;
    case '3': Control=3;break;
    case '4': Control=4;break;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    //glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(100,100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutIdleFunc(display); //Cambiar si es necesario
    glutKeyboardFunc(teclado); // Cambiar si es necesario
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}

