#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <vector>
#include "Circle.h"
#include "Quad.h"
#include "Cenario.h"
#include <time.h>
#include "biblioteca_tiny/tinyxml2.h"



using namespace tinyxml2;
using namespace std;


Cenario::Cenario()
{
	objFilmado = 0;
	lights = -1;
	d1 = 0;
	d2 = 0;
	movCam = 0;
	lines = 0;
	radarON = 1;
	gradeON = 0;
	Luz1ON = 1;
	Luz2ON = 1;

};


int Cenario::readySVG(string filename){
	XMLDocument xmlDoc;
	xmlDoc.LoadFile((filename).data());
	XMLNode *pRoot = xmlDoc.FirstChild();
	XMLElement *pRectElement = pRoot->FirstChildElement("rect");
	while(pRectElement!=NULL)
	{
		int x, y, width, height, strokewidth, stroke;
		pRectElement->QueryIntAttribute("x", &x);
		pRectElement->QueryIntAttribute("y", &y);
		pRectElement->QueryIntAttribute("width", & width);
		pRectElement->QueryIntAttribute("height", &height);
		const char* fill = pRectElement->Attribute( "fill" );
		pRectElement->QueryIntAttribute("stroke-width", &strokewidth);
		pRectElement->QueryIntAttribute("stroke", &stroke);
		const char* id = pRectElement->Attribute("id");

		  newQuad(x, y, width, height, fill, id);		
		
		pRectElement = pRectElement->NextSiblingElement("rect");
	}
	
	XMLElement *pCircleElement = pRoot->FirstChildElement("circle");
	while(pCircleElement!=NULL)
	{
		int cx, cy, r;
		pCircleElement->QueryIntAttribute("cx", &cx);
		pCircleElement->QueryIntAttribute("cy", &cy);
		pCircleElement->QueryIntAttribute("r", &r);
		const char* fill = pCircleElement->Attribute("fill");
		const char* id = pCircleElement->Attribute("id");
		  newCircle(cx,cy,r,fill,id);
		pCircleElement = pCircleElement->NextSiblingElement("circle");	
	}	
	  defineView();
	  DefineHelicopters();
}

int Cenario::readyXML(const char* filename){
	
	XMLDocument xmlDoc;
	xmlDoc.LoadFile(filename);

	XMLNode *pRoot = xmlDoc.FirstChild();

	XMLNode *parquivosDeEntradaElement = pRoot->FirstChildElement("arquivosDeEntrada");	

	XMLElement *parquivoDaArenaElement = parquivosDeEntradaElement->FirstChildElement("arquivoDaArena");
	
		string nome = parquivoDaArenaElement->Attribute( "nome" );
		string tipo = parquivoDaArenaElement->Attribute( "tipo" );
		string caminho = parquivoDaArenaElement->Attribute( "caminho" );

		string CAMINHO;
		CAMINHO += caminho + nome + "." + tipo;

	XMLElement *phelicopteroElement = pRoot->FirstChildElement("helicoptero");

		float velTiro, velHelicoptero;
		float tempoDeVoo;
		phelicopteroElement->QueryFloatAttribute("velTiro", &velTiro);
		phelicopteroElement->QueryFloatAttribute("velHelicoptero", &velHelicoptero);
		phelicopteroElement->QueryFloatAttribute("tempoDeVoo", &tempoDeVoo);		

		  VELTIRO = velTiro;
		  VELHELICOPTERO1 = velHelicoptero;	
		 // printf("velHelicoptero: %.2f\n", velHelicoptero);

		  TempoDeVoo = tempoDeVoo;

	XMLElement *phelicopteroInimigoElement = pRoot->FirstChildElement("helicopteroInimigo");
		
		float freqTiro, velHelicoptero2;
		phelicopteroInimigoElement->QueryFloatAttribute("freqTiro", &freqTiro);
		phelicopteroInimigoElement->QueryFloatAttribute("velHelicoptero", &velHelicoptero2);
		  VELHELICOPTERO2 = velHelicoptero2;
		 // printf("velHelicoptero2: %.2f\n", velHelicoptero2);
		  FREQ_TIRO = 1/freqTiro;
	readySVG(  CAMINHO );
}

void Cenario::define(char* svgFile){
	readyXML(strcat(svgFile,"config.xml"));
}


void Cenario::DefineLuz(void){
  // Define cores para um objeto dourado
  GLfloat LuzAmbiente[]   = {0.24725f, 0.1995f, 0.07f } ;
  GLfloat LuzDifusa[]   = {0.75164f, 0.60648f, 0.22648f, 1.0f };
  GLfloat LuzEspecular[] = {0.626281f, 0.555802f, 0.366065f, 1.0f };
  GLfloat Especularidade[] = {1.0f, 1.0f, 1.0f, 1.0f };
  GLfloat PosicaoLuz0[]  = { 3.0f, 3.0f, 0.0f, 1.0f  };

   // ****************  Fonte de Luz 0

	//glEnable ( GL_COLOR_MATERIAL );

   // Habilita o uso de iluminação

  if(Luz1ON)  glEnable(GL_LIGHTING);
  else glDisable( GL_LIGHTING );



	// Ativa o uso da luz ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LuzAmbiente);
	// Define os parametros da Luz número Zero
	glLightfv(GL_LIGHT0, GL_AMBIENT, LuzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LuzDifusa  );
	glLightfv(GL_LIGHT0, GL_SPECULAR, LuzEspecular  );
	glLightfv(GL_LIGHT0, GL_POSITION, PosicaoLuz0 );
	glEnable(GL_LIGHT0);



  // Ativa o "Color Tracking"
  glEnable(GL_COLOR_MATERIAL);

  // Define a reflectancia do material
  glMaterialfv(GL_FRONT,GL_SPECULAR, Especularidade);

  // Define a concentração do brilho.
  // Quanto maior o valor do Segundo parametro, mais
  // concentrado será o brilho. (Valores válidos: de 0 a 128)
 glMateriali(GL_FRONT,GL_SHININESS,90);


}


