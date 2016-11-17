#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <vector>
#include "Circle.h"
#include "Quad.h"
#include "Tiro.h"
#include "Helicopter.h"
#include "Biblioteca.h"
#include "biblioteca_tiny/tinyxml2.h"
#include "Cenario.h"

using namespace tinyxml2;
using namespace std;


int r = 0;
int cam = 3;
int h = 0;
GLfloat ratio;
GLfloat angCam = 90;




int keyStatus[256];


Cenario *cenario = new Cenario();




void keyPress(unsigned char key, int x, int y){
    switch (key){
        case 'w':
        case 'W':
             keyStatus[(int)('w')] = 1; //Using keyStatus trick
             break;
        case 's':
        case 'S':
             keyStatus[(int)('s')] = 1; //Using keyStatus trick
             break;
        case 'a':
        case 'A':
             keyStatus[(int)('a')] = 1; //Using keyStatus trick
             break;
        case 'd':
        case 'D':
             keyStatus[(int)('d')] = 1; //Using keyStatus trick
             break;
        case 'E':
        case 'e':
            cenario->EsferasON_OFF(); //habilitar esferas de colisao
             break;
        case 'q':
        case 'Q':
            cenario->linesON_OFF(); //habilitar esferas de colisao
             break;
        case 'i':
        case 'I':
            cenario->lights*=-1; //habilitar esferas de colisao
             break;
        case '2':
             cam = 2; 
             break;
         case '1':
             cam = 1;
             break;
        case '3':
             cam = 3; 
             break;
	    case '7':
             cam = 7; 
             break;
        case '8':
             cam = 8; 
             break;
        case '4':
             cam = 4; 
             break;
         case '5':
             cam = 5; 
             break;
        case 't':
        case 'T':
                cenario->toggleObjFilmado();
             break;
        case 'r':
        case 'R':
                if(cenario->radarON) cenario->radarON = 0;
                else cenario->radarON = 1;
             break;
        case 'J':
        case 'j':
             if(!cenario->Jogador->morto) cenario->objFilmado = 0;
             break;
        case 'p':
        case 'P':
        	cenario->Jogador->Pousar();
            break; 
        case '=':
        case '+':
        	cenario->Jogador->upNivel();
            break; 
        case '-':
        case '_':
        	cenario->Jogador->downNivel();
            break; 
        case '6':
        	cam = 6;
            break; 
        case 'g':
        case 'G':
            if( cenario->gradeON ) cenario->gradeON = 0;
            else cenario->gradeON = 1;
            break; 
        case '!':
            if( cenario->Luz1ON ) cenario->Luz1ON = 0;
            else cenario->Luz1ON = 1;
            break;
        case 'l':
        case 'L':
            if( cenario->Luz1ON ) cenario->Luz1ON = 0;
            else cenario->Luz1ON = 1;
            break;  

          }
    glutPostRedisplay();
}

void keyup(unsigned char key, int x, int y){
    keyStatus[(int)(key)] = 0;
    glutPostRedisplay();
}

void ResetKeyStatus(){
    int i;
    //Initialize keyStatus
    for(i = 0; i < 256; i++)
       keyStatus[i] = 0; 
}


