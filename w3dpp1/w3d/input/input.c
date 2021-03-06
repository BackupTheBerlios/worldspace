/***************************************************************************
                          input.c  -  description
                             -------------------
    begin                : dom ene 19 2003
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


extern float camara[4][4];

float velocidad;                /* Multiplicador de velocidad. M�ximo 10.0f */
float velocidad_r = 1.0f;       /* velocidad=10.0f-(10/velocidad_r) */

extern float intervalo;

int input_teclado(void)
{
    Uint8 *keys;
    float x, y, z;


    keys = SDL_GetKeyState(NULL);


    if (keys[SDLK_w]) {

        velocidad_r += 0.005f;

    }

    if (keys[SDLK_s]) {
        velocidad_r -= 0.006f;
        if (velocidad_r < 1.0f)
            velocidad_r = 1.0f;


    }

    if (keys[SDLK_e]) {


        SDL_WarpMouse(config.SCREEN_SIZE_X / 2, config.SCREEN_SIZE_Y / 2);

    }

    if (keys[SDLK_q]) {
        SDL_WarpMouse(320, 240);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glGetFloatv(GL_MODELVIEW_MATRIX, &camara[0][0]);
        camara[2][2] = 1.0f;
        camara[3][2] = -1.0f;


    }

/* if (keys[SDLK_SPACE]) {
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
    }
} */



    if (keys[SDLK_p]) {
        glShadeModel(GL_FLAT);
    }
    if (keys[SDLK_o]) {
        glShadeModel(GL_SMOOTH);
    }




    if (keys[SDLK_a]) {

        glMatrixMode(GL_MODELVIEW);
        x = camara[3][0];
        y = camara[3][1];
        z = camara[3][2];

        camara[3][0] = 0;
        camara[3][1] = 0;
        camara[3][2] = 0;
        camara[3][3] = 1;
        glLoadMatrixf(&camara[0][0]);
        glRotatef(-60.f * intervalo, 0.0f, 0.0f, 1.0f);
        glGetFloatv(GL_MODELVIEW_MATRIX, &camara[0][0]);
        camara[3][0] = x;
        camara[3][1] = y;
        camara[3][2] = z;
        camara[3][3] = 1;



    }
    if (keys[SDLK_d]) {

        glMatrixMode(GL_MODELVIEW);
        x = camara[3][0];
        y = camara[3][1];
        z = camara[3][2];

        camara[3][0] = 0;
        camara[3][1] = 0;
        camara[3][2] = 0;
        camara[3][3] = 1;
        glLoadMatrixf(&camara[0][0]);
        glRotatef(60.f * intervalo, 0.0f, 0.0f, 1.0f);
        glGetFloatv(GL_MODELVIEW_MATRIX, &camara[0][0]);
        camara[3][0] = x;
        camara[3][1] = y;
        camara[3][2] = z;
        camara[3][3] = 1;

    }




    return 0;
}


void input_mouse(void)
{


    float x, y, z;
    int mouse_x, mouse_y;       /* Coordenadas del rat�n */


    Uint8 *keys;

    keys = SDL_GetKeyState(NULL);

    if (SDL_WM_GrabInput(SDL_GRAB_QUERY) == SDL_GRAB_OFF)
        return;

    SDL_GetMouseState(&mouse_x, &mouse_y);

    glMatrixMode(GL_MODELVIEW);
    x = camara[3][0];
    y = camara[3][1];
    z = camara[3][2];

    camara[3][0] = 0;
    camara[3][1] = 0;
    camara[3][2] = 0;
    camara[3][3] = 1;
    glLoadMatrixf(&camara[0][0]);
    glRotatef((config.SCREEN_SIZE_X / 2 - (mouse_x)) * intervalo / 6.0f,
              0.0f, 1.0f, 0.0f);
    glRotatef(((mouse_y) - config.SCREEN_SIZE_Y / 2) * intervalo / 6.0f,
              1.0f, 0.0f, 0.0f);

    glGetFloatv(GL_MODELVIEW_MATRIX, &camara[0][0]);
    camara[3][0] = x;
    camara[3][1] = y;
    camara[3][2] = z;
    camara[3][3] = 1;



    /* Actualizaci�n de variables din�micas */

    velocidad = 10.0f - (10 / velocidad_r);

    camara[3][2] += (velocidad * intervalo * camara[2][2]);
    camara[3][1] += (velocidad * intervalo * camara[2][1]);
    camara[3][0] += (velocidad * intervalo * camara[2][0]);

    /*  Nave liebre */

/*  	nave1->x += (-0.5f * intervalo* nave1->base[2].x);
   	nave1->y += (-0.5f * intervalo* nave1->base[2].y);
  	nave1->z += (-0.5f * intervalo* nave1->base[2].z);

  	disparo_laser.posicion[0]+=(20.1f* intervalo* disparo_laser.direccion[0]);
  	disparo_laser.posicion[1]+=(20.1f* intervalo* disparo_laser.direccion[1]);
  	disparo_laser.posicion[2]+=(20.1f* intervalo* disparo_laser.direccion[2]);

  	if (disparo_laser.ttl>0)
  	   if (get_timer()-disparo_laser.ttl>5000)
  	         disparo_laser.ttl=0;

*/
}