void Cenario::defineView()
{
	ViewingHeight = Quads[0].height;
	ViewingWidth = Quads[0].width;	
}


void Cenario::newQuad(int x, int y, int width, int height, const char* fill, const char* id )
{
	Quad* quad = new Quad(x, y, width, height, fill, id);	
	Quads.push_back(*quad);
}


void Cenario::newCircle(int cx , int cy , int r, const char* fill ,  const char* id )
{
	Circle* circle = new Circle(cx,cy,r,fill,id);
	Circles.push_back(*circle);
}

float Cenario::pointDistance(float x, float y, float X, float Y, float z, float Z)
{
	float d = sqrt(pow(X-x,2)+pow(Y-y,2)+pow(Z-z,2));
	return d;
}


void Cenario::DefineHelicopters(){

	vector<Helicopter> h3;	
	
	for (vector<Circle>::iterator it = Circles.begin() ; it != Circles.end(); ++it){
		if(it->id == "Jogador"){
			Jogador = new Helicopter(it->cx , it->cy, VELHELICOPTERO1, it->radius, ViewingWidth, ViewingHeight, it->id);
			//printf("velocidade : %.2f \n", VELHELICOPTERO1  );
			Jogador->combustivel = 100;
		}
		
		if(it->id == "Inimigo"){ 
		Helicopter *haux = new Helicopter(it->cx , it->cy, VELHELICOPTERO2, it->radius, ViewingWidth, ViewingHeight, it->id);
					//haux->yHelic = 0.75*haux->scale + haux->Nivel* 

					h3.push_back(*haux);
					//printf("velocidade : %.2f \n", VELHELICOPTERO2  );	
		}
		
	}

	Inimigo = h3;

	altura = 0.5 - (-0.75 );
	//printf("altura sem escala: %0f\n",altura);
	altura *= Jogador->scale;
	//printf("altura com escala: %0f\n",altura);
	altura = altura*(25/3) ;

	//altura*=5

	//printf("5 x altura com escala: %0f\n",altura);

	Jogador->altura = altura;

	for (int i = 0; i < Inimigo.size(); i++){
		Inimigo[i].altura = altura;
		Inimigo[i].distance = pointDistance( Inimigo[i].xHelic , Inimigo[i].yHelic , Jogador->xHelic , Jogador->yHelic , Inimigo[i].zHelic , Jogador->zHelic );
	}

}

void Cenario::camHelicopter(int helicopter, int cam, float angCam, float ratio){
	if(helicopter==0){
		Jogador->PosicUser(cam,angCam,ratio);
	}
	else {
		while( Inimigo[objFilmado - 1].morto  ){
			toggleObjFilmado();
		}
		if( objFilmado==0 && Jogador->morto ) cam = 8;
		Inimigo[helicopter - 1].PosicUser(cam,angCam,ratio);
	}
}

void Cenario::toggleObjFilmado(){
	if(objFilmado==Inimigo.size()) objFilmado = 0;
	else objFilmado++;
}

void Cenario::filma(int cam, float angCam, float ratio){
	camHelicopter(objFilmado,cam,angCam,ratio);
}

void Cenario::drawHelicopters(){

	for (int i = 0; i < Inimigo.size(); i++){
		if(!Inimigo[i].morto) Inimigo[i].Desenha();
	}
	if(!Jogador->morto) Jogador->Desenha();
}

void Cenario::drawWorldPoints(){

	if( gradeON ){
	    glBegin(GL_LINES);
	    glColor3f(0,1,1);
	    for(float i=0; i<=ViewingWidth; i+=50){
	    		glVertex3f(i,altura,0);
	    		glVertex3f(i,altura, ViewingWidth);
	    }
	     for(float i=0; i<=ViewingHeight; i+=50){
	    		glVertex3f(0,altura,i);
	    		glVertex3f( ViewingWidth ,altura, i);
	    }


	    for(float i=0; i<=ViewingWidth; i+=50){
	    		glVertex3f(i,0,0);
	    		glVertex3f(i,0, ViewingWidth);
	    }
	     for(float i=0; i<=ViewingHeight; i+=50){
	    		glVertex3f(0,0,i);
	    		glVertex3f( ViewingWidth ,0, i);
	    }
	}
    
    glEnd();

    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_POLYGON);
		glVertex3d(0.0,  -0.1, 0.0);
		glVertex3d(0.0,  -0.1, ViewingHeight);
		glVertex3f(ViewingWidth, -0.1, ViewingHeight);
		glVertex3f(ViewingWidth, -0.1, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
		glVertex3d(0.0,  altura + 0.1, 0.0);
		glVertex3d(0.0,  altura + 0.1, ViewingHeight);
		glVertex3f(ViewingWidth, altura + 0.1, ViewingHeight);
		glVertex3f(ViewingWidth, altura + 0.1, 0.0f);
	glEnd();

}
void Cenario::incrementaTodosTiros(float speed)
{
	Jogador->IncrementaTiros(speed);
	for (vector<Helicopter>::iterator it = Inimigo.begin() ; it != Inimigo.end(); ++it)
	it->IncrementaTiros(speed);
}

int Cenario::verifColisao(float xa, float ya, float za, float Ta ,float xb, float yb, float zb, float Tb)
{
	float d = pointDistance(xa,  ya,  xb, yb , za , zb );
	if( d < (Ta+Tb) ) return 1;
	else return 0;
}

