#ifndef __BIBLIOTECA_H__
#define __BIBLIOTECA_H__

#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <vector>
#include "Circle.h"
#include "Quad.h"
//#include "Tiro.h"
#include "Helicopter.h"
#include "Cenario.h"
#include "biblioteca_tiny/tinyxml2.h"

using namespace tinyxml2;
using namespace std;


void keyPress(unsigned char key, int x, int y);    

void keyup(unsigned char key, int x, int y);

void ResetKeyStatus();


void updatePaddle( GLdouble timeDiff );


void idle(void);

void init(void);

void reshape( int w, int h );

void display( void );


void arrow_keys ( int a_keys, int x, int y );

int startFunctions(int argc, char** argv);

void mouseMove(int mouse_x, int mouse_y);

void mouseClick(int button, int status ,int x, int y);

void runningFunctions();


#endif
