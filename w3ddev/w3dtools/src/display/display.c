
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

#include "w3d_base.h"
#include "globales.h"
#include "sdl_gl.h"

SDL_Rect **resoluciones;
extern double matriz_proyeccion[4][4];
extern double matriz_proyeccion_ortogonal[4][4];

/*!
int ini_display(void)

Inicialización del contexto OpenGL mediante SDL.
Abrirá la ventana SDL y le asignará un contexto OpenGL.
A su vez, llamará a la inicialización de OpenGL.
*/

int ini_display(void)
{

    unsigned short int x_size, y_size, i, resolucion_ok = NO;
    SDL_Surface *screen;

    T_FUNC_IN x_size = configuracion.Xtam;
    y_size = configuracion.Ytam;

    if (SDL_Init(SDL_INIT_VIDEO) != 1)
	log_msj("[OK] Subsistema SDL_video inicializado\n");
    else {
	log_msj("[KO] Error inesperado en SDL_Init: %s\n", SDL_GetError());
	_return NO;
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    resoluciones = SDL_ListModes(NULL, SDL_OPENGL | SDL_FULLSCREEN);

    if (configuracion.FullScreen == 1) {

	/* Comprobamos que la resolucion es valida */
	for (i = 0; resoluciones[i]; ++i) {
	    if ((resoluciones[i]->w == x_size)
		&& (resoluciones[i]->h == y_size)) {
		T_FUNC_IN
		    log_msj
		    ("[display.c] La resolucion de %d x %d que has elegido es soportada por tu ordenador\n",
		     x_size, y_size);
		T_FUNC_OUT resolucion_ok = SI;
		break;
	    }
	}
	if (resolucion_ok == NO) {
	    log_msj
		("La resolucion del fichero w3d.ini no es válida, prueba con alguna de estas:\n");
	    for (i = 0; resoluciones[i]; ++i) {
		log_msj(" %d x %d \n", resoluciones[i]->w,
			resoluciones[i]->h);
	    }
	    SDL_Quit();
	    _return NO;
	}

	screen =
	    SDL_SetVideoMode(x_size, y_size, 16,
			     SDL_OPENGL | SDL_FULLSCREEN);
	if (!screen) {
	    log_msj
		("[KO] No se pudo inicializar OpenGL en pantalla completa %s\n",
		 SDL_GetError());
	    SDL_Quit();
	    _return NO;
	}
    } else {
	screen = SDL_SetVideoMode(x_size, y_size, 16, SDL_OPENGL);
	if (!screen) {
	    log_msj("[KO] No se pudo inicializar OpenGL en ventana %s\n",
		    SDL_GetError());
	    SDL_Quit();
	    _return NO;
	}
    }

    log_msj("[OK] Contexto OpenGL inicializado\n");

    /* Cursor desabilitado. Se utilizara el del GUI */
    SDL_ShowCursor(SDL_DISABLE);

    /* Título de la ventana */
    SDL_WM_SetCaption("WorldSpace", "WorldSpace");

    /* Podemos fijar el ratón a nuestra aplicación aquí */
    SDL_WM_GrabInput(SDL_GRAB_OFF);

    /* Hacemos que el ratón se ponga en el centro de la pantalla */
    SDL_WarpMouse((Uint16) (configuracion.Xtam / 2),
		  (Uint16) (configuracion.Ytam / 2));

    log_msj("[OK] SDL preparado\n");

    _return SI;

}

/*!
Cierre el contexto gráfico
*/
int cerrar_display(void)
{
    T_FUNC_IN SDL_Quit();

    _return SI;
}

/*!
Cambia la resolucion del contexto gráfico
*/
int cambia_display(int xdis, int ydis, int pan_completa)
{

    SDL_Surface *screen;

    T_FUNC_IN configuracion.Xtam = xdis;
    configuracion.Ytam = ydis;
    configuracion.FullScreen = pan_completa;

    /* Cambiamos la resolucion con los parametros pasados */
    if (configuracion.FullScreen == 1) {
	screen =
	    SDL_SetVideoMode(configuracion.Xtam, configuracion.Ytam, 16,
			     SDL_OPENGL | SDL_FULLSCREEN);
	if (!screen) {
	    log_msj
		("[KO] No se pudo inicializar OpenGL en pantalla completa %s\n",
		 SDL_GetError());
	    SDL_Quit();
	    _return NO;
	}
    } else {
	screen =
	    SDL_SetVideoMode(configuracion.Xtam, configuracion.Ytam, 16,
			     SDL_OPENGL);
	if (!screen) {
	    log_msj("[KO] No se pudo inicializar OpenGL en ventana %s\n",
		    SDL_GetError());
	    SDL_Quit();
	    _return NO;
	}
    }

    /* Redimensionamos la ventana y actualizamos las matrices de proyeccion */
    glViewport(0, 0, (GLsizei) configuracion.Xtam,
	       (GLsizei) configuracion.Ytam);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f,
		   (GLfloat) configuracion.Xtam /
		   (GLfloat) configuracion.Ytam, 0.01f, 100000.0f);
    glGetDoublev(GL_PROJECTION_MATRIX, &matriz_proyeccion[0][0]);
    glLoadIdentity();
    glOrtho(0, configuracion.Xtam, 0, configuracion.Ytam, -100, 100);
    glGetDoublev(GL_PROJECTION_MATRIX, &matriz_proyeccion_ortogonal[0][0]);
    glLoadMatrixd(&matriz_proyeccion[0][0]);

    return SI;
}