//verifica a colisao do jogador com os inimigos
bool Cenario::EnemyColision(){
	for(int i = 0; i<Inimigo.size(); i++){
		if( !Inimigo[i].morto && !Jogador->morto)
		if( Inimigo[i].helicopterColision( 	Jogador->xe1, Jogador->ye1, Jogador->ze1, Jogador->r1, 
											Jogador->xe2, Jogador->ye2, Jogador->ze2, Jogador->r2,  
											Jogador->xe3, Jogador->ye3, Jogador->ze3, Jogador->r3  ) )
			return 1;
	}
	return 0;
}

void Cenario::EsferasON_OFF(){
	Jogador->esferasON_OFF();
	for(int i = 0; i<Inimigo.size(); i++){
		Inimigo[i].esferasON_OFF();
	}
}

void Cenario::linesON_OFF(){

	if(lines) lines=0;
	else lines=1;

}

void Cenario::DrawLines(){

	for(int i = 0; i<Inimigo.size() && lines && !Jogador->morto ; i++){
		if(!Inimigo[i].morto){
			glBegin(GL_LINES);
				glColor3f(1,0,0);
				glVertex3f(Inimigo[i].xHelic,Inimigo[i].yHelic,Inimigo[i].zHelic);
				glVertex3f(Jogador->xHelic,Jogador->yHelic,Jogador->zHelic);
			glEnd();
		}
	}
	for(int i = 0; i<Circles.size() && lines && !Jogador->morto ; i++){
		if(Circles[i].id=="ObjetoResgate" && !Circles[i].condicao){
			glBegin(GL_LINES);
				glColor3f(0,0,1);
				glVertex3f(Circles[i].cx,Jogador->scale/2 ,Circles[i].cy);
				glVertex3f(Jogador->xHelic,Jogador->yHelic,Jogador->zHelic);
			glEnd();
		}
	}
}

void Cenario::shotEnemy(){

	for(int i = 0; i<Inimigo.size(); i++){

		for(int j = 0; j<Jogador->Tiros.size() ; j++){

			if( !Jogador->Tiros[j].out ){

				bool a = Inimigo[i].shotColision( Jogador->Tiros[j].x1 , Jogador->Tiros[j].y1 , Jogador->Tiros[j].z1 , 0.1*Jogador->scale );
				if(a){
					Inimigo[i].morto = 1;
					Jogador->Tiros[j].out = 1;
					Jogador->Tiros[j].cx = 100*ViewingWidth;
					Jogador->Tiros[j].cy = 100*altura;
					Jogador->Tiros[j].cz = 100*ViewingHeight;
				}	
				else{
					bool b = Inimigo[i].shotColision( Jogador->Tiros[j].x2 , Jogador->Tiros[j].y2 , Jogador->Tiros[j].z2 , 0.1*Jogador->scale );
					if(b) {
						Inimigo[i].morto = 1;
						Jogador->Tiros[j].out = 1;
						Jogador->Tiros[j].cx = 100*ViewingWidth;
						Jogador->Tiros[j].cy = 100*altura;
						Jogador->Tiros[j].cz = 100*ViewingHeight;
					}
				}

			}

		}


	}
}


void Cenario::desenhaCircQuads()
{

	for (vector<Quad>::iterator it2 = Quads.begin() ; it2 != Quads.end(); ++it2){
		
		if(it2->id=="PostoAbastecimento"){
			glColor3f(0.9,0.9,0.9);
			it2->Build(ViewingHeight,ViewingWidth);

			for (int i = 0; i <= it2->width; i+=5){

				glPushMatrix();
				glTranslated( it2->x + i, 0.2, it2->z);
				glColor3f( sin( Jogador->angHelice*M_PI/180 ),0,0 );
				glutSolidSphere( 0.6 , 8, 8 );
				glPopMatrix();

				glPushMatrix();
				glTranslated( it2->x + i, 0.2, it2->z + it2->height);
				glColor3f( sin( Jogador->angHelice*M_PI/180 ),0,0 );
				glutSolidSphere( 0.6 , 8 , 8 );
				glPopMatrix();
			}

			for (int i = 0; i <= it2->height; i+=5){

				glPushMatrix();
				glTranslated( it2->x , 0.2, it2->z + i);
				glColor3f( sin( 2*Jogador->angHelice*M_PI/180 ),0,0 );
				glutSolidSphere( 0.6 , 8, 8 );
				glPopMatrix();

				glPushMatrix();
				glTranslated( it2->x + it2->width, 0.2, it2->z + i );
				glColor3f( sin( 2*Jogador->angHelice*M_PI/180 ),0,0 );
				glutSolidSphere( 0.6 , 8 , 8 );
				glPopMatrix();
			}
			break;
		}
		
  	}

	for (vector<Circle>::iterator it = Circles.begin() ; it != Circles.end(); ++it){
		if(it->id=="ObjetoResgate"){
								glColor3f( sin( 1.2 *Jogador->angHelice*M_PI/180 ) , sin( 0.8*Jogador->angHelice*M_PI/180 ) , sin( 0.2*Jogador->angHelice*M_PI/180 ) );

			if(it->condicao==0){
				glPushMatrix();
					glTranslatef( it->cx , Jogador->scale, it->cy );
					glutSolidSphere( Jogador->scale , 15 , 15 );
				glPopMatrix();
			}
		}
	}
	
}


void Cenario::verifResgate(){
	for (int i = 0; i < Circles.size() ; i++){

		if(Circles[i].id=="ObjetoResgate"){
			if( Circles[i].condicao==0 ){
				bool a = Jogador->resgateColision( Circles[i].cx , Jogador->scale/2 , Circles[i].cy , Jogador->scale );
				if(a) Circles[i].condicao=1;	
			}
		}

	}

}


