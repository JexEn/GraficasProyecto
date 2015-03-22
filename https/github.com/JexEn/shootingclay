/*
    Daniel Garza
    Jaime Neri
    
    Proyecto Final Graficas

*/

#include  <windows.h>
#include <iostream>
#include <GL/glut.h>
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
char miNombre[10] = {'J','a','i','m','e',' ','N','e','r','i'};
char miMatricula[9] = {'A','0','1','0','3','4','1','1','2'};
char marcadorIzq[200] = ""; 
char marcadorDer[200] = "";
float mueveRaquetaIzq = 0;
float mueveRaquetaDer = 0;
float  pelotaX = 0;
float pelotaY = 0;
float sumadorX = 4;
float sumadorY = 4;
int golesDer = 0;
int golesIzq = 0;
bool tocaRaquetaIzq = false;
bool tocaRaquetaDer = false;
bool tocaPared = false;
bool primerSeleccion = false;
bool cronometro = false;
bool* keyStates = new bool[256];
bool* keySpecialStates = new bool[256];

bool desaparece = false;


void init(void){
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH );//sombreado plano
    //glShadeModel (GL_FLAT );
    //PlaySound("C:\\Users\\JNeri\\Documents\\Graficas\\Semana 6\\Tarea_Pong\\trophy_rush.wav", NULL, SND_SYNC|SND_FILENAME|SND_LOOP);
}

void myTimer(int v){

    if(cronometro && !desaparece){

        tocaPared = false;
        tocaRaquetaIzq = false;
        tocaRaquetaDer = false;

        if((pelotaY >= 190) || (pelotaY <= -190)){
            sumadorX = sumadorX * 1.03;
            sumadorY = sumadorY * -1.02;
            tocaPared = true;
        }

        if ( ((pelotaX >= 380) && (pelotaX <=397)) &&  ((pelotaY <= (mueveRaquetaDer+40)) && (pelotaY >= (mueveRaquetaDer-40))) || ((pelotaX <= -380) && (pelotaX >=-397)) &&  ((pelotaY <= (mueveRaquetaIzq+40)) && (pelotaY >= (mueveRaquetaIzq-40))) ){
            sumadorX = sumadorX * -1.07;
            sumadorY = sumadorY * 1.04;
            PlaySound("C:\\Users\\JNeri\\Documents\\Graficas\\Semana 6\\Tarea_Pong\\smb_bump.wav", NULL, SND_ASYNC|SND_FILENAME);

            if (pelotaX>0){
                tocaRaquetaDer = true;
            }
            else{
                tocaRaquetaIzq = true;

            }

        }

        if(pelotaX >= 440){
            golesIzq+=1;
            sumadorX=-4;
            sumadorY=4;
            pelotaX=0;
            pelotaY=0;
            PlaySound("C:\\Users\\JNeri\\Documents\\Graficas\\Semana 6\\Tarea_Pong\\smb_coin.wav", NULL, SND_ASYNC|SND_FILENAME);
        }

        if(pelotaX <= -440){
            golesDer+=1;
            sumadorX=4;
            sumadorY=4;
            pelotaX=0;
            pelotaY=0;
            PlaySound("C:\\Users\\JNeri\\Documents\\Graficas\\Semana 6\\Tarea_Pong\\smb_coin.wav", NULL, SND_ASYNC|SND_FILENAME);

        }

        pelotaX+=sumadorX;
        pelotaY+=sumadorY;

        if(tocaPared || tocaRaquetaIzq || tocaRaquetaDer){
            glutPostRedisplay();
            glutTimerFunc(60, myTimer, 1);
        }
        else{
            glutPostRedisplay();
            glutTimerFunc(20, myTimer, 1);
        }
    }

     // if(!cronometro){
     //    glutPostRedisplay();
     //    glutTimerFunc(50,myTimer,1);
     // }
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

void gameArea() {
    keyOperation();
    keySpecialOperation();

    //Recordatorio de tamaño de Ortho...

    //         -x      x     -y     y     -z    z
    //glOrtho(-400.0, 400, -200.0, 200.0, 100, 300 )

    GLint k;
    //LIMPIA EL BUFFER DE PROFUNDIDAD
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLint xRaster = -300, yRaster = 150;
    glColor3f(1.0, 1.0, 1.0);

    //Marcador Izquierdo
    sprintf(marcadorIzq,"%1d",golesIzq);
    draw3dString(GLUT_STROKE_MONO_ROMAN,marcadorIzq,xRaster,yRaster, 0);

    // Marcador Derecho
    xRaster = 300;
    sprintf(marcadorDer,"%1d",golesDer);
    draw3dString(GLUT_STROKE_MONO_ROMAN,marcadorDer,xRaster,yRaster, 0);

    //Texto en la parte inferior / opciones

    xRaster = -370;
    yRaster = -160;
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

    xRaster = 70;
    yRaster = -160;
    for (k=0; k<10;k++){
        glRasterPos2i(xRaster,yRaster);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, miNombre[k]);
        xRaster +=15;
    }

    xRaster = 70;
    yRaster = -180;
    for (k=0; k<9;k++){
        glRasterPos2i(xRaster,yRaster);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, miMatricula[k]);
        xRaster +=15;
    }

    // Dibujar raquetas

    glPushMatrix();
    if(tocaRaquetaIzq)
        glColor3f(0.0,0.0,1.0);
    else
        glColor3f(1.0, 1.0, 1.0);
    glTranslated(-395,mueveRaquetaIzq,0);
    glScaled(0.3,1,1);
    glutSolidCube(80);
    glPopMatrix();

    glPushMatrix();
    if(tocaRaquetaDer)
        glColor3f(0.0,0.0,1.0);
    else
        glColor3f(1.0, 1.0, 1.0);
    glTranslated(395,mueveRaquetaDer,0);
    glScaled(0.4,1,1);
    glutSolidCube(80);
    glPopMatrix();

    glPushMatrix();
    if(tocaRaquetaDer || tocaRaquetaIzq || tocaPared)
        glColor3f(1.0, 0.0, 0.0);
    else
        glColor3f(1.0, 1.0, 1.0);
    glLineWidth(1);
    glTranslated(pelotaX,pelotaY,0);
    glutWireCube(20);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glutSolidSphere(15,500,500);
    glPopMatrix();

    //glPushMatrix();
    glLineWidth(3);
    glBegin(GL_LINES);
     //Arriba (amarillo)
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(0.0,200.0,0.0);
    glVertex3f(0.0,-200.0,0.0);
    glVertex3f(-380.0,-200.0,0.0);
    glVertex3f(-380.0,200.0,0.0);
    glVertex3f(380.0,-200.0,0.0);
    glVertex3f(380.0,200.0,0.0);
    glEnd();

    glPopMatrix();
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
        cronometro = false;
        glutPostRedisplay();
            break;
        case 'r':
        case 'R':
            mueveRaquetaIzq = 0;
            mueveRaquetaDer = 0;
            pelotaX = 0;
            pelotaY = 0;
            sumadorX = 4;
            sumadorY = 4;
            golesDer = 0;
            golesIzq = 0;
            cronometro = false;
            glutPostRedisplay();
            break;
        case 'i':
        case 'I':
            if(!cronometro){
                primerSeleccion = true;
                glutTimerFunc(100,myTimer,1);
                cronometro = true;
            }
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

    creacionMenu();

    glutMainLoop();
    return 0;
}
