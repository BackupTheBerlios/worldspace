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
#include "audio.h"

/*!
================================== DECLARACION DE VARIABLES
!*/

/*!
Matrices de proyección. aquí se guardan un par de matrices de proyección.
Esto nos permite ahorrarnos unas cuantas llamadas a gluPerspective.
!*/
double matriz_proyeccion[4][4];
double matriz_proyeccion_ortogonal[4][4];

/*!
Esta matriz es una de las más importantes, ya que referenciará siempre la
posición del observador, osea, nosotros
!*/

float camara[4][4];

/*!
  Esta función muestra un logo por pantalla para demostrar que la inicialización
  gráfica OpenGL ha sido satisfactoria
*/
int logo(void)
{

    T_FUNC_IN SDL_Event event;
    Uint8 *keys;

    modelo *logo;
    float angulo = 0;
    GLfloat Ambient0[] = { 0.0f, 0.0f, 1.0f, 0.0f };
    GLfloat LightPosition0[] = { 1.0f, -1.0f, 1.0f, 0.0f };
    GLfloat Diffuse0[4];
    ALfloat SonPosition [] = {0.0,0.0,0.0};
    ALfloat SonVelocidad [] = {1.0,1.0,1.0};

    log_msj("[engine.c] Veamos ese logo...\n");
    Diffuse0[3] = 1.0f;
    glLightfv(GL_LIGHT0, GL_AMBIENT, Ambient0);
    glLightfv(GL_LIGHT0, GL_POSITION, LightPosition0);
    glMatrixMode(GL_MODELVIEW);
    SDL_GL_SwapBuffers();
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    logo = carga_mad("logo.mad");
    carga_sonido("ws_datos/sonidos/logo.wav",1);

    reproducir_sonido(1, SonPosition, SonVelocidad,1.0,1.0,100.0,AL_FALSE);

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
        if (logo != NULL)
            render_mad(logo);
        SDL_GL_SwapBuffers();
        angulo += 2.0f;

        SDL_PollEvent(&event);
        keys = SDL_GetKeyState(NULL);
        if (keys[SDLK_ESCAPE]) {
            //print("ESC\n");
            break;
        }

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

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

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
    camara[3][0] = ((rand() % 100) - 50);
    camara[3][1] = ((rand() % 100) - 50);
    camara[3][2] = ((rand() % 100) - 50);

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
