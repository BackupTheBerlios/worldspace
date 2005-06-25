/***************************************************************************
                          engine.c  -  Renderización y algoritmos 3D
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

#include <math.h>
#include <stdlib.h>

#include "sdl_gl.h"
#include "w3d_base.h"
#include "globales.h"
#include "mad.h"

static GLfloat fFondo[] = { 1.0f, 0.5f, 0.5f, 0.0f };

/*!
  Esta función muestra un logo por pantalla para demostrar que la inicialización
  gráfica OpenGL ha sido satisfactoria
*/
int logo(void)
{
    SDL_Event event;
    Uint8 *keys;
    int taux, iAlto, iAncho;
    int intervalo;
    modelo *logo;
    float fAngulo, fSize, fInc, fIter;
    GLfloat Ambient0[] = { 0.0f, 0.0f, 1.0f, 0.0f };
    GLfloat LightPosition0[] = { 1.0f, -1.0f, 1.0f, 0.0f };
    GLfloat Diffuse0[4];

    T_FUNC_IN;

    log_msj("[engine.c] Veamos ese logo...\n");
    Diffuse0[3] = 1.0f;
    glLightfv(GL_LIGHT0, GL_AMBIENT, Ambient0);
    glLightfv(GL_LIGHT0, GL_POSITION, LightPosition0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);

    logo = carga_mad("logo.mad");

    taux = SDL_GetTicks();
    iAncho = configuracion.Xtam;
    iAlto = configuracion.Ytam;
    fAngulo = fIter = fInc = fSize = 0.0f;

    while (fIter < 1000.0f) {
	glClearColor(fFondo[0], fFondo[1], fFondo[2], fFondo[3]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Diffuse0);

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -(fAngulo / 34.28f) + 1.0f);
	glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(-fAngulo / 2, 1.0f, 1.0f, 1.0f);
	if (logo != NULL)
	    render_mad(logo);
	glPopMatrix();

	SDL_GL_SwapBuffers();

	Diffuse0[0] = fAngulo / 1000.0f;
	Diffuse0[1] = (fAngulo - 360) / 1000.0f;
	Diffuse0[2] = fAngulo / 360.0f;

	fFondo[0] = (fFondo[0] > 0.0f) ? fFondo[0] - 0.002f : 0.0f;
	fFondo[1] = (fFondo[1] > 0.0f) ? fFondo[1] - 0.001f : 0.0f;
	fFondo[2] = (fFondo[2] > 0.0f) ? fFondo[2] - 0.001f : 0.0f;

	SDL_PollEvent(&event);
	keys = SDL_GetKeyState(NULL);
	if (keys[SDLK_ESCAPE]) {
	    break;
	}

	intervalo = SDL_GetTicks() - taux;
	taux = SDL_GetTicks();
	fInc = (float) ((intervalo * 1000.0f) / 2000.0f);
	fIter += fInc;
	if (fAngulo < 720.0f)
	    fAngulo += fInc;
	if (fSize < 3.0f)
	    fSize += 0.01f;
    }

    w_begin();
    //---------------------------------------------------
    imprime(vFuente[eAgulon], (float) iAncho * 0.32f, (float) iAlto * 0.9f,
	    2.0f, "WorldSpace");
    imprime(vFuente[eAgulon], (float) iAncho * 0.47f, (float) iAlto * 0.2f,
	    2.0f, "3D");
    //---------------------------------------------------
    w_end();

    while (1) {
	SDL_PollEvent(&event);
	keys = SDL_GetKeyState(NULL);
	if (keys[SDLK_ESCAPE]) {
	    break;
	}
	if (event.type == SDL_QUIT) {
	    log_msj(">>Abortado<<<");
	    exit(0);
	}
	SDL_Delay(15);
	SDL_GL_SwapBuffers();
    }
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    T_FUNC_OUT return SI;

}

/*!
Inicialización propia de OpenGL

Este código es un poco complejo...glMatrixMode srive para indicar que vamos a modificar la matriz de proyección.
glLoadIndentity() la resetea. Con gluPerspective lo que hacemos es indicar a OpenGL que vamos a utilizar perspectiva.
Esto hace que a medida que las cosas estén más lejos se van haciendo más pequeñas y tienden al centro. Esta perspectiva
hará que lo que veamos sea más realista. Además, los dos últimos parámetros sirven para indicar que el rango de visivilidad
va desde .1 a 100. Es decir, lo que esté situado a más de 100 unidades de la cámara no se ver
Esta versión de inicialización es una versión básica.
!*/
int ini_gl(char show_logo)
{

    /* Esto resetea la matriz de modelado y la de la camara */

    T_FUNC_IN glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f,
		   (GLfloat) configuracion.Xtam /
		   (GLfloat) configuracion.Ytam, 0.01f, 100000.0f);

    glGetDoublev(GL_PROJECTION_MATRIX, &matriz_proyeccion[0][0]);

    glLoadIdentity();

    glLoadIdentity();
    glOrtho(0, configuracion.Xtam, 0, configuracion.Ytam, -100, 100);
    glGetDoublev(GL_PROJECTION_MATRIX, &matriz_proyeccion_ortogonal[0][0]);

    glLoadMatrixd(&matriz_proyeccion[0][0]);

    log_msj("[engine.c] Matrices de proyección creadas\n");

    /* Ahora establecemos el color de fondo por defecto. Está en formato RGBA y lo ponemos a negro */

    //glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    //glClearColor(1.0f, 0.5f, 0.5f, 0.0f);
    glClearColor(fFondo[0], fFondo[1], fFondo[2], fFondo[3]);

    /* Estas 3 líneas habilitan del Buffer de profundidad */

    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    /* Activación del blending */

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    /* Esta función sirve para optimizar el renderizado, y se utiliza para muchas cosas. En este caso es para
       hacer un buen cálculo de la perspectiva perdiendo un poco de rendimiento */

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    /* Smooth shading */
    glShadeModel(GL_SMOOTH);

    /* Puntos difusos */

    glEnable(GL_POINT_SMOOTH);

    /* Cull faces - Las caras traseras se ignoran */

    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (show_logo)
	logo();

    log_msj("[OK] OpenGL inicializado\n");

    T_FUNC_OUT return SI;

}

int ini_engine()
{

    T_FUNC_IN SDL_ShowCursor(0);
    SDL_WM_GrabInput(SDL_GRAB_ON);
    ini_gl(NO);

    glGetFloatv(GL_MODELVIEW_MATRIX, &camara[0][0]);
    camara[2][2] = 1.0f;
    camara[3][0] = ((rand() % 100) - 50.0f);
    camara[3][1] = ((rand() % 100) - 50.0f);
    camara[3][2] = ((rand() % 100) - 50.0f);

    /*
       id_textura_crosshair = encola_textura("crosshair.tga", GL_RGBA);
       id_textura_localizador = encola_textura("localizador.tga", GL_RGBA);

       if (!genera_texturas(GL_LINEAR)) {
       _sis_msj("\n\t\t\tError generando texturas [KO]");
       return NO;
       } else
       _sis_msj("\n[OK]\t\t\tTexturas Generadas");

       glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient0);
       glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse0);
       glLightfv(GL_LIGHT0, GL_POSITION, LightPosition0);

       glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient1);
       glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse0);

       glEnable(GL_LIGHT0);
       glEnable(GL_LIGHT1);

     */

    T_FUNC_OUT return SI;
}
