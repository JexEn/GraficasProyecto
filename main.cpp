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
#include <time.h>
#include <mmsystem.h>
#include "imageloader.h"

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
char marcadorPuntaje[200] = "";

float velocidadDeDificultad = 80;
bool gameStart = false;
int balasRestantes = 3;
int rasterBalas = -399;
int puntaje = 0;
int tiempoTranscurridoParpadeo = 0;

static GLuint texName[36];

//variables de movimiento para un disco
bool colisionDiscoUno = false;
float tiempoTranscurridoUno = 0;
float traslacionDiscoUnoX = -100;
float traslacionDiscoUnoY = 10;
float traslacionDiscoUnoZ = -20;

bool colisionDiscoDos = false;
float tiempoTranscurridoDos = 0;
float traslacionDiscoDosX = 100;
float traslacionDiscoDosY = 10;
float traslacionDiscoDosZ = -20;

int anguloDeTiro = 0;
int rasterBalaDisparadaZ = 0;
int rasterDiscosDeRonda = -200;
int rasterCuantosNecesitasX = -210;

float screenHeight = 600;
float traslacionBalaX = 800;
float traslacionBalaY = 600;
float traslacionBalaZ = 0;
bool balaDisaparada = false;

bool discoEnJuego = 0;

bool discoUnoEnPantalla = false;
bool discoDosEnPantalla = false;

int cualDiscoVas = 0;
bool esAventado[10] = {true,false,true,true,true,true,true,true,true,true};
bool colorDisco[10] = {true,false,false,false,false,false,false,false,false,false};


bool cronometro = false;
bool aparecerNombres = true;
bool* keyStates = new bool[256];
bool* keySpecialStates = new bool[256];
char buffer[300] = "";
char buffer2[700]= "";

//Control de menu principal
bool newGame = false;
bool difficultyText = false;
bool instrucciones = false;

bool desaparece = false;

bool nextMiniRound = false;

float triangleRasterY = 100;

int contExplosionUno = 0;
int contExplosionDos = 0;
bool boolExplosionUno = false;
bool boolExplosionDos = false;


void explosion (int b);
void animacionExplosion (float x, float y, float z);

void init(void){
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH );//sombreado plano
    srand(time(0));


}

void loadTexture(Image* image,int k){

    glBindTexture(GL_TEXTURE_2D, texName[k]); //Tell OpenGL which texture to edit

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
                 0,                            //0 for now
                 GL_RGB,                       //Format OpenGL uses for image
                 image->width, image->height,  //Width and height
                 0,                            //The border of the image
                 GL_RGB, //GL_RGB, because pixels are stored in RGB format
                 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
                 //as unsigned numbers
                 image->pixels);               //The actual pixel data

}



void initRendering(){
    GLuint i=0;
       GLfloat ambientLight[] = {0.2f, 0.2f, 0.2f, 1.0f};
    //glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

    GLfloat directedLight[] = {0.9f, 0.9f, 0.9f, 1.0f};
    GLfloat directedLightPos[] = {-10.0f, 15.0f, 20.0f, 0.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, directedLight);
    glLightfv(GL_LIGHT0, GL_POSITION, directedLightPos);
    //glEnable(GL_DEPTH_TEST);
    //glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);
    //glEnable(GL_NORMALIZE); ///Users/mariaroque/Imagenes

    glEnable(GL_TEXTURE_2D);

    glEnable(GL_COLOR_MATERIAL);
    glGenTextures(26, texName); //Make room for our texture
    Image* image;

    /* = loadBMP("/Users/mariaroque/Imagenes/img01.bmp");
    loadTexture(image,0);

    image = loadBMP("/Users/mariaroque/Imagenes/img02.bmp");
    loadTexture(image,1);

    image = loadBMP("/Users/mariaroque/Imagenes/img03.bmp");
    loadTexture(image,2);

    image = loadBMP("/Users/mariaroque/Imagenes/img04.bmp");
    loadTexture(image,3);

    image = loadBMP("/Users/mariaroque/Imagenes/img05.bmp");
    loadTexture(image,4);

    image = loadBMP("/Users/mariaroque/Imagenes/img06.bmp");
    loadTexture(image,5);*/

    image = loadBMP("C:/Users/Chinolee/Documents/Graficas/GraficasProyecto/background.bmp");loadTexture(image,i++);
    image = loadBMP("C:/Users/Chinolee/Documents/Graficas/GraficasProyecto/sabritas.bmp");loadTexture(image,i++);
    image = loadBMP("C:/Users/Chinolee/Documents/Graficas/GraficasProyecto/bgmenu.bmp");loadTexture(image,i++);
    image = loadBMP("C:/Users/Chinolee/Documents/Graficas/GraficasProyecto/bginstrucciones.bmp");loadTexture(image,i++);

    // image = loadBMP("C:\\Users\\Chinolee\\GraficasProyecto\\imagenes\\bandera argentina.bmp");loadTexture(image,i++);
    // image = loadBMP("C:\\Users\\Chinolee\\GraficasProyecto\\imagenes\\bandera brasil.bmp");loadTexture(image,i++);
    // image = loadBMP("C:\\Users\\Chinolee\\GraficasProyecto\\imagenes\\bandera canada.bmp");loadTexture(image,i++);

    delete image;
}


