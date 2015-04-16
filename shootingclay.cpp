/*
    Daniel Garza A01190362
    Jaime Neri A01034112

    Proyecto Final Graficas

    Para hacer commits en Github...
    1) git add -A
    2) git commit -m "mensaje"
    3) git push origin master

    si el push no pasa, entonces...
    1) git stash
    2) git pull
    3) git stash pop

*/


#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <windows.h>
#include <GL/glut.h>
#endif
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <utility>
#include <math.h>
#include <mmsystem.h>

float x=1.0;
using namespace std;
const float medida = 50;  // Mitad del tamaño de cada lado del cubo
int opcion =1;
char inicio[8] = { 'I','-','I','N','I','C','I', 'O'};
char detener[9] = {'D','-','D','E','T','E','N','E','R'};
char reset[7] = {'R','-','R','E','S','E','T'};
char eexit[8] = {'E','S','C','-','E','X','I','T'};
char miNombre[10] = {'J','a','i','m','e',' ','N','e','r','i'};
char miMatricula[9] = {'A','0','1','0','3','4','1','1','2'};
char marcadorIzq[200] = "";
char marcadorDer[200] = "";
int velocidadDeDificultad = 40;
float tiempoTranscurrido = 0;
float traslacionDiscoUnoZ = 0;
float traslacionDiscoUnoY = 0;
bool cronometro = false;
bool aparecerNombres = true;
bool* keyStates = new bool[256];
bool* keySpecialStates = new bool[256];
char buffer[300] = "";
bool difficultyText = false;

bool desaparece = false;

GLUquadricObj *discoUno;
GLUquadricObj *discoDos;

void init(void){
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH );//sombreado plano

    discoUno = gluNewQuadric();
    gluQuadricNormals(discoUno, GLU_SMOOTH);

    discoDos = gluNewQuadric();
    gluQuadricNormals(discoDos, GLU_SMOOTH);


    //glShadeModel (GL_FLAT);
    //PlaySound("C:\\Users\\JNeri\\Documents\\Graficas\\Semana 6\\Tarea_Pong\\trophy_rush.wav", NULL, SND_SYNC|SND_FILENAME|SND_LOOP);
}



void discos (int v){

    /*

    x = Vo * t * cos(45°)
    y = Vo * t * sen(45°) - (0.5g*(t^2))
    t+=0.001

    */

    if (!desaparece){
        // se trasladan con timers
        //comprobar si existe un juego activo, para aventarlo; hay que dibujarlos
        if(v == 1){
            traslacionDiscoUnoZ = velocidadDeDificultad * tiempoTranscurrido * cos(45);
            traslacionDiscoUnoY = (velocidadDeDificultad * tiempoTranscurrido * sin(45)) - (4.9 * pow(tiempoTranscurrido, 2));
            tiempoTranscurrido+=0.002;
            glutTimerFunc(1, discos, 1);
            glutPostRedisplay();

        // else if (v == 2)
        }
    }

}

/*void discoDos (int v){


}*/

void draw3dString (void *font, char *s, float x, float y, float z){
    unsigned int i;
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    glTranslatef(x, y, z);

    glScaled(0.2, 0.2, 0.2);

    //if (!dibujaPortada && opcion ==1)  glRotatef(45, 1, 0, 0);
    for (i = 0; i < s[i] != '\0'; i++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, s[i]);

    }
    glPopMatrix();
}
void draw3dStringScale (void *font, float scale, char *s, float x, float y, float z){
    unsigned int i;
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    glTranslatef(x, y, z);

    glScaled(scale, scale, scale);

    //if (!dibujaPortada && opcion ==1)  glRotatef(45, 1, 0, 0);
    for (i = 0; i < s[i] != '\0'; i++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, s[i]);

    }
    glPopMatrix();
}

