#ifndef __TIRO_H__
#define __TIRO_H__

#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

using namespace std;

class Tiro
{
public:
	float cx, cy, cz;
	float ang1Tiro;
	float ang2Tiro;
	float ang3Tiro;

	float ang4Tiro;
	float ang5Tiro;

	float speed;

	bool out;	
	float scale;

	float x1,y1,z1, x2,y2,z2;

	Tiro(float x, float y , float z, float ang1Helic, float ang2Helic, float ang3Helic, float ang1Arma, float ang2Arma, float Scale);

	void incrementa_tiro(float speed);
	
	void DesenhaTiro();

};

#endif

