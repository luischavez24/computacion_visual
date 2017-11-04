
#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include<conio.h>
#include <math.h>
#include<iostream>

using namespace std;

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
float curvaBezierCasteljau(float, int, int );
void addPunto(float x, float y);
void menu_color(int opcion);
void menu_principal (int opcion);
float dim=400;

float pcontrol[20][2];

int N= 0, paso=0;

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
    glClearColor(1.0,1.0,1.0,0.0);
    glShadeModel(GL_FLAT);
    //int m_color = glutCreateMenu(menu_color);
    //    glutAddMenuEntry("Red", 1);
    //    glutAddMenuEntry("Green", 2);
    //    glutAddMenuEntry("Blue", 3);
    int menu = glutCreateMenu(menu_principal);

    glutAddMenuEntry("Draw curve", 1);
    glutAddMenuEntry("No draw curve", 2);
    glutAddMenuEntry("Add point", 3);
    glutAddMenuEntry("Alter point at ...", 4);
    //    glutAddSubMenu("Select a color", m_color);
    glutAddMenuEntry("Close", 5);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
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

void listPoints()
{

    printf("--------List of points-------\n");
    for(int i = 0; i < N; i++)
    {
        printf("Point at %d index: (%.2f, %.2f)\n", i + 1, pcontrol[i][0], pcontrol[i][1]);
    }
    printf("------------------------------\n");
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
        x = curvaBezierCasteljau(u, 0, N);
        y = curvaBezierCasteljau(u, 1, N);

        glVertex2f(x,y);
    }
    glEnd();
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

void addPunto(float x, float y)
{
    if(N<20)
    {
        pcontrol[N][0] = x;
        pcontrol[N][1] = y;
        N++;
    }
    else
    {
        printf("You can´t add another point");
    }
}

void menu_add_point()
{
    float x_p, y_p;
    printf("Please enter a point (x,y) \n");
    cin>>x_p;
    cin>>y_p;
    addPunto(x_p, y_p);

}

void menu_alter_point()
{
    float x_p, y_p;
    int item;
    listPoints();

    printf("Which point do you want to edit?: ");
    cin>>item;

    do{
        printf("Please enter a point (x,y) \n");
        cin>>x_p;
        cin>>y_p;

        pcontrol[item - 1][0] = x_p;
        pcontrol[item - 1][1] = y_p;

    } while(item > N);

}

void menu_color(int opcion)
{
    switch(opcion)
    {
    case 1:
        glColor3f(1.0,0.0,0.0);
        glutPostRedisplay();
        break;
    case 2:
        glColor3f(0.0,1.0,0.0);
        glutPostRedisplay();
        break;
    case 3:
        glColor3f(0.0,0.0,1.0);
        glutPostRedisplay();
        break;
    }


}

void menu_principal (int opcion)
{
    system("cls");
    switch (opcion)
    {
    case 1:
        paso=1;
        // se grafica la curva de Bezier
        glutPostRedisplay();
        break;
    case 2:
        paso=0;
        // No se grafica la curva de Bezier
        glutPostRedisplay();
        break;

    case 3 :
        menu_add_point();
        glutPostRedisplay();
        break;

    case 4 :
        menu_alter_point();
        glutPostRedisplay();
        break;
    case 5:
        exit(0);
        break;
    }
}
