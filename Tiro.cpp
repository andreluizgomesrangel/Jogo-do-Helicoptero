#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include "Tiro.h"
#include "Helicopter.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>

using namespace std;

Tiro::Tiro(float x, float y , float z, float ang1Helic, float ang2Helic, float ang3Helic, float ang1Arma, float ang2Arma, float Scale){
	cx = x;
	cy = y;
	cz = z;

	ang1Tiro = ang1Helic;
	ang2Tiro = ang2Helic;
	ang3Tiro = ang3Helic;

	ang4Tiro = ang1Arma;
	ang5Tiro = ang2Arma;

	scale = Scale;

	speed = 1;


	float a,b,c;
	a = 1.59;
	b = 0.8;
	c = 0.4;	
	float H = pow(pow( a, 2 ) + pow( b , 2 ) , 0.5);
	float ang = (180/M_PI)*atan(b/a);
	float ang2 = (180/M_PI)*atan(c/H);
	x1 = cx + H*scale*cos( ( ang1Tiro  - ang  )*M_PI/180)*cos( ang2Tiro*M_PI/180 )   +  0.25*cos( ang4Tiro*M_PI/180 );
	y1 = cy - c*scale - a*scale*sin( ang2Tiro*M_PI/180 ) + a*scale*sin( ang2Tiro*M_PI/180 )*tan( ang3Tiro*M_PI/180 ) + 0.25*sin( ang5Tiro*M_PI/180 );
	z1 = cz - H*scale*sin( ( ang1Tiro  - ang  )*M_PI/180) +  0.25*sin( ang4Tiro*M_PI/180 ); 

	x2 = cx + H*scale*cos( ( ang1Tiro  + ang  )*M_PI/180)*cos( ang2Tiro*M_PI/180 )   +  0.25*cos( ang4Tiro*M_PI/180 );
	y2 = cy - c*scale - a*scale*sin( ang2Tiro*M_PI/180 ) + a*scale*sin( ang2Tiro*M_PI/180 )*tan( ang3Tiro*M_PI/180 ) + 0.25*cos( ang5Tiro*M_PI/180 );
	z2 = cz - H*scale*sin( ( ang1Tiro  + ang  )*M_PI/180) +  0.25*sin( ang4Tiro*M_PI/180 ); 

}

void Tiro::incrementa_tiro(float speed)
{
		float H = pow(pow( cx, 2 ) + pow( cy , 2 ) , 0.5);

		cx += speed*cos( (ang1Tiro + ang4Tiro)*M_PI/180);
		cz += -speed*sin( (ang1Tiro + ang4Tiro)*M_PI/180);
		cy += -speed*sin( (ang2Tiro + ang5Tiro )*M_PI/180);
	
		x1 += speed*cos( (ang1Tiro + ang4Tiro)*M_PI/180);
		z1 += -speed*sin( (ang1Tiro + ang4Tiro)*M_PI/180);
		y1 += -speed*sin((ang2Tiro + ang5Tiro )*M_PI/180);

		x2 += speed*cos( (ang1Tiro + ang4Tiro)*M_PI/180);
		z2 += -speed*sin( (ang1Tiro + ang4Tiro)*M_PI/180);
		y2 += -speed*sin((ang2Tiro + ang5Tiro )*M_PI/180);



}

void Tiro::DesenhaTiro()
{


		//printf("( %.0f %.0f %.0f ) , ( %.0f %.0f %.0f )\n",x1,y1,z1,x2,y2,z2 );

		/*glPushMatrix();
		glColor3f(1,1,0);
		glTranslatef(x1,y1,z1);
		glScalef(scale*0.1,scale*0.1,scale*0.1);
		glutSolidSphere(1,10,10);
   		glPopMatrix();

   		glPushMatrix();
		glColor3f(1,1,0);
		glTranslatef(x2,y2,z2);
		glScalef(scale*0.1,scale*0.1,scale*0.1);
		glutSolidSphere(1,10,10);
   		glPopMatrix();*/

		glPushMatrix();
				glTranslatef(cx,cy,cz);
				glRotatef(-90,1,0,0);
				glScalef(scale,scale,scale);
				glRotatef(ang1Tiro,0,0,1);
				glRotatef(ang2Tiro,0,1,0);
				glRotatef(ang3Tiro,1,0,0);

			glPushMatrix();

					glTranslatef(1.59 , -0.8, -0.4);
					glRotatef(ang4Tiro,0,0,1);
					glRotatef(ang5Tiro,0,1,0);
					
					//glutSolidSphere(1,10,10);

					glColor3f(0.8, 0.8, 0); //right center bag
					glScalef(0.3,0.3,0.3);
					glPushMatrix();
						glRotated(90, 0, 1, 0);
						glRotatef(ang2Tiro,1,0,0);
						glTranslatef(0.0,-0.0,0.45);
						glScalef( 1 , 0.5 , 0.5 );
						gluCylinder(gluNewQuadric(),0.22,0.20,1.0,5,5);
					glPopMatrix();

					glColor3f(1, 1 , 0.0); //right back bag
					glPushMatrix();
						glRotated(90, 0, 1, 0);
						glRotatef(ang2Tiro,1,0,0);
						glTranslatef(0.0,-0.0,0.2);
						glScalef( 1 , 0.5 , 0.5 );
						gluCylinder(gluNewQuadric(),0.10,0.22,0.5,5,5);
					glPopMatrix();

					glColor3f(1, 1, 0.0); 
					glPushMatrix();  // right back gun
						glRotated(90, 0, 1, 0);
						glRotatef(ang2Tiro,1,0,0);
						glTranslatef(0.0,-0.0,0.79);
						glScalef( 1 , 0.5 , 0.5 );
						gluCylinder(gluNewQuadric(),0.2,0.1,0.9,5,5);

						glPopMatrix();

				glPopMatrix();

				glPushMatrix();

				
					glTranslatef(1.59 , 0.8, -0.4);
					glRotatef(ang4Tiro,0,0,1);
					glRotatef(ang5Tiro,0,1,0);
					//glutSolidSphere(1,10,10);

					
					glColor3f(0.8, 0.8, 0.0); //right center bag
					glScalef(0.3,0.3,0.3);
					glPushMatrix();
						glRotated(90, 0, 1, 0);
						glRotatef(ang2Tiro,1,0,0);
						glTranslatef(0.0,-0.0,0.45);
						glScalef( 1 , 0.5 , 0.5 );
						gluCylinder(gluNewQuadric(),0.22,0.20,1.0,5,5);
					glPopMatrix();

					glColor3f(1, 1, 0.0); //right back bag
					glPushMatrix();
						glRotated(90, 0, 1, 0);
						glRotatef(ang2Tiro,1,0,0);
						glTranslatef(0.0,-0.0,0.2);
						glScalef( 1 , 0.5 , 0.5 );
						gluCylinder(gluNewQuadric(),0.10,0.22,0.5,5,5);
					glPopMatrix();

					glColor3f(1, 1, 0.0); 
					glPushMatrix();  // right back gun
						glRotated(90, 0, 1, 0);
						glRotatef(ang2Tiro,1,0,0);
						glTranslatef(0.0,-0.0,0.79);
						glScalef( 1 , 0.5 , 0.5 );
						gluCylinder(gluNewQuadric(),0.2,0.1,0.9,5,5);
					glPopMatrix();

				glPopMatrix();

	glPopMatrix();

}


