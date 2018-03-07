#include <stdlib.h>
#include<conio.h>
#include <gl/glut.h>
#include <stdio.h>

#define EJES 1
#define CASILLA_NEGRA 2
#define CASILLA_BLANCA 3
#define TABLERO_8_8 4
#define TABLERO_6_8 5
#define TABLERO_8_10 6
#define TABLERO_6_4 7
#define PAREDES 8
#define BLOQUE_H 9
#define BLOQUE_V 10
#define BLOQUE_HB 11
#define BLOQUE_VB 12
#define BPAREDES 13
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

float r = 0.7, g = 0, b = 0;

int sentido_giro = 1, lista_actual = 4;

float xAv = 0.5, zAv = 3.25;

bool juegoIniciado = false;
/**
    Funcion que dibuja un cubo unitario
    param : color
*/

int laberito_map_hor [7][6] =
{
    {1, 1, 0, 1, 1, 1},
    {0, 1, 0, 1, 1, 0},
    {1, 0, 1, 0, 1, 1},
    {1, 1, 0, 1, 1, 0},
    {0, 0, 1, 0, 0, 0},
    {0, 1, 1, 1, 1, 1},
    {1, 1, 1, 0, 1, 1}
};

int laberito_map_ver [7][6] =
{
    {1, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 1, 0},
    {1, 0, 0, 1, 0, 0},
    {1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 0},
    {0, 0, 0, 1, 0, 0},
    {1, 1, 1, 1, 1, 1}
};

void bloque_pared()
{

    glNewList(BLOQUE_H, GL_COMPILE);
    glPushMatrix();
    glScalef(1.0,1.0,0.3);
    glutSolidCube(1);
    glPopMatrix();
    glEndList();

    glNewList(BLOQUE_V, GL_COMPILE);
    glPushMatrix();
    glScalef(0.3,1.0,1.0);
    glutSolidCube(1);
    glPopMatrix();
    glEndList();
}

void bordes_pared()
{
    glNewList(BLOQUE_HB, GL_COMPILE);
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glScalef(1.0,1.0,0.3);
    glutWireCube(1);
    glPopMatrix();
    glEndList();

    glNewList(BLOQUE_VB, GL_COMPILE);
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.3,1.0,1.0);
    glutWireCube(1);
    glPopMatrix();
    glEndList();
}

void paredes ()
{
    float coordenadainicialx = -2.5;
    float coordenadainicialz = -2.85;

    glNewList(PAREDES, GL_COMPILE);
    for(int i = 0; i < 7; i++)
    {
        coordenadainicialx = -2.5;
        for(int j = 0; j < 6; j++)
        {
            if(laberito_map_hor[i][j] == 1)
            {
                glPushMatrix();
                glTranslatef(coordenadainicialx, 0.7, coordenadainicialz);
                glCallList(BLOQUE_H);
                glPopMatrix();
            }
            coordenadainicialx ++;
        }

        coordenadainicialz ++;
    }

    coordenadainicialx = -2.85;
    coordenadainicialz = -2.5;

    for(int i = 0; i < 7; i++)
    {
        coordenadainicialz = -2.5;
        for(int j = 0; j < 6; j++)
        {
            if(laberito_map_ver[i][j] == 1)
            {
                glPushMatrix();
                glTranslatef(coordenadainicialx, 0.7, coordenadainicialz);
                glCallList(BLOQUE_V);
                glPopMatrix();
            }
            coordenadainicialz ++;
        }

        coordenadainicialx ++;
    }

    glEndList();
}

void bparedes ()
{
    float coordenadainicialx = -2.5;
    float coordenadainicialz = -2.85;

    glNewList(BPAREDES, GL_COMPILE);
    for(int i = 0; i < 7; i++)
    {
        coordenadainicialx = -2.5;
        for(int j = 0; j < 6; j++)
        {
            if(laberito_map_hor[i][j] == 1)
            {
                glPushMatrix();
                glTranslatef(coordenadainicialx, 0.7, coordenadainicialz);
                glCallList(BLOQUE_HB);
                glPopMatrix();
            }
            coordenadainicialx ++;
        }

        coordenadainicialz ++;
    }

    coordenadainicialx = -2.85;
    coordenadainicialz = -2.5;

    for(int i = 0; i < 7; i++)
    {
        coordenadainicialz = -2.5;
        for(int j = 0; j < 6; j++)
        {
            if(laberito_map_ver[i][j] == 1)
            {
                glPushMatrix();
                glTranslatef(coordenadainicialx, 0.7, coordenadainicialz);
                glCallList(BLOQUE_VB);
                glPopMatrix();
            }
            coordenadainicialz ++;
        }

        coordenadainicialx ++;
    }

    glEndList();
}

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

