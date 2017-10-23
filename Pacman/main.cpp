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
void dibujarPendulo(GLfloat, GLfloat, GLfloat, GLfloat);
void idleFunc();
void regionCircuferencia(GLfloat aInit,GLfloat aEnd, GLfloat cx, GLfloat cy, GLfloat r);
void espacio(GLfloat width, GLfloat heigth);
void dibujarOjo(float x, float y);

GLfloat w = 16, h = 10, radio = 0.5, x_av = - w/2 + radio, y_av = 0, ang = 145, rot_x= 1, rot_y= 1;
GLfloat angulo_boca = 90;
GLfloat r = 1, g = 1, b = 0;   //colores

float convertirGrados(float degree)
{
    return (GL_PI/180) * degree;
}

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
}

void display(void)
{
    //GLfloat cam_x=1.5, cam_y = 1, cam_z = 1, lejos=3;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    espacio(w, h);
    glPushMatrix();
        //glTranslatef(x_av, y_av, 0);
        dibujarOjo(0.1+x_av,0.25+y_av);
        regionCircuferencia(convertirGrados(angulo_boca/2),convertirGrados(360-angulo_boca/2),x_av,y_av,radio);
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
void dibujarOjo(float x, float y)
{
    glColor3f(r,g,b);
    glLineWidth(4.5);
    glBegin(GL_POINTS);
        glVertex3f(x,y,0);
    glEnd();
    glLineWidth(1);
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

float recta(float angulo_inclinacion, float x, float x0, float y0)
{
    return (tan(convertirGrados(angulo_inclinacion))) * (x - x0) + y0;
}

GLfloat dx = 0.0025, dy = recta(ang,-w/2 + radio,- w/2 + radio, 0.5) - recta(ang, -w/2 + radio - dx,- w/2 + radio, 0.5);
GLfloat aumento_boca = 0.05;

// Idle Func
void idleFunc(){

    x_av += dx * rot_x;
    y_av += dy * rot_y;

    if(y_av >= h/2-radio || y_av <= -h/2 + radio)
    {
        rot_y*= -1;
        r = 0;
        g = 0;
        b = 1;

    }
    else if(x_av >= w/2-radio || x_av <= -w/2 + radio)
    {
        rot_x*=-1;
        r = 0;
        g = 1;
        b = 0;
    }
    if(angulo_boca >= 90 || angulo_boca <= 0){
        aumento_boca *= -1;
    }
    angulo_boca += aumento_boca;

    display();
}

void regionCircuferencia(GLfloat aInit,GLfloat aEnd, GLfloat cx, GLfloat cy, GLfloat r) {
    glBegin(GL_LINE_STRIP);
        glColor3f(r,g,b);
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

