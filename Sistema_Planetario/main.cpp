#include <stdlib.h>
#include<conio.h>
#include<stdio.h>
#include<math.h>
#include <gl/glut.h>
#define PI 3.1415926
void ejes(int);
GLdouble angulo=0, incremento_angulo=0.1;
GLdouble const radio=0.5;
GLfloat px0=0,py0=0,pz0=5;
GLfloat px1=0,py1=0,pz1=4;
static GLfloat theta[] = {0.0,0.0,0.0};
static GLfloat theta2[] = {0.0,0.0,0.0};
static GLint axis = 1 ;
GLfloat aLuna = 0.0, xLuna = 0.0f, zLuna = 0.0f, e, rp, bLuna;

void iniciar(void)
{
    glClearColor (1.0, 1.0, 1.0, 0.0);
    glShadeModel (GL_FLAT);
}
void orbita_lunar(GLfloat a, GLfloat b)
{
    e = sqrt(1 - pow(b,2)/pow(a,2));
    GLfloat x, z, r;
    bLuna = b;
    glColor3f(0.0, 0.0, 0.0);

    glBegin(GL_LINE_STRIP);
    for(GLfloat ang = 0.0f; ang <= 2*PI; ang += 2*PI/150)
    {
        r = b/sqrt(1 - pow(e*cos(ang),2));
        x = r * cos(ang);
        z = r * sin(ang);
        glVertex3f(x,0,z);
    }
    glEnd();
}
void tierra_luna()
{

    /*glRotatef(theta[0],1.0,0.0,0.0);
    glRotatef(theta[1],0.0,1.0,0.0);
    glRotatef(theta[2],0.0,0.0,1.0);*/
    glRotatef(45,1.0,0.0,0.0);
    glPushMatrix();
        orbita_lunar(8.0f,4.0f);
    glPopMatrix();
    glPushMatrix();
        glColor3f (0.0, 0.0, 1.0);
        glRotatef(theta[1],0.0,1.0,0.0);
        glRotatef(90,1.0,0.0,0.0);
        glutWireSphere(2,18,18);
    glPopMatrix();

    glPushMatrix();
        glColor3f(1.0,0.0,0.0);
        glTranslatef(xLuna, 0, zLuna);
        glRotatef(theta[1],0.0,1.0,0.0);
        glRotatef(90,1.0,0.0,0.0);
        glutWireSphere(0.2,18,18);

    glPopMatrix();
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

    //glutWireDodecahedron();
    tierra_luna();
    glFlush();
    glPopMatrix();
    glutSwapBuffers();
}
void CubeSpin()
{
    rp = bLuna/sqrt(1 - pow(e*cos(aLuna),2));
    xLuna = rp * cos(aLuna);
    zLuna = rp * sin(aLuna);
    aLuna += 0.001;
    if(aLuna >= 2*PI) aLuna -= 2*PI;

    theta[axis] += 0.1;
    if(theta[axis]>360) theta[axis] -= 360.0;
    theta2[axis] += 0.04;
    if(theta2[axis]>360) theta2[axis] -= 360.0;
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
    case 'i' :
        avanza();
        break;
    case 'm' :
        retro();
        break;
    case 'j' :
        angulo=angulo+incremento_angulo;
        rotacamara();
        break;
    case 'k' :
        angulo=angulo-incremento_angulo;
        rotacamara();
        break;
    /*case 'a' :
        axis = 0;
        break;
    case 's' :
        axis = 1;
        break;
    case 'd' :
        axis = 2;
        break;*/
    case 'f' :
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
