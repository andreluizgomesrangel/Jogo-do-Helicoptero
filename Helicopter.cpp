#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include "Helicopter.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <time.h>
#include  "Tiro.h"

using namespace std;

Helicopter::Helicopter(float x, float y, float veloc, float r, float width, float hight, string ID){

	Nivel = 0;
	scale = r/10;
	angHelice = 0;
	angHelice2 = 0 ;
	angHelicoptero = rand()%360;
	ang2Helicoptero = 0;
	ang3Helicoptero = 0;
	xHelic = x;
	yHelic = 0.75*scale;
	velHelic = veloc;

	zHelic = y;
	mov = 0;
	movL = 0;
	movR = 0;
	radius = r;
	distCamera3pessoa = r/2;

	velHelice = 8;
	velHelice2 = velHelice;

	angGunXZ = 0;
	angGunXZ2 = 0;

	frontCord();
	w = width;
	h = hight;
	id = ID;
	ResetKeyStatus();

	ang1Cam = 180;
	ang2Cam = 90;
	ang1CamAux = ang1Cam;
	ang2CamAux = ang2Cam;

	xe1 = xHelic;
	ye1 = yHelic;
	ze1 = zHelic;
	r1 = 1.5*scale;

	xe2 = xHelic - 2.0*cos( angHelicoptero*M_PI/180 )*scale;
	ye2 = yHelic + 2.0*sin( ang2Helicoptero*M_PI/180 )*scale;
	ze2 = zHelic + 2.0*sin( angHelicoptero*M_PI/180 )*scale;
	r2 = 0.7*scale;

	xe3 = xHelic - 3.3*cos( angHelicoptero*M_PI/180 )*scale;
	ye3 = yHelic + 3.3*sin( ang2Helicoptero*M_PI/180 )*scale;
	ze3 = zHelic + 3.3*sin( angHelicoptero*M_PI/180 )*scale ;
	r3 = 0.6*scale;

	esferas = 0;

	morto = 0;
	pousado = 1;

	deslocamento1 = 0;
	deslocamento2 = 0;

	freqTiro = 0;

}