int Cenario::gerarDirecaoInimigo()
{
	int d = rand()%8000;
	if(d<6000) return 1;
	if(d>6500) return 0;
	return -1;
}

int Cenario::gerarDirecaoAngInimigo()
{
	int d = rand()%8000;
	if(d<2999) return 1;
	if(d>6000) return 0;
	return -1;
}


int Cenario::gerarUpInimigo()
{
	int d = rand()%8000;
	if(d<2000) return 1;
	if(d>7900) return 0;
	return -1;
}

void Cenario::gerarMovimento(int inim, float speed){

//
	
	int direcao = gerarDirecaoInimigo();
	int ang = gerarDirecaoAngInimigo();
	int up = gerarUpInimigo();

	float x,y,z, nivel;
	x = Inimigo[inim].xHelic;
	y = Inimigo[inim].yHelic;
	z = Inimigo[inim].zHelic;
	nivel = Inimigo[inim].Nivel;


	// SOBE/DESCE
	if(Inimigo[inim].Nivel==0) Inimigo[inim].upNivel();
	if( up > 0 ) Inimigo[inim].upNivel();
	if( up < 0 && Inimigo[inim].Nivel>1){
	Inimigo[inim].downNivel();
	}

	if (!Inimigo[inim].pousado){

		// FRENTE / TRAS
		
			Inimigo[inim].movHelic(speed*(float)direcao);
	    	Inimigo[inim].mov = direcao;

    		if( fabs(Inimigo[inim].xHelic - 2*Inimigo[inim].r1) < Inimigo[inim].r1 || fabs(Inimigo[inim].zHelic - 2*Inimigo[inim].r1)< Inimigo[inim].r1 || 
    			fabs(Inimigo[inim].xHelic -    ViewingWidth ) < 2*Inimigo[inim].r1 || fabs(Inimigo[inim].zHelic - ViewingHeight ) < 2*Inimigo[inim].r1 ) {

    			Inimigo[inim].rodaHelic(1.0);
    			Inimigo[inim].movHelic(speed);
    			ang = 0;

    		}

	    	//ROTACAO
	    	Inimigo[inim].rodaHelic((float)ang/2.0);
			if(Inimigo[inim].mov || Inimigo[inim].mov == -1){
				if( ang<0 )Inimigo[inim].movR = 1;
				else Inimigo[inim].movR = 0;
				if( ang>0 )Inimigo[inim].movL = 1;
				else Inimigo[inim].movL = 0;
			}
			else{
				Inimigo[inim].movR = 0;
				Inimigo[inim].movL = 0;
			}

		bool c = InimigoColidir( inim );

		if(c){

			Inimigo[inim].movHelic(-speed*direcao);
			Inimigo[inim].rodaHelic(-(float)ang/2.0);
			Inimigo[inim].Nivel = nivel;			

		}

	}

}

void Cenario::gerarMovimentoTODOS(float speed){

	srand(time(NULL));
	for (int i = 0; i < Inimigo.size() ; i ++ ){
		if(Inimigo[i].Nivel==0) Inimigo[i].Nivel++;
		if(!Inimigo[i].morto && Inimigo[i].Nivel>0){
			float d = pointDistance( Inimigo[i].xHelic , Inimigo[i].yHelic , Jogador->xHelic , Jogador->yHelic , Inimigo[i].zHelic , Jogador->zHelic );
			float x,y,z, nivel;
			x = Inimigo[i].xHelic;
			y = Inimigo[i].yHelic;
			z = Inimigo[i].zHelic;
			nivel = Inimigo[i].Nivel;

			// depois de 1 movimento
			gerarMovimento(i, speed);

			if(!Jogador->morto){

				if( d < pointDistance( Inimigo[i].xHelic , Inimigo[i].yHelic , Jogador->xHelic , Jogador->yHelic , Inimigo[i].zHelic , Jogador->zHelic ) ){	
					if( Jogador->Nivel > Inimigo[i].Nivel )Inimigo[i].upNivel();
					else Inimigo[i].downNivel();
					if(Inimigo[i].Nivel == 0) Inimigo[i].upNivel();
					Inimigo[i].xHelic = x;
					Inimigo[i].yHelic = y;
					Inimigo[i].zHelic = z;
				}
				
				else{
					if( Inimigo[i].freqTiro >= FREQ_TIRO ){
						Inimigo[i].freqTiro = 0;
						//Inimigo[i].mirar( Jogador->xHelic , Jogador->yHelic , Jogador->zHelic );
						Inimigo[i].CriaTiro();

						Inimigo[i].distance = pointDistance( Inimigo[i].xHelic , Inimigo[i].yHelic , Jogador->xHelic , Jogador->yHelic , Inimigo[i].zHelic , Jogador->zHelic );
						if( Inimigo[i].distance < Inimigo[i].r1  )
						{
							Inimigo[i].movHelic(-0.1);
							//Inimigo[i].mirar( Jogador->xHelic , Jogador->yHelic , Jogador->zHelic );
							
						}


						for(int j=0; j< Inimigo.size(); j++){
							float a, b, c;
							a = pointDistance( Inimigo[i].xe1 , Inimigo[i].ye1 , Inimigo[j].xe1 , Inimigo[j].ye1 , Inimigo[i].ze1 , Inimigo[j].ze1 );
							b = pointDistance( Inimigo[i].xe1 , Inimigo[i].ye1 , Inimigo[j].xe2 , Inimigo[j].ye2 , Inimigo[i].ze1 , Inimigo[j].ze2 );
							c = pointDistance( Inimigo[i].xe1 , Inimigo[i].ye1 , Inimigo[j].xe3 , Inimigo[j].ye3 , Inimigo[i].ze1 , Inimigo[j].ze3 );
							if( ( a < 2*Inimigo[i].r1 + Inimigo[j].r1) || ( b < 2*Inimigo[i].r1 + Inimigo[j].r2 ) || ( c < 2*Inimigo[i].r1 + Inimigo[j].r3 ) )
								{
									Inimigo[i].movHelic(-0.05);
									continue;
								}

							a = pointDistance( Inimigo[i].xe3 , Inimigo[i].ye3 , Inimigo[j].xe1 , Inimigo[j].ye1 , Inimigo[i].ze3 , Inimigo[j].ze1 );
							b = pointDistance( Inimigo[i].xe3 , Inimigo[i].ye3 , Inimigo[j].xe2 , Inimigo[j].ye2 , Inimigo[i].ze3 , Inimigo[j].ze2 );
							c = pointDistance( Inimigo[i].xe3 , Inimigo[i].ye3 , Inimigo[j].xe3 , Inimigo[j].ye3 , Inimigo[i].ze3 , Inimigo[j].ze3 );
							if( ( a < 2*Inimigo[i].r3 + Inimigo[j].r1) || ( b < 2*Inimigo[i].r3 + Inimigo[j].r2 ) || ( c < 2*Inimigo[i].r3 + Inimigo[j].r3 ) )
								{
									Inimigo[i].movHelic(0.05);
									continue;
								}

						}


					}
					//printf(" Tiro ! ");
				}
			}


		if( 
			Inimigo[i].xHelic == Inimigo[i].r1 
			|| Inimigo[i].zHelic == Inimigo[i].r1 
			|| Inimigo[i].xHelic == ( ViewingWidth - Inimigo[i].r1 ) 
			|| Inimigo[i].zHelic == ( ViewingHeight - Inimigo[i].r1 ) 
			){
				Inimigo[i].rodaHelic(0.5);
			}

			
		}
	Inimigo[i].freqTiro ++;
	}

}

