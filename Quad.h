#ifndef __QUAD_H__
#define __QUAD_H__

#include <iostream>
#include "Quad.h"

using namespace std;

class Quad
{
public:
	int x, y, z, width, height;
	string fill;
	string id;


	Quad();
	Quad(int x, int y, int width, int height, string fill, string id);

	
	void Show();
	void Build(int altura, int largura);

};

#endif