void Helicopter::cabin(){ 
	if(id=="Jogador") glColor3f(0.07, 0.1, 0.07);
	else glColor3f(0.5 , 0.07, 0.07);
	glPushMatrix();
	glBegin(GL_POLYGON);
		glVertex3d(0.5, 0.5, 0.5);
		glVertex3d(0.5, -0.5, 0.5);
		glVertex3f(0.8f, -0.5f, 0.4f);
		glVertex3f(0.8f, 0.5f, 0.4f);
	glEnd();


	//Windscreen removed
	glBegin(GL_POLYGON);
		glVertex3d(1.2, 0.5, 0.0);
		glVertex3d(1.2, -0.5, 0.0);				
		glVertex3f(1.4f, -0.5f, -0.1f);
		glVertex3f(1.4f, 0.5f, -0.1f);
	glEnd();
	
	glBegin(GL_POLYGON);						
		glVertex3f(1.4f, 0.5f, -0.1f);
		glVertex3f(1.4f, -0.5f, -0.1f);
		glVertex3d(1.4, -0.5, -0.4);
		glVertex3d(1.4, 0.5, -0.4);
	glEnd();
	

	glBegin(GL_POLYGON);
	glVertex3f(1.4f, -0.5f, -0.1f);
	glVertex3f(1.4f, 0.5f, -0.1f);
	glVertex3f(1.6f, 0.5f, -0.2f);
	glVertex3f(1.6f,-0.5f, -0.2f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(1.6f, 0.5f, -0.2f);
	glVertex3f(1.6f,-0.5f, -0.2f);
	glVertex3d(1.6, -0.5,  -0.3); // baixo direita
	glVertex3d(1.6,  0.5,  -0.3); // baixo esquerda
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3d(1.6, -0.5,  -0.3);
	glVertex3d(1.6,  0.5,  -0.3); 
	glVertex3f(1.2f, 0.5f, -0.5f);
	glVertex3f(1.2f,-0.5f, -0.5f);
	glEnd();



	glBegin(GL_POLYGON);						
		glVertex3f(1.4f, 0.5f, -0.4f);
		glVertex3f(1.4f, -0.5f, -0.4f);
		glVertex3d(1.2, -0.5, -0.5);
		glVertex3d(1.2, 0.5, -0.5);
	glEnd();
	glBegin(GL_POLYGON);		
		glVertex3d(1.2, -0.5, -0.5);
		glVertex3d(1.2, 0.5, -0.5);
		glVertex3f(0.5f, 0.5f, -0.5f);
		glVertex3f(0.5f, -0.5f, -0.5f);
	glEnd();
	// Positive y side
	glBegin(GL_POLYGON);		
		glVertex3f(1.2f, 0.5f, 0.0f);
		glVertex3f(1.4f, 0.5f, -0.1f);
		glVertex3d(1.4, 0.5, -0.4);
		glVertex3d(1.2, 0.5, -0.5);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3d(1.0, 0.5, 0.2);
		glVertex3f(1.2f, 0.5f, 0.0f);
		glVertex3d(1.2, 0.5, -0.5);
		glVertex3d(1.0, 0.5, -0.5);
	glEnd();
	// Negative y side
	glBegin(GL_POLYGON);		
		glVertex3d(1.0, -0.5, -0.5);
		glVertex3d(1.2, -0.5, -0.5);
		glVertex3d(1.4, -0.5, -0.4);
		glVertex3f(1.4f, -0.5f, -0.1f);
		glVertex3f(1.2f, -0.5f, 0.0f);
		glVertex3d(1.0, -0.5, 0.2);
	glEnd();
	// Doors
	// Positive y side
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glColor3f(0.07, 0.1, 0.07);
	glColor4d(0.08 ,0.12 ,0.08, 0.6);
	glPushMatrix();
	glTranslated(0.5, 0.5, 0.0);
	glRotated( 0, 0, 0, 1);	 // porta
	glDisable(GL_CULL_FACE);
	glBegin(GL_POLYGON);
		glVertex3d(0.0, 0.0, -0.5);
		glVertex3d(0.5, 0.0, -0.5);
		glVertex3d(0.5, 0.0, 0.2);
		glVertex3d(0.3, 0.0, 0.4);
		glVertex3d(0.0, 0.0, 0.5);
	glEnd();
	glPopMatrix();
	// Negative y side
	glPushMatrix();
	glTranslated(0.5, -0.5, 0.0);
	glRotated(  -0 , 0, 0, 1);	 //porta
	glDisable(GL_CULL_FACE);
	glBegin(GL_POLYGON);
		glVertex3d(0.0, 0.0, -0.5);
		glVertex3d(0.5, 0.0, -0.5);
		glVertex3d(0.5, 0.0, 0.2);
		glVertex3d(0.3, 0.0, 0.4);
		glVertex3d(0.0, 0.0, 0.5);
	glEnd();
	glPopMatrix();	
	glPopMatrix();
}

// Draw helicopter - Rotor	
void Helicopter::rotor(){	

	glColor3d(0.1, 0.1, 0.0);
	glPushMatrix();		
	glTranslated(0.0,0.0,0.65);
	glRotated(angHelice, 0.0, 0.0, 1.0);
	glScaled(5.0, 0.25, 0.01);	
	glutSolidCube(1);
	glPopMatrix();

	glColor3d(1, 1, 1);
	glPushMatrix();		
	glTranslated(0.0,0.0,0.65 + 0.01);
	glRotated(angHelice, 0.0, 0.0, 1.0);
	glScaled(1.0, 0.40, 0.01);	
	glutSolidCube(1);
	glPopMatrix();


	glColor3d(0.1, 0.1, 0.0);
	glPushMatrix();
	glTranslated(0.0,0.0,0.65);
	glRotated(angHelice, 0.0, 0.0, 1.0);
	glScaled(0.25, 5.0, 0.01);	
	glutSolidCube(1);
	glPopMatrix();

	glColor3d(1, 1, 1);
	glPushMatrix();
	glTranslated(0.0,0.0,0.65 + 0.01);
	glRotated(angHelice, 0.0, 0.0, 1.0);
	glScaled(0.25, 1.0, 0.01);	
	glutSolidCube(1);
	glPopMatrix();

	//Tail rotor
	glPushMatrix();

		glPushMatrix();
		glColor3d( sin(2*angHelice*M_PI/180) , sin(angHelice*M_PI/180) , sin(0.5*angHelice*M_PI/180)  );
		glTranslated(-3.3, -0.06, 0.08);
		glScaled(0.05, 0.06,0.05);
		//glutSolidCube(1);
		glutSolidSphere(1,10,10);
		glPopMatrix();

		glPushMatrix();
		glTranslated(-3.3, 0.06, 0.08);
		glRotated(90, 1.0, 0.0, 0.0);
		glScaled(0.3, 0.3, 1.0);
		glColor3d(0.8, 0.8, 1.0);
		glTranslated(0.0 , 0.0, -0.1);
		gluCylinder(gluNewQuadric(),0.15,0.15,0.20,10,10);
		glTranslated(0.0 , 0.0, -0.13);
		gluCylinder(gluNewQuadric(),0.02,0.15,0.10,10,10);
		glPopMatrix();

	glColor3d(0.1, 0.1, 0.0);
	glTranslated(-3.3, 0.18, 0.08);
	glRotated(angHelice2, 0.0, 1.0, 0.0);
	glScaled(0.95, 0.01, 0.08);
	glutSolidCube(1);

	glPopMatrix();

	glPushMatrix();
	glTranslated(-3.3, 0.18, 0.08);
	glRotated(angHelice2, 0.0, 1.0, 0.0);
	glScaled(0.08, 0.01, 0.95);
	glutSolidCube(1);
	glPopMatrix();

	// Draw - Rotor axle
	glColor3d(0.8, 0.8, 1.0);
	glPushMatrix();
	glTranslated(0.0 , 0.0, 0.5);
	gluCylinder(gluNewQuadric(),0.15,0.15,0.20,10,10);
	glPopMatrix();

	glColor3d(0.8, 0.8, 1.0);
	glPushMatrix();
	glTranslated(0.0 , 0.0, 0.5 + 0.20 + 0.01);
	gluCylinder(gluNewQuadric(),0.15,0.01,0.10,10,10);
	glPopMatrix();		
}

void Helicopter::bag(){

	glColor3f(0.07, 0.1, 0.07);	
	glPushMatrix();
		glRotated(90, 0, 1, 0);
		glTranslatef(0.40,-0.8,0.65);
		glScalef( 1 , 0.5 , 0.5 );
		gluCylinder(gluNewQuadric(),0.22,0.20,1.0,5,5);
	glPopMatrix();

	glColor3f(0.1, 0.1, 0.1); //right back bag
	glPushMatrix();
		glRotated(90, 0, 1, 0);
		glTranslatef(0.40,-0.8,0.4);
		glScalef( 1 , 0.5 , 0.5 );
		gluCylinder(gluNewQuadric(),0.10,0.22,0.5,5,5);
	glPopMatrix();


	glColor3d(0.8, 0.8, 1.0); //left center bag
	glPushMatrix();
		glRotated(90, 0, 1, 0);
		glTranslatef(0.40,0.8,0.65);
		glScalef( 1 , 0.5 , 0.5 );
		gluCylinder(gluNewQuadric(),0.22,0.20,1.0,5,5);
	glPopMatrix();

	glColor3f(0.1, 0.1, 0.1); //left back bag
	glPushMatrix();
		glRotated(90, 0, 1, 0);
		glTranslatef(0.40,0.8,0.4);
		glScalef( 1 , 0.5 , 0.5 );
		gluCylinder(gluNewQuadric(),0.10,0.22,0.5,5,5);
	glPopMatrix();

	glColor3f(0.1, 0.1, 0.1); 
	glPushMatrix();  // right back gun
		glRotated(90, 0, 1, 0);
		glTranslatef(0.40,-0.8,0.99);
		glScalef( 1 , 0.5 , 0.5 );
		gluCylinder(gluNewQuadric(),0.2,0.1,0.9,5,5);
	glPopMatrix();

	glPushMatrix(); // right back gun
		glRotated(90, 0, 1, 0);
		glTranslatef(0.40,0.8,0.99);
		glScalef( 1 , 0.5 , 0.5 );
		gluCylinder(gluNewQuadric(),0.2,0.1,0.9,5,5);
	glPopMatrix();

	glColor3f(0.05, 0.05, 0.1); 
	glPushMatrix();  // right center gun
		glRotated(90, 0, 1, 0);
		glTranslatef(0.40,-0.8,1.39);
		glScalef( 1 , 0.5 , 0.5 );
		gluCylinder(gluNewQuadric(),0.12,0.03,0.5,5,5);
	glPopMatrix();

	glPushMatrix();  // left center gun
		glRotated(90, 0, 1, 0);
		glTranslatef(0.40,0.8,1.39);
		glScalef( 1 , 0.5 , 0.5 );
		gluCylinder(gluNewQuadric(),0.12,0.03,0.5,5,5);
	glPopMatrix();

}

void Helicopter::gun1(){
	glPushMatrix();  // right front gun
		glRotated(90, 0, 1, 0);
		glScalef( 1 , 0.5 , 0.5 );
		gluCylinder(gluNewQuadric(), 0.03 , 0.02 , 0.5 , 5 , 5 );
	glPopMatrix();

}

void Helicopter::gun2(){
	
	glPushMatrix();  // right front gun
		glRotated(90, 0, 1, 0);
		//glTranslatef(0.40,0.55,1.59);
		glScalef( 1 , 0.5 , 0.5 );
		gluCylinder(gluNewQuadric(),0.03,0.02,0.5,5,5);
	glPopMatrix();
	
}

void Helicopter::suport(){
	if(id=="Jogador") glColor3f(0.07, 0.1, 0.07);
	else glColor3f(0.5 , 0.07, 0.07);
	glPushMatrix();
		glTranslated(0.8,-0.75,-0.4);
		glRotated(-90, 1, 0, 0);
		gluCylinder(gluNewQuadric() , 0.05, 0.15 ,0.25,6,6);
	glPopMatrix();

	glPushMatrix();
		glTranslated(0.8,0.75,-0.4);
		glRotated(90, 1, 0, 0);
		gluCylinder(gluNewQuadric() , 0.05, 0.15 ,0.25,6,6);
	glPopMatrix();
}

void Helicopter::skids(){	
	glColor3d(0.8, 0.8, 1.0);
	// Skid legs - front
	glPushMatrix();
		glTranslated(0.8,-0.45,-0.75);
		gluCylinder(gluNewQuadric(),0.03, 0.03 ,0.25,10,10);
	glPopMatrix();

	glPushMatrix();
		glTranslated(0.8,0.45,-0.75);
		gluCylinder(gluNewQuadric(),0.03,0.03,0.25,10,10);
	glPopMatrix();

	// Skid legs - back
	glPushMatrix();
		glTranslated(-0.4,-0.45,-0.75);
		gluCylinder(gluNewQuadric(),0.03,0.03,0.25,10,10);
	glPopMatrix();

	glPushMatrix();
		glTranslated(-0.4,0.45,-0.75);
		gluCylinder(gluNewQuadric(),0.03,0.03,0.25,10,10);
	glPopMatrix();

	// Bottom of skids
	glPushMatrix();
		glRotated(90, 0, 1, 0);
		glTranslated(0.75,-0.45,-0.75);
		gluCylinder(gluNewQuadric(),0.03,0.03,2.0,10,10);
	glPopMatrix();

	glPushMatrix();
		glRotated(90, 0, 1, 0);
		glTranslated(0.75,0.45,-0.75);
		gluCylinder(gluNewQuadric(),0.03,0.03,2.0,10,10);
	glPopMatrix();	
}

void Helicopter::DesenhaCubo(){
	glBegin ( GL_QUADS );
		// Front Face
		glNormal3f(0,0,1);
		glVertex3f(-1.0f, -1.0f,  1.0f);
		glVertex3f( 1.0f, -1.0f,  1.0f);
		glVertex3f( 1.0f,  1.0f,  1.0f);
		glVertex3f(-1.0f,  1.0f,  1.0f);
		// Back Face
		glNormal3f(0,0,-1);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f,  1.0f, -1.0f);
		glVertex3f( 1.0f,  1.0f, -1.0f);
		glVertex3f( 1.0f, -1.0f, -1.0f);
		// Top Face
		glNormal3f(0,1,0);
		glVertex3f(-1.0f,  1.0f, -1.0f);
		glVertex3f(-1.0f,  1.0f,  1.0f);
		glVertex3f( 1.0f,  1.0f,  1.0f);
		glVertex3f( 1.0f,  1.0f, -1.0f);
		// Bottom Face
		glNormal3f(0,-1,0);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f( 1.0f, -1.0f, -1.0f);
		glVertex3f( 1.0f, -1.0f,  1.0f);
		glVertex3f(-1.0f, -1.0f,  1.0f);
		// Right face
		glNormal3f(1,0,0);
		glVertex3f( 1.0f, -1.0f, -1.0f);
		glVertex3f( 1.0f,  1.0f, -1.0f);
		glVertex3f( 1.0f,  1.0f,  1.0f);
		glVertex3f( 1.0f, -1.0f,  1.0f);
		// Left Face
		glNormal3f(-1,0,0);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f,  1.0f);
		glVertex3f(-1.0f,  1.0f,  1.0f);
		glVertex3f(-1.0f,  1.0f, -1.0f);
	glEnd();
}

