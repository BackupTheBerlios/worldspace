/***************************************************************************
                          init_gl.c  -  inicializaciones de opengl
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


#include "../opengl.h"
#include "../global.h"
#include "../engine/mad.h"
#include "logo.h"

/*!
  Esta funci�n muestra un logo por pantalla para demostrar que la inicializaci�n
  gr�fica OpenGL ha sido satisfactoria 
*/
int logo(void)
{
//    return SI;
    modelo *logo;
    float angulo = 0;
    GLfloat Ambient0[] = { 0.0f, 0.0f, 1.0f, 0.0f };
    GLfloat LightPosition0[] = { 1.0f, -1.0f, 1.0f, 0.0f };
    GLfloat Diffuse0[4];

    Diffuse0[3] = 1.0f;
    glLightfv(GL_LIGHT0, GL_AMBIENT, Ambient0);
    glLightfv(GL_LIGHT0, GL_POSITION, LightPosition0);
    glMatrixMode(GL_MODELVIEW);
    SDL_GL_SwapBuffers();
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    logo = carga_mad("logo.mad");

    while (angulo < 720) {
	Diffuse0[0] = angulo / 720.0f;
	Diffuse0[1] = (angulo - 360) / 720.0f;
	Diffuse0[2] = angulo / 360.0f;
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Diffuse0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glRotatef(angulo, 1.0f, 1.0f, 0.0f);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -(angulo / 34.28) + 1.0f);
	glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(-angulo / 2, 1.0f, 1.0f, 1.0f);
	render_mad(logo);
	SDL_GL_SwapBuffers();
	angulo += 2.0f;
    }
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    return SI;

}


/*! Inicializaci�n propia de OpenGL

Este c�digo es un poco complejo...glMatrixMode srive para indicar que vamos a modificar la matriz de proyecci�n.
glLoadIndentity() la resetea. Con gluPerspective lo que hacemos es indicar a OpenGL que vamos a utilizar perspectiva.
Esto hace que a medida que las cosas est�n m�s lejos se van haciendo m�s peque�as y tienden al centro. Esta perspectiva
har� que lo que veamos sea m�s realista. Adem�s, los dos �ltimos par�metros sirven para indicar que el rango de visivilidad
va desde .1 a 100. Es decir, lo que est� situado a m�s de 100 unidades de la c�mara no se ver

Esta versi�n de inicializaci�n es una versi�n b�sica.
*/


int gl_basic_ini(void)
{

    /* Vamos a preparar las matrices de proyecci�n */

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f,
		   (GLfloat) config.SCREEN_SIZE_X /
		   (GLfloat) config.SCREEN_SIZE_Y, 0.01f, 100000.0f);

    /* Esto resetea la matriz de modelado y la de la camara */


    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();


    /* Ahora establecemos el color de fondo por defecto. Est� en formato RGBA y lo ponemos a negro */

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    /* Estas 3 l�neas habilitan del Buffer de profundidad */

    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    /* Activaci�n del blending */

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    /* Esta funci�n sirve para optimizar el renderizado, y se utiliza para muchas cosas. En este caso es para
       hacer un buen c�lculo de la perspectiva perdiendo un poco de rendimiento */

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);


    /* Smooth shading */
    glShadeModel(GL_SMOOTH);

    /* Puntos difusos */

    glEnable(GL_POINT_SMOOTH);

    /* Cull faces - Las caras traseras se ignoran */

    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (logo())
	return SI;
    else
	return NO;

}
