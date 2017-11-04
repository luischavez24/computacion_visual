#include <stdlib.h>
#include<conio.h>
#include <gl/glut.h>
#include <stdio.h>
#define EJES 1
#define CASILLA_NEGRA 2
#define CASILLA_BLANCA 3
#define TABLERO 4

// Bustamante Falcon, Jose Carlos
// Chavez Aliaga, Luis Ricardo

//angulo de rotacion
static GLfloat theta = 0.0f;
//angulo de incremento
GLfloat incremento = 0.05f;
//lado de la casilla
static GLfloat lado = 0.5f;
//altura de la casilla
static GLfloat altura = 0.2f;
//colores de iteracion
static GLboolean color = 0;


/**
    Funcion que dibuja un cubo unitario
    param : color
*/
void caras(bool color)
{
    //caras del tablero no visibles

    glColor3f(0.5,0.0,0.0);
    glBegin(GL_POLYGON);
    glVertex3f(1,1,1);
    glVertex3f(1,-1,1);
    glVertex3f(-1,-1,1);
    glVertex3f(-1,1,1);
    glVertex3f(1,1,1);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(1,1,-1);
    glVertex3f(1,-1,-1);
    glVertex3f(-1,-1,-1);
    glVertex3f(-1,1,-1);
    glVertex3f(1,1,-1);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-1,1,1);
    glVertex3f(-1,1,-1);
    glVertex3f(-1,-1,-1);
    glVertex3f(-1,-1,1);
    glVertex3f(-1,1,1);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(1,1,1);
    glVertex3f(1,1,-1);
    glVertex3f(1,-1,-1);
    glVertex3f(1,-1,1);
    glVertex3f(1,1,1);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-1,-1,1);
    glVertex3f(1,-1,1);
    glVertex3f(1,-1,-1);
    glVertex3f(-1,-1,-1);
    glVertex3f(-1,-1,1);
    glEnd();

    //Cara superior de la casilla y su color respectivo
    if(color)
    {
        glBegin(GL_POLYGON);
        glColor3f(1,1,1);
        glVertex3f(-1,1,1);
        glVertex3f(1,1,1);
        glVertex3f(1,1,-1);
        glVertex3f(-1,1,-1);
        glVertex3f(-1,1,1);
        glEnd();

    }
    else
    {
        glBegin(GL_POLYGON);
        glColor3f(0,0,0);
        glVertex3f(-1,1,1);
        glVertex3f(1,1,1);
        glVertex3f(1,1,-1);
        glVertex3f(-1,1,-1);
        glVertex3f(-1,1,1);
        glEnd();
    }

}
/**
    Dibuja el cubo unitario y los escala para generar una casilla del
    tablero
    param : color
*/
void micasilla(bool color, int tipo_casilla)
{
    glNewList(tipo_casilla, GL_COMPILE);
        glPushMatrix();
        glScalef(lado,altura,lado);
        caras(color);
        glPopMatrix();
    glEndList();

}

/**
    Dibuja un tablero sobre el eje xz
    Se itera el tablero de fila en fila y columna en columna
*/
void tablero(void)
{
    glNewList(TABLERO, GL_COMPILE);
        bool color = 0;
        for(float i = -3.5; i < 4; i ++)
        {
            color = !color;
            for(float j = -3.5; j < 4; j++)
            {
                glPushMatrix();
                glTranslatef(i,0.0,j);
                //micasilla(color);
                glCallList((color) ? CASILLA_BLANCA : CASILLA_NEGRA);
                glPopMatrix();
                color = !color;
            }
        }
    glEndList();
}
/**
    Dibuja los ejes coordenados x, y,z
*/
void dibujar_ejes()
{
    glNewList(EJES, GL_COMPILE);
        // Eje X
        glBegin(GL_LINE_STRIP);
        glColor3f(1,0,0);
        glVertex3f(0,0,0);
        glVertex3f(100,0,0);
        glEnd();
        // Eje y
        glBegin(GL_LINE_STRIP);
        glColor3f(0,1,0);
        glVertex3f(0,0,0);
        glVertex3f(0,100,0);
        glEnd();
        // Eje Z
        glBegin(GL_LINE_STRIP);
        glColor3f(0,0,1);
        glVertex3f(0,0,0);
        glVertex3f(0,0,100);
        glEnd();
    glEndList();
}


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.5,0.3,0.5,0,0,0,0,1,0);
    glCallList(EJES);
    glRotatef(theta,0.0,1.0,.0);
    glCallList(TABLERO);
    glutSwapBuffers();
}

/**
    Gira segun el incremento determinado por teclado
*/
void girar_objeto_geometrico ()
{
    theta += incremento;
    if(theta > 360) theta -= 360.0;
    display();
}

/**
    Indica el teclado si aumentar la velocidad de rotacion o no
*/
void teclado(unsigned char tecla,int x,int y)
{
    switch(tecla)
    {
    case '+' :
        incremento += 0.05;
        break;
    case '-' :
        incremento -= 0.05;
        break;
    case 'f' :
        exit(0) ;
        break;
    }
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
void init ()
{
    // Creacion de las Vistas de Visualización
    micasilla(1, CASILLA_BLANCA);
    micasilla(0, CASILLA_NEGRA);
    tablero();
    dibujar_ejes();
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500,500);
    glutCreateWindow("Tablero de Ajedrez");
    glutReshapeFunc(myReshape);
    init();
    glutDisplayFunc(display);
    glutIdleFunc(girar_objeto_geometrico);
    glutKeyboardFunc(teclado);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
}



