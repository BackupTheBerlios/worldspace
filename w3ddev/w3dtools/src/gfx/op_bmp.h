//==========================================================================
//  op_bmp.h  -  Cabecera del modulo de carga de BMP
//
//  begin     : sat apr 12 2003 / sab 12 abr 2003
//  copyright : (C) 2003 by Grupo WorldSpace
//  email     : eric@users.berlios.de
//==========================================================================
//                                                                         *
//   This program is free software; you can redistribute it and/or modify  *
//   it under the terms of the GNU General Public License as published by  *
//   the Free Software Foundation; either version 2 of the License, or     *
//   (at your option) any later version.                                   *
//                                                                         *
//==========================================================================

#ifndef _Carga_BMP_
#define _Carga_BMP_
//==========================================================================
#include "sdl_gl.h"
#include "w3d_base.h"

#define VALOR_MB  19778

#ifdef _LINUX
typedef long LONG;
typedef unsigned short int WORD;
typedef unsigned long int DWORD;
#endif                          // _LINUX

typedef struct stBitmapFicCab {
    WORD bfTipo;                // Cadena identificación "BM" (?).
    DWORD bfSize;               // Tamaño del fichero en bytes.
    WORD bfReservado1;          // Reservado, siempre a 0.
    WORD bfReservado2;          // Reservado, siempre a 0.
    DWORD bfBitsSuma;           // Corrección de la imagen en bytes.
} miBitmapFicCab;               // BITMAPFILEHEADER

typedef struct {
    byte bCad[14];
} miByte14;

typedef struct {
    DWORD bfSize;               // 4 Tamaño de BITMAPINFOHEADER ne bytes.
    LONG biAncho;               // 4 Ancho de la imagen en pixels.
    LONG biAlto;                // 4 Altura de la imagen en pixels
    WORD biPlanos;              // 2 Número de planos de color. siempre es 1.
    WORD biCuentaBits;          // 2 Número de bits de color
    DWORD biCompresion;         // 4 Tipo de compresión usada.
    DWORD biSizeImagen;         // 4 Tamaño de la imagen en bytes.
    LONG biXPxlsPorMetro;       // 4 Pixels por metro en horizontal.
    LONG biYPxlsPorMetro;       // 4 Pixels por metro en vertical.
    DWORD biColUsados;          // 4 Número de colores usados.
    DWORD biColImportantes;     // 4 Número de colores "importantes".
} miBitmapInfCab;               // BITMAPINFOHEADER

typedef struct {
    byte rgbAzul;
    byte rgbVerve;
    byte rgbRojo;
    byte rgbReservado;
} miRgbQuad;

typedef struct {
    miBitmapInfCab bmiHeader;
    miRgbQuad bmiColors[1];
} miBitmap;

SDL_Surface *carga_bmp_SDL(char *sFichero);

void *carga_bmp(char *sFichero, int *tam_x, int *tam_y);
//==========================================================================
#endif                          //_Carga_BMP_

//==========================================================================
//  Fin de op_bmp.h
//==========================================================================
