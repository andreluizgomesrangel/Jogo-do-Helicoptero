#ifndef __CENARIO_H__
#define __CENARIO_H__

#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <vector>
#include "Helicopter.h"
#include "Quad.h"
#include "Circle.h"
#include "Cenario.h"
#include "biblioteca_tiny/tinyxml2.h"

using namespace tinyxml2;
using namespace std;

class Cenario
{
public:

	// imagem
	GLuint chao;

	// atributos de helicoptero
	float VELTIRO, VELHELICOPTERO1, VELHELICOPTERO2;
	int keyStatus[256];
	float FREQ_TIRO;
	float TempoDeVoo;

	bool radarON;
	bool gradeON;
	bool Luz1ON;
	bool Luz2ON;

	//atributos do cenario
	Helicopter *Jogador;
	vector<Helicopter> Inimigo;

	int objFilmado;

	int ViewingWidth;
	int ViewingHeight;
	float altura;
	
	float d1, d2;
	bool movCam;
	bool lines;


	int comecou;
	int pause;
	int VITORIA;
	int pontuacao;
	int total;

	vector<Circle> Circles;
	vector<Quad> Quads;

	int lights;

	Cenario();

	int readySVG(string filename);
	int readyXML(const char* filename);
	void define(char* svgFile);
	void DefineLuz(void);

	void defineView();

	void newCircle(int cx , int cy , int r, const char* fill ,  const char* id );

	void newQuad(int x, int y, int width, int height, const char* fill, const char* id );

	float pointDistance(float x, float y, float X, float Y, float z, float Z);
	
	void DefineHelicopters();

	void camHelicopter(int helicopter, int cam, float angCam, float ratio);

	void toggleObjFilmado();

	void filma(int cam, float angCam, float ratio);

	void drawHelicopters();

	void drawWorldPoints();

	void incrementaTodosTiros(float speed);

	int verifColisao(float xa, float ya, float za, float Ta ,float xb, float yb, float zb, float Tb);

	bool EnemyColision();

	void linesON_OFF();

	void DrawLines();

	void EsferasON_OFF();

	void shotEnemy();

	void desenhaCircQuads();

	void verifResgate();

	int gerarDirecaoInimigo();

	int gerarDirecaoAngInimigo();

	void gerarMovimento(int inim, float speed);

	int gerarUpInimigo();

	void gerarMovimentoTODOS(float speed);

	void IncrementaTirosTODOS(float speed);

	void shotJogador(int inim);

	void shotJogadorTODOS();

	void DisplayOnRadar(float x, float y, float z, float nivel, string id);

	void DisplayRadar();

	void barraDeCombustivel();

	void desenha(int cam, float angCam, float ratio);

	void helicopterColisionTODOS();

	bool InimigoColidir( int inim );

	bool JogadorColidir();

	bool verificaBase();

	bool verificaVitoria();

	void drawText(const char* text, int lenght, int x, int y);

	void texto(string text, int x, int y);
};

#endif

