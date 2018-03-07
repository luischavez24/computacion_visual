#include <stdlib.h>
#include<conio.h>
#include<stdio.h>
#include<math.h>
#include <gl/glut.h>

#define CUADRITO 1
#define TABLERO10x10 2
#define TABLERO8X8 3
#define TABLERO8X6 4
#define TABLERO6X10 5
#define TABLERO6X6 6

void ejes(int);
static GLfloat theta[] = {0.0,0.0,0.0};
static GLint axis = 1 ;
float incremento_velo = 0.5;
int paso = 1;
int cx=0,cy=0,cz=0;
float m = 2.5,n = 2.5;
float redimX = 1, redimZ = 1;

int lista_actual = TABLERO6X6;


float trasX=-0.5, trasZ=-3.0;

void dibujarTriangulo1()
{
    glColor3f(0,0,1);
    glBegin(GL_POLYGON);
    glVertex3f(0.5,0,-0.5);
    glVertex3f(-0.5,0,0.5);
    glVertex3f(-0.5,0,-0.5);
    glVertex3f(0.5,0,-0.5);
    glEnd();

    glColor3f(0,0,0);
    glBegin(GL_POLYGON);
    glVertex3f(0.5,0,-0.5);
    glVertex3f(0.5,-1,-0.5);
    glVertex3f(-0.5,-1,-0.5);
    glVertex3f(-0.5,0,-0.5);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(0,0,0);
    glVertex3f(-0.5,0,-0.5);
    glVertex3f(-0.5,-1,-0.5);
    glVertex3f(-0.5,-1,0.5);
    glVertex3f(-0.5,0,0.5);
    glEnd();
}

void dibujarTriangulo2()
{
    glColor3f(0,1,0);
    glBegin(GL_POLYGON);
    glVertex3f(0.5,0,-0.5);
    glVertex3f(-0.5,0,0.5);
    glVertex3f(0.5,0,0.5);
    glVertex3f(0.5,0,-0.5);
    glEnd();

    glColor3f(0,0,0);
    glBegin(GL_POLYGON);
    glVertex3f(0.5,0,-0.5);
    glVertex3f(0.5,-1,-0.5);
    glVertex3f(0.5,-1,0.5);
    glVertex3f(0.5,0,0.5);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(0,0,0);
    glVertex3f(0.5,0,0.5);
    glVertex3f(0.5,-1,0.5);
    glVertex3f(-0.5,-1,0.5);
    glVertex3f(-0.5,0,0.5);
    glEnd();
}

void cuadrito() {
    //lista CUADRITO
    glNewList(CUADRITO, GL_COMPILE);
        glPushMatrix();
            glScalef(1,0.45,1);
            dibujarTriangulo1();
            dibujarTriangulo2();
        glPopMatrix();
    glEndList();
}

void generarTablero(float m, float n, int lista)
{
    glNewList(lista, GL_COMPILE);

        for (float i = -m; i <= m; i++)
        {
            for (float j = -n; j <= n; j++)
            {
                glPushMatrix();
                    glTranslatef(i, 0, j);
                    glCallList(CUADRITO);
                glPopMatrix();
            }
        }
    glEndList();
}

void paredesH(int escax)
{
    glPushMatrix();
    glScalef(escax,1,0.5);
    //Por la posición del tablero
    glTranslatef(0,0.3,0);
    glutSolidCube(0.5);
    glPopMatrix();
}