void tablero(int n, int m, int lista)
{
    glNewList(lista, GL_COMPILE);
    bool color = 0;
    for(float i = -n/2 + 0.5 ; i < n/2; i ++)
    {
        color = !color;
        for(float j = -m/2 + 0.5; j < m/2; j++)
        {
            glPushMatrix();
            glTranslatef(i,0.0,j);
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

float razonRedim(float dim, float base)
{

    return (dim - base) / base;

}

void ajustarTablero(int tabActual)
{
    float redX = 1, redY = 1;

    if(tabActual == TABLERO_6_4)
    {
        redX = 1 + razonRedim(8,6);
        redY = 1 + razonRedim(8,4);

    }
    else if(tabActual == TABLERO_6_8)
    {
        redX = 1 + razonRedim(8,6);
    }
    else if(tabActual == TABLERO_8_10)
    {
        redY = 1 + razonRedim(8,10);
    }

    glScalef(redX,1,redY);
}

void display (void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.5,1,0.5,0,0,0,0,1,0);
    //gluLookAt(0.0,0.5,0.0,0,0,0,0,0,1);
    glCallList(EJES);
    if(!juegoIniciado)
    {
        glRotatef(theta,0.0,1.0,.0);
    }
    else
    {
        glPushMatrix();
        glTranslatef(xAv, 0.85, zAv);
        glColor3f(1.0,0.0,1.0);
        glutSolidCube(0.5);
        glPopMatrix();
    }

    glColor3f(r,g,b);
    glCallList(PAREDES);
    glCallList(BPAREDES);
    glPushMatrix();
    ajustarTablero(lista_actual);
    glCallList(lista_actual);
    glPopMatrix();

    glutSwapBuffers();
}

/**
    Gira segun el incremento determinado por teclado
*/

void girar_objeto_geometrico ()
{
    theta +=  sentido_giro * incremento;
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
    case 'w' :
        zAv -= 0.25;
        break;
    case 's' :
        zAv += 0.25;
        break;
    case 'a' :
        xAv -= 0.25;
        break;
    case 'd' :
        xAv += 0.25;
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

void submenu_color(int opcion)
{
    switch(opcion)
    {
    case 1:
        r = 0.7;
        g = 0.0;
        b = 0.0;
        break;
    case 2:
        r = 0.0;
        g = 0.7;
        b = 0.0;
        break;
    case 3:
        r = 0.0;
        g = 0.0;
        b = 0.7;
        break;
    }
}

void submenu_ops_giro(int opcion)
{
    switch(opcion)
    {
    case 1:
        sentido_giro *= -1;
        break;
    case 2:
        incremento *= 1.45;
        break;
    case 3:
        incremento /= 1.45;
        break;
    }
}

void submenu_mosaico(int opcion)
{
    switch(opcion)
    {
    case 1:
        lista_actual = TABLERO_8_8;
        break;
    case 2:
        lista_actual = TABLERO_6_8;
        break;
    case 3:
        lista_actual = TABLERO_8_10;
        break;
    case 4:
        lista_actual = TABLERO_6_4;
        break;
    }
}

void menu_principal (int opcion)
{
    switch(opcion)
    {
    case 4 :
        juegoIniciado = true;
        break;
    case 5 :
        exit(0);
        break;
    }
}

void init ()
{
    glClearColor(0.0,0.0,0.2,0.0);
    // Creacion de las Vistas de Visualización
    micasilla(1, CASILLA_BLANCA);
    micasilla(0, CASILLA_NEGRA);

    tablero(8,8,TABLERO_8_8);
    tablero(6,8,TABLERO_6_8);
    tablero(6,4,TABLERO_6_4);
    tablero(8,10,TABLERO_8_10);
    dibujar_ejes();
    bloque_pared();
    bordes_pared();
    paredes();
    bparedes();
    int sMenuColor = glutCreateMenu(submenu_color);

    glutAddMenuEntry("Rojo", 1);
    glutAddMenuEntry("Verde", 2);
    glutAddMenuEntry("Azul", 3);

    int sMenuGiro = glutCreateMenu(submenu_ops_giro);
    glutAddMenuEntry("Invertir Giro", 1);
    glutAddMenuEntry("Aumentar Velocidad", 2);
    glutAddMenuEntry("Disminuir Velocidad", 3);

    int sMenuMosaico = glutCreateMenu(submenu_mosaico);
    glutAddMenuEntry("8 x 8", 1);
    glutAddMenuEntry("6 x 8", 2);
    glutAddMenuEntry("8 x 10", 3);
    glutAddMenuEntry("6 x 4", 4);

    int mPrincipal = glutCreateMenu(menu_principal);
    glutAddSubMenu("Colores", sMenuColor);
    glutAddSubMenu("Giros", sMenuGiro);
    glutAddSubMenu("Tableros", sMenuMosaico);
    glutAddMenuEntry("Iniciar juego", 4);
    glutAddMenuEntry("Salir", 5);

    glutAttachMenu(GLUT_RIGHT_BUTTON);

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



