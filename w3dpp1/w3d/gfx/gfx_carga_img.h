/***************************************************************************
                          gfx_carga_img.h  -  Carga de ficheros graficos
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


/*! Carga un TGA en memoria. El TGA debe cumplir las siguientes características:
Ser de 24 bits + Canal ALPHA. (32 bits) y SIN COMPRIMIR
El tamaño debe ser cuadrado (x=y) y 32x32 o 64x64 o 128x128 o 256x256
Devuelve un puntero a la imagen y el tamaño (variable tam) de la imagen.*/

extern void *carga_tga(char *filename,int *tam_x,int *tam_y);