void laberintoH()
{
    glColor3f(cx,cy,cz);
    //1 ex
    glPushMatrix();
    glTranslatef(-2,0,-3);
    paredesH(4);
    glPopMatrix();

    //2 ex
    glPushMatrix();
    glTranslatef(1.5,0,-3);
    paredesH(6);
    glPopMatrix();

    //3
    glPushMatrix();
    glTranslatef(-2.5,0,-2);
    paredesH(2);
    glPopMatrix();

    //4
    glPushMatrix();
    glTranslatef(0.5,0,-2);
    paredesH(6);
    glPopMatrix();

    //5
    glPushMatrix();
    glTranslatef(1,0,-1);
    paredesH(8);
    glPopMatrix();

    //6
    glPushMatrix();
    glTranslatef(1,0,0);
    paredesH(4);
    glPopMatrix();

    //7
    glPushMatrix();
    glTranslatef(-1.5,0,1);
    paredesH(2);
    glPopMatrix();

    //8
    glPushMatrix();
    glTranslatef(1.5,0,1);
    paredesH(2);
    glPopMatrix();

    //9
    glPushMatrix();
    glTranslatef(-0.5,0,2);
    paredesH(6);
    glPopMatrix();

    //10 ex
    glPushMatrix();
    glTranslatef(-1.5,0,3);
    paredesH(6);
    glPopMatrix();

    //11 ex
    glPushMatrix();
    glTranslatef(2,0,3);
    paredesH(4);
    glPopMatrix();

}

void paredesV(int escalez)
{
    glPushMatrix();
    glScalef(0.5,1,escalez);
    //Por la posicion del tablero
    glTranslatef(0,0.3,0);
    glutSolidCube(0.5);
    glPopMatrix();
}

void laberintoV()
{
    //1 ex
    glPushMatrix();
    glTranslatef(-3,0,0);
    paredesV(12);
    glPopMatrix();

     //2
    glPushMatrix();
    glTranslatef(-2,0,0);
    paredesV(4);
    glPopMatrix();

    //3
    glPushMatrix();
    glTranslatef(-1,0,1.5);
    paredesV(2);
    glPopMatrix();

    //4
    glPushMatrix();
    glTranslatef(-1,0,-1);
    paredesV(4);
    glPopMatrix();

    //5
    glPushMatrix();
    glTranslatef(0,0,2.5);
    paredesV(2);
    glPopMatrix();

    //6
    glPushMatrix();
    glTranslatef(0,0,0.5);
    paredesV(2);
    glPopMatrix();

    //7
    glPushMatrix();
    glTranslatef(1,0,1.5);
    paredesV(2);
    glPopMatrix();

    //8
    glPushMatrix();
    glTranslatef(2,0,0.5);
    paredesV(2);
    glPopMatrix();

    //9
    glPushMatrix();
    glTranslatef(2,0,2.5);
    paredesV(2);
    glPopMatrix();

    //10 ex
    glPushMatrix();
    glTranslatef(3,0,0);
    paredesV(12);
    glPopMatrix();
}

void iniciar(void)
{
    glClearColor (1.0, 1.0, 1.0, 0.0);
    glShadeModel (GL_FLAT);
    glLineWidth(1.5);

    cuadrito();
    generarTablero(4.5, 4.5, TABLERO10x10);
    generarTablero(3.5, 3.5, TABLERO8X8);
    generarTablero(3.5, 2.5, TABLERO8X6);
    generarTablero(2.5, 4.5, TABLERO6X10);
    generarTablero(2.5, 2.5, TABLERO6X6);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glLoadIdentity();

    gluLookAt(0.5,0.8,0.5,0,0,0,0,1,0);
    ejes(3);
/*
    glRotatef(theta[0],1.0,0.0,0.0);
    glRotatef(theta[1],0.0,1.0,0.0);
    glRotatef(theta[2],0.0,0.0,1.0);
*/
    if (paso==1){
        glPushMatrix();
            glScalef(redimX,1,redimZ);
            glCallList(lista_actual);
        glPopMatrix();
        laberintoH();
        laberintoV();

        glPushMatrix();
        glColor3f(1,1,0);
            glTranslatef(trasX, 0.3, trasZ);
            printf("%.2f,%2f\n",trasX,trasZ);
            glutSolidCube(0.5);
        glPopMatrix();

    }

    glFlush();
    glPopMatrix();
    glutSwapBuffers();
}

void CubeSpin()
{
    theta[axis] += incremento_velo;
    if(theta[axis]>360) theta[axis] -= 360.0;
    display();
}