void Cenario::IncrementaTirosTODOS(float speed){
	Jogador->IncrementaTiros(speed);
	for (int i = 0; i < Inimigo.size(); i++){
		Inimigo[i].IncrementaTiros(speed);
	}
}


void Cenario::shotJogador(int inim){

	for(int j = 0; j < Inimigo[inim].Tiros.size() ; j++ ){

		if ( !Inimigo[inim].Tiros[j].out ){

			bool a = Jogador->shotColision( Inimigo[inim].Tiros[j].x1 , Inimigo[inim].Tiros[j].y1 , Inimigo[inim].Tiros[j].z1 , 0.1*Inimigo[inim].scale );
			if(a){
				Jogador->morto = 1;
				Inimigo[inim].Tiros[j].out = 1;
				objFilmado = inim + 1;
			}	
			else{
				bool b = Jogador->shotColision( Inimigo[inim].Tiros[j].x2 , Inimigo[inim].Tiros[j].y2 , Inimigo[inim].Tiros[j].z2 , 0.1*Inimigo[inim].scale );
				if(b) {
					Jogador->morto = 1;
					Inimigo[inim].Tiros[j].out = 1;
					objFilmado = inim + 1;
				}
			}

		}
	}	
}


void Cenario::shotJogadorTODOS(){
	if(!Jogador->pousado)
	for (int i = 0; i < Inimigo.size() && !Jogador->morto ; i++ ){
		shotJogador(i);
	}
}


void Cenario::DisplayOnRadar(float x, float y, float z, float nivel, string id){


	float scala =   ( 0.005 + (float)nivel)/100.0;

	float xH, yH, zH;

	xH = 4*x/ViewingWidth;
	xH = 4 - xH;
	xH = 1.0*xH/4;
	xH = xH - 2;

	zH = 4*z/ViewingHeight;
	zH = 1.0*zH/4;
	zH = zH - 2;
     
    glPushMatrix();
    	
    	glTranslatef(xH, zH, 0);
    	glScalef( scala ,scala , scala );
    	glBegin(GL_POLYGON);
    	 	glColor3f(0,0,0);
			glVertex3f( 0 , 0 , 0 );
        	glVertex3f( 0 , 1.0 , 0 );
        	glVertex3f( 1.0 , 1.0 , 0 );
        	glVertex3f( 1.0 , 0 , 0 );

    	glEnd();
    glPopMatrix();

}



