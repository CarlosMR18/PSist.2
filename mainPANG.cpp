



//***********************
// PANG Open GL
// Programación de Sistemas
// Claudio Rossi, Universidad Politécnica de Madrid 
// (C) 2022 
//***********************




#include <stdio.h>
#include <math.h>
#include <stdlib.h>
//#include <unistd.h> En windows viene por defecto y no tiene ese nombre
#include <string.h>

#include "Shape.h"
#include "Ball.h"
#include "Bullet.h"
#include "Man.h"
#include "ObjectsList.h" // Es la cabecera de la clase ObjectList

#include "commonstuff.h"
#include "GLstuff.h"


//***********************
// Prototipos de funciones 
//***********************

// Callback de la logica del juego
void myLogic();

//Callback de dibujo
void OnDibuja(void);	

//Callbacks para teclado y raton
void OnKeyboardDown(unsigned char key, int x, int y);
void OnMouseBtn(int button, int state,int x, int y);
void OnMouseMoveBtn(int x, int y);
void OnSpecKeyboardDown(int key, int x, int y);

void printdata();
void gameover(int score);  // no usada

  
//***********************
// Variables globales
//***********************

// Posición de la camara
float cam_pos[6]={0, 0, 27};


// Modo del Mouse
int MODE=NONE;

// Objetos globales
ObjectsList worldobjects;
Man *theMan=NULL;
Bullet *theBullet=NULL;

// Varias constantes usadas en el programa
int shotTime=0;
int nMan=3;
int score=0;

// Textura para el fondo
GLuint KLtexture;



//***********************
// Programa principal
//***********************


int main(int argc,char* argv[])
{

  // inicializaciones
    char nombre_pantalla[10] = "PANG 2022";

  // Inicialización GLUT
  glutInit(&argc, argv);

  // Inicializaciones openGL (ver GLstuff.c)
  init_GL_stuff( nombre_pantalla, WINX, WINY); //Hemos modificado el argumento
  
  // Define call backs te GLUT

  // Display function: contiene las instrucciones de dibujo
  glutDisplayFunc(OnDibuja);
  
    // Idle function: contiene la logica del juego
  glutIdleFunc(myLogic);
  
  // Callbacks de teclado y ratón  (solo se usa las para el teclado)
  glutKeyboardFunc(OnKeyboardDown);
  glutSpecialFunc(OnSpecKeyboardDown);
  glutMotionFunc(OnMouseMoveBtn);
  glutMouseFunc(OnMouseBtn);

  
  // Posicciona el punto de vista (cámara)
  gluLookAt(cam_pos[0],cam_pos[1],cam_pos[2],  // posicion del  ojo  
	    0.0, 0.0, 0.0,		        // hacia que punto mira  
	    0.0, 1.0, 0.0);         // vector "UP"  (vertical positivo)


  
  // Creacción de los objetos iniciales
  theMan = worldobjects.getMan();

  // WORLDOBJECTS es declarada estática, se inicializa "automaticamente" - ya ha creado y contiene las pelotas  //***

  
  // Carga la imagen del fondo
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  KLtexture= LoadTexture(800,600, "PANG.bmp" ); 
  glBindTexture (GL_TEXTURE_2D, KLtexture);

  
  // bucle infinito de Open GL
  glutMainLoop();

  // Esto solo sirve para que el compilador no proteste, nunca se llegará aquí
  return 0;   

}

/************************** FIN DEL MAIN ************************************/





//***********************
// Callbacks
//***********************


// Imprime puntuacción y numero de vidas
void printdata()
{
  int i,l;
  char buffer[50];
  
  glPushMatrix();

  sprintf(buffer,"Men: %d       Score: %d",nMan,score);
  l=strlen(buffer); 

  glDisable(GL_LIGHTING);
  glColor3f(1.0f, 1.0f, 1.0f);
  glRasterPos3f(-9, 9,-0.1);
  for( i=0; i < l; i++) 
    {
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, buffer[i]); // Print a character on the screen
    }
  glEnable(GL_LIGHTING);

  glPopMatrix();

}