void intro(){

    int xRaster = -370;
    int yRaster = 35;
    int k = 0;
    for (k=0; k<8;k++){
        glRasterPos2i(xRaster,yRaster);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, inicio[k]);
        xRaster +=15;
    }

    xRaster = -370;
    yRaster = 15;
    for (k=0; k<9;k++){
        glRasterPos2i(xRaster,yRaster);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, detener[k]);
        xRaster +=15;
    }

    xRaster = -200;
    yRaster = 35;
    for (k=0; k<7;k++){
        glRasterPos2i(xRaster,yRaster);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, reset[k]);
        xRaster +=15;
    }

    xRaster = -200;
    yRaster = 15;
    for (k=0; k<8;k++){
        glRasterPos2i(xRaster,yRaster);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, eexit[k]);
        xRaster +=15;
    }

    if(aparecerNombres){
        glColor3d(1,1,1);
        sprintf(buffer, "Daniel Garza Lee A01190362");
        draw3dStringScale(GLUT_STROKE_MONO_ROMAN, 0.1, buffer, -400, 1, 0);
        sprintf(buffer, "Jaime Neri A01034112");
        draw3dStringScale(GLUT_STROKE_MONO_ROMAN, 0.1, buffer, -200, 1, 0);
    }
}

void newgame(){
    glColor3d(1,1,1);
    if(difficultyText){
        sprintf(buffer, "New Game");
        draw3dStringScale(GLUT_STROKE_MONO_ROMAN, 0.2, buffer, -50, 100,0);
        glColor3d(0,0,0);
        //Medidas de NewGame
        glRectd(-55,30,100,70);
    }
    if(!difficultyText){
        sprintf(buffer, "Easy");
        draw3dStringScale(GLUT_STROKE_MONO_ROMAN, 0.2, buffer, 0, 125, 0);
        sprintf(buffer, "Medium");
        draw3dStringScale(GLUT_STROKE_MONO_ROMAN, 0.2, buffer, 0, 100, 0);
        sprintf(buffer, "Hard");
        draw3dStringScale(GLUT_STROKE_MONO_ROMAN, 0.2, buffer, 0, 75, 0);
        glColor3d(0,0,0);
        //Medida Easy
        glRectd(-5,115,70,140);
        //Medida Medium
        glRectd(-5,85,100,114);
        //Medida Hard
        glRectd(-5,60,70,84);
    }
}

void gameArea() {

    //Recordatorio de tamaño de Ortho...

    //         -x      x     -y     y     -z    z
    //glOrtho(-400.0, 400, -200.0, 200.0, 100, 300 )

    //LIMPIA EL BUFFER DE PROFUNDIDAD
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //Texto en la parte inferior / opciones
    intro();
    newgame();

    // Dibujar discos

    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(1);
    glTranslated(0,traslacionDiscoUnoY,traslacionDiscoUnoZ);
    glScaled(1.3,0.4,1);
    glutWireCube(20);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glutSolidSphere(15,500,500);
    glPopMatrix();

    glutSwapBuffers();
}

typedef enum{menuInicial, menuPausa, menuReset, menuAyuda, menuExit, menuBasura}
opcionesMenu;



void reshape (int w, int h){
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();

    glFrustum (-400.0, 400.0, 0.0, 200.0, 99, 1100.0);

    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 100, 0, 0, 0, 0, 1, 0);
}


void keyboard(unsigned char key, int mouseX, int mouseY){
    keyStates[key] = true;

    switch(key){
        case 'd':
        case 'D':
        // cronometro = false;
        glutPostRedisplay();
            break;
        case 'r':
        case 'R':
            // cronometro = false;
            glutPostRedisplay();
            break;
        case 'i':
        case 'I':
            desaparece = false;
            glutTimerFunc(1, discos, 1);
            glutPostRedisplay();
            break;
        case 27:
        exit(0); break;



    }

}

void dispara(int button, int state, int mouseX, int mouseY){

    // restar uno del contador de disparos disponibles
    // si el contador es zero, entonces no se puede disparar
        /* left button increase joint angle, right button decreases it */

    if(button==GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        desaparece = false;
    }
    if(button==GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        desaparece = true;
    }
    glutPostRedisplay();

    // validar si es que le atinaste a un disco o no

}


int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE| GLUT_RGB| GLUT_DEPTH);
    glutInitWindowSize (800, 600);
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    init ();
    glEnable(GL_DEPTH_TEST); //para diferenciar que vertices estan al frente y detras ver ejemplo del documento de word
    glutDisplayFunc(gameArea);
//    glutTimerFunc(25, myTimer, 1);

    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(dispara);

    // creacionMenu();

    glutMainLoop();
    return 0;
}