// Drawing the transparent object/s
void Helicopter::transparentObj(){	
	glPushMatrix();	
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	
	// Windscreen
	glColor4d(0.1, 0.1, 0.1, 0.85);
	glBegin(GL_POLYGON);		
		glVertex3d(1.2, -0.5, 0.0);
		glVertex3d(1.2, 0.5, 0.0);
		glVertex3f(0.8f, 0.5f, 0.4f);
		glVertex3f(0.8f, -0.5f, 0.4f);
	glEnd(); 

	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);
	glPopMatrix();
}

//Draw helicopter - Main body
void Helicopter::mainBody(){	

	if(id=="Jogador") glColor3f(0.07, 0.1, 0.07);
	else glColor3f(0.5 , 0.07, 0.07);
	// Main body torso
	glPushMatrix();	
	glutSolidCube(1);
	glPopMatrix();
	//The tail section
	glPushMatrix();
	// Positive y side
	glBegin(GL_POLYGON);		
		glVertex3f(-3.0f, 0.05f, -0.3f);
		glVertex3f(-3.0f, 0.05f, -0.1f);
		glVertex3f(-1.25f, 0.2f, -0.1f);
		glVertex3d(-1.25, 0.2, -0.4);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3d(-1.25, 0.2, -0.4);
		glVertex3f(-1.25f, 0.2f, -0.1f);
		glVertex3f(-0.5, 0.5, 0.5);
		glVertex3f(-0.5, 0.5, -0.5);
	glEnd();
	glBegin(GL_POLYGON);		
		glVertex3f(-3.0f, 0.05f, -0.3f);
		glVertex3f(-3.25f, 0.05f, -0.3f);
		glVertex3f(-3.5f, 0.05f, 0.2f);
		glVertex3f(-3.25f, 0.05f, 0.2f);
		glVertex3f(-3.0f, 0.05f, -0.1f);
	glEnd();
	// Negative y side
	glBegin(GL_POLYGON);
		glVertex3f(-0.5, -0.5, -0.5);
		glVertex3f(-0.5, -0.5, 0.5);
		glVertex3f(-1.25f, -0.2f, -0.1f);
		glVertex3d(-1.25, -0.2, -0.4);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3f(-3.0f, -0.05f, -0.1f);
		glVertex3f(-3.0f, -0.05f, -0.3f);
		glVertex3d(-1.25, -0.2, -0.4);
		glVertex3f(-1.25f, -0.2f, -0.1f);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3f(-3.0f, -0.05f, -0.1f);
		glVertex3f(-3.25f, -0.05f, 0.2f);
		glVertex3f(-3.5f, -0.05f, 0.2f);
		glVertex3f(-3.25f, -0.05f, -0.3f);
		glVertex3f(-3.0f, -0.05f, -0.3f);
	glEnd();
	// Top
	glBegin(GL_POLYGON);		
		glVertex3f(-1.25f, 0.2f, -0.1f);
		glVertex3f(-1.25f, -0.2f, -0.1f);
		glVertex3f(-0.5, -0.5, 0.5);
		glVertex3f(-0.5, 0.5, 0.5);
	glEnd();
	glBegin(GL_POLYGON);		
		glVertex3f(-1.25f, 0.2f, -0.1f);
		glVertex3f(-3.0f, 0.05f, -0.1f);
		glVertex3f(-3.0f, -0.05f, -0.1f);
		glVertex3f(-1.25f, -0.2f, -0.1f);
	glEnd();
	glBegin(GL_POLYGON);		
		glVertex3f(-3.0f, 0.05f, -0.1f);
		glVertex3f(-3.25f, 0.05f, 0.2f);
		glVertex3f(-3.25f, -0.05f, 0.2f);
		glVertex3f(-3.0f, -0.05f, -0.1f);
	glEnd();
	glBegin(GL_POLYGON);		
		glVertex3f(-3.25f, 0.05f, 0.2f);
		glVertex3f(-3.5f, 0.05f, 0.2f);
		glVertex3f(-3.5f, -0.05f, 0.2f);
		glVertex3f(-3.25f, -0.05f, 0.2f);
	glEnd();
	// Bottom
	glBegin(GL_POLYGON);
		glVertex3f(-0.5, 0.5, -0.5);
		glVertex3f(-0.5, -0.5, -0.5);
		glVertex3d(-1.25, -0.2, -0.4);
		glVertex3d(-1.25, 0.2, -0.4);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3d(-1.25, 0.2, -0.4);
		glVertex3d(-1.25, -0.2, -0.4);
		glVertex3f(-3.0f, -0.05f, -0.3f);
		glVertex3f(-3.0f, 0.05f, -0.3f);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3f(-3.0f, -0.05f, -0.3f);
		glVertex3f(-3.25f, -0.05f, -0.3f);
		glVertex3f(-3.25f, 0.05f, -0.3f);
		glVertex3f(-3.0f, 0.05f, -0.3f);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3f(-3.25f, -0.05f, -0.3f);
		glVertex3d(-3.5, -0.05, 0.2);
		glVertex3f(-3.5f, 0.05f, 0.2f);
		glVertex3f(-3.25f, 0.05f, -0.3f);
	glEnd();
	glPopMatrix();	
}

