#include <stdlib.h>
#include<conio.h>
#include<stdio.h>
#include<math.h>
#include <gl/glut.h>
GLdouble const pi = 3.141592654;
GLdouble angulo=0;
GLint modelo=1;
GLdouble const radio=1.0;
static GLfloat theta[] = {0.0,0.0,0.0};
static GLint axis = 2 ;
GLfloat L=1.5,R,alfa;


void iniciar(void)
{
    glClearColor (1.0, 1.0, 1.0, 0.0);
    glColor3f (1.0, 0.0, 0.0);
    glLineWidth(2.0);
    glShadeModel (GL_FLAT);
}
void estructura(void)
{
    R=L/sin(M_PI/8);
    alfa=45; //M_PI/4;
    glScalef(0.25,0.25,0.25);
    for(float i=0;i<8;i++)
    {
        glPushMatrix();
        glRotatef(i*alfa,0,0,1);
        glTranslatef(R*cos(M_PI/8)+L,0,0);
        glutWireCube(2*L);
        glPopMatrix();
    }
}

void superficie(int n, float paso)
{

    for(float i = -n; i < n; i += paso)
    {
        glBegin(GL_LINE_STRIP);
        for(float j = -n; j < n; j += paso)
        {
            glVertex3f(i, j, exp(-i*i) + exp(-j*j));
        }
        glEnd();

        glBegin(GL_LINE_STRIP);
        for(float j = -n; j < n; j += paso)
        {
            glVertex3f(j, i, exp(-i*i) + exp(-j*j));
        }
        glEnd();
    }
}

void circulo(float radio, int ptos_base, float referencia){

    glBegin(GL_LINE_STRIP);
        for(float ang = 0; ang <= 2*pi; ang += 2*pi/ptos_base){
            glVertex3f(radio*sin(ang), referencia, radio*cos(ang));
        }
    glEnd();
}

void cilindro(int nCortes, int nPara){
    float radio =1, altura=2;

    for(float h = -altura/2; h <= altura/2; h += altura/nPara){
        circulo(radio, nCortes, h);
    }


    for(float ang = 0; ang <= 2*pi; ang += 2*pi/nCortes){
        glBegin(GL_LINE_STRIP);
            glVertex3f(radio*sin(ang), altura/2, radio*cos(ang));
            glVertex3f(radio*sin(ang), -altura/2, radio*cos(ang));
        glEnd();
    }
}

void circulo_relleno(float radio, int ptos_base, float referencia){

    glBegin(GL_POLYGON);
        for(float ang = 0; ang <= 2*pi; ang += 2*pi/ptos_base){
            glVertex3f(radio*sin(ang), referencia, radio*cos(ang));
        }
    glEnd();
}

void cilindro_relleno(int nCortes, int nPara){
    float radio =1, altura=2, paso = 2*pi/nCortes;
    circulo_relleno(radio, nCortes, -altura/2);
    circulo_relleno(radio, nCortes, altura/2);
    for(float ang = 0; ang <= 2*pi; ang += paso){
        glBegin(GL_POLYGON);
            glVertex3f(radio*sin(ang), altura/2, radio*cos(ang));
            glVertex3f(radio*sin(ang + paso), altura/2, radio*cos(ang + paso));
            glVertex3f(radio*sin(ang + paso), -altura/2, radio*cos(ang + paso));
            glVertex3f(radio*sin(ang), -altura/2, radio*cos(ang));
            glVertex3f(radio*sin(ang), altura/2, radio*cos(ang));
        glEnd();
    }
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0,0.0,5,0,0.0,4,0,1,0);
    glRotatef(theta[0],1.0,0.0,0.0);
    glRotatef(theta[1],0.0,1.0,0.0);
    glRotatef(theta[2],0.0,0.0,1.0);
    switch(modelo)
    {
    case 1:
        glutWireCube(2);
        break;
    case 2:
        glutWireSphere(1,10,10);
        break;
    case 3:
        glutWireTorus(0.2,1.5,10,10);
        break;
    case 4:
        estructura();
        break;
    case 6:
        superficie(5,0.3f);
        break;
    case 5:
        //cilindro(72,50);
        cilindro_relleno(10,15);
        break;
    }
    glFlush();
    glutSwapBuffers();
}
void CubeSpin()
{
    theta[axis] += 0.05;
    if(theta[axis]>360) theta[axis] -= 360.0;
    display();
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
void menu_rotaciones(int opcion)
{
    switch(opcion)
    {
    case 1:
        axis = 0;
        break;
    case 2:
        axis = 1;
        break;
    case 3:
        axis = 2;
        break;
    case 4 :
        exit(0);
        break;
    }
}
void menu_modelos_alambricos(int opcion)
{
    switch(opcion)
    {
    case 1:
        modelo=4;
        break;
    case 3 :
        exit(0);
        break;
    }
}
void menu_glut(int opcion)
{
    switch(opcion)
    {
    case 1:
        modelo=1;
        break;
    case 2:
        modelo=2;
        break;
    case 3:
        modelo=3;
        break;
    }
}
void menu_color(int opcion)
{
    switch(opcion)
    {
    case 1:
        glColor3f (1.0, 0.0, 0.0);
        break;
    case 2:
        glColor3f (0.0, 1.0, 0.0);
        break;
    case 3:
        glColor3f (0.0, 0.0, 1.0);
        break;
    }
}
void menu_primi_propia(int opcion)
{
    switch(opcion)
    {
    case 1:
        modelo=4;
        break;
    case 2:
        modelo=5;
        break;
    case 3:
        modelo=6;
    }
}
void menu_principal(int opcion)
{
    switch(opcion)
    {
//case 1: int i=0;break;
    case 4:
        exit( -1 );
    }
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500,500);
    glutCreateWindow("Modelos Alambricos usando menus jerarquicos con Glut ");
    int submenu_glut=glutCreateMenu(menu_glut);
    glutAddMenuEntry("Cubo",1);
    glutAddMenuEntry("Esfera",2);
    glutAddMenuEntry("Toroide",3);
    int submenu_primi_propia=glutCreateMenu(menu_primi_propia);
    glutAddMenuEntry("Estructura", 1);
    glutAddMenuEntry("Cilindro", 2);
    glutAddMenuEntry("Funci�n", 3);
    int submenu_modelos_alambricos=glutCreateMenu(menu_modelos_alambricos);
    glutAddSubMenu("Libreria glut",submenu_glut);
    glutAddSubMenu("Libreria propia",submenu_primi_propia);
    int submenu_rotaciones=glutCreateMenu(menu_rotaciones);
    glutAddMenuEntry("Eje X",1);
    glutAddMenuEntry("Eje Y",2);
    glutAddMenuEntry("Eje Z",3);
    int submenu_color=glutCreateMenu(menu_color);
    glutAddMenuEntry("Rojo",1);
    glutAddMenuEntry("Verde",2);
    glutAddMenuEntry("Azul",3);
    int menu=glutCreateMenu(menu_principal);
    glutAddSubMenu("Modelos Alambricos",submenu_modelos_alambricos);
    glutAddSubMenu("Rotaciones",submenu_rotaciones);
    glutAddSubMenu("Colores",submenu_color);
    glutAddMenuEntry("Salir",4);
// usaremos el boton derecho del mouse
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    iniciar();
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutIdleFunc(CubeSpin);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}
