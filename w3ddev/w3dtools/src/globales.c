//==========================================================================
//  globales.c - Módulo de declaración de las variables globales.
//               Se utilizarán en casi todos los módulos del programa
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

#include "color.h"
#include "fuente.h"
#include "textura.h"

//==========================================================================
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

//==========================================================================
miColor vPaleta[256 * 2];
float fFondo[] = { 0.0f, 0.0f, 0.0f, 1.0f };    // Negro

//==========================================================================

// ==================================================================
//  Fuentes.
// ==================================================================
#define PfCOORD  { 0.0f, 0.0f, 0.0f, 0.0f },

#define LfCOORD  PfCOORD PfCOORD PfCOORD PfCOORD \
                 PfCOORD PfCOORD PfCOORD PfCOORD

#define XfCOORD  LfCOORD LfCOORD LfCOORD LfCOORD \
                 LfCOORD LfCOORD LfCOORD LfCOORD \
                 LfCOORD LfCOORD LfCOORD LfCOORD \
                 LfCOORD LfCOORD LfCOORD LfCOORD
// ==================================================================
miFuente vFuente[] = {
    {0, 15, -3, 0, 0, FT2, "def.tga", 0, 0, {XfCOORD}},
    {0, 16, -4, 0, 0, FT2, "agulon.tga", 0, 0, {XfCOORD}},
    {0, 16, -2, 0, 0, AT1, "font.bmp", 0, 0, {XfCOORD}},
};                              //! Un par de fuentes...

miLFuentes vListaFuentes = { NUM_FUENTES, vFuente };

// ==================================================================

//==========================================================================
//  Fin de globales.c
//==========================================================================