void Helicopter::seat(){
	glColor3f(1.0, 1.0, 0.0);
	// Seat 1 bottom
	glPushMatrix();
	glTranslated(0.75, 0.25, -0.25);
	glScaled(1.85, 0.75, 0.25);
	glutSolidCube(0.5);
	glPopMatrix();
	// Seat 1 back 
	glPushMatrix();
	glTranslated(0.6, 0.25, 0);
	glScaled(0.25, 0.75, 0.8);
	glutSolidCube(0.5);
	glPopMatrix();
	// Seat 2 bottom
	glPushMatrix();
	glTranslated(0.75, -0.25, -0.25);
	glScaled(0.85, 0.75, 0.25);
	glutSolidCube(0.5);
	glPopMatrix();
	// Seat 2 back 
	glPushMatrix();
	glTranslated(0.6, -0.25, 0);
	glScaled(0.25, 0.75, 0.8);
	glutSolidCube(0.5);
	glPopMatrix();
	// Joystick
	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslated(1.1, -0.25, -0.5);
	glRotated(ang2Helicoptero,0,1,0);
	glRotated(ang3Helicoptero*1.5,1,0,0);

	gluCylinder(gluNewQuadric(),0.02,0.02,0.35,10,10);
	glTranslated(0, 0, 0.35);
	glScaled(0.1, 0.1, 0.2);
	glutSolidSphere(0.5, 10, 10);
	glPopMatrix();
}	