void Cenario::DisplayRadar(){

	
        /*Outline border*/
         	
        glBegin(GL_LINE_LOOP);
        	glColor3f(0,0,0);
        	glVertex3f( -2 , -2 , 0 );
        	glVertex3f( -2 , -1.0 , 0 );
        	glVertex3f( -1.0 , -1.0 , 0 );
        	glVertex3f( -1.0 , -2.0 , 0 );
        glEnd();
   
   if(!Jogador->morto){

	   	float scala =   ( 5 + (float)Jogador->Nivel)/200.0;
		float xH, yH, zH;

		xH = 4*Jogador->xHelic/ViewingWidth;
		xH = 4 - xH;
		xH = 1.0*xH/4;
		xH = xH - 2;

		zH = 4*Jogador->zHelic/ViewingHeight;
		zH = 1.0*zH/4;
		zH = zH - 2;
	     
	    glPushMatrix();
	    	glTranslatef(xH, zH, 0);
	    	glScalef( scala ,scala , scala );
	    	glBegin(GL_POLYGON);
	    	 	glColor3f(0,1,0);
				glVertex3f( 0 , 0 , 0 );
	        	glVertex3f( 0 , 1.0 , 0 );
	        	glVertex3f( 1.0 , 1.0 , 0 );
	        	glVertex3f( 1.0 , 0 , 0 );
	    	glEnd();
	    glPopMatrix();
    	
   		glPushMatrix();
	   		glColor3f(0,1,0);
	   		glTranslatef( xH , zH , 0 );
	   		glutSolidCube(0.01);
   		glPopMatrix();
	}
	//DisplayOnRadar( Jogador->xHelic, Jogador->yHelic,Jogador->zHelic, Jogador->Nivel , Jogador->id );

	for( int i = 0; i<Inimigo.size() ; i++ ){
		glColor3f(0,0,0);
		if(!Inimigo[i].morto){
			float scala =   ( 5 + (float)Inimigo[i].Nivel)/200.0;

			float xH, yH, zH;

			xH = 4*Inimigo[i].xHelic/ViewingWidth;
			xH = 4 - xH;
			xH = 1.0*xH/4;
			xH = xH - 2;

			zH = 4*Inimigo[i].zHelic/ViewingHeight;
			zH = 1.0*zH/4;
			zH = zH - 2;
		     
		    glPushMatrix();
		    	
		    	glTranslatef(xH, zH, 0);
		    	glScalef( scala ,scala , scala );
		    	glBegin(GL_POLYGON);
		    	 	glColor3f(1,0,0);
					glVertex3f( 0 , 0 , 0 );
		        	glVertex3f( 0 , 1.0 , 0 );
		        	glVertex3f( 1.0 , 1.0 , 0 );
		        	glVertex3f( 1.0 , 0 , 0 );
		    	glEnd();

	    	glPopMatrix();


	   		glPushMatrix();
		   		glColor3f(0,0,0);
		   		glTranslatef( xH , zH , 0 );
		   		//glutSolidCube(0.01);
	   		glPopMatrix();
	   	}

	}

	for( int i = 0; i<Circles.size() ; i++ ){
		glColor3f(0,0,0);
		if(!Circles[i].condicao && Circles[i].id=="ObjetoResgate"){
			float scala =   3.005 /100.0;

			float xH, yH, zH;

			xH = 4*Circles[i].cx/ViewingWidth;
			xH = 4 - xH;
			xH = 1.0*xH/4;
			xH = xH - 2;

			zH = 4*Circles[i].cy/ViewingHeight;
			zH = 1.0*zH/4;
			zH = zH - 2;
		     
		    glPushMatrix();
		    	
		    	glTranslatef(xH, zH, 0);
		    	glScalef( scala ,scala , scala );
		    	glBegin(GL_POLYGON);
		    	 	glColor3f(0,0,1);
					glVertex3f( 0 , 0 , 0 );
		        	glVertex3f( 0 , 1.0 , 0 );
		        	glVertex3f( 1.0 , 1.0 , 0 );
		        	glVertex3f( 1.0 , 0 , 0 );
		    	glEnd();

	    	glPopMatrix();


	   		glPushMatrix();
		   		glColor3f(0,0,0);
		   		glTranslatef( xH , zH , 0 );
		   		glutSolidCube(0.01);
	   		glPopMatrix();
	   	}

	}



	float xB, zB;
	xB = 4.0*(float)Quads[1].x/ViewingWidth;
	xB = 4 - xB;
	xB = 1.0*xB/4;
	xB = xB - 2;

	zB = 4.0*(float)Quads[1].z/ViewingHeight;
	zB = 1.0*zB/4;
	zB = zB - 2;

	

	glPushMatrix();
		float newWidth = Quads[1].width/(float)ViewingWidth ;
		float newHight = Quads[1].height/(float)ViewingHeight ;
		
		glBegin(GL_POLYGON);
		 	glColor3f(1,1,1);
			glVertex3f( xB , zB , 0 );
			glColor3f(1,1,0);
	    	glVertex3f( xB , zB + newHight , 0 );
	    	glColor3f(0,1,1);
	    	glVertex3f( xB - newWidth , zB + newHight  , 0 );
	    	glColor3f(1,0,1);
	    	glVertex3f( xB - newWidth , zB , 0 );
		glEnd();
	glPopMatrix();

}

void Cenario::barraDeCombustivel(){

	glPushMatrix();
		glTranslatef( 2 - 0.2 - 0.05 , -2 , 0 );
		glBegin(GL_LINE_LOOP);
			glVertex3f( 0 , 0 , 0 );
			glVertex3f( 0 , 10*(0.5*0.2 + 0.01) , 0 );
			glVertex3f( 0.2 , 10*(0.5*0.2 + 0.01) , 0 );
			glVertex3f( 0.2 , 0 , 0 );
		glEnd();

		glPushMatrix();
			glTranslatef(0.1 , 0.2*0.5*0.5 ,0);
			glPushMatrix();
				//printf("combustivel: %.0f\n", Jogador->combustivel);
				for(float i = 0 ; i < Jogador->combustivel ; i+=10){
					glPushMatrix();
						glScalef(0.2, 0.2 ,0.2);
						glScalef(1,0.5,1);
						glutSolidCube(1);
					glPopMatrix();
					glTranslatef( 0, 0.5*0.2 + 0.01 , 0);
				}
			glPopMatrix();
		glPopMatrix();

	glPopMatrix();

}

void Cenario::desenha(int cam, float angCam, float ratio){

	///////////////////////////// 2D /////////////////////////////
    glDisable(GL_COLOR_MATERIAL);

    /*Orthogonal viewing*/
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(-2.0,  2.0,  -2.0, 2.0,  -2.0, 10000);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    DefineLuz();
    gluLookAt(  0.0 , 0.0 , 2.0, 
    		    0.0 , 0.0 , 0.0,
    		    0.0 , 1.0 , 0.0  ); 

// DESENHA 2D AQUI // 

    /*Panel*/
   if( verificaVitoria() ){

   	texto( " VENCEU ! " , -2 , -1.5);
   	glColor3f(0,0,0);
   	glTranslatef(-1.5,-1.0,0);
   	glScalef(1,0.5,1);
   	glutWireCube(1);

   }
   else if( Jogador->morto ){

   	texto( " PERDEU ! " , -2 , -1.5);
   	glColor3f(0,0,0);
   	glTranslatef(-1.5,-1.0,0);
   	glScalef(1,0.5,1);
   	glutWireCube(1);
  
   }



    if(radarON && !Jogador->morto &&!verificaVitoria() ) {
    	DisplayRadar();
    	barraDeCombustivel();
    }
   
    
   
///// FIM DO DESENHO 2D ////

    /*Restore the viewing mode*/
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
/////////////////////////////END 2D////////////////////////

	
	desenhaCircQuads();
	filma(cam,angCam,ratio);
  	drawWorldPoints();
	drawHelicopters();
    DrawLines();

}


