/***************************************************************************
                          op_tga.h  -  Cabecera de los ficheros TGA
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

#ifndef _Carga_TGA_
#define _Carga_TGA_
//==========================================================================
//¡ Utilizamos esta estructura para cargar TGA.!
//==========================================================================
typedef	struct
{
	GLubyte	* imageData;
	GLuint	  bpp;
	GLuint	  width;
	GLuint	  height;
	GLuint	  texID;
} miImagenTGA;

void * carga_tga ( char * sFichero, int * tam_x, int * tam_y );
//==========================================================================
#endif //_Carga_TGA_

//==========================================================================
//  Fin de op_tga.h
//==========================================================================
