/*!!!!!!!!!!!!!!!!!!!!!!!!!!

Este fichero no es oficial, el oficial será el proporcionado por Loki

*/

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

/* XPM */
static const char *cursor_xpm[] = {
    "32 32 3 1",
    "  c None",
    ". c None",
    "X c #000000",
    /* XPM */
    "XX                              ",
    "X.X                             ",
    "X..X                            ",
    "X...X                           ",
    "X....X                          ",
    "X.....X                         ",
    "X......X                        ",
    "X.......X                       ",
    "X........X                      ",
    "X.........X                     ",
    "X..........X                    ",
    "X...........X                   ",
    "X............X                  ",
    "X.............X                 ",
    "X..............X                ",
    "XXXXXXXXXXXXXXXXX               ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "0,0"
};

static SDL_Cursor *init_system_cursor(const char *image[]);
SDL_Cursor *cursor;

/*!

int sis_ini_display(void)

Inicialización del contexto OpenGL mediante SDL.
Abrirá la ventana SDL y le asignará un contexto OpenGL.
A su vez, llamará a la inicialización de OpenGL.
*/

int ini_display(void)
{

    unsigned short int x_size, y_size;
    SDL_Surface *screen;
    SDL_Surface *icon;

    T_FUNC_IN x_size = configuracion.Xtam;
    y_size = configuracion.Ytam;

    if (SDL_Init(SDL_INIT_VIDEO) != 1)
        log_msj("[OK] ]Subsistema SDL_video inicializado\n");
    else {
        log_msj("[KO] Error inesperado en SDL_Init: %s\n", SDL_GetError());
        _return NO;
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    if (configuracion.FullScreen == 1) {
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

    cursor = init_system_cursor(cursor_xpm);
    SDL_SetCursor(cursor);

    /* Cursor fuera */
    SDL_ShowCursor(0);

    /* Título de la ventana */
    SDL_WM_SetCaption("WorldSpace", "WorldSpace");

    /* Podemos fijar el ratón a nuestra aplicación aquí */
    SDL_WM_GrabInput(SDL_GRAB_OFF);

    /* Hacemos que el ratón se ponga en el centro de la pantalla */
    SDL_WarpMouse(configuracion.Xtam / 2, configuracion.Ytam / 2);

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

/* Stolen from the mailing list */
/* Creates a new mouse cursor from an XPM */

static SDL_Cursor *init_system_cursor(const char *image[])
{
    int i, row, col;
    Uint8 data[4 * 32];
    Uint8 mask[4 * 32];
    int hot_x, hot_y;

    i = -1;
    for (row = 0; row < 32; ++row) {
        for (col = 0; col < 32; ++col) {
            if (col % 8) {
                data[i] <<= 1;
                mask[i] <<= 1;
            } else {
                ++i;
                data[i] = mask[i] = 0;
            }
            switch (image[4 + row][col]) {
            case 'X':
                data[i] |= 0x01;
                mask[i] |= 0x01;
                break;
            case '.':
                mask[i] |= 0x01;
                break;
            case ' ':
                break;
            }
        }
    }
    sscanf(image[4 + row], "%d,%d", &hot_x, &hot_y);
    return SDL_CreateCursor(data, mask, 32, 32, hot_x, hot_y);
}
