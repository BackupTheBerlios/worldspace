//==========================================================================
//  texturas.h  -  Cabecera del modulo de texturas
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

#ifndef _wTextura_h_
#define _wTextura_h_
//==========================================================================
#define LIM_TEXTURAS      100
#define TIPO_TEXTURA_NUM  AT0 = 0, AT1, FT0, FT1, FT2
#define TIPO_TEXTURA_CAD  "AT0", "AT1", "FT0", "FT1", "FT2"
#define TIPO_TEXTURA_LIM  5

enum { TIPO_TEXTURA_NUM };  // Tipo de texturas (enumerado)

typedef struct stTex {
	int    iNText;			// Número Identificador de la textura.
	int    iTipo;			// Tipo de textura.
	int    iAncho;			// X
	int    iAlto;			// Y
	char   sFichero[256];	// Nombre fichero de la textura.
	struct stTex * pSig;	// Puntero a sig, para utilizar en una lista.
} miTextura;

typedef struct  {
	int         iNtexturas; // Número de texturas.
	miTextura * vTextura;   // Lista de texturas.
} miLTexturas;

//==========================================================================
int  encola_textura       ( miTextura * prTextura );
void cerrar_texturas      ( void );
int  carga_listaTexturas  ( miLTexturas * prListaTexturas );
int  genera_texturas      ( void );
int  carga_texturas       ( void );
int  carga_textura        ( miTextura * prTextura );
void activa_textura       ( int iTextura );
//==========================================================================
#endif //_wTextura_h_

//==========================================================================
//  Fin de textura.h.
//==========================================================================