void discos (int v){

    /*
    x = Vo * t * cos(45°)
    y = Vo * t * sen(45°) - (0.5g*(t^2))
    t+=0.001
    */
        tiempoTranscurridoParpadeo += 1;
        if(!discoUnoEnPantalla && !discoDosEnPantalla)
          {
            v=3;
            for(int i=0;i<10;i++){
                esAventado[i]=true;
            }
            nextMiniRound = true;
            glutPostRedisplay();
         }

        // se trasladan con timers
        //comprobar si existe un juego activo, para aventarlo; hay que dibujarlos
        if(v == 1 && discoUnoEnPantalla){
            traslacionDiscoUnoZ = velocidadDeDificultad * tiempoTranscurridoUno * cos(45);
            traslacionDiscoUnoY = (velocidadDeDificultad * tiempoTranscurridoUno * sin(45)) - (4.9 * pow(tiempoTranscurridoUno, 2));

                traslacionDiscoUnoX+=1;

            tiempoTranscurridoUno += 0.02;


            //El disco ha salido del rango de la pantalla?
            //Sí: desaparecerlo. "destruir" timers.

            if(traslacionDiscoUnoZ > 1400 || traslacionDiscoUnoY < 0){
                discoUnoEnPantalla = false;
                // cualDiscoVas+=2;
                // if(cualDiscoVas==10)
                //     cualDiscoVas=0;
                srand(time(NULL));
                // traslacionDiscoUnoX = rand() % 400;
                // anguloDeTiro = rand()%30+20;
            }

        }

        if (v == 2 && discoDosEnPantalla){

            traslacionDiscoDosZ = velocidadDeDificultad * tiempoTranscurridoDos * cos(70);
            traslacionDiscoDosY = (velocidadDeDificultad * tiempoTranscurridoDos * sin(70)) - (4.9 * pow(tiempoTranscurridoDos, 2));

                traslacionDiscoDosX-=1;

                tiempoTranscurridoDos += 0.02;


                //El disco ha salido del rango de la pantalla?
                //Sí: desaparecerlo. "destruir" timers.

                if(traslacionDiscoDosZ > 1400 || traslacionDiscoDosY < 0){
                    discoDosEnPantalla = false;
                    // cualDiscoVas+=2;
                    // if(cualDiscoVas==10)
                    //     cualDiscoVas=0;
                    srand(time(NULL));
                    // traslacionDiscoUnoX = rand() % 400;
                    // anguloDeTiro = rand()%30+20;
                }

        }

        /*if(balaDisaparada){
            traslacionBalaZ+=50;
             if(traslacionBalaZ>2000){
                 balaDisaparada = false;
             }
        }
        */

        /* si la bala hace colision con un disco con el discoUno*/
        if(
           traslacionBalaX-70 <= traslacionDiscoUnoX &&
           traslacionBalaX+70 >= traslacionDiscoUnoX &&
           traslacionBalaY-45 <= traslacionDiscoUnoY &&
           traslacionBalaY+45 >= traslacionDiscoUnoY
           )
            {
            colisionDiscoUno = true;
            explosion(1);
        }

        /* Si la bala hace colision con el discoDos*/
        if(
           traslacionBalaX-70 <= traslacionDiscoDosX &&
           traslacionBalaX+70 >= traslacionDiscoDosX &&
           traslacionBalaY-45 <= traslacionDiscoDosY &&
           traslacionBalaY+45 >= traslacionDiscoDosY
           )
            {
            colisionDiscoDos = true;
            explosion(2);
        }



        if(v==1 && discoDosEnPantalla)
            {
            glutPostRedisplay();
            glutTimerFunc(1, discos, 2);  // <-- Deberia mandar v = 2 cuando ya manejemos dos discos
        }
        else
        if (v == 2 && discoUnoEnPantalla){
            glutPostRedisplay();
            glutTimerFunc(1, discos, 1);
         }else
         if(v==1 && !discoDosEnPantalla){
            glutPostRedisplay();
            glutTimerFunc(1, discos, 1);
         }
         else
            if(v==2 && !discoUnoEnPantalla)
            {
            glutPostRedisplay();
            glutTimerFunc(1, discos, 2);
         }


    // if(colisionDiscoUno){
    //     colisionDiscoUno = false;
    //     desaparece = false;
    //     glutPostRedisplay();
    //     glutTimerFunc(1000,discos,1);
    // }

}

