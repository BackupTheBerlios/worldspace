/***************************************************************************
                          memoria.h
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

#ifndef _Memoria_h_
#define _Memoria_h_
// ==================================================================
#define LIM_MEM	  60		// Tamaño del vector de bloques
#define mNULO(s)  if (s==NULL) return -1;

typedef struct stMem {
	int    iDes;			// Descriptor de memoria
	char   sChivato[32];	// Indica se quien es el bloque de memoria
	void * pMem;			// Puntero al bloque de memoria
	struct stMem * pSig;	// Puntero al siguiente bloque cuando se use
} miMemoria;

// ==================================================================
void * dar_m              ( int iSize, char * sDonde );
void * liberar_m          ( void * );
int    bloques_asignados  ( void );
void   control_memoria    ( void );
// ==================================================================
#endif // _Memoria_h_

//==========================================================================
//  Fin de memoria.h
//==========================================================================
