/*
#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include<conio.h>
#include <math.h>


void dibujarEjes(void);
void init(void);
void display(void);
void reshape(int,int);
void keyboard(unsigned char, int, int);
void graficaCurvaBezier(void);
float CoeficienteNewton(int,int);
float factorial(int);
float CurvaBezier(float,int);
void graficaPuntosBezier(void);
float curvaBezierCasteljau(float, int , int );
float dim=400;

/*float pcontrol[6][2]= {
    {-10.0,0.0},
    {-10.0,10.0},
    {10.0,10.0},
    {10.0,0.0},
    {10.0,-10.0},
    //{0.0,-0.0},
    {-10.0,-10.0}

};

float pcontrol[5][2] = {
    {-3.0,  3.0},
    {1.0 ,  4.0},
    { 0.0 , 10.0},
    { 5.0 ,  5.0},
    {10.0 ,  0.0}
};



int N= 5, paso=0;

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(dim,dim);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Grafico de una curva de Bezier 2D");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

void dibujarEjes(void)
{
    glBegin(GL_LINES);
    glVertex2f(-20,0);
    glVertex2f(20,0);
    glVertex2f(0,-20);
    glVertex2f(0,20);
    glEnd();
}

void init(void)
{
// parametros: rojo, amarillo y azul, el cuarto es el parametro alpha
// color de fondo
    glClearColor(0.0,0.0,0.0,0.0);
    glShadeModel(GL_FLAT);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
// salva el estado actual de la matriz
    glPushMatrix();
    glColor3f(1.0,0.0,0.0);
    dibujarEjes();
    glColor3f(0.0,0.0,1.0);
    if (paso==1)
    {
        glPointSize(5);
        graficaPuntosBezier();
        glPointSize(1);
        glColor3f(0.0,1.0,0.0);
        graficaCurvaBezier();
    }
    glPopMatrix();
// reecupera el estado del matriz
    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)

    {
    case 'b':
        paso=1;
// se grafica la curva de Bezier
        glutPostRedisplay();
        break;
    case 'n':
        paso=0;
// No se grafica la curva de Bezier
        glutPostRedisplay();
        break;
    case 27:
        exit(0);
        break;

    }
}

void reshape(int w, int h)
{
    glViewport(0,0,(GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(
        -20.0,20.0,
        -20.0,20,
        -1.0,1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void graficaPuntosBezier(void)
{
    float x,y;
    glBegin(GL_POINTS);
    for(int i=0; i<N; i++)
    {
        x=pcontrol[i][0];
        y=pcontrol[i][1];
        glVertex2f(x,y);
    }
    glEnd();
}

void graficaCurvaBezier(void)
{
    float x,y;
    glBegin(GL_LINE_STRIP);
    for(float u = 0.0; u <= 1; u+= 0.01)
    {
        x=CurvaBezier(u,0);
        y=CurvaBezier(u,1);

        /*x = curvaBezierCasteljau(u, 0, N);
        y = curvaBezierCasteljau(u, 1, N);

        glVertex2f(x,y);
    }
    glEnd();
}

/**
    Newton Coefficients using Dynamic Programming

int coefNewton(int n, int k)
{
    int tPascal[n + 1][n + 1];

    for(int i = 0; i < n + 1; i++)
    {
        for(int j =0; j < n +1; j++ )
        {
            if(j == 0 || i == j)
            {
                tPascal[i][j] = 1;
            }
            else
            {
                tPascal[i][j] = 0;
            }
        }
    }

    for(int i = 2; i < n + 1; i++)
    {
        for(int j =1; j < k +1; j++ )
        {
            tPascal[i][j] = tPascal[i - 1][j] + tPascal[i - 1][j - 1];

        }
    }

    return tPascal[n][k];
}


float CurvaBezier(float u,int coordenada)
{
    float suma=0.0;
    for(int i=0; i<N; i++)
    {
        suma=suma+pcontrol[i][coordenada]*coefNewton(N-1,i)*pow(u,N-1-
                i)*pow(1.0-u,i);
    }
    return suma;
}

float curvaBezierCasteljau(float u, int coordenada, int n)
{
    float tCasteljau[n][n];

    for(int i = 0; i <= n; i++)
    {
        tCasteljau[0][i] = pcontrol[i][coordenada];
    }

    for(int i = 1; i < n; i++)
    {
        for(int j = 0; j < n - i; j++)
        {
            tCasteljau[i][j] = (1 - u) * tCasteljau[i-1][j] + u * tCasteljau[i-1][j + 1];
        }
    }

    return tCasteljau[n - 1][0];
}
*/