void Helicopter::Transitorio(){

		//if(id=="Inimigo") printf("Nivel: %d\n",Nivel );
      ( (float)Nivel*((float)altura/5.0) + 0.75*scale > yHelic && subindo) ? yHelic+=0.1 : subindo = 0;
      ( (float)Nivel*((float)altura/5.0) + 0.75*scale < yHelic && descendo  ) ? yHelic-=0.1 : descendo = 0;
		    
      if(mov==0 && ang2Helicoptero!=0){
	      if (ang2Helicoptero>0) ang2Helicoptero-=0.2;
	      if (ang2Helicoptero<0) ang2Helicoptero+=0.2;				
      }
      else if(mov==1)  (ang2Helicoptero< 10.0) ? ang2Helicoptero+=0.1 : ang2Helicoptero+=0;
      else if(mov==-1) (ang2Helicoptero>-10.0) ? ang2Helicoptero-=0.2 : ang2Helicoptero+=0;

	if (movL == 0 && movR == 0 && ang3Helicoptero!=0){
		if(ang3Helicoptero>0) ang3Helicoptero-=0.2;
		if(ang3Helicoptero<0) ang3Helicoptero+=0.2;
	}
	else if(movR==1) (ang3Helicoptero < 16) ? ang3Helicoptero+=0.4 : ang3Helicoptero+=0;
	else if(movL==1) (ang3Helicoptero > -16) ? ang3Helicoptero-=0.4 : ang3Helicoptero-=0;
	
	( mov || movR || movR && velHelice2  < 1.5*velHelice ) ? velHelice2 += velHelice/20 : velHelice2+=0 ;
	if(mov == 0 && velHelice2 > velHelice ){
		velHelice2 -= velHelice/10;
	}

 
}

float Helicopter::getXBullet(GLfloat modelMatrix[16]){
	float newx = 0;
	newx = xHelic * modelMatrix[0] + yHelic * modelMatrix[4] + zHelic * modelMatrix[8] + 1 * modelMatrix[12];
	return newx;
}

float Helicopter::getYBullet(GLfloat modelMatrix[16]){
	float newy = 0;
	newy = xHelic * modelMatrix[1] + yHelic * modelMatrix[5] + zHelic * modelMatrix[9] + 1 * modelMatrix[13];
	return newy;
}


float Helicopter::getZBullet(GLfloat modelMatrix[16]){
	float newz = 0;
	newz = xHelic * modelMatrix[2] + yHelic * modelMatrix[6] + zHelic * modelMatrix[10] + 1 * modelMatrix[14];
	return newz;
}



void Helicopter::Desenha(){			
			Transitorio();
			DesenhaTiros();
			ballsCord();

			if(esferas){
				//esefera da cabine
				glPushMatrix();
					glTranslatef(xe1,ye1,ze1);
					glColor3f(1,0,1);
					glutWireSphere(r1,8,8);
				glPopMatrix();

				//esfera do meio
				glPushMatrix();
					glTranslatef(xe2,ye2,ze2);
					glColor3f(1,0,1);
					glutWireSphere(r2,8,8);
				glPopMatrix();

				//esfera do fim da cauda
				glPushMatrix();
					glTranslatef(xe3,ye3,ze3);
					glColor3f(1,0,1);
					glutWireSphere(r3,8,8);
				glPopMatrix();
			}

			glPushMatrix();	
				glTranslatef(xHelic,yHelic,zHelic);

				glRotatef(-90,1,0,0);
				glScalef(scale,scale,scale);
				glRotatef(angHelicoptero,0,0,1);
				glRotatef(ang2Helicoptero,0,1,0);
				glRotatef(ang3Helicoptero,1,0,0);
				    mainBody();						
					rotor();		
					skids();			
					seat();
					bag();
					suport();
					cabin();
					transparentObj();
				glPushMatrix();
					glTranslatef(1.59, -0.8, -0.4);
					glRotatef(angGunXZ,0,0,1);
					glRotatef(angGunXZ2,0,1,0);
					gun1();
					glTranslatef(0.25 , 0 , 0 );
				glPopMatrix();
				glPushMatrix();
					glTranslatef(1.59, 0.8, -0.4);
					glRotatef(angGunXZ,0,0,1);
					glRotatef(angGunXZ2,0,1,0);
					gun1();
					glTranslatef(0.25 , 0 , 0 );	
				glPopMatrix();
			glPopMatrix();		
	angHelice+=velHelice;
	if(angHelice>=360) angHelice-=360;
	else if(angHelice<0) angHelice+=360;

	angHelice2+=velHelice2;
	if(angHelice2>=360) angHelice2-=360;
	else if(angHelice2<0) angHelice2+=360;

	angGunXZinc(-deslocamento1*0.2); 
	angGunXZ2inc(deslocamento2*0.2);
	deslocamento1 = 0;
	deslocamento2 = 0; 

	if( yHelic > 0.75*scale ) pousado = 0;
	else pousado = 1;			

}



void Helicopter::ballsCord(){
	xe1 = xHelic;
	ye1 = yHelic;
	ze1 = zHelic;

	xe2 = xHelic - 2.0*cos( angHelicoptero*M_PI/180 )*scale;
	ye2 = yHelic + 2.0*sin( ang2Helicoptero*M_PI/180 )*scale;
	ze2 = zHelic + 2.0*sin( angHelicoptero*M_PI/180 )*scale;

	xe3 = xHelic - 3.3*cos( angHelicoptero*M_PI/180 )*scale;
	ye3 = yHelic + 3.3*sin( ang2Helicoptero*M_PI/180 )*scale;
	ze3 = zHelic + 3.3*sin( angHelicoptero*M_PI/180 )*scale ;
}

