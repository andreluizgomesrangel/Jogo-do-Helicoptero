#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include "Circle.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string>

using namespace std;

Circle::Circle(){}

Circle::Circle(float cx, float cy, float radius, string fill, string id)
{
	this->cx = cx;
	this->cy = cy;
	this->radius = radius;
	this->fill = fill;
	this->id = id;
	this->condicao = 0;
}

void Circle::Show_radius()
{
	printf("( raio: %.0f ",this->radius);
}
void Circle::Show_center()
{
	printf("( cx %.0f, cy %.0f )\n",this->cx,this->cy);
}

void Circle::Show_id()
{
	cout << this->id;
}

void Circle::Show()
{
	 Show_radius();
	Show_center();	
}

void Circle::Build(int altura, int largura)
{
    	if(this->fill=="white") glColor3f(1,1,1);
	if(this->fill=="green") glColor3f(0,1,0);
	if(this->fill=="red") glColor3f(1,0,0);
	if(this->fill=="blue") glColor3f(0,0,1);
	if(this->fill=="gray") glColor3f(0.5,0.5,0.5);
    	float rad = 2*3.1415;
	int r = this->radius; 
	glBegin(GL_POLYGON);
	for(float i = 0; i < rad ; i+=0.1) 
	{ 
		glVertex2f(this->cx + r*cos(i) - largura/2 , altura/2 - this->cy - r*sin(i));
	
	} 
	glEnd();
	
}
