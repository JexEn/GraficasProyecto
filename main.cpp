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
#include <mmsystem.h>

float x=1.0;
using namespace std;
const float medida = 50;  // Mitad del tamaño de cada lado del cubo
int opcion =1;
char inicio[8] = { 'I','-','I','N','I','C','I', 'O'};
char detener[9] = {'D','-','D','E','T','E','N','E','R'};
char reset[7] = {'R','-','R','E','S','E','T'};
char eexit[8] = {'E','S','C','-','E','X','I','T'};
bool aparecerNombres = true;
bool* keyStates = new bool[256];
bool* keySpecialStates = new bool[256];
char buffer[300] = "";
bool difficultyText = false;

bool desaparece = false;

void init(void){
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH );//sombreado plano
    //glShadeModel (GL_FLAT );
    //PlaySound("C:\\Users\\JNeri\\Documents\\Graficas\\Semana 6\\Tarea_Pong\\trophy_rush.wav", NULL, SND_SYNC|SND_FILENAME|SND_LOOP);
}

void myTimer(int v){

}

void discoUno (int v){

    // se trasladan con timers

    //comprobar si existe un juego activo, para aventarlo

    // hay que dibujarlos


    //glutPostRedisplay();
    //glutTimerFunc(5,discoUno,1);
}

void discoDos (int v){


}

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
    int yRaster = -160;
    int k = 0;
    for (k=0; k<8;k++){
        glRasterPos2i(xRaster,yRaster);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, inicio[k]);
        xRaster +=15;
    }

    xRaster = -370;
    yRaster = -180;
    for (k=0; k<9;k++){
        glRasterPos2i(xRaster,yRaster);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, detener[k]);
        xRaster +=15;
    }

    xRaster = -200;
    yRaster = -160;
    for (k=0; k<7;k++){
        glRasterPos2i(xRaster,yRaster);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, reset[k]);
        xRaster +=15;
    }

    xRaster = -200;
    yRaster = -180;
    for (k=0; k<8;k++){
        glRasterPos2i(xRaster,yRaster);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, eexit[k]);
        xRaster +=15;
    }

    if(aparecerNombres){
        glColor3d(1,1,1);
        sprintf(buffer, "Daniel Garza Lee A01190362");
        draw3dStringScale(GLUT_STROKE_MONO_ROMAN, 0.1, buffer, -399, -200, 0);
        sprintf(buffer, "Jaime Neri A01034112");
        draw3dStringScale(GLUT_STROKE_MONO_ROMAN, 0.1, buffer, -190, -200, 0);
    }
}

void newgame(){
    glColor3d(1,1,1);
    if(!difficultyText){
        sprintf(buffer, "New Game");
        draw3dStringScale(GLUT_STROKE_MONO_ROMAN, 0.2, buffer, -50,50,0);
        glColor3d(0,0,0);
        //Medidas de NewGame
        glRectd(-55,30,100,70);
    }
    if(difficultyText){ 
        sprintf(buffer, "Easy");
        draw3dStringScale(GLUT_STROKE_MONO_ROMAN, 0.2, buffer, 0,  50, 0);
        sprintf(buffer, "Medium");
        draw3dStringScale(GLUT_STROKE_MONO_ROMAN, 0.2, buffer, 0,   0, 0);
        sprintf(buffer, "Hard");
        draw3dStringScale(GLUT_STROKE_MONO_ROMAN, 0.2, buffer, 0, -50, 0);
        glColor3d(0,0,0);
        //Medida Easy
        glRectd(-5,30,70,70);
        //Medida Medium
        glRectd(-5,-30,100,20);
        //Medida Hard
        glRectd(-5,-70,70,-20);
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

    glutSwapBuffers();
}

typedef enum{menuInicial, menuPausa, menuReset, menuAyuda, menuExit, menuBasura}
opcionesMenu;



void reshape (int w, int h){
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    if (opcion == 1)
        glOrtho(-400.0, 400, -200, 200, 100, 300 ); //izq, der, abajo, arriba, cerca, lejos

    else
        glFrustum (-200.0, 200.0, -200.0, 200.0, 100, 300.0);

    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();
    gluLookAt(0, 0, 200, 0, 0, 0, 0, 1, 0);
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
            glutPostRedisplay();
            break;
        case 27:
        exit(0); break;



    }

}

void dispara(int button, int state, int mouseX, int mouseY){

    // restar uno del contador de disparos disponibles
    // si el contador es zero, entonces no se puede disparar

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
    glutTimerFunc(25, myTimer, 1);

    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(dispara);

    // creacionMenu();

    glutMainLoop();
    return 0;
}