void explosion(int b){

    balaDisaparada = false;
    traslacionBalaX = 800;
    traslacionBalaY = 600;
    traslacionBalaZ = 0;

    if(b==1){
        discoUnoEnPantalla = false;
        // traslacionDiscoUnoX =  10000;
        // traslacionDiscoUnoY = 10000;
        // traslacionDiscoUnoZ = 10000;
        puntaje += 1000;
        colorDisco[cualDiscoVas]=true;
    }

    if (b==2){
        discoDosEnPantalla = false;
        // traslacionDiscoDosX =  10000;
        // traslacionDiscoDosY = 10000;
        // traslacionDiscoDosZ = 10000;
        puntaje += 1000;
        colorDisco[cualDiscoVas+1]=true;
    }
}

void disparaBala(){
    balaDisaparada = true;
    traslacionBalaZ = 0;
}

void draw3dString (void *font, char *s, float x, float y, float z){
    unsigned int i;
    glDisable(GL_TEXTURE_2D);
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
    glEnable(GL_TEXTURE_2D);
}

void draw3dStringScale (void *font, float scale, char *s, float x, float y, float z){
    unsigned int i;
    glDisable(GL_TEXTURE_2D);
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
    glEnable(GL_TEXTURE_2D);
}

void intro(){
    if(aparecerNombres){

        glColor3d(1,1,1);
        sprintf(buffer, "Daniel Garza Lee A01190362");
        draw3dStringScale(GLUT_STROKE_MONO_ROMAN, 0.1, buffer, -400, 1, 0);
        sprintf(buffer, "Jaime Neri A01034112");
        draw3dStringScale(GLUT_STROKE_MONO_ROMAN, 0.1, buffer, -200, 1, 0);
    }
}

void menuInstrucciones(){

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texName[3]);
        glPushMatrix();
        glColor3d(1,1,1);
        glScalef(14.5,42,1.0);
        glTranslated(0,0,100);
        glBegin(GL_QUADS);
            glTexCoord3f(0.0f, 0.0f, -1500.0f);
            glVertex3f(-420.0f, 0.0f, -1500.0f);

            glTexCoord3f(1.0f, 0.0f, -1500.0f);
            glVertex3f(420.0f, 0.0f, -1500.0f);

            glTexCoord3f(1.0f, 1.0f, -1500.0f);
            glVertex3f(420.0f, 220.0f, -1500.0f);

            glTexCoord3f(0.0f, 1.0f, -1500.0f);
            glVertex3f(-420.0f, 220.0f, -1500.0f);
        glEnd();
        glPopMatrix();

        glDisable(GL_TEXTURE_2D);

        glColor3d(1,1,1);
        sprintf(buffer2, "> Hay comida chatarra volando! Debemos");
        draw3dStringScale(GLUT_STROKE_MONO_ROMAN, 0.1, buffer2, -380, 590, 0);
        sprintf(buffer2, "destruirla para que no caiga en manos equivocadas!");
        draw3dStringScale(GLUT_STROKE_MONO_ROMAN, 0.1, buffer2, -100, 590, 0);
        sprintf(buffer2, "equivocadas!");
        draw3dStringScale(GLUT_STROKE_MONO_ROMAN, 0.1, buffer2, 170, 590, 0);
        sprintf(buffer2, "> Utiliza el cursor del mouse para");
        draw3dStringScale(GLUT_STROKE_MONO_ROMAN, 0.1, buffer2, -380, 570, 0);
        sprintf(buffer2, "apuntar y da click para disparar!");
        draw3dStringScale(GLUT_STROKE_MONO_ROMAN, 0.1, buffer2, -140, 570, 0);
        sprintf(buffer2, "> Tienes tres tiros por cada dos");
        draw3dStringScale(GLUT_STROKE_MONO_ROMAN, 0.1, buffer2, -380, 550, 0);
        sprintf(buffer2, "objetos, hazlos contar!");
        draw3dStringScale(GLUT_STROKE_MONO_ROMAN, 0.1, buffer2, -150, 550, 0);
        sprintf(buffer2, "> Destruye una cierta cantidad para avanzar!");
        draw3dStringScale(GLUT_STROKE_MONO_ROMAN, 0.1, buffer2, -380, 530, 0);
        sprintf(buffer2, "avanzar! Fin de juego si no lo logras");
        draw3dStringScale(GLUT_STROKE_MONO_ROMAN, 0.1, buffer2, -130, 530, 0);
        sprintf(buffer2, "Estas listo?");
        draw3dStringScale(GLUT_STROKE_MONO_ROMAN, 0.1, buffer2, -150, 510, 0);
        sprintf(buffer2, "Presiona backspace para");
        draw3dStringScale(GLUT_STROKE_MONO_ROMAN, 0.15, buffer2, -220, 490, 0);
        sprintf(buffer2, "regresar al menu anterior");
        draw3dStringScale(GLUT_STROKE_MONO_ROMAN, 0.15, buffer2, 30, 490, 0);

}

