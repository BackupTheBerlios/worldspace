/***************************************************************************
                          display.c  -  description
                             -------------------
    begin                : Thu Nov 14 2002
    copyright            : (C) 2002 by neuralgya
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



#include "display.h"
#include "init_gl.h"
#include "../opengl.h"
#include "../global.h"


/*!

int sis_ini_display(void)

Inicialización del contexto OpenGL mediante SDL.
Abrirá la ventana SDL y le asignará un contexto OpenGL.
A su vez, llamará a la inicialización de OpenGL.
*/

int sis_ini_display(void)
{


    unsigned short int x_size, y_size;
    SDL_Surface *screen;


    x_size = config.SCREEN_SIZE_X;
    y_size = config.SCREEN_SIZE_Y;


    if (SDL_Init(SDL_INIT_VIDEO)!=1)
      	_sis_msj("[OK]\t\tSubsistema SDL_video inicializado\n");
    else {
       	_sis_msj("[KO]\\ttError inesperado en SDL_Init: ");
        _sis_msj(SDL_GetError());
        _sis_msj("\n");
        return NO;
    }

    /*SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 1 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 1 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 1 );
   SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8 );
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);*/
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    if (config.FULLSCREEN == 1) {
        screen =
            SDL_SetVideoMode(x_size, y_size, 16,
                             SDL_OPENGL | SDL_FULLSCREEN);
        if (!screen) {
            _sis_msj("[KO]\\ttNo se pudo inicializar OpenGL en pantalla completa ");
            _sis_msj(SDL_GetError());
            _sis_msj("\n");
            SDL_Quit();
            return NO;
        }
    } else {
        screen = SDL_SetVideoMode(x_size, y_size, 16, SDL_OPENGL);
        if (!screen) {
            _sis_msj("[KO]\\ttNo se pudo inicializar OpenGL en ventana ");
            _sis_msj(SDL_GetError());
            _sis_msj("\n");
            SDL_Quit();
            return -1;
        }
    }

    _sis_msj("[OK]\t\tContexto OpenGL inicializado\n");

		/* Cursor fuera */
    SDL_ShowCursor(0);

		/* Título de la ventana */
    SDL_WM_SetCaption("WorldSpace", "WorldSpace");

		/* Podemos fijar el ratón a nuestra aplicación aquí */
		SDL_WM_GrabInput(SDL_GRAB_OFF);

    /* Hacemos que el ratón se ponga en el centro de la pantalla */
		SDL_WarpMouse(config.SCREEN_SIZE_X/2, config.SCREEN_SIZE_Y/2);

    _sis_msj("[OK]\t\tContexto OpenGL preparado");


    /* Inicializamos OpenGL */

		if (!gl_basic_ini()) {
      _sis_msj("\n[KO]\t\t\tError inesperado inicializando OpenGL");
      return NO;
    }
    else {
      _sis_msj("\n[OK]\t\tOpenGL inicializado con éxito\n");

    }
		return SI;

}

/*!
Cierre el contexto gráfico
*/
int sis_cerrar_display(void)
{
    SDL_Quit();
    return SI;
}






  
  
