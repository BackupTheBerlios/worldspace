/***************************************************************************
                          memoria.c  -  Gestor de memoria
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
// ==================================================================
//  memoria.c
// ==================================================================
#include <stdlib.h>

#include "globales.h"

// ==================================================================
//  Funciones generales de uso de memoria.
// ==================================================================
static int Bloques_asignados = 0;
// ==================================================================
//  Damos memoria. Utilizamos esta función porque ya controla
//  la salida por error.
// ==================================================================
void * dar_m ( int iSize )
{
	void * pBloc;
	pBloc = malloc (iSize);
	if (pBloc==NULL)
	{
		log_msj("No hay memoria suficiente. Bloques asignados %d",
				  Bloques_asignados);
		// Lo mejor es terminar el programa, para liberar a las funciones
		// que llamen el control del error.
	}
	else
		Bloques_asignados ++;

	return pBloc;  // Si ha ido mal devuelve NULL.
}


// ==================================================================
//  Libera la memoria asignada por 'DarM'.
// ==================================================================
void * liberar_m ( void * pBloc )
{
	if (pBloc)
	{
		Bloques_asignados --;
		if (Bloques_asignados<0) Bloques_asignados = 0;
		free (pBloc);
	}
	return NULL;  // El puntero que quede inicializado a NULL.
}


// ==================================================================
//  Informa del numero de bloques asignados/asociados de memoria
// ==================================================================
int   bloques_asignados ( void )
{
	return Bloques_asignados;
}



// ==================================================================
//  Fin de wMemoria.c
// ==================================================================
