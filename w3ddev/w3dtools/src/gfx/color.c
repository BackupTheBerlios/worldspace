//==========================================================================
//  color.c  -  Módulo de definición de colores.
//              Nos permite definir cualquier color y utilizarlo.
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
#include "globales.h"

//==========================================================================
//  Mantenemos los colores de vPaleta.
//  Nos sirve si no tenemos definida por paleta, para tener identificado
//  los colores por un único valor entre 0 y 255.
//==========================================================================
#define vROJO   vCol[0]
#define vVERDE  vCol[1]
#define vAZUL   vCol[2]
#define vALPHA  vCol[3]
//==========================================================================
int ini_colores  ( void )
{
	float F[3];
	int i;

	for ( i=256; i<256*2; i++ )
	{
		vPaleta[i].vROJO  = 0;
		vPaleta[i].vVERDE = 0;
		vPaleta[i].vAZUL  = 0;
		vPaleta[i].vALPHA = 255;
	}
	// cNegro
	// cRojo
	vPaleta[cROJO].vROJO  = 255;
	vPaleta[cROJO].vVERDE =   0;
	vPaleta[cROJO].vAZUL  =   0;
	// cRojo_o
	vPaleta[cROJO_O].vROJO  = 160;
	vPaleta[cROJO_O].vVERDE =   0;
	vPaleta[cROJO_O].vAZUL  =   0;
	// cVerde
	vPaleta[cVERDE].vROJO  =   0;
	vPaleta[cVERDE].vVERDE = 255;
	vPaleta[cVERDE].vAZUL  =   0;
	// cVerde_o
	vPaleta[cVERDE_O].vROJO  =   0;
	vPaleta[cVERDE_O].vVERDE = 160;
	vPaleta[cVERDE_O].vAZUL  =   0;
	// cAzul
	vPaleta[cAZUL].vROJO  =   0;
	vPaleta[cAZUL].vVERDE =   0;
	vPaleta[cAZUL].vAZUL  = 255;
	// cAzul_o
	vPaleta[cAZUL_O].vROJO  =   0;
	vPaleta[cAZUL_O].vVERDE =   0;
	vPaleta[cAZUL_O].vAZUL  = 160;
	// cAMARILLO
	vPaleta[cAMARILLO].vROJO  = 255;
	vPaleta[cAMARILLO].vVERDE = 255;
	vPaleta[cAMARILLO].vAZUL  =   0;
	// cAMARILLO_B (Brillante)
	vPaleta[cAMARILLO_B].vROJO  = 255;
	vPaleta[cAMARILLO_B].vVERDE = 255;
	vPaleta[cAMARILLO_B].vAZUL  = 128;
	// cCIAN
	vPaleta[cCIAN].vROJO  =   0;
	vPaleta[cCIAN].vVERDE = 255;
	vPaleta[cCIAN].vAZUL  = 255;
	// cGRIS
	vPaleta[cGRIS].vROJO  = 192;
	vPaleta[cGRIS].vVERDE = 192;
	vPaleta[cGRIS].vAZUL  = 192;
	// cVIOLETA
	vPaleta[cVIOLETA].vROJO  = 255;
	vPaleta[cVIOLETA].vVERDE =   0;
	vPaleta[cVIOLETA].vAZUL  = 255;
	// cMarron
	vPaleta[cMARRON].vROJO  = 208;
	vPaleta[cMARRON].vVERDE = 144;
	vPaleta[cMARRON].vAZUL  = 112;
	// cBlanco
	vPaleta[cBLANCO].vROJO  = 255;
	vPaleta[cBLANCO].vVERDE = 255;
	vPaleta[cBLANCO].vAZUL  = 255;
	// cSombra
	vPaleta[cSOMBRA].vROJO  = 95;
	vPaleta[cSOMBRA].vVERDE = 95;
	vPaleta[cSOMBRA].vAZUL  = 95;
	// =================================
	//  Transparentes
	// =================================
	// cGris_T
	vPaleta[cGRIS_T].vROJO  = 192;
	vPaleta[cGRIS_T].vVERDE = 192;
	vPaleta[cGRIS_T].vAZUL  = 192;
	vPaleta[cGRIS_T].vALPHA = 160;
	// cAzul_T
	vPaleta[cAZUL_T].vROJO  =   0;
	vPaleta[cAZUL_T].vVERDE =   0;
	vPaleta[cAZUL_T].vAZUL  = 255;
	vPaleta[cAZUL_T].vALPHA =  80;
	// cRojo_T
	vPaleta[cROJO_T].vROJO  = 255;
	vPaleta[cROJO_T].vVERDE =   0;
	vPaleta[cROJO_T].vAZUL  =   0;
	vPaleta[cROJO_T].vALPHA = 160;
	// cVerde_T
	vPaleta[cVERDE_T].vROJO  =   0;
	vPaleta[cVERDE_T].vVERDE = 255;
	vPaleta[cVERDE_T].vAZUL  =   0;
	vPaleta[cVERDE_T].vALPHA = 160;
	// cBlanco_T
	vPaleta[cBLANCO_T].vROJO  = 255;
	vPaleta[cBLANCO_T].vVERDE = 255;
	vPaleta[cBLANCO_T].vAZUL  = 255;
	vPaleta[cBLANCO_T].vALPHA =  96;
	// =================================
	//  Mas Transparentes
	// =================================
	// cBlanco_T
	vPaleta[cBLANCO_TT].vROJO  = 255;
	vPaleta[cBLANCO_TT].vVERDE = 255;
	vPaleta[cBLANCO_TT].vAZUL  = 255;
	vPaleta[cBLANCO_TT].vALPHA =  24;

	// =================================
	//  Fondo
	// =================================
	F[0] = (fFondo[0]*10 * 255)/10;
	F[1] = (fFondo[1]*10 * 255)/10;
	F[2] = (fFondo[2]*10 * 255)/10;
	vPaleta[cFONDO].vROJO  = (255 * fFondo[0] > 255)? 255: (byte) F[0];
	vPaleta[cFONDO].vVERDE = (255 * fFondo[1] > 255)? 255: (byte) F[1];
	vPaleta[cFONDO].vAZUL  = (255 * fFondo[2] > 255)? 255: (byte) F[2];

	return 0;
}


//==========================================================================
//  Fin de color.c
//==========================================================================
