/***************************************************************************
                          sdl_gl.h  -  Inclusión de librerías SDL y GL
                             -------------------
    begin                : lun feb 10 2003
    copyright            : (C) 2003 by Grupo WorldSpace
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


#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif                          // WIN32
#if defined(__APPLE__) && defined(__MACH__)
#include <OpenGL/gl.h>          // Cabecera para la librería  OpenGL32
#include <OpenGL/glu.h>         // Cabecera para la librería  GLu32
#else                           /*  */
#include <GL/gl.h>              // Cabecera para la librería  OpenGL32
#include <GL/glu.h>             // Cabecera para la librería  GLu32
#endif                          // __APPLE__ && __MACH__
#include <SDL/SDL.h>