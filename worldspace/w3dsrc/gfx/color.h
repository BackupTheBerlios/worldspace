//==========================================================================
//  color.h  -  Cabecera del m�dulo de definici�n de colores.
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

#ifndef  _COLOR_H_
#define  _COLOR_H_
//==========================================================================
#include "sdl_gl.h"

enum {
	//===========
	cNEGRO = 256,    // Vamos a reservar los primerors 256 n�meros
	cAZUL       ,    // en una �nica estructura vPaleta. Por si apareciera
	cAZUL_O     ,    // HW con paleta.
	cVERDE      ,    // Por ahora, solo ser� una reserva, falta el c�digo
	cVERDE_O    ,    // que rellene esos valores cuando se encuentre.
	cROJO       ,
	cROJO_O     ,    // El c�digo que inicia estos valores est� en
	cAMARILLO   ,    // 'wInicio_colores'
	cAMARILLO_B ,
	cCIAN       ,
	cGRIS       ,
	cBLANCO     ,
	cVIOLETA    ,
	cMARRON     ,
	cSOMBRA     ,
	cFONDO      ,
	//===========
	cGRIS_T     ,    // Apartir de aqu� estan los transparentes
	cAZUL_T     ,    // Funci�n de transparencia: glBlendFunc (GL_SRC_ALPHA,GL_ONE);
	cROJO_T     ,
	cVERDE_T    ,
	cBLANCO_T   ,
	//===========
	cBLANCO_TT  ,    // SuperTrasparente
	//===========
	cNUM_COLORES     // Definimos el limite actual de los colores.
};                   // Definimos los colores espec�ficos de la aplicacion.
                     // Ver funcion wInicio_colores.

#define Col_Trans  cGRIS_T
#define cNO_COLOR  cNUM_COLORES
#define muColor(c)  if ((c)<cNO_COLOR)  glColor4ubv (vPaleta[(c)].vCol)

typedef struct {
	/* GLubyte cRojo; GLubyte cVerde; GLubyte cAzul; GLfloat Alpha; */
	GLubyte vCol[4];
} miColor;

int ini_colores  ( void );
//==========================================================================
#endif   // _COLOR_H_

//==========================================================================
//  Fin de color.h
//==========================================================================
