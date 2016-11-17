#ifndef __CIRCLE_H__
#define __CIRCLE_H__

#include <iostream>
#include "Circle.h"

using namespace std;

class Circle
{
public:
	float cx, cy;
	float radius;
	string fill;
	string id;
	int condicao;


	Circle();
	Circle(float cx, float cy, float radius, string fill, string id);

	void Show_radius();
	void Show_center();
	void Show_id();
	void Show();
	void Build(int altura, int largura);

};

#endif

