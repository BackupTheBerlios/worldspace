/***************************************************************************
                          opengl.h  -  Inclusión de cabeceras OpenGL
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

/*!
Este fichero se utiliza para incluir las cabeceras opengl.
Como se ve, dependiendo del sistema, las cabeceras están
en un sitio u otro. El preprocesador del lcc y el Visual C
define la variable _WIN32. Entonces solo lee el código
entre ifdef _WIN32 y endif.
El makefile de Linux define la variable LINUX, leyendo el
compilador de Linux la otra parte
*/

#ifdef _WIN32							// Para windows
#include <windows.h>
#endif


#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>



#ifndef _OGLMAX
#define _OGLMAX

#define GL_PI 3.1415f
#endif
