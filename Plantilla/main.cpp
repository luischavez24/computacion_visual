#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<GL/glut.h>
#define pi 3.1416f

void init(void);
void display(void);
void reshape(int,int);
void menu();


GLdouble angulo = 0.0, incremento = 0.02;
static GLfloat theta[] = {0.0,0.0,0.0};
GLint axis = 2 ;
int modelo = 0;
GLfloat px0=0,py0=0,pz0=5;
GLfloat px1=0,py1=0,pz1=4;
GLdouble const radio=0.5;

/**< funciones propias */



void dibujar_ejes(int longitud)
{
        // Eje X
        glBegin(GL_LINE_STRIP);
        glColor3f(1,0,0);
        glVertex3f(0,0,0);
        glVertex3f(longitud,0,0);
        glEnd();
        // Eje y
        glBegin(GL_LINE_STRIP);
        glColor3f(0,1,0);
        glVertex3f(0,0,0);
        glVertex3f(0,longitud,0);
        glEnd();
        // Eje Z
        glBegin(GL_LINE_STRIP);
        glColor3f(0,0,1);
        glVertex3f(0,0,0);
        glVertex3f(0,0,longitud);
        glEnd();
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
void retrocede()
{
    px1=px0;
    pz1=pz0;
    px0=px0-radio*sin(angulo);
    pz0=pz0+radio*cos(angulo);
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


void menu_modelos_alambricos(int opcion)
{
    switch(opcion)
    {
    case 3 :
        exit(0);
        break;
    }
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


void menu_principal(int opcion)
{
    switch(opcion)
    {
    case 4:
        exit(-1);
    }
}

void menu() {

            int submenu_glut=glutCreateMenu(menu_glut);
            glutAddMenuEntry("Cubo",1);
            glutAddMenuEntry("Esfera",2);
            glutAddMenuEntry("Toroide",3);

            int submenu_primi_propia=glutCreateMenu(menu_primi_propia);
            glutAddMenuEntry("Estructura", 1);
            glutAddMenuEntry("Cilindro", 2);
            glutAddMenuEntry("Función", 3);

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

}

/**< Configuración GLUT */

void init(void)
{
    glClearColor(1.0,1.0,1.0,0.0);
    glShadeModel(GL_FLAT);
    glLineWidth(1.5);
    glPointSize(3.0);
}

void teclado(unsigned char tecla,int x,int y)
{
    switch(tecla)
    {
    case 'a' :
        avanza();
        break;
    case 'r' :
        retrocede();
        break;
    case 'i' :
        angulo=angulo+incremento;
        rotacamara();
        break;
    case 'd' :
        angulo=angulo-incremento;
        rotacamara();
        break;
    case '+' :
        incremento *= 1.35;
        break;
    case '-' :
        incremento /= 1.35;
        break;
    case 'f' :
        exit(0);
        break;
    }
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);   //para hacer mas de una transformación
    glLoadIdentity();
    gluLookAt(0.5,0.3,0.5,0,0,0,0,1,0);
    dibujar_ejes(3);

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
    }

    /**<Inicio de código  */

    glColor3f(1.0,0.0,1.0);

    /**<Fin de código  */
    glFlush();
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

void idle()
{
    theta[axis] += incremento;
    if(theta[axis] > 360)
        theta[axis] -= 360.0;
    display();
}

/**< Fin de Configuración Glut */


int main(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_ALPHA);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Plantilla");
    menu();


    glutKeyboardFunc(teclado);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);
    init();
    glEnable(GL_DEPTH_TEST);

    glutMainLoop();
    return 0;

}