void updatePaddle( GLdouble timeDiff ){

    float speed = cenario->Jogador->velHelic*timeDiff; //Correct speed of movement with the time difference between calls
    float speed2 = cenario->VELHELICOPTERO2*timeDiff;
    cenario->gerarMovimentoTODOS(speed2);


    //printf("| speed : %.5f |", speed  );
    //printf("velocidade : %.5f | vel: %.5f |\n", cenario->Jogador->velHelic , cenario->Jogador->vel );
 

	//Treat keyPress

    	if(keyStatus[(int)('w')] && !cenario->Jogador->pousado )
    	{
    		cenario->Jogador->movHelic(speed);
            cenario->Jogador->mov = 1;

            if( cenario->JogadorColidir() ){
                cenario->Jogador->movHelic(-speed);
                cenario->Jogador->mov = 0;
            }
    		
    	}
    	else cenario->Jogador->mov = 0;
    	if(keyStatus[(int)('s')] && !cenario->Jogador->pousado )
    	{
    		cenario->Jogador->movHelic(-0.7*speed);
    		cenario->Jogador->mov = -1;
            if( cenario->JogadorColidir() ){
                cenario->Jogador->movHelic(0.7*speed);
                cenario->Jogador->mov = 0;
            }
    	}

    	if(keyStatus[(int)('d')] && !cenario->Jogador->pousado )
    	{
    		cenario->Jogador->rodaHelic(-0.7*speed);
    		if(cenario->Jogador->mov || cenario->Jogador->mov == -1) cenario->Jogador->movR = 1;
            if( cenario->JogadorColidir() ){
                cenario->Jogador->movHelic(0.7*speed);
                cenario->Jogador->mov = 0;
                cenario->Jogador->movR = 0;
            }
    	}
    	else cenario->Jogador->movR = 0;
    	if(keyStatus[(int)('a')] && !cenario->Jogador->pousado )
    	{
    		cenario->Jogador->rodaHelic(0.7*speed);
    		if(cenario->Jogador->mov || cenario->Jogador->mov == -1) cenario->Jogador->movL = 1;
            if( cenario->JogadorColidir() ){
                cenario->Jogador->movHelic(-0.7*speed);
                cenario->Jogador->mov = 0;
                cenario->Jogador->movL = 0;
            }
    	}
    	else cenario->Jogador->movL = 0;

    if ( cenario->verificaBase() && cenario->Jogador->pousado ){
        cenario->Jogador->combustivel = 100;
    }

}

void idle(void){
    static GLdouble previousTime = 0;
    GLdouble currentTime;
    GLdouble timeDiference;
    
    // Elapsed time from the initiation of the game.
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    
    timeDiference = currentTime - previousTime; // Elapsed time from the previous frame.
    previousTime = currentTime; //Update previous time

   	updatePaddle( timeDiference );

    cenario->EnemyColision();
    cenario->shotEnemy();
    cenario->IncrementaTirosTODOS(cenario->VELTIRO*timeDiference);
    cenario->helicopterColisionTODOS();

    if( !cenario->Jogador->morto && !cenario->verificaVitoria() ){

        cenario->shotJogadorTODOS();
        cenario->Jogador->incrementeCombustivel(-timeDiference/(10*cenario->TempoDeVoo));
        cenario->verifResgate();

    }

    glutPostRedisplay();
}