void Helicopter::movHelic(float inc){

	//printf("inc speed: %.1f \n",inc);

	if( yHelic <= 0.75*scale || morto) return;


	xHelic += inc*cos( (3.1416*angHelicoptero)/180 );
	if(xHelic <= r1) xHelic = r1;
	if(xHelic >= w - r1 ) xHelic = w - r1;
	zHelic += -inc*sin( (3.1416*angHelicoptero)/180 );
	if(zHelic<=r1) zHelic = r1;
	if(zHelic >= h - r1) zHelic = h - r1;


	if(!wallColision()){
		frontCord();
		ballsCord();
	}
	
}

void Helicopter::rodaHelic(float inc){

	angHelicoptero+=inc;
	if(angHelicoptero>=360) angHelicoptero-=360;
	else if(angHelicoptero<0) angHelicoptero+=360;



	wallColision();
	frontCord();
	ballsCord();

}

void Helicopter::frontCord(){
	xFrente = xHelic +  1.4*radius*0.1*cos(angHelicoptero*3.14/180);
	yFrente = yHelic;
	zFrente = zHelic - 1.4*radius*0.1*sin(angHelicoptero*3.14/180);
}

void Helicopter::angGunXZinc(float inc){
	angGunXZ +=inc;
	if(angGunXZ>45) angGunXZ = 45;
	else if(angGunXZ<-45) angGunXZ = -45;
}

void Helicopter::angGunXZ2inc(float inc){
	angGunXZ2 +=inc;
	if(angGunXZ2>45) angGunXZ2 = 45;
	else if(angGunXZ2<-45) angGunXZ2 = -45;
}

void Helicopter::PosicUser(int cam, float angCam, float ratio){

	// Set the clipping volume
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angCam,ratio,0.01,2000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if(cam!=3){
		ang1Cam = 180;
		ang2Cam = 90;
		ang1CamAux = ang1Cam;
		ang2CamAux = ang2Cam;
	}

	// CAMERA ATRAS DO HELICOPTERO OLHANDO PARA FRENTE COM ELE
	if(cam == 6){
	gluLookAt( xHelic -  distCamera3pessoa*cos( angHelicoptero*3.14/180),  yHelic + distCamera3pessoa*0.5,  zHelic +  distCamera3pessoa*sin( angHelicoptero*3.14/180) ,
		        xHelic ,  yHelic,  zHelic,
			  0.0f,1.0f,0.0f);
	}

	// CAMERA PERSPECTIVA ENVOLTA DO HELICOPTERO
	else if(cam == 3 ){

		//printf("nivel: %d | ang2: %.0f | ",Nivel ,ang2Cam );
	(Nivel==4 && ang2CamAux>20) ?  ang2CamAux-=10 : ang2CamAux-=0;
	(Nivel != 4 ) ?  ang2CamAux = ang2Cam : ang2CamAux+=0;
	

	gluLookAt(  xHelic + distCamera3pessoa*cos( (ang1Cam - angHelicoptero )*M_PI/180)  ,  yHelic + distCamera3pessoa*0.5*sin( ang2CamAux*M_PI/180 ),  zHelic + distCamera3pessoa*sin((ang1Cam - angHelicoptero)*M_PI/180)  ,
		        xHelic ,  yHelic ,  zHelic ,
			  0.0f,1.0f,0.0f);
	}

	// CAMERA NO CENTRO DO MAPA 2
	else if(cam == 7){
	gluLookAt( w/2 , altura , 0 ,
		        xHelic ,  yHelic ,  zHelic,
			  0.0f,1.0f,0.0f);
	}
	// CAMERA NO CENTRO DO MAPA
	else if(cam == 8){
	gluLookAt( w/2 , altura , h/2 ,
		        xHelic ,  yHelic ,  zHelic,
			  0.0f,1.0f,0.0f);
	}

	// CAMERA PERSPECTIVA NO HELICOPTERO
	else if(cam == 1){
	gluLookAt(  xHelic ,  yHelic +  distCamera3pessoa*0.1 ,  zHelic -  distCamera3pessoa,
		        xHelic ,  yHelic  ,  zHelic,
			  0.0f,1.0f,0.0f);
	}

	// CAMERA DE DENTRO DA CABINE
	if(cam == 4){
	gluLookAt(
		        xHelic + (0.6* radius/10)*cos( angHelicoptero*3.14/180) ,  yHelic + (0.25* radius/10)*cos( ang2Helicoptero*M_PI/180 )  ,  zHelic - (0.6* radius/10)*sin( angHelicoptero*3.14/180),
		        xHelic +  distCamera3pessoa*cos( angHelicoptero*3.14/180),  yHelic -distCamera3pessoa*sin( ang2Helicoptero*M_PI/180 ) ,  zHelic  -  distCamera3pessoa*sin( angHelicoptero*3.14/180) ,
			  0.0f,1.0f,0.0f);
	}

	//CAMERA NA ARMA
	else if(cam == 2){
	gluLookAt(  xHelic +  distCamera3pessoa*0.2*cos( angHelicoptero*3.14/180),  yHelic + distCamera3pessoa*0.1 - 0.4*distCamera3pessoa*sin( ang2Helicoptero*M_PI/180 ),  zHelic -  distCamera3pessoa*0.2*sin( angHelicoptero*3.14/180) ,
		         xHelic +  distCamera3pessoa*cos( (angHelicoptero + angGunXZ )*3.14/180),  yHelic - 1.4*distCamera3pessoa*sin( ang2Helicoptero*M_PI/180 ) ,  zHelic  -  distCamera3pessoa*sin( (angHelicoptero + angGunXZ )*3.14/180) ,
			  0.0f,1.0f,0.0f);
	}


	//CAMERA QUE SEGUE O TIRO
	else if(cam == 5){
		if(Tiros.size()>0 && !Tiros[0].out)
	gluLookAt(  Tiros[0].x1 -  scale*cos( angHelicoptero*3.14/180),  Tiros[0].y1 + scale,  Tiros[0].z1 +  scale*sin( angHelicoptero*3.14/180) ,
		         Tiros[0].x1 +  scale*cos( angHelicoptero*3.14/180),  Tiros[0].y1,  Tiros[0].z1  -  scale*sin( angHelicoptero*3.14/180) ,
			  0.0f,1.0f,0.0f);
		else {
		cam = 2;
		gluLookAt(  xHelic +  distCamera3pessoa*0.2*cos( angHelicoptero*3.14/180),  yHelic + distCamera3pessoa*0.1 - 0.4*distCamera3pessoa*sin( ang2Helicoptero*M_PI/180 ),  zHelic -  distCamera3pessoa*0.2*sin( angHelicoptero*3.14/180) ,
		         xHelic +  distCamera3pessoa*cos( (angHelicoptero + angGunXZ )*3.14/180),  yHelic - 1.4*distCamera3pessoa*sin( ang2Helicoptero*M_PI/180 ) ,  zHelic  -  distCamera3pessoa*sin( (angHelicoptero + angGunXZ )*3.14/180) ,
			  0.0f,1.0f,0.0f);
		}
	}

	
}