//no usada
void gameover(int score)
{
  int i,l;
  char buffer[30];
  
  glPushMatrix();

    sprintf(buffer,"GAME OVER! Points: %d",score);

  l=strlen(buffer); 

  glDisable(GL_LIGHTING);
  glColor3f(1.0f, 1.0f, 1.0f);
  glRasterPos3f(-9, 9,-0.1);
  for( i=0; i < l; i++) 
    {
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, buffer[i]); // Print a character on the screen
    }
  glEnable(GL_LIGHTING);

  glPopMatrix();

}


// Logica del juego: mueve los objetos mandando el mensaje "move"
void myLogic()
{
  int res;
  
  // borra el proyectil después de cierto tiempo si no ha dado con nada
  if(shotTime++>MAXSHOTTIME)
    {
      worldobjects.remove(theBullet);    // si theBullet==NULL no pasa nada, la remove no lo encuentra y no hace nada
      theBullet = NULL;
      shotTime = 0;
    }

  // Pide al mudo que mueva los objetos
  worldobjects.move();

  // Pide si ha habido colisión, pasa referencia a proyectil y nave, retorna tipo de colisión y posición de la colisión
  // res==0:  No ha colisicón
  // res==1:  Bola/jugador
  // res>=2:  Bola/Proyectil, depende del tipo de asteroide (grande/mediano/pequeño)
  res = worldobjects.collisions(theBullet,theMan);    //***  //***

  
  if(res==1)    
    {
      nMan--;

      // Esto habría que mejorarlo...  //***
      if(nMan==0)
	{
	  gameover(1);
	  exit(1);
	}
      
      theMan->resetpos();
      worldobjects.reposition(theMan); //El profesor se contradice.
    }

  if(res>=2)    
    {
      worldobjects.remove(theBullet);     //***
      theBullet = NULL;
      shotTime = 0;
      score += 100*(res-1);
    }



}
 
/**************************************************************/ 

void OnDibuja(void)
{ 
  //Borrado de la pantalla	
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Dibuja la imagen del fondo
  displaytext(KLtexture);

  // Manda el mensaje "draw" al mundo
  worldobjects.draw();    

  // imprime datos
  printdata();
 
  //Al final, cambiar el buffer
  glutSwapBuffers();
  glutPostRedisplay();//se le indica que redibuje la pantalla
  /**************************************************************/}



   


void OnKeyboardDown(unsigned char key, int x, int y)
{ 
  int mod;

  mod=glutGetModifiers();

  switch(key)
    {
    case 'q':
    case ESC:
      exit(1);
    case ' ':
      // Si no hay proyectil, lo crea  //***
      if(!theBullet)
	{
	  theBullet=theMan->fire(); 
	  worldobjects.add(theBullet);
	}
      
      break;
      //    case ',': theMan->hyperjump(); break;  // hyper jump (mueve el hombre a una posición random)  --- NO USADA

    }		

}


void OnSpecKeyboardDown(int key, int x, int y)
{ 
  switch(key)
    {

    case GLUT_KEY_DOWN:
      break;
    case GLUT_KEY_UP:
      break;
    case GLUT_KEY_LEFT:  theMan->strafe(-0.25,0,0);
      break;
    case GLUT_KEY_RIGHT: theMan->strafe(0.25,0,0);
      break;
    case GLUT_KEY_PAGE_DOWN:
      break;
    case GLUT_KEY_PAGE_UP:
      break;
    }		

}

// No usada
void OnMouseBtn(int button, int state,int x, int y)
{
  if(state==GLUT_DOWN)
    if(button==GLUT_LEFT_BUTTON)
      MODE=TRANS;
    else
      if(button==GLUT_RIGHT_BUTTON)
        MODE=ROT;
      else
        MODE=NONE;
}

 
// No usada
void  OnMouseMoveBtn  (int x, int y)
{

  //  printf("MOUSE MOVES!\n");
    
  if(MODE==TRANS)
    {
     
    }
  else
    {
     
    }

}



