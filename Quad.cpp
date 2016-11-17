#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "Quad.h"
using namespace std;


Quad::Quad(){}
Quad::Quad(int x, int z, int width, int height, string fill, string id)
{
	this->x = x;
	this->z = z;
	this->width = width;
	this->height = height;
	this->fill = fill;
	this->id = id;
}


void Quad::Show()
{
	printf("x %d, z %d, width %d, height %d ",x,z,width,height);
	cout<< " fill " << fill;
	cout<< " id " << id;
	//printf("\n");
	
}

void Quad::Build(int altura, int largura)
{
	glBegin(GL_POLYGON);
		glVertex3f(x         , 0.2, z );
		glVertex3f(x + width , 0.2, z );
		glVertex3f(x + width , 0.2, z + height);
		glVertex3f(x         , 0.2, z + height);
	glEnd();
}
