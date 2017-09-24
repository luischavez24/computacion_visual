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
void regionCircuferencia(GLfloat aInit, GLfloat cx, GLfloat cy, GLfloat r);

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

    GLfloat r = 0.0f, l = 1.0f, aInit = 0.0f ,c1 = -l/2, c2 = -l/2;
    int vx = -1, vy = 1;
    glClear(GL_COLOR_BUFFER_BIT);
    ejes(l);
    glBegin(GL_LINE_STRIP);
    glPushMatrix();
    glColor3f(0.0,0.0,0.5);

    for(int i = 0; i < 7; i++) {
        r += l;
        // El vector que se multiplica escalarmente tiene como coordenas un par anterior
        vx *= -1;vy *= -1;
        regionCircuferencia(aInit, c1,c2, r);
        c1 *= vx; c2 *= vy;
        aInit += GL_PI/2;
    }

    glPopMatrix();

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

void regionCircuferencia(GLfloat aInit, GLfloat cx, GLfloat cy, GLfloat r) {

    GLfloat ang, x, y;
    for(ang = aInit; ang  <= aInit + GL_PI/2 ; ang += 2*GL_PI/80) {
        x = r * cos(-ang) + cx;
        y = r * sin(-ang) + cy;
        glVertex2f(x,y);
    }
}

void ejes(GLfloat l) {

    glColor3f(1.0,0.0,0.0);
    glBegin(GL_LINE_STRIP);
    glPushMatrix();
    glVertex2f(-l/2,-l/2);
    glVertex2f(250,-l/2);
    glPopMatrix();
    glEnd();

    glBegin(GL_LINE_STRIP);
    glPushMatrix();
    glVertex2f(-l/2,l/2);
    glVertex2f(l/2,-250);
    glPopMatrix();
    glEnd();

    glBegin(GL_LINE_STRIP);
    glPushMatrix();
    glVertex2f(l/2,l/2);
    glVertex2f(-250,l/2);
    glPopMatrix();
    glEnd();

    glBegin(GL_LINE_STRIP);
    glPushMatrix();
    glVertex2f(l/2,-l/2);
    glVertex2f(l/2,250);
    glPopMatrix();
    glEnd();
}
