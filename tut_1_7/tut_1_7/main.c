/***************************************************************************
                          main.c  -  Función principal y de intercambio de buffers
                             -------------------
    begin                : mié jul 10 2002
    copyright            : (C) 2002 by neuralgya
    email                : neuralgya@mail.berlios.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include <stdio.h>
#include <stdlib.h>



#include "estructuras.h"
#include "opengl.h"
#include "w3d_api.h"
#include "sys_data.h"

unsigned int tiempo_antiguo, taux;
SDL_Event event;



/* Inicialización del contexto OpenGL mediante SDL */

int sys_init_display(void)
{


    unsigned short int x_size, y_size;
    SDL_Surface *screen;


    x_size = config.SCREEN_SIZE_X;
    y_size = config.SCREEN_SIZE_Y;


    if (SDL_Init(SDL_INIT_VIDEO)!=1)
      	sys_msg("[OK]\t\tSubsistema SDL_video inicializado\n");
    else {
       	sys_msg("[KO]\\ttError inesperado en SDL_Init\n");
        sys_msg(SDL_GetError());
        return -1;
    }


    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    if (config.FULLSCREEN == 1) {
        screen =
            SDL_SetVideoMode(x_size, y_size, 16,
                             SDL_OPENGL | SDL_FULLSCREEN);
        if (!screen) {
            sys_err("No se pudo inicializar OpenGL en pantalla completa\n");
            sys_err(SDL_GetError());
            SDL_Quit();
            return -1;
        }
    } else {
        screen = SDL_SetVideoMode(x_size, y_size, 16, SDL_OPENGL);
        if (!screen) {
            sys_err("No se pudo inicializar OpenGL en ventana\n");
            sys_err(SDL_GetError());
            SDL_Quit();
            return -1;
        }
    }
	
    sys_msg("[OK]\t\tSubsistema de video inicializado\n");

		/* Cursor fuera */
    SDL_ShowCursor(0);
	
		/* Título dela ventana */
    SDL_WM_SetCaption("WorldSpace", "WorldSpace");
		
		/* Podemos fijar el ratón a nuestra aplicación aquí */
		SDL_WM_GrabInput(SDL_GRAB_OFF);

    /* Hacemos que el ratón se ponga en el centro de la pantalla */
		SDL_WarpMouse(config.SCREEN_SIZE_X/2, config.SCREEN_SIZE_Y/2);

    sys_msg("[OK]\t\tContexto OpenGL preparado\n");

    /* Logo */

//    w3d_logo();

    /* Inicializamos OpenGL */

//		init_gl();


    return 0;
}


/*! Básicamente, el bucle principal.Usamos SDL */


void main_loop(void)
{
    int done;
    done = 0;
    while (done==0) {
        if (SDL_PollEvent(&event))

            if (event.type == SDL_QUIT)
                done = 1;

					

//        gl_renderiza_escena();
        SDL_GL_SwapBuffers();
    }

    /*! Cerramos el contexto OpenGL */
		SDL_Quit();


    return 0;



}

/*! El comienzo de todo.... */

#ifdef _LINUX
int main(int argc, char *argv[])
{
#endif
#ifdef _WIN32W3D
int WINAPI WinMain( HINSTANCE	hInstance,
					HINSTANCE	hPrevInstance,
					LPSTR		lpCmdLine,
					int 		nCmdShow)
{
#endif



    /* Inicialización del sistema de logs y configuración */
		system_init();
    sys_msg("[OK]\tSistema básico inicializado\n");

    	
    if (sys_init_display() != 0) {
        sys_err("No se pudo iniciar el Sistema gráfico\n");
        system_close();
        return -1;
    }


		sys_msg("[OK]\tSistema gráfico inicializado\n");

    main_loop();

		sys_msg("[OK]\tCierre satisfactorio\n");

    return 0;
}