void Helicopter::upNivel(){
	if(Nivel<4){
		subindo = 1;
		descendo = 0;
		Nivel++;
	}
	if(yHelic>0.75*scale) pousado = 0;
}

void Helicopter::downNivel(){
	if(Nivel>0){
	subindo = 0;
	descendo = 1;
	Nivel--;
	}
	if(yHelic<=0.75*scale){
		pousado = 1;
		yHelic = 0.75*scale;
	}
}

void Helicopter::Pousar(){
	if(Nivel>0){
	subindo = 0;
	descendo = 1;
	Nivel = 0;
	}	
}


void Helicopter::updateHelicopter( GLdouble timeDiff ){

    float speed =   velHelic * timeDiff; //Correct speed of movement with the time difference between calls
 	float x,y;
	//Treat keyPress	
	if(keyStatus[(int)('w')])
	{
		  movHelic(speed);
		  mov = 1;
	}
	else   mov = 0;
	if(keyStatus[(int)('s')])
	{
		  movHelic(-0.6*speed);
		  mov = -1;
	}

	if(keyStatus[(int)('d')])
	{
		  rodaHelic(-0.5);
		if(  mov ||   mov == -1)   movR = 1;
	}
	else   movR = 0;
	if(keyStatus[(int)('a')])
	{
		  rodaHelic(0.5);
		if(  mov ||   mov == -1)   movL = 1;
	}
	else   movL = 0;
}

void Helicopter::keyup(unsigned char key, int x, int y){
    keyStatus[(int)(key)] = 0;
    glutPostRedisplay();
}

void Helicopter::ResetKeyStatus(){
    int i;
    //Initialize keyStatus
    for(i = 0; i < 256; i++)
       keyStatus[i] = 0; 
}
 void Helicopter::CriaTiro(){
 	Tiro *T = new Tiro( xHelic,yHelic,zHelic, angHelicoptero, ang2Helicoptero, ang3Helicoptero,angGunXZ, angGunXZ2, scale  );
 	Tiros.insert(Tiros.begin(),*T);
 	//printf("ang2: %.0f\n",ang2Helicoptero );
 }
 void Helicopter::IncrementaTiros(float speed)
{
	for(int i =0; i< Tiros.size(); i++ )
	{
		if( !Tiros[i].out ){
			Tiros[i].incrementa_tiro(speed);
			if(Tiros[i].x1 > w  || Tiros[i].z1 > h || Tiros[i].y1 > altura){
				Tiros[i].out = 1;
				Tiros[i].cx = 100*w;
				Tiros[i].cy = 100*altura;
				Tiros[i].cz = 100*h;
			}

			if(Tiros[i].x1 < 0  || Tiros[i].z1 < 0 || Tiros[i].y1 < 0){
				Tiros[i].out = 1;
				Tiros[i].cx = 100*w;
				Tiros[i].cy = 100*altura;
				Tiros[i].cz = 100*h;
			}
		}
	}

}

void Helicopter::DesenhaTiros()
{

	//for (vector<Tiro>::iterator it2 = Tiros.begin() ; it2 != Tiros.end(); ++it2)
	for (int i = 0; i< Tiros.size() ; i++)
	{
		if(!Tiros[i].out) Tiros[i].DesenhaTiro();			
  	}
	
}

float Helicopter::pointDistance(float x, float y, float X, float Y, float z, float Z)
{
	float d = sqrt(pow(X-x,2)+pow(Y-y,2)+pow(Z-z,2));
	return d;
}


int Helicopter::verifColisao(float xa, float ya, float za, float Ta ,float xb, float yb, float zb, float Tb)
{
	float d = pointDistance(xa,  ya,  xb, yb , za , zb );
	if( d < (Ta+Tb) ) return 1;
	else return 0;
}

bool Helicopter::wallColision(){

	int a = 0;
		// esfera da cabine
	a = verifColisao( xe1, ye1, ze1, r1 , xe1,  ye1, 0 , 0 ); //bater na parede dos fundos
	if(a) return 1;
	a = verifColisao( xe1, ye1, ze1, r1 , xe1,  ye1, h , 0 ); //bater na parede da frente
	if(a) return 1;
	a = verifColisao( xe1, ye1, ze1, r1 , 0 ,  ye1, ze1 , 0 ); //bater na parede da direita
	if(a) return 1;
	a = verifColisao( xe1, ye1, ze1, r1 , w ,  ye1, ze1 , 0 ); //bater na parede da esquerda
	if(a) return 1;

		// esfera da trazeira
	a = verifColisao( xe3, ye3, ze3, r3 , xe3,  ye3, 0 , 0 ); //bater na parede dos fundos
	if(a) return 1;
	a = verifColisao( xe3, ye3, ze3, r3 , xe3,  ye3, h , 0 ); //bater na parede da frente
	if(a) return 1;
	a = verifColisao( xe3, ye3, ze3, r3 , 0 ,  ye3, ze3 , 0 ); //bater na parede da direita
	if(a) return 1;
	a = verifColisao( xe3, ye3, ze3, r3 , w ,  ye3, ze3 , 0 ); //bater na parede da esquerda
	if(a) return 1;

	
	
		return 0;
	
	
}

