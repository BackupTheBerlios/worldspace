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

int sis_ini_display(void)
{


    unsigned short int x_size, y_size;
    SDL_Surface *screen;
    SDL_Surface *icon;
    char *path_icono;
    path_icono = prepara_apertura("img/icon.bmp");


    x_size = config.SCREEN_SIZE_X;
    y_size = config.SCREEN_SIZE_Y;

    if (SDL_Init(SDL_INIT_VIDEO) != 1)
        _sis_msj("\n[OK]\t\tSubsistema SDL_video inicializado\n");
    else {
        _sis_msj("[KO]\\ttError inesperado en SDL_Init: ");
        _sis_msj(SDL_GetError());
        _sis_msj("\n");
        return NO;
    }

    if ((icon = SDL_LoadBMP(path_icono)) != NULL) {
        SDL_SetColorKey(icon,
                        SDL_SRCCOLORKEY,
                        SDL_MapRGB(icon->format, 255, 255, 255));
        SDL_WM_SetIcon(icon, NULL);
    }


    /*SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 1 );
       SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 1 );
       SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 1 );
       SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8 );
       SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32); */
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    if (config.FULLSCREEN == 1) {
        screen =
            SDL_SetVideoMode(x_size, y_size, 16,
                             SDL_OPENGL | SDL_FULLSCREEN);
        if (!screen) {
            _sis_msj
                ("[KO]\\ttNo se pudo inicializar OpenGL en pantalla completa ");
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

    cursor = init_system_cursor(cursor_xpm);
    SDL_SetCursor(cursor);
    /* Cursor fuera */
    SDL_ShowCursor(0);

    /* Título de la ventana */
    SDL_WM_SetCaption("WorldSpace", "WorldSpace");

    /* Podemos fijar el ratón a nuestra aplicación aquí */
    SDL_WM_GrabInput(SDL_GRAB_OFF);

    /* Hacemos que el ratón se ponga en el centro de la pantalla */
    SDL_WarpMouse(config.SCREEN_SIZE_X / 2, config.SCREEN_SIZE_Y / 2);

    _sis_msj("[OK]\t\tContexto OpenGL preparado");


    /* Inicializamos OpenGL */

    if (!gl_basic_ini(SI)) {
        _sis_msj("\n[KO]\t\t\tError inesperado inicializando OpenGL");
        return NO;
    } else {
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
