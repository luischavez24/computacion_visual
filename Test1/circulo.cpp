#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<GL/glut.h>
#define GL_PI 3.1416f

// Definicion de funciones

void init(void);
void display(void);
void reshape(int,int);

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

    glColor3f(0.0,0.5,0.0);

}

void display(void) {

    int cant = 6;

    GLfloat ang, lgn = 16.0f, x, y, lim;

    glClear(GL_COLOR_BUFFER_BIT);

    for (int i = 0; i < cant ; i++) {

        // Determinar el angulo
        ang = (i % 2 == 0) ? -GL_PI/4:0.0f;
        // Determinar el radio del circulo
        lgn *= sqrt(2)/2;
        // Determinar el luaar de la ultima coordenada
        lim = 2*GL_PI + ang;

        glBegin(GL_LINE_STRIP);

        glPushMatrix();

        for(int a = ang; ang <= lim; ang += 2*GL_PI/4){
            x = lgn * cos(ang);
            y = lgn * sin(ang);
            glVertex2f(x,y);
        }

        glPopMatrix();

        glEnd();

    }

    glFlush();

}

void reshape(int w, int h) {

    glViewport(0, 0, (GLsizei) w, (GLsizei) h);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    glOrtho(-10.0, 10.0, -10.0, 10, -10.0, 10.0);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

}
