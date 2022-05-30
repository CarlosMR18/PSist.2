//#define _CRT_SECURE_NO_DEPRECATE Codigo para solucionar error de fopen no secure.
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
 
 

//#ifdef linux
#ifdef __APPLE__
#include "GLUT/glut.h"
#include <stdlib.h>
#else
#ifdef __linux__
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/glut.h>
#else
#include <windows.h>
#include <GL/glut.h> //Se ha implementado en el sistema la libreria glut.
#endif
#endif

// Prototipos de funciones
GLuint LoadTexture(int, int, const char * filename );

void displaytext(GLuint Thetexture);

void init_GL_stuff(char*,int,int);
 