void newgame(){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texName[2]);
    glPushMatrix();
    glScalef(14.5,42,1.0);
    glTranslated(0,0,100);
    glBegin(GL_QUADS);
    glTexCoord3f(0.0f, 0.0f, -1500.0f);
    glVertex3f(-420.0f, 0.0f, -1500.0f);
    glTexCoord3f(1.0f, 0.0f, -1500.0f);
    glVertex3f(420.0f, 0.0f, -1500.0f);
    glTexCoord3f(1.0f, 1.0f, -1500.0f);
    glVertex3f(420.0f, 220.0f, -1500.0f);
    glTexCoord3f(0.0f, 1.0f, -1500.0f);
    glVertex3f(-420.0f, 220.0f, -1500.0f);
    glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    if(!difficultyText){
        glColor3d(1,0,0);
        //Medidas de NewGame
        // glPushMatrix();
        // glTranslated(0,0,-10);
        // glRectd(-60,105,100,135);
        // glPopMatrix();
        glColor3d(1,1,1);
        glBegin(GL_TRIANGLES);
            glVertex2f(-90.0,triangleRasterY+15.0);
            glVertex2f(-90.0,triangleRasterY+5.0);
            glVertex2f(-70.0,triangleRasterY+10.0);
        glEnd();
        sprintf(buffer, "New Game");
        draw3dStringScale(GLUT_STROKE_MONO_ROMAN, 0.2, buffer, -50, 100,0);
        sprintf(buffer, "Instrucciones");
        draw3dStringScale(GLUT_STROKE_MONO_ROMAN, 0.2, buffer, -50, 50,0);
    }
    if(difficultyText && !newGame){
        glColor3d(1,1,1);

        glBegin(GL_TRIANGLES);
            glVertex2f(-40.0,triangleRasterY+15.0);
            glVertex2f(-40.0,triangleRasterY+5.0);
            glVertex2f(-20.0,triangleRasterY+10.0);
        glEnd();

        sprintf(buffer, "Easy");
        draw3dStringScale(GLUT_STROKE_MONO_ROMAN, 0.2, buffer, 0, 125, 0);
        sprintf(buffer, "Normal");
        draw3dStringScale(GLUT_STROKE_MONO_ROMAN, 0.2, buffer, 0, 100, 0);
        sprintf(buffer, "Hard");
        draw3dStringScale(GLUT_STROKE_MONO_ROMAN, 0.2, buffer, 0, 75, 0);

    }
}

void gameArea() {

    //Recordatorio de tamaño de Ortho...
    //         -x      x     -y     y     -z    z
    //glOrtho(-400.0, 400, -200.0, 200.0, 100, 300 )
    //LIMPIA EL BUFFER DE PROFUNDIDAD
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,1,1);
    //Texto en la parte inferior / opciones
    if(!instrucciones)
        intro();

    if(!newGame && !instrucciones)
        newgame();

    if (instrucciones)
        menuInstrucciones();


    //dibujar ammo
