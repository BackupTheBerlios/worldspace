// Tratamiento de los eventos del teclado

#include "teclado.h"
#include "opengl.h"
#include "timer.h"
#include "init_sys.h"
#include "audio.h"
#include <SDL/SDL.h>




extern float camara[4][4]; /* Matriz de la camara definida en render.c*/
extern modelo *nave1;
extern laser_struct disparo_laser;
extern ALfloat PosSonidoNave1[3];
float VelSonidoNave1[3] = {1.0f,1.0f,1.0f};
/*
VelSonidoNave1[0] = 1.0f;
VelSonidoNave1[1] = 1.0f;
VelSonidoNave1[2] = 1.0f;
/*Alfloat VelSonidoNave1[] = {1.0f,1.0f,1.0}; */
float velocidad;						/* Multiplicador de velocidad. Máximo 10.0f */
float velocidad_r=1.0f;					/* velocidad=10.0f-(10/velocidad_r) */



int mouse_x,mouse_y;				/* Coordenadas del ratón */

/*!         |
			| Y+
			|
			|
			|
X+	--------o
	       /
		  /
		 / Z+

*/
/* Esta matriz esta en modo Vx,Vy,Vz,O */


int tecla_pulsada(void) {

	float x,y,z;

  Uint8 *keys;

   keys = SDL_GetKeyState(NULL);

	
if (keys[SDLK_ESCAPE])
             		return -1;
 	
if (keys[SDLK_w]) {

			velocidad_r+=0.005f;

	}

	if (keys[SDLK_s]) {
			velocidad_r-=0.006f;
			if (velocidad_r<1.0f)
				velocidad_r=1.0f;

	
	}

	if (keys[SDLK_e]) {


			SDL_WarpMouse(config.SCREEN_SIZE_X/2,config.SCREEN_SIZE_Y/2);

  }

	if (keys[SDLK_q]) {
			SDL_WarpMouse(320,240);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glGetFloatv(GL_MODELVIEW_MATRIX,&camara[0][0]);
			camara[2][2]=1.0f;
			camara[3][2]=-1.0f;


	}
	
 if (keys[SDLK_SPACE]) {
    if (disparo_laser.ttl==0) {
          memcpy(&disparo_laser.posicion[0],&camara[3][0],sizeof(float)*3);
          memcpy(&disparo_laser.direccion[0],&camara[2][0],sizeof(float)*3);
          disparo_laser.posicion[0]+=(0.1f*  disparo_laser.direccion[0]);
          disparo_laser.posicion[1]+=(0.1f*  disparo_laser.direccion[1]);
          disparo_laser.posicion[2]+=(0.1f*  disparo_laser.direccion[2]);

          disparo_laser.ttl=get_timer();
          disparo_laser.color[0]=0.0f;
          disparo_laser.color[1]=0.0f;
          disparo_laser.color[2]=1.0f;
          disparo_laser.color[3]=1.0f;

          /* Reproducimos sonido laser */
          if ( audio_on == 1){
              ReproducirSonido ( 0,disparo_laser.posicion, (disparo_laser.direccion),1.0f, 1.0f,10.0f, AL_FALSE);
          }
    }
}
 
     
		
	if (keys[SDLK_p]) {
		  glShadeModel(GL_FLAT);
	}
    if (keys[SDLK_o]) {
		  glShadeModel(GL_SMOOTH);
	}
    if (keys[SDLK_m]) {
		  ReproducirMusica ( );
	}
    if (keys[SDLK_n]){
        if ( audio_on == 1 ){
            ReproducirSonido ( 2, PosSonidoNave1, VelSonidoNave1 ,1.0f,1.0f,0.0f,AL_TRUE);
        }
    }
	if (keys[SDLK_a]) {

		glMatrixMode(GL_MODELVIEW);
		x=camara[3][0];
		y=camara[3][1];
		z=camara[3][2];

		camara[3][0]=0;
		camara[3][1]=0;
		camara[3][2]=0;
		camara[3][3]=1;
		glLoadMatrixf(&camara[0][0]);
		glRotatef(-60.f*intervalo,0.0f,0.0f,1.0f);
		glGetFloatv(GL_MODELVIEW_MATRIX,&camara[0][0]);
		camara[3][0]=x;
		camara[3][1]=y;
		camara[3][2]=z;
		camara[3][3]=1;



	}
	if (keys[SDLK_d]) {

		glMatrixMode(GL_MODELVIEW);
		x=camara[3][0];
		y=camara[3][1];
		z=camara[3][2];

		camara[3][0]=0;
		camara[3][1]=0;
		camara[3][2]=0;
		camara[3][3]=1;
		glLoadMatrixf(&camara[0][0]);
		glRotatef(60.f*intervalo,0.0f,0.0f,1.0f);
		glGetFloatv(GL_MODELVIEW_MATRIX,&camara[0][0]);
		camara[3][0]=x;
		camara[3][1]=y;
		camara[3][2]=z;
		camara[3][3]=1;

	}




return 0;
}

void input_mouse(void) {


    float x,y,z;

    Uint8 *keys;

    keys = SDL_GetKeyState(NULL);


    SDL_GetMouseState(&mouse_x,&mouse_y);

		glMatrixMode(GL_MODELVIEW);
		x=camara[3][0];
		y=camara[3][1];
		z=camara[3][2];

		camara[3][0]=0;
		camara[3][1]=0;
		camara[3][2]=0;
		camara[3][3]=1;
		glLoadMatrixf(&camara[0][0]);
		glRotatef((config.SCREEN_SIZE_X/2-(mouse_x))*intervalo/6.0f,0.0f,1.0f,0.0f);
		glRotatef(((mouse_y)-config.SCREEN_SIZE_Y/2)*intervalo/6.0f,1.0f,0.0f,0.0f);

		glGetFloatv(GL_MODELVIEW_MATRIX,&camara[0][0]);
		camara[3][0]=x;
		camara[3][1]=y;
		camara[3][2]=z;
		camara[3][3]=1;



		/* Actualización de variables dinámicas */

		velocidad=10.0f-(10/velocidad_r);

		camara[3][2] += (velocidad * intervalo* camara[2][2]);
		camara[3][1] += (velocidad * intervalo* camara[2][1]);
		camara[3][0] += (velocidad * intervalo* camara[2][0]);

	/*  Nave liebre */
	
  	nave1->x += (-0.5f * intervalo* nave1->base[2].x);
   	nave1->y += (-0.5f * intervalo* nave1->base[2].y);
  	nave1->z += (-0.5f * intervalo* nave1->base[2].z);
  	
  	disparo_laser.posicion[0]+=(20.1f* intervalo* disparo_laser.direccion[0]);
  	disparo_laser.posicion[1]+=(20.1f* intervalo* disparo_laser.direccion[1]);
  	disparo_laser.posicion[2]+=(20.1f* intervalo* disparo_laser.direccion[2]);

  	if (disparo_laser.ttl>0)
  	   if (get_timer()-disparo_laser.ttl>5000)
  	         disparo_laser.ttl=0;
		

}

