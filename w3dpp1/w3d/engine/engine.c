/***************************************************************************
                          engine.c  -  description
                             -------------------
    begin                : sáb ene 18 2003
    copyright            : (C) 2003 by neuralgya
    email                : neuralgya@users.berlios.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "../opengl.h"
#include "../global.h"
#include "estructuras.h"

#include "espacio.h"
#include "texturas.h"

double matriz_proyeccion_A[4][4];
double matriz_proyeccion_B[4][4];
double matriz_proyeccion_C[4][4];

float camara[4][4];

float intervalo;

extern GLuint *matriz_texturas;


/* Matriz de sprites de fondo del espacio */
lista_sprites_spc *sprites_spc;
unsigned int n_sprites_spc;

/* Lista de puntos de estrellas */

float *estrellas;
unsigned int n_estrellas;



int init_espacio(void) {


  /* Cargamos la lista de sprites de espacio */

	if (!(carga_espacio("espacio1.txt"))) {
		_sis_msj("\t\tError cargando espacio[KO]");
		return NO;
	}
	/* Ahora se supone que en sprites_spc tenemos la lista completa
	de los sprites de espacio.*/

	if (!(crea_estrellas(10000))) {
			_sis_msj("\n\t\tFallé al crear estrellas[KO]");
			return NO;
	}

	return SI;
}


int init_engine(){

     if (init_espacio()) {
	_sis_msj("\n[OK]\t\tEspacio inicializado");
    }
     else  
	return NO;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,
		   (GLfloat) config.SCREEN_SIZE_X /
		   (GLfloat) config.SCREEN_SIZE_Y, 0.01f, 100000.0f);

	glGetDoublev(GL_PROJECTION_MATRIX,&matriz_proyeccion_A[0][0]);

	glLoadIdentity();
    gluPerspective(45.0f,
		   (GLfloat) config.SCREEN_SIZE_X /
		   (GLfloat) config.SCREEN_SIZE_Y, 0.01f, 100000.0f);

	glGetDoublev(GL_PROJECTION_MATRIX,&matriz_proyeccion_B[0][0]);

	glLoadIdentity();
	glOrtho(0,config.SCREEN_SIZE_X,0,config.SCREEN_SIZE_Y,-100,100);
	glGetDoublev(GL_PROJECTION_MATRIX,&matriz_proyeccion_C[0][0]);

	glLoadMatrixd(&matriz_proyeccion_A[0][0]);

	_sis_msj("\n\t\t[OK]Matrices de proyección creadas");

	glGetFloatv(GL_MODELVIEW_MATRIX,&camara[0][0]);
         	camara[2][2]=1.0f;
	camara[3][2]=-1.0f;

	if (!genera_texturas()) {
	    _sis_msj("\n\t\t\tError generando texturas [KO]");
	    return NO;
	}
	else
	     _sis_msj("\n[OK]\t\t\tTexturas Generadas");
	


    return SI;
}

int renderiza_escena() {

          int aux,aux2;

         SDL_ShowCursor(0);
         gl_basic_ini(NO);
    	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* Dibujamos el fondo */

	/* Primero preparamos el estado de OpenGL */

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(&matriz_proyeccion_B[0][0]);
	gluLookAt(	camara[3][0],camara[3][1],camara[3][2],			// Posición
			camara[3][0]+camara[2][0],camara[3][1]+camara[2][1],camara[3][2]+camara[2][2],								// Punto al que miramos
			camara[1][0],camara[1][1],camara[1][2]);		// Orientación Y




	glMatrixMode(GL_MODELVIEW);
 	glDisable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
         	glLoadIdentity();
         glDisable(GL_LIGHTING);

         /* Dibujamos estrellas */
         glColor3f(1.0f,1.0f,1.0f);
	for (aux=0;aux<n_estrellas;aux+=4) {
		glPointSize(estrellas[aux+3]);
		glBegin(GL_POINTS);
		    glVertex3f(estrellas[aux],estrellas[aux+1],estrellas[aux+2]);
		glEnd();
	}

	glPointSize(4.0f);

	/* Dibujamos sprites de fondo */
	glEnable(GL_TEXTURE_2D);
	for (aux=0;aux<n_sprites_spc;aux++) {
	    glLoadMatrixf(&sprites_spc[aux].matriz);
	    glBindTexture(GL_TEXTURE_2D,matriz_texturas[sprites_spc[aux].textura]);
		aux2=sprites_spc[aux].tam_x;
		glBegin(GL_QUADS);
		    glTexCoord2f(1.0f, 1.0f); glVertex2f( aux2,  aux2);
		    glTexCoord2f(1.0f, 0.0f); glVertex2f( aux2,  -aux2);
		    glTexCoord2f(0.0f, 0.0f); glVertex2f(-aux2,  -aux2);
		    glTexCoord2f(0.0f, 1.0f); glVertex2f(-aux2,  aux2);
		glEnd();
		}

	glEnable(GL_DEPTH_TEST);
	glClear(GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glFlush();
	SDL_GL_SwapBuffers();

    return SI;
}


int game_loop() {

    int done=0;

    SDL_Event event;
    Uint8 *keys;
    static float taux,tiempo_antiguo;


    while (done==0) {
        taux = SDL_GetTicks();
        intervalo = (taux - tiempo_antiguo)/1000.0f;
        tiempo_antiguo = taux;


        if (SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT)
                done = 1;

            keys = SDL_GetKeyState(NULL);
            if (keys[SDLK_ESCAPE])
	    done = 1;
}


            //input_mouse();
            renderiza_escena();
    }

     return SI;
} 