glDisable(GL_TEXTURE_2D);

    if(gameStart){
        rasterBalas = -399;
        for(int i = 0; i<balasRestantes; i++){
            glColor3d(1,0,0);
            glRectd(rasterBalas,30,rasterBalas+10,55);
            glColor3d(1,1,0);
            glRectd(rasterBalas,15,rasterBalas+10,55);
            rasterBalas+=35;
        }

glEnable(GL_TEXTURE_2D);

        glColor3d(1,1,1);
        sprintf(buffer, "S H O T S");
        draw3dStringScale(GLUT_STROKE_MONO_ROMAN, 0.1, buffer, -400, 3, 0);


glDisable(GL_TEXTURE_2D);

    //Discos que faltan por ser aventados en la ronda
        if(((int)tiempoTranscurridoParpadeo%100) == 0 ){
            if(esAventado[cualDiscoVas]){
                esAventado[cualDiscoVas] = false;
                esAventado[cualDiscoVas+1] = false;
            }else{
                esAventado[cualDiscoVas] = true;
                esAventado[cualDiscoVas+1] = true;
            }
        }

        for(int i=0; i<10; i++){

            if(esAventado[i]){
                glPushMatrix();
                if(colorDisco[i])
                    glColor3f(1.0, 0.0, 0.0);
                else glColor3f(1.0, 1.0, 1.0);
                glLineWidth(1);
                glTranslated(rasterDiscosDeRonda,585,0);
                glRotated(30,0,0,1);
                glScaled(1,0.8,0.1);
                glutSolidSphere(15,100,100);
                glPopMatrix();
            }
            rasterDiscosDeRonda+=35;
        }

        for (int i=0; i<32;i++){
        glPushMatrix();
        glColor3d(0,0,1);
        glRectd(rasterCuantosNecesitasX,555,rasterCuantosNecesitasX+3,562);
        glPopMatrix();
        rasterCuantosNecesitasX+= 5;
        }

        rasterCuantosNecesitasX = -210;
        rasterDiscosDeRonda = -200;

glEnable(GL_TEXTURE_2D);

        //Textura / Fondo, para que no se vea tan pirata el area de juego...
        glColor3d(1,1,1);
        glBindTexture(GL_TEXTURE_2D, texName[0]);
        glPushMatrix();
        glScalef(14.5,42,1.0);
        glTranslated(0,0,100);
        glBegin(GL_QUADS);
            glTexCoord3f(0.0f, 0.0f, -1500.0f);
            glVertex3f(-420.0f, 0.0f, -1500.0f);

            glTexCoord3f(1.0f, 0.0f, -1500.0f);
            glVertex3f(420.0f, 0.0f, -1500.0f);

            glTexCoord3f(1.0f, 1.0f, -1500.0f);
            glVertex3f(420.0f, 220.0f, -1500.0f);

            glTexCoord3f(0.0f, 1.0f, -1500.0f);
            glVertex3f(-420.0f, 220.0f, -1500.0f);
        glEnd();
        glPopMatrix();


        //Scoreboard
        glColor3d(1,1,1);
        sprintf(marcadorPuntaje,"%1d",puntaje);
        draw3dStringScale(GLUT_STROKE_MONO_ROMAN, 0.07, marcadorPuntaje, 320, 12, 0);
        sprintf(buffer, "S C O R E");
        draw3dStringScale(GLUT_STROKE_MONO_ROMAN, 0.07, buffer, 320, 1, 0);

        glColor3d(0,0,0);
        glPushMatrix();
        //glTranslated(0,0,1);
        glRectd(300,0,403,40);
        glPopMatrix();

    }

    // Dibujar discos; el dibujado es independiente uno del otro
    // pero usan el mismo timer.

    if(discoUnoEnPantalla){
        glBindTexture(GL_TEXTURE_2D, texName[1]);
        glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
        glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

        //Activar la generación de coordenadas
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);

        glPushMatrix();
        glColor3f(1.0, 1.0, 1.0);
        glLineWidth(1);
        glTranslated(traslacionDiscoUnoX,traslacionDiscoUnoY,-traslacionDiscoUnoZ);
        glScaled(1.6,0.6,0.2);
        //glutWireCube(20);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glutSolidSphere(15,50,50);
        glPopMatrix();

        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
    } else if(newGame){
        glColor3d(1,1,1);
        glPointSize(5);
        if(boolExplosionUno == false){
            boolExplosionUno = true;
            contExplosionUno = 0;
        }
        if(boolExplosionUno && contExplosionUno < 100){
            glPushMatrix();
            glTranslated(0,contExplosionUno,0);
            sprintf(buffer, "1000");
            draw3dStringScale(GLUT_STROKE_MONO_ROMAN, 0.07, buffer, traslacionDiscoUnoX, traslacionDiscoUnoY, 0);
            glPopMatrix();
            contExplosionUno++;
        } else{
            boolExplosionUno = false;
        }
        // glBegin(GL_POINTS);
        // glPushMatrix();
        // glVertex2f(traslacionDiscoUnoX,traslacionDiscoUnoY);
        //     glPushMatrix();
        //         glVertex2f(traslacionDiscoUnoX,traslacionDiscoUnoY+5);
        //         glTranslated(0,tiempoTranscurridoExplosion,0);
        //     glPopMatrix();
        //     glPushMatrix();
        //         glVertex2f(traslacionDiscoUnoX,traslacionDiscoUnoY-5);
        //         glTranslated(0,-tiempoTranscurridoExplosion,0);
        //     glPopMatrix();
        //     glPushMatrix();
        //         glVertex2f(traslacionDiscoUnoX+5,traslacionDiscoUnoY);
        //         glTranslated(tiempoTranscurridoExplosion,0,0);
        //     glPopMatrix();
        //     glPushMatrix();
        //         glVertex2f(traslacionDiscoUnoX-5,traslacionDiscoUnoY);
        //         glTranslated(-tiempoTranscurridoExplosion,0,0);
        //     glPopMatrix();
        // glPopMatrix();
        // glEnd();
    }

    if(discoDosEnPantalla){
        glBindTexture(GL_TEXTURE_2D, texName[1]);
        glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
        glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

        //Activar la generación de coordenadas
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);

        glPushMatrix();
        glColor3f(1.0, 1.0, 1.0);
        glLineWidth(1);
        glTranslated(traslacionDiscoDosX,traslacionDiscoDosY,-traslacionDiscoDosZ);
        glScaled(1.6,0.6,0.2);
        //glutWireCube(20);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glutSolidSphere(15,50,50);
        glPopMatrix();

        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
    }else if(newGame){
        glColor3d(1,1,1);
        glPointSize(5);

        if(boolExplosionDos == false){
            boolExplosionDos = true;
            contExplosionDos = 0;
        }
        if(boolExplosionDos && contExplosionDos < 100){
            glPushMatrix();
            glTranslated(0,contExplosionDos,0);
            sprintf(buffer, "1000");
            draw3dStringScale(GLUT_STROKE_MONO_ROMAN, 0.07, buffer, traslacionDiscoDosX, traslacionDiscoDosY, 0);
            glPopMatrix();
            contExplosionDos++;
        } else{
            boolExplosionDos = false;
        }
        // glBegin(GL_POINTS);
        // glPushMatrix();
        // glVertex2f(traslacionDiscoDosX,traslacionDiscoDosY);
        // glVertex2f(traslacionDiscoDosX,traslacionDiscoDosY+5);
        // glVertex2f(traslacionDiscoDosX,traslacionDiscoDosY-5);
        // glVertex2f(traslacionDiscoDosX+5,traslacionDiscoDosY);
        // glVertex2f(traslacionDiscoDosX-5,traslacionDiscoDosY);
        // glPopMatrix();
        // glEnd();
    }