// **********************************************************************
//  void init(void)
//		Inicializa os parâmetros globais de OpenGL
//
// **********************************************************************
void init(void){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Fundo de tela preto
	glShadeModel(GL_SMOOTH);						
	glColorMaterial ( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
	glEnable(GL_DEPTH_TEST);
	glEnable ( GL_CULL_FACE );
	
}

void reshape( int w, int h ){

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;
	ratio = 1.0f * w / h;
	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	// Set the viewport to be the entire window
    //glViewport(0, 0, w, h);

	cenario->filma(cam,angCam,ratio);

}



void display( void ){

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    /* glViewport(0, 500 , 250 , 250);
    cenario->desenha(4 ,angCam,ratio);
    glViewport(250, 500 , 250 , 250);
    cenario->desenha(4 ,angCam,ratio); */ 


    glViewport(0, 0, 500 , 500);
    cenario->desenha(cam,angCam,ratio);


	// Enable color tracking
    glEnable(GL_COLOR_MATERIAL);
    
	glutSwapBuffers();
}

void display2( void ){

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glViewport(0, 500 , 250 , 250);
    cenario->desenha(4 ,angCam,ratio);
  
    // Enable color tracking
    glEnable(GL_COLOR_MATERIAL);
    
    glutSwapBuffers();
}


void radar ( void ){

    //glMatrixMode(GL_PROJECTION); 
   // glOrtho(0 , 100  , 0 ,100 ,100,-100);   
    //glMatrixMode(GL_MODELVIEW);  
    //glLoadIdentity();

}


void arrow_keys ( int a_keys, int x, int y )  {
	switch ( a_keys ) 
	{
		case GLUT_KEY_UP:       // When Up Arrow Is Pressed...
			cenario->Jogador->incAng2Cam(4);
			//glutFullScreen ( ); // Go Into Full Screen Mode
			break;
	    case GLUT_KEY_DOWN:     // When Down Arrow Is Pressed...
	    	cenario->Jogador->incAng2Cam(-4);
			//glutInitWindowSize  ( cenario->ViewingWidth , cenario->ViewingHeight );
			break;
		case GLUT_KEY_LEFT:     // When Down Arrow Is Pressed...
	    	cenario->Jogador->incAng1Cam(4);
			//glutInitWindowSize  ( cenario->ViewingWidth , cenario->ViewingHeight );
			break;
		case GLUT_KEY_RIGHT:     // When Down Arrow Is Pressed...
	    	cenario->Jogador->incAng1Cam(-4);
			//glutInitWindowSize  ( cenario->ViewingWidth , cenario->ViewingHeight );
			break;
		default:
			break;
	}
}

int startFunctions(int argc, char** argv){
	glutInit( &argc, argv ); 
	glutInitDisplayMode (GLUT_SINGLE | GLUT_DEPTH | GLUT_RGB );
	if(argc!=2){
		printf("Caminho do Arquivo nao foi fornecido!\n"); 
		return 0;
	}

	cenario->define(argv[1]);

	glutInitWindowPosition (0,0);
	glutInitWindowSize  ( 500 , 500 ); 
	glutCreateWindow    ( "Computação Gráfica - Trabalho Final" ); 
	ResetKeyStatus();
	init ();

}


void mouseClick(int button, int status ,int x, int y){
	// button: 0 | 2
	// status: 0 | 1	

        
		if(button==0 && status==1) {
			if( !cenario->Jogador->pousado ) cenario->Jogador->CriaTiro();
		}
        if(button == 2 && status == 0){
            cenario->movCam = 1;
        } 
        if(button == 2 && status == 1){
            cenario->movCam = 0;
        } 
}

void mouseMotion( int mouse_x, int mouse_y ){



    if( cenario->d1 == 0 ) {  }
    else{   
        if(cenario->Jogador->morto==0){
            cenario->Jogador->deslocamento1 = mouse_x - cenario->d1;

            if( cenario->movCam ){
               
                cenario->Jogador->incAng1Cam(cenario->Jogador->deslocamento1);
            }

        }

    }



    if( cenario->d2 == 0 ) {  }
    else{   
        if(cenario->Jogador->morto==0){
            cenario->Jogador->deslocamento2 = mouse_y - cenario->d2;

            if( cenario->movCam ){
                cenario->Jogador->incAng2Cam(cenario->Jogador->deslocamento2);
            }

        }
    }


    cenario->d1 = mouse_x;
    cenario->d2 = mouse_y;

    
}

void mouseMove(int mouse_x, int mouse_y){

    
        if( cenario->d1 == 0 ) {  }
        else{   
            if(cenario->Jogador->morto==0) cenario->Jogador->deslocamento1 = mouse_x - cenario->d1;
        }
        if( cenario->d2 == 0 ) {  }
        else{   
            if(cenario->Jogador->morto==0) cenario->Jogador->deslocamento2 = mouse_y - cenario->d2;
        }
        cenario->d1 = mouse_x;
        cenario->d2 = mouse_y;

}


void runningFunctions(){
	glutDisplayFunc ( display2 );  
    glutDisplayFunc ( display ); 
	glutReshapeFunc ( reshape );
	glutKeyboardFunc ( keyPress );
	glutKeyboardUpFunc(keyup);
    glutPassiveMotionFunc(mouseMove);
    glutMotionFunc(mouseMotion);
	glutMouseFunc(mouseClick);
	glutSpecialFunc ( arrow_keys );
	glutIdleFunc ( display );
	glutIdleFunc(idle);
	glutMainLoop ( );  
}