void Cenario::helicopterColisionTODOS(){

	for (int i = 0; i < Inimigo.size() ; i++){

		if(!Jogador->morto && !Inimigo[i].morto){
			bool a = 0;
			a = Inimigo[i].helicopterColision(  Jogador->xe1 , Jogador->ye1 , Jogador->ze1 , Jogador->r1 , 
										   		Jogador->xe2 , Jogador->ye2 , Jogador->ze2 , Jogador->r2 , 
										   		Jogador->xe3 , Jogador->ye3 , Jogador->ze3 , Jogador->r1 ) ;
			
		}

		for(int j = 0; j < Inimigo.size() ; j++ ){

			if(i!=j && !Inimigo[j].morto){

				bool a = 0;
				a =	Inimigo[i].helicopterColision( Inimigo[j].xe1 , Inimigo[j].ye1 , Inimigo[j].ze1 , Inimigo[j].r1 , 
										   		   Inimigo[j].xe2 , Inimigo[j].ye2 , Inimigo[j].ze2 , Inimigo[j].r2 , 
										           Inimigo[j].xe3 , Inimigo[j].ye3 , Inimigo[j].ze3 , Inimigo[j].r1 ) ;
				

			}

		}

	}

}


bool Cenario::InimigoColidir( int inim ){

	if(!Jogador->morto){
		float d11 = pointDistance( Inimigo[inim].xe1, Inimigo[inim].ye1, Jogador->xe1, Jogador->ye1, Inimigo[inim].ze1, Jogador->ze1 );
		if(d11 < Inimigo[inim].r1 + Jogador->r1) return 1;

		float d12 = pointDistance( Inimigo[inim].xe1, Inimigo[inim].ye1, Jogador->xe2, Jogador->ye2, Inimigo[inim].ze1, Jogador->ze2 );
		if(d12 < Inimigo[inim].r1 + Jogador->r2) return 1;

		float d13 = pointDistance( Inimigo[inim].xe1, Inimigo[inim].ye1, Jogador->xe3, Jogador->ye3, Inimigo[inim].ze1, Jogador->ze3 );
		if(d13 < Inimigo[inim].r1 + Jogador->r3) return 1;


		float d21 = pointDistance( Inimigo[inim].xe2, Inimigo[inim].ye2, Jogador->xe1, Jogador->ye1, Inimigo[inim].ze2, Jogador->ze1 );
		if(d21 < Inimigo[inim].r2 + Jogador->r1) return 1;

		float d22 = pointDistance( Inimigo[inim].xe2, Inimigo[inim].ye2, Jogador->xe2, Jogador->ye2, Inimigo[inim].ze2, Jogador->ze2 );
		if(d22 < Inimigo[inim].r2 + Jogador->r2) return 1;

		float d23 = pointDistance( Inimigo[inim].xe2, Inimigo[inim].ye2, Jogador->xe3, Jogador->ye3, Inimigo[inim].ze2, Jogador->ze3 );
		if(d23 < Inimigo[inim].r2 + Jogador->r3) return 1;


		float d31 = pointDistance( Inimigo[inim].xe3, Inimigo[inim].ye3, Jogador->xe1, Jogador->ye1, Inimigo[inim].ze3, Jogador->ze1 );
		if(d31 < Inimigo[inim].r3 + Jogador->r1) return 1;

		float d32 = pointDistance( Inimigo[inim].xe3, Inimigo[inim].ye3, Jogador->xe2, Jogador->ye2, Inimigo[inim].ze3, Jogador->ze2 );
		if(d32 < Inimigo[inim].r3 + Jogador->r2) return 1;

		float d33 = pointDistance( Inimigo[inim].xe3, Inimigo[inim].ye3, Jogador->xe3, Jogador->ye3, Inimigo[inim].ze3, Jogador->ze3 );
		if(d33 < Inimigo[inim].r3 + Jogador->r3) return 1;
	}

	for( int i = 0 ; i < Inimigo.size() ; i++ ){
		if( i!=inim && !Inimigo[i].morto){

			float d11 = pointDistance( Inimigo[inim].xe1, Inimigo[inim].ye1, Inimigo[i].xe1, Inimigo[i].ye1, Inimigo[inim].ze1, Inimigo[i].ze1 );
			if(d11 < Inimigo[inim].r1 + Inimigo[i].r1) return 1;

			float d12 = pointDistance( Inimigo[inim].xe1, Inimigo[inim].ye1, Inimigo[i].xe2, Inimigo[i].ye2, Inimigo[inim].ze1, Inimigo[i].ze2 );
			if(d12 < Inimigo[inim].r1 + Inimigo[i].r2) return 1;

			float d13 = pointDistance( Inimigo[inim].xe1, Inimigo[inim].ye1, Inimigo[i].xe3, Inimigo[i].ye3, Inimigo[inim].ze1, Inimigo[i].ze3 );
			if(d13 < Inimigo[inim].r1 + Inimigo[i].r3) return 1;



			float d21 = pointDistance( Inimigo[inim].xe2, Inimigo[inim].ye2, Inimigo[i].xe1, Inimigo[i].ye1, Inimigo[inim].ze2, Inimigo[i].ze1 );
			if(d21 < Inimigo[inim].r2 + Inimigo[i].r1) return 1;

			float d22 = pointDistance( Inimigo[inim].xe2, Inimigo[inim].ye2, Inimigo[i].xe2, Inimigo[i].ye2, Inimigo[inim].ze2, Inimigo[i].ze2 );
			if(d22 < Inimigo[inim].r2 + Inimigo[i].r2) return 1;

			float d23 = pointDistance( Inimigo[inim].xe2, Inimigo[inim].ye2, Inimigo[i].xe3, Inimigo[i].ye3, Inimigo[inim].ze2, Inimigo[i].ze3 );
			if(d23 < Inimigo[inim].r2 + Inimigo[i].r3) return 1;



			float d31 = pointDistance( Inimigo[inim].xe3, Inimigo[inim].ye3, Inimigo[i].xe1, Inimigo[i].ye1, Inimigo[inim].ze3, Inimigo[i].ze1 );
			if(d31 < Inimigo[inim].r3 + Inimigo[i].r1) return 1;

			float d32 = pointDistance( Inimigo[inim].xe3, Inimigo[inim].ye3, Inimigo[i].xe2, Inimigo[i].ye2, Inimigo[inim].ze3, Inimigo[i].ze2 );
			if(d32 < Inimigo[inim].r3 + Inimigo[i].r2) return 1;

			float d33 = pointDistance( Inimigo[inim].xe3, Inimigo[inim].ye3, Inimigo[i].xe3, Inimigo[i].ye3, Inimigo[inim].ze3, Inimigo[i].ze3 );
			if(d33 < Inimigo[inim].r3 + Inimigo[i].r3) return 1;
		}

	}

	return 0;

}