glEnable(GL_TEXTURE_2D);
    glutSwapBuffers();
}


void reshape (int w, int h){
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();

    glFrustum (-400.0, 400.0, 0.0, 600.0, 99, 2000.0);

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
            tiempoTranscurridoUno = 0;
            tiempoTranscurridoDos = 0;
            triangleRasterY = 100.0;
            velocidadDeDificultad = 80;
            balasRestantes = 3;
            instrucciones = false;
            puntaje = 0;
            aparecerNombres = true;
            newGame = false;
            gameStart = false;
            difficultyText = false;
            //desaparece = true;
            colisionDiscoUno = false;
            colisionDiscoDos = false;
            discoUnoEnPantalla = false;
            discoDosEnPantalla = false;
            traslacionDiscoUnoX = -100;
            traslacionDiscoUnoY = 10;
            traslacionDiscoUnoZ = -20;

            traslacionDiscoDosX = 100;
            traslacionDiscoDosY = 10;
            traslacionDiscoDosZ = -20;


            for (int i=0;i<10;i++){
                colorDisco[i]= false;

            }

            // cronometro = false;
            glutPostRedisplay();
            break;
        case 'i':
        case 'I':
            // desaparece = false;
            // glutTimerFunc(1, discos, 1);
            glutPostRedisplay();
            break;
        case 8:
        if (instrucciones){
        instrucciones = false;
        triangleRasterY=100.0;
        glutPostRedisplay();
        }
        break;
        case 13:
        if(difficultyText && !newGame){
            if(triangleRasterY == 100.0){ //La dificultad seleccionada es Normal
                newGame = true;
                gameStart = true;
                discoUnoEnPantalla = true;
                discoDosEnPantalla = true;
                desaparece = false;
                glutPostRedisplay();
                glutTimerFunc(1000, discos, 1);
            }else if(triangleRasterY == 125.0){ //La dificultad seleccionada es Easy
                newGame = true;
                gameStart = true;
                discoUnoEnPantalla = true;
                discoDosEnPantalla = true;
                desaparece = false;
                velocidadDeDificultad = (3*velocidadDeDificultad)/4;
                glutPostRedisplay();
                glutTimerFunc(1000, discos, 1);
            } else if(triangleRasterY == 75.0){ //La dificultad seleccionada es Hard
                newGame = true;
                gameStart = true;
                discoUnoEnPantalla = true;
                discoDosEnPantalla = true;
                desaparece = false;
                velocidadDeDificultad = velocidadDeDificultad * 1.5;
                glutPostRedisplay();
                glutTimerFunc(1000, discos, 1);
                }
            }else if(triangleRasterY==50.0){
            instrucciones = true;
            glutPostRedisplay();
        }else{
            aparecerNombres = false;
            difficultyText = true;
            glutPostRedisplay();
            }
            break;
        case 27:
        exit(0);
        break;
        case 32:
        if(nextMiniRound){
            nextMiniRound=false;
            discoUnoEnPantalla = true;
            discoDosEnPantalla = true;

            tiempoTranscurridoParpadeo = 0;

            traslacionDiscoUnoX = -100;
            traslacionDiscoUnoY=10;
            traslacionDiscoUnoZ=-20;

            traslacionDiscoDosX = 100;
            traslacionDiscoDosY=10;
            traslacionDiscoDosZ=-20;

            balasRestantes = 3;
            cualDiscoVas+=2;
            tiempoTranscurridoUno = 0;
            tiempoTranscurridoDos = 0;
            glutPostRedisplay();
            glutTimerFunc(1000,discos,1);
            }
        break;
        }

}