void menu_rotaciones(int opcion)
{
    switch(opcion)
    {
        case 1: incremento_velo *= 1;
                 break;
        case 2: incremento_velo *= -1;
                 break;
    }
}

void menu_colores(int opcion)
{
    switch(opcion)
    {
        case 1: cx=1;cy=0;cz=0;
                 break;
        case 2: cx=0;cy=0;cz=0;
                 break;
        case 3: cx=0;cy=1; cz=1;
                 break;
    }
}

void menu_mosaico(int opcion)
{
    switch(opcion)
    {
        case 1: paso=1;
                glutPostRedisplay();
                break;
        case 2: paso=0;
                glutPostRedisplay();
                break;
    }
}

void menu_redimensionar(int opcion)
{
    switch(opcion)
    {
        case 1: lista_actual = TABLERO10x10;
                redimX = 0.6; redimZ = 0.6;
                break;
        case 2: lista_actual = TABLERO8X8;
                redimX = 0.75; redimZ = 0.75;
                break;
        case 3: lista_actual = TABLERO8X6;
                redimX = 0.75; redimZ = 1;
                break;
        case 4: lista_actual = TABLERO6X10;
                redimX = 1; redimZ = 0.6;
                break;
                // valor por defecto
        case 5: lista_actual = TABLERO6X6;
                redimX = 1; redimZ = 1;
                break;
    }
}

void menu_principal(int op)
{
    switch(op)
    {
        case 4: exit(-1); break;
    }
}

void teclado(unsigned char tecla,int x,int y)
{
    switch(tecla)
    {
    case '+' :
        incremento_velo *= 1;
        break;
    case '-' :
        incremento_velo /= 1;
        break;
    case 'q' :
        exit(0);
        break;
    case 's' :
        trasZ += 0.5;
       // trasX =+ 0.5;
        break;
     case 'd' :
        trasX += 0.5;
       // trasX =+ 0.5;
        break;
     case 'a' :
        trasX += -0.5;
       // trasX =+ 0.5;
        break;
     case 'w' :
        trasZ += -0.5;
       // trasX =+ 0.5;
        break;

    }
}

void ejes(int longitud)
{
    glBegin(GL_LINES);
    glColor3f(0,1,0);
    glVertex3d(0,0,longitud);
    glVertex3d(0,0,0);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1,0,0);
    glVertex3d(0,0,0);
    glVertex3d(0,longitud,0);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0,0,1);
    glVertex3d(0,0,0);
    glVertex3d(longitud,0,0);
    glEnd();
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

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500,500);
    glutCreateWindow("camara movil");

    int submenu_rotaciones=glutCreateMenu(menu_rotaciones);
        glutAddMenuEntry("Giro horario",1);
        glutAddMenuEntry("Giro antihorario",2);

    int submenu_colores=glutCreateMenu(menu_colores);
        glutAddMenuEntry("Rojo",1);
        glutAddMenuEntry("negro",2);
        glutAddMenuEntry("Cyan",3);

    int submenu_mosaico=glutCreateMenu(menu_mosaico);
        glutAddMenuEntry("Activar Mosaico",1);
        glutAddMenuEntry("Desactivar Mosaico",2);

    int submenu_redimensionar=glutCreateMenu(menu_redimensionar);
        glutAddMenuEntry("10 x 10",1);
        glutAddMenuEntry("8 x 8",2);
        glutAddMenuEntry("8 x 6",3);
        glutAddMenuEntry("6 x 10",4);
        glutAddMenuEntry("6 x  6",5);

        int menu =glutCreateMenu(menu_principal);
        glutAddSubMenu("Giros",submenu_rotaciones);
        glutAddSubMenu("Colores",submenu_colores);
        glutAddSubMenu("Mosaico",submenu_mosaico);
        glutAddSubMenu("Redimensionar",submenu_redimensionar);

        glutAttachMenu(GLUT_RIGHT_BUTTON);

    iniciar();
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutIdleFunc(CubeSpin);
    glutKeyboardFunc(teclado);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}