bool Cenario::JogadorColidir(){

	for( int i = 0 ; i < Inimigo.size() ; i++ ){

		if(!Inimigo[i].morto){
			float d11 = pointDistance( Jogador->xe1, Jogador->ye1, Inimigo[i].xe1, Inimigo[i].ye1, Jogador->ze1, Inimigo[i].ze1 );
			if(d11 < Jogador->r1 + Inimigo[i].r1) return 1;

			float d12 = pointDistance( Jogador->xe1, Jogador->ye1, Inimigo[i].xe2, Inimigo[i].ye2, Jogador->ze1, Inimigo[i].ze2 );
			if(d12 < Jogador->r1 + Inimigo[i].r2) return 1;

			float d13 = pointDistance( Jogador->xe1, Jogador->ye1, Inimigo[i].xe3, Inimigo[i].ye3, Jogador->ze1, Inimigo[i].ze3 );
			if(d13 < Jogador->r1 + Inimigo[i].r3) return 1;



			float d21 = pointDistance( Jogador->xe2, Jogador->ye2, Inimigo[i].xe1, Inimigo[i].ye1, Jogador->ze2, Inimigo[i].ze1 );
			if(d21 < Jogador->r2 + Inimigo[i].r1) return 1;

			float d22 = pointDistance( Jogador->xe2, Jogador->ye2, Inimigo[i].xe2, Inimigo[i].ye2, Jogador->ze2, Inimigo[i].ze2 );
			if(d22 < Jogador->r2 + Inimigo[i].r2) return 1;

			float d23 = pointDistance( Jogador->xe2, Jogador->ye2, Inimigo[i].xe3, Inimigo[i].ye3, Jogador->ze2, Inimigo[i].ze3 );
			if(d23 < Jogador->r2 + Inimigo[i].r3) return 1;



			float d31 = pointDistance( Jogador->xe3, Jogador->ye3, Inimigo[i].xe1, Inimigo[i].ye1, Jogador->ze3, Inimigo[i].ze1 );
			if(d31 < Jogador->r3 + Inimigo[i].r1) return 1;

			float d32 = pointDistance( Jogador->xe3, Jogador->ye3, Inimigo[i].xe2, Inimigo[i].ye2, Jogador->ze3, Inimigo[i].ze2 );
			if(d32 < Jogador->r3 + Inimigo[i].r2) return 1;

			float d33 = pointDistance( Jogador->xe3, Jogador->ye3, Inimigo[i].xe3, Inimigo[i].ye3, Jogador->ze3, Inimigo[i].ze3 );
			if(d33 < Jogador->r3 + Inimigo[i].r3) return 1;
		}
		
	}

	return 0;

}


bool Cenario::verificaBase(){

	//printf("posicao z: %.0f  |  limites z: %d a %d \n", Jogador->zHelic , Quads[1].z ,Quads[1].z + Quads[1].width);
	if( Jogador->xHelic > Quads[1].x  && Jogador->xHelic < Quads[1].x + Quads[1].width && 
		Jogador->zHelic > Quads[1].z  && Jogador->zHelic < Quads[1].z + Quads[1].height) return 1;
	else return 0;
}



bool Cenario::verificaVitoria(){

	for (int i = 0; i < Circles.size() ; i++){
		
		if( Circles[i].id == "ObjetoResgate" )
			if( !Circles[i].condicao ) return 0;

	}

	printf(" GANHOU ! \n");
	return 1;

}



void Cenario::drawText(const char* text, int lenght, int x, int y){
	glMatrixMode(GL_PROJECTION);
	double *matrix = new double[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	//glOrtho(0,800,0,600,-5,5);
	glOrtho(-2, 2 , -2 ,2 ,100,-100);  
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2f(x,y);
	for(int i=0 ; i<lenght; i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);
	
}	

void Cenario::texto(string text, int x, int y)
{
	//string text;
	//text = " THIS IS SPARTA !";
	drawText(text.data(), text.size(), x, y);
}