void specialKeys(int key, int x, int y) {

    switch(key) {
        case GLUT_KEY_UP:
            if(aparecerNombres){
                triangleRasterY+=50.0;
                if(triangleRasterY>100.0)
                    triangleRasterY=100.0;
            }
            if(difficultyText){
                triangleRasterY+=25.0;
                if(triangleRasterY>125.0)
                    triangleRasterY=125.0;
            }
            glutPostRedisplay(); break;
        case GLUT_KEY_DOWN:
            if(aparecerNombres){
                triangleRasterY-=50.0;
                if(triangleRasterY<50.0)
                    triangleRasterY=50.0;
            }
            if(difficultyText){
                triangleRasterY-=25.0;
                if(triangleRasterY<75.0)
                    triangleRasterY=75.0;
            }
            glutPostRedisplay(); break;
    }
}

void dispara(int button, int state, int mouseX, int mouseY){

    // restar uno del contador de disparos disponibles
    // si el contador es zero, entonces no se puede disparar
        /* left button increase joint angle, right button decreases it */

        //Si el usuario oprime el boton izq del mouse
          if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN /*&& balasRestantes >=1*/){
            balasRestantes-=1;
            traslacionBalaY = screenHeight-mouseY;
            traslacionBalaX = mouseX-400;
            disparaBala();
            PlaySound("C:\\Users\\Chinolee\\Documents\\Graficas\\GraficasProyecto\\shotgun.wav", NULL, SND_ASYNC|SND_FILENAME);
        }
    glutPostRedisplay();

}


int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE| GLUT_RGB| GLUT_DEPTH);
    glutInitWindowSize (800, 600);
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);

    init();
    initRendering();
    glEnable(GL_DEPTH_TEST); //para diferenciar que vertices estan al frente y detras ver ejemplo del documento de word

    glutDisplayFunc(gameArea);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutMouseFunc(dispara);


    glutMainLoop();
    return 0;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <assert.h>
