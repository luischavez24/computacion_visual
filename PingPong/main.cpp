#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <GL/glut.h>
#define GL_PI 3.1416f

float FactorY=0.080;
float FactorX=0.097;
float X=0;
float Y=0;

void Pelotita(){
    glScalef(1.0,1.0,0);
    glutSolidCube(0.5);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	if(X>=10){
        X=10;
        FactorX*=-1;
	}else if(X<=-10){
        X=-10;
        FactorX*=-1;
    }
	if(Y>=10){
        Y=10;
        FactorY*=-1;
	}else if(Y<=-10){
        Y=-10;
        FactorY*=-1;
    }
    glPushMatrix();
    glTranslatef(X,Y,0);
	Pelotita();
	glPopMatrix();
	X+=FactorX;
	Y+=FactorY;
	glFlush();
    glutSwapBuffers();

}

void reshape(int w, int h)
{
    glViewport(0,0,(GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0,10.0,-10.0,10,-10.0,10.0);
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

