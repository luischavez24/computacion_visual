#include <stdlib.h>
#include<conio.h>
#include <gl/glut.h>
#include<stdio.h>

// declaracion de variables
// GLfloat ...;
// theta[] me indica los ángulos iniciales en los 3 s

static GLfloat theta[] = {0.0,0.0,0.0};
// eje es el ángulo a rotar
static GLint eje = 2;
// valores de escalamiento
static GLfloat sx = 1, sy = 1, sz = 1;

class Punto3i {
    public:
        int x;
        int y;
        int z;

        Punto3i()
        {
            this->x = 0;
            this->y = 0;
            this->z = 0;
        }

        Punto3i(int x, int y, int z)
        {
            this->x = x;
            this->y = y;
            this->z = z;
        }
};

//static Punto3i *points = new Punto3i[8];
static Punto3i points[8];
void createPoints()
{
    points[0] = Punto3i(-1,-1,-1);
    points[1] = Punto3i(-1,1,-1);
    points[2] = Punto3i(1,1,-1);
    points[3] = Punto3i(1,-1,-1);
    points[4] = Punto3i(-1,-1,1);
    points[5] = Punto3i(-1,1,1);
    points[6] = Punto3i(1,1,1);
    points[7] = Punto3i(1,-1,1);
}
/**
    Función cara
    -> Parametros:
        p1: entero
        p2: entero
        p3: entero
        p4: entero
    -> Funcionamiento:

    Dibuja un cuadrilatero de vertices p1, p2, p3, p4
    en el sentido de izquierda a derecha,

    -> Retorna
        vacio
*/
void cara(int p1, int p2, int p3, int p4)  //se cambió a float
{
    glBegin(GL_POLYGON);
        glVertex3f(points[p1].x,points[p1].y,points[p1].z);
        glVertex3f(points[p2].x,points[p2].y,points[p2].z);
        glVertex3f(points[p3].x,points[p3].y,points[p3].z);
        glVertex3f(points[p4].x,points[p4].y,points[p4].z);
       // glVertex3f(points[p1].x,points[p1].y,points[p1].z);
    glEnd();
}

// construya su objeto geométrico mediante mipoligono()
void cubo(void)
{
    createPoints();

    glColor3f(1,0,0);
    cara(0,1,2,3);

    glColor3f(0,1,0);
    cara(4,5,6,7);

    glColor3f(0,0,1);
    cara(0,1,5,4);

    glColor3f(1,1,0);
    cara(2,3,7,6);

    glColor3f(1,0,1);
    cara(0,4,7,3);

    glColor3f(0,1,1);
    cara(1,5,6,2);
}

void ejes() {
    glBegin(GL_LINES);
    glLineWidth(2.0);

    glColor3f(1,1,1);
        glVertex3f(-250,0,0);
        glVertex3f(250,0,0);
    glEnd();
    glBegin(GL_LINES);
        glVertex3f(0,-250,0);
        glVertex3f(0,250,0);
    glEnd();
    glBegin(GL_LINES);
        glVertex3f(500,300,0);
        glVertex3f(-500,-300,0);
    glEnd();
}

// dibujamos nuestra escena
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    ejes();

// composicion de rotaciones
    glRotatef(theta[0],1.0,0.0,0.0);
    glRotatef(theta[1],0.0,1.0,0.0);
    glRotatef(theta[2],0.0,0.0,1.0);

    glScalef(sx,sy,sz);

    //cubo();        //dibuja cubo, librería propia
    //glutWireSphere(1,15,15);    //dibuja una esfera , libreria glut
    glColor3f(1.0,0.0,0.0);
    //glutSolidSphere(1,25,25);
    glutWireIcosahedron();
    glFlush();
// intercambiamos los buffers, el que se muestra y el que esta oculto
    glutSwapBuffers();
}
// esta función controla el angulo de rotación según el eje de giro
void IdleFunc()
{
    theta[eje] += 0.1;
    if(theta[eje]>360) theta[eje] -= 360.0;
    display();
}

//función a espera de eventos de teclado, responde de acuerdo a tecla pulsada.
void teclado(unsigned char tecla,int x,int y)
{
    switch(tecla)
    {
    case 'a' :
        eje = 0;
        break;
    case 's' :
        eje = 1;
        break;
    case 'd' :
        eje = 2;
        break;
    case 'q':
        sx += sx*0.15;
        break;
    case 'w':
        sy += sy*0.15;
        break;
    case 'e':
        sz += sz*0.15;
        break;
    case 'z':
        sx -= sx*0.15;
        break;
    case 'x':
        sy -= sy*0.15;
        break;
    case 'c':
        sz -= sz*0.15;
        break;
    case 'f' :
        exit(0) ;
        break;

    }
}
// control de ventana (recuerde el volumen de visualización)
// modifique dicho volumen según su conveniencia
void myReshape(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(w <=h)
        glOrtho(-2.0,2.0,-2.0*(GLfloat)h/(GLfloat)w,
                2.0*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
    else
        glOrtho(-2.0*(GLfloat)w/(GLfloat)h,
                2.0*(GLfloat)w/(GLfloat)h, -2.0,2.0,-10.0,10.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500,500);   //tamañ de la ventana
    glutCreateWindow("Cubo Rotando :3");
    glutReshapeFunc(myReshape);
// invocamos a display() para dibujar nuestra escena
    glutDisplayFunc(display);
// esta funcion llama a IdleFunc() mientras no haya evento
//alguno    ocasionado por el usuario
    glutIdleFunc(IdleFunc);
    glutKeyboardFunc(teclado);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}
