/***************************************************************************
                          op_bmp.c  -  Carga de imagenes en formatos BMP
                             -------------------
    begin                : sat apr 12 2003 / sab 12 abr 2003
    copyright            : (C) 2003 by Grupo WorldSpace
    email                : eric@users.berlios.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
//==========================================================================
//  Carga de imagenes en formatos BMP
//==========================================================================
#include "memoria.h"
#include "globales.h"
#include "sdl_gl.h"
#include "op_bmp.h"

//==========================================================================
// Carga un fichero BMP. Devuelve un puntero al bitmap si hay exito,
// y NULL si no.
//==========================================================================
SDL_Surface * carga_bmp (char *sFichero)
{
    int i, j;
    Uint8 * rowhi, *rowlo;
    Uint8 * tmpbuf, tmpch;

    SDL_Surface *image;

    image = SDL_LoadBMP(sFichero);
    if ( image == NULL )
	{
        log_msj( "\n Incapaz de cargar %s: %s\n", sFichero, SDL_GetError());
        return(NULL);
    }

    /* GL surfaces are upsidedown and RGB, not BGR :-) */
    tmpbuf = (Uint8 *)dar_m(image->pitch);
    rowhi = (Uint8 *)image->pixels;
    rowlo = rowhi + (image->h * image->pitch) - image->pitch;
    for ( i=0; i<image->h/2; ++i ) {
        for ( j=0; j<image->w; ++j ) {
            tmpch = rowhi[j*3];
            rowhi[j*3] = rowhi[j*3+2];
            rowhi[j*3+2] = tmpch;
            tmpch = rowlo[j*3];
            rowlo[j*3] = rowlo[j*3+2];
            rowlo[j*3+2] = tmpch;
        }
        memcpy(tmpbuf, rowhi, image->pitch);
        memcpy(rowhi, rowlo, image->pitch);
        memcpy(rowlo, tmpbuf, image->pitch);
        rowhi += image->pitch;
        rowlo -= image->pitch;
    }
    liberar_m(tmpbuf);

    return(image);
}


//==========================================================================
//  Fin de op_bmp.c
//==========================================================================
