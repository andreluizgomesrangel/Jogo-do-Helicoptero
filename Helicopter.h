#ifndef __HELICOPTER_H__
#define __HELICOPTER_H__

#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <vector>
#include "Tiro.h"
#include "biblioteca_tiny/tinyxml2.h"


using namespace std;

class Helicopter{
public:

	float angHelice;
	float angHelice2;
	float velHelice;
	float velHelice2;
	float angHelicoptero;
	float ang2Helicoptero;
	float ang3Helicoptero;
	float xHelic;
	float yHelic;
	float zHelic;
	float velHelic;
	float angGunXZ;
	float angGunXZ2;


	int keyStatus[256];

	int Nivel;
	float distCamera3pessoa;
	float xFrente;
	float yFrente;
	float zFrente;
	float scale;

	//canhao
	float xArma1;
	float yArma1;
	float zArma1;
	float xArma2;
	float yArma2;
	float zArma2;
	float deslocamento1, deslocamento2;


	//cam
	float ang1Cam, ang2Cam;

	//transitorio
	int mov;
	int movR;
	int movL;
	int subindo;
	int descendo;
	float radius;
	string id;
	float ang1CamAux, ang2CamAux;
	
	//inimigo
	float distance;

	//cenario
	float w;
	float h;
	float altura;


	//colicao
	float xe1,ye1,ze1, r1;
	float xe2,ye2,ze2, r2;
	float xe3,ye3,ze3, r3;
	bool esferas;



	float largura_helic;
	float altura_helic;

	bool pousado;
	int morto;
	
	float combustivel;
	
	vector<Tiro> Tiros;
	float freqTiro;

	Helicopter(float x, float y, float vel, float r, float width, float hight, string ID);
	void transparentObj();
	void mainBody();
	void cabin();
	void seat();
	void rotor();
	void bag();
	void gun1();
	void gun2();
	void suport();
	void skids();

	void DesenhaCubo();
	void Transitorio();
	float getXBullet(GLfloat modelMatrix[16]);
	float getYBullet(GLfloat modelMatrix[16]);
	float getZBullet(GLfloat modelMatrix[16]);
	void Desenha();
	void ballsCord();
	void movHelic(float inc);
	void rodaHelic(float inc);

	void frontCord();
	void angGunXZinc(float inc);
	void angGunXZ2inc(float inc);

	void PosicUser(int cam, float angCam, float ratio);
	void upNivel();
	void downNivel();
	void Pousar();
	void updateHelicopter( GLdouble timeDiff );
	void keyup(unsigned char key, int x, int y);
	void ResetKeyStatus();

	void CriaTiro();
	void IncrementaTiros(float speed);
	void DesenhaTiros();

	float pointDistance(float x, float y, float X, float Y, float z, float Z);
	int verifColisao(float xa, float ya, float za, float Ta ,float xb, float yb, float zb, float Tb);
	bool wallColision();
	bool helicopterColision(float XE1, float YE1, float ZE1, float R1, 
									float XE2, float YE2, float ZE2, float R2, 
									float XE3, float YE3, float ZE3, float R3 );
	void esferasON_OFF();

	bool shotColision(float x, float y, float z, float raio);

	void incAng1Cam(float inc);

	void incAng2Cam(float inc);

	bool resgateColision(float x, float y, float z, float raio);

	void mirar(float x, float y, float z);

	void incrementeCombustivel(float inc);
};

#endif


