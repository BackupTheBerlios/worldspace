//==========================================================================
//  fuente.h  -  Cabecera  del módulo de carga de las fuentes.
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

#ifndef  _FUENTE_H_
#define  _FUENTE_H_
//==========================================================================
#include "w3d_base.h"

#ifndef __UINT__
#define __UINT__
typedef unsigned int uint;
#endif

typedef struct stFuente {
	uint    mapabits;			// Identificador del mapa/textura
	int     tam_base;			// Tamaño base
	int     espacio_base;		// Espacio base
	char    inicializado;		// 0=NO 1=SI
	int     iGrupo;				// 0 primer grupo, 1 segundo grupo.
	int     iTipo;				// Tipo de textura utilizada
	char    sFichero [256];		// Nombre del fichero de textura
	int     iAncho;				// Ancho y alto
	int     iAlto;				// del fichero Textura.
	float   fCoord [128][4];	// Coordenadas de cada letra
} miFuente;

typedef struct  {
	int        iNfuentes;		// Número de texturas.
	miFuente * vFuente;			// Lista de texturas.
} miLFuentes;

enum {
	eDef = 0,
	eAgulon ,
	eFont   ,
	NUM_FUENTES
};                   // Declaramos las fuentes especificas de la aplicacion

//==========================================================================
int  carga_listaFuentes ( miLFuentes * vListaFuentes );
int  carga_fuente       ( miFuente * Fuente );
int  imprime            ( miFuente Fuente, float x, float y, float tam, char *texto, ...);
int  imprimeC           ( miFuente Fuente, int Color, float x, float y, float tam, char *texto, ... );
void w_begin            ( void );
void w_end              ( void );
//==========================================================================
#endif   // _FUENTE_H_

//==========================================================================
//  Fin de fuente.h
//==========================================================================