#include <fstream>
#include "imageloader.h"

using namespace std;

Image::Image(char* ps, int w, int h) : pixels(ps), width(w), height(h)
{

}

Image::~Image()
{
    delete[] pixels;
}

namespace
{
//Converts a four-character array to an integer, using little-endian form
    int toInt(const char* bytes)
    {
        return (int)(((unsigned char)bytes[3] << 24) |
                     ((unsigned char)bytes[2] << 16) |
                     ((unsigned char)bytes[1] << 8) |
                     (unsigned char)bytes[0]);
    }

//Converts a two-character array to a short, using little-endian form
    short toShort(const char* bytes)
    {
        return (short)(((unsigned char)bytes[1] << 8) |
                       (unsigned char)bytes[0]);
    }

//Reads the next four bytes as an integer, using little-endian form
    int readInt(ifstream &input)
    {
        char buffer[4];
        input.read(buffer, 4);
        return toInt(buffer);
    }

//Reads the next two bytes as a short, using little-endian form
    short readShort(ifstream &input)
    {
        char buffer[2];
        input.read(buffer, 2);
        return toShort(buffer);
    }

//Just like auto_ptr, but for arrays
    template<class T>
    class auto_array
    {
    private:
        T* array;
        mutable bool isReleased;
    public:
        explicit auto_array(T* array_ = NULL) :
                array(array_), isReleased(false)
        {
        }

        auto_array(const auto_array<T> &aarray)
        {
            array = aarray.array;
            isReleased = aarray.isReleased;
            aarray.isReleased = true;
        }

        ~auto_array()
        {
            if (!isReleased && array != NULL)
            {
                delete[] array;
            }
        }

        T* get() const
        {
            return array;
        }

        T &operator*() const
        {
            return *array;
        }

        void operator=(const auto_array<T> &aarray)
        {
            if (!isReleased && array != NULL)
            {
                delete[] array;
            }
            array = aarray.array;
            isReleased = aarray.isReleased;
            aarray.isReleased = true;
        }

        T* operator->() const
        {
            return array;
        }

        T* release()
        {
            isReleased = true;
            return array;
        }

        void reset(T* array_ = NULL)
        {
            if (!isReleased && array != NULL)
            {
                delete[] array;
            }
            array = array_;
        }

        T* operator+(int i)
        {
            return array + i;
        }

        T &operator[](int i)
        {
            return array[i];
        }
    };
}

Image* loadBMP(const char* filename)
{
    ifstream input;
    input.open(filename, ifstream::binary);
    assert(!input.fail() || !"Could not find file");
    char buffer[2];
    input.read(buffer, 2);
    assert(buffer[0] == 'B' && buffer[1] == 'M' || !"Not a bitmap file");
    input.ignore(8);
    int dataOffset = readInt(input);

    //Read the header
    int headerSize = readInt(input);
    int width;
    int height;
    switch (headerSize)
    {
    case 40:
        //V3
        width = readInt(input);
        height = readInt(input);
        input.ignore(2);
        assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");
        assert(readShort(input) == 0 || !"Image is compressed");
        break;
    case 12:
        //OS/2 V1
        width = readShort(input);
        height = readShort(input);
        input.ignore(2);
        assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");
        break;
    case 64:
        //OS/2 V2
        assert(!"Can't load OS/2 V2 bitmaps");
        break;
    case 108:
        //Windows V4
        assert(!"Can't load Windows V4 bitmaps");
        break;
    case 124:
        //Windows V5
        assert(!"Can't load Windows V5 bitmaps");
        break;
    default:
        assert(!"Unknown bitmap format");
    }

    //Read the data
    int bytesPerRow = ((width * 3 + 3) / 4) * 4 - (width * 3 % 4);
    int size = bytesPerRow * height;
    auto_array<char> pixels(new char[size]);
    input.seekg(dataOffset, ios_base::beg);
    input.read(pixels.get(), size);

    //Get the data into the right format
    auto_array<char> pixels2(new char[width * height * 3]);
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            for (int c = 0; c < 3; c++)
            {
                pixels2[3 * (width * y + x) + c] =
                    pixels[bytesPerRow * y + 3 * x + (2 - c)];
            }
        }
    }

    input.close();
    return new Image(pixels2.release(), width, height);
}