bool Helicopter::helicopterColision(float XE1, float YE1, float ZE1, float R1, 
									float XE2, float YE2, float ZE2, float R2, 
									float XE3, float YE3, float ZE3, float R3 ){

		int a = 0;

		a = verifColisao( xe1, ye1, ze1, 1.5*r1 , XE1,  YE1, ZE1 , R1 );
		if(a) {
			//esfera 1 com esfera 1
			movHelic(-scale/8.0);
			if(ye1 == YE1 ){
				if( Nivel < 4 ) upNivel();
				else if( Nivel > 1 ) downNivel();
			}
			else rodaHelic((rand()%3 - 1)/2.0);
			return 1;
			
		}
		a = verifColisao( xe1, ye1, ze1, 1.5*r1 , XE2,  YE2, ZE2 , R2 );
		if(a) {
			//esfera 1 com esfera 2
			movHelic(-scale/8.0);
			if(ye1 == YE1 ){
				if( Nivel < 4 ) upNivel();
				else if( Nivel > 1 ) downNivel();
			}
			else rodaHelic(-0.5);
			return 1;
		}
		a = verifColisao( xe1, ye1, ze1, 1.5*r1 , XE3,  YE3, ZE3 , R3 );
		if(a) {
			//esfera 1 com esfera 3
			movHelic(-scale/8.0);
			if(ye1 == YE1 ){
				if( Nivel < 4 ) upNivel();
				else if( Nivel > 1 ) downNivel();
			}
			else rodaHelic(0.5);
			return 1;
		}

		a = verifColisao( xe2, ye2, ze2, 1.5*r2 , XE1,  YE1, ZE1 , R1 );
		if(a) {
			//esfera 2 com esfera 1
			if(ye1 == YE1 ){
				if( Nivel < 4 ) upNivel();
				else if( Nivel > 1 ) downNivel();
			}
			return 1;
		}
		a = verifColisao( xe2, ye2, ze2, 1.5*r2 , XE2,  YE2, ZE2 , R2 );
		if(a) {
			//esfera 2 com esfera 2
			if(ye1 == YE1 ){
				if( Nivel < 4 ) upNivel();
				else if( Nivel > 1 ) downNivel();
			}
			return 1;
		}
		a = verifColisao( xe2, ye2, ze2, 1.5*r2 , XE3,  YE3, ZE3 , R3 );
		if(a) {
			//esfera 2 com esfera 3
			if(ye1 == YE1 ){
				if( Nivel < 4 ) upNivel();
				else if( Nivel > 1 ) downNivel();
			}
			return 1;
		}

		a = verifColisao( xe3, ye3, ze3, 1.5*r3 , XE1,  YE1, ZE1 , R1 );
		if(a) {
			//esfera 3 com esfera 1
			movHelic(scale/8.0);
			if(ye1 == YE1 ){
				if( Nivel < 4 ) upNivel();
				else if( Nivel > 1 ) downNivel();
			}
			
			return 1;
		}
		a = verifColisao( xe3, ye3, ze3, 1.5*r3 , XE2,  YE2, ZE2 , R2 );
		if(a) {
			//esfera 3 com esfera 2
			movHelic(scale/8.0);
			if(ye1 == YE1 ){
				if( Nivel < 4 ) upNivel();
				else if( Nivel > 1 ) downNivel();
			}
			
			return 1;
		}
		a = verifColisao( xe3, ye3, ze3, 1.5*r3 , XE3,  YE3, ZE3 , R3 );
		if(a) {
			//esfera 3 com esfera 3
			movHelic(scale/8.0);
			if(ye1 == YE1 ){
				if( Nivel < 4 ) upNivel();
				else if( Nivel > 1 ) downNivel();
			}
			
			return 1;
		}

		
	
			return 0;	
}




void Helicopter::esferasON_OFF(){
	if(esferas) esferas=0;
	else esferas = 1;
}

bool Helicopter::shotColision(float x, float y, float z, float raio){
	int a = 0;
	a =  verifColisao( xe1, ye1, ze1, r1, x, y, z, raio );
	if(a) return 1;
	a = verifColisao( xe2, ye2, ze2, r2, x, y, z, raio );
	if(a) return 1;
	a = verifColisao( xe3, ye3, ze3, r3, x, y, z, raio );
	if(a) return 1;

	return 0 ;
}

void Helicopter::incAng1Cam(float inc){
	ang1Cam += inc;
	//printf("%.0f\n",ang1Cam );
	if(ang1Cam>270) ang1Cam = 270;
	if(ang1Cam<90) ang1Cam = 90;
}

void Helicopter::incAng2Cam(float inc){
	ang2Cam += inc;
	//printf("%.0f\n",ang2Cam );
	if(ang2Cam>90) ang2Cam = 90;
	if(ang2Cam<0) ang2Cam = 0;
}

bool Helicopter::resgateColision(float x, float y, float z, float raio){
	int a = 0;
	a =  verifColisao( xe1, ye1, ze1, r1, x, y, z, raio );
	if(a) return 1;
	a = verifColisao( xe2, ye2, ze2, r2, x, y, z, raio );
	if(a) return 1;
	a = verifColisao( xe3, ye3, ze3, r3, x, y, z, raio );
	if(a) return 1;

	return 0 ;
}


void Helicopter::mirar(float x, float y, float z){

	float dx = x - xHelic ;
	float dy = y - yHelic ;
	float dz = z - zHelic ;

	float ang = atan( dz/dx );
	ang = ang*180/M_PI;
	
	if(ang<0) ang += 360;

	//printf("ang: %.1f\n",ang );
	if(x < xHelic){		
		ang += 180;
	}

	if( fabs(angHelicoptero - ang))
	angHelicoptero = ang;

	

}

void Helicopter::incrementeCombustivel(float inc)
{

	combustivel+=inc;
	if(combustivel>100) combustivel = 100;
	if(combustivel<0) combustivel = 0;
	if(combustivel==0) {morto = 1; printf("acabou o cobustivel!\n"); pousado = 1;}

}