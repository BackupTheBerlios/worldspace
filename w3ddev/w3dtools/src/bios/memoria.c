//===========================================================================
//  memoria.c  -  Gestor de memoria
//
//  begin     : sat apr 12 2003 / sab 12 abr 2003
//  copyright : (C) 2003 by Grupo WorldSpace
//  email     : eric@users.berlios.de
//===========================================================================
//                                                                         *
//   This program is free software; you can redistribute it and/or modify  *
//   it under the terms of the GNU General Public License as published by  *
//   the Free Software Foundation; either version 2 of the License, or     *
//   (at your option) any later version.                                   *
//                                                                         *
//===========================================================================

#include <stdlib.h>
#include <string.h>

#include "globales.h"
#include "memoria.h"

//===========================================================================
//  Funciones generales de uso de memoria.
//===========================================================================
static int Bloques_asignados = 0;
static miMemoria * prMemoria = NULL;
//===========================================================================
//  Damos memoria. Utilizamos esta función porque ya controla
//  la salida por error.
//  Ahora le añadimos un registro de lo que se asigna para luego
//  poder liberar toda la memoria.
//===========================================================================
void * dar_m ( int iSize, char * sChivato )
{
	void * pBloc;
	int i;

	pBloc = malloc (iSize);
	if (pBloc==NULL)
	{
		log_msj("No hay memoria suficiente. Bloques asignados %d\n",
				  Bloques_asignados);
		// Lo mejor es terminar el programa, para liberar a las funciones
		// que llamen el control del error.
		return NULL;
	}

	if (prMemoria==NULL)
	{
		prMemoria = (miMemoria *) malloc(sizeof(miMemoria) * LIM_MEM);
		if (prMemoria==NULL)
		{
			log_msj("No hay memoria para el Vector de memoria\n");
			free(pBloc);
			return NULL;
		}
		for ( i=0; i<LIM_MEM; i++ )
		{
			prMemoria[i].iDes = -1;		// No se esta utilizando
			prMemoria[i].pSig = NULL;
			prMemoria[i].pMem = NULL;
			mInicio(prMemoria[i].sChivato);
		}
	}

	for ( i=0; i<LIM_MEM; i++ )
	{
		if (prMemoria[i].iDes == -1)
			break;
	}

	if (i==LIM_MEM)
	{
		free(pBloc);
		log_msj("Donde: [%s]\n", sChivato );
		log_msj("Hemos superado el límite de memoria de LIM_MEM : %d\n",
			LIM_MEM);
		log_msj("Aumenta el valor de LIM_MEM y recompila el programa\n");
		return NULL;
	}

	Bloques_asignados ++;
	prMemoria[i].iDes = i;
	prMemoria[i].pSig = NULL;	// No lo estamos utilizando POR AHORA
	prMemoria[i].pMem = pBloc;
	strncpy(prMemoria[i].sChivato, sChivato, sizeof(prMemoria[i].sChivato)-1);

	return pBloc;  // Si ha ido mal devuelve NULL.
}


// ==================================================================
//  Libera la memoria asignada por 'dar_m'.
// ==================================================================
void * liberar_m ( void * pBloc )
{
	if (pBloc)
	{
		int i;

		Bloques_asignados --;
		if (Bloques_asignados<0) Bloques_asignados = 0;
		free (pBloc);

		for ( i=0; i<LIM_MEM; i++ )
		{
			if (prMemoria[i].pMem == pBloc)
			{
				prMemoria[i].iDes = -1;
				prMemoria[i].pMem = NULL;
				prMemoria[i].pSig = NULL;
				mInicio(prMemoria[i].sChivato);
				break;
			}
		}

		if (i==LIM_MEM)
		{
			log_msj("Bloque de memoria no asignado por el gestor\n");
		}
	}
	return NULL;  // El puntero que quede inicializado a NULL.
}


//===========================================================================
//  Informa del numero de bloques asignados/asociados de memoria
//  Nos servirá para decirnos si estamos haciendo bien las cosas. Al final
//  de cada programa nos deberá dar 0.
//===========================================================================
int   bloques_asignados ( void )
{
	return Bloques_asignados;
}


//===========================================================================
//  Función con la que liberaremos lo que hayamos asignado con 'dar_m'.
//===========================================================================
void control_memoria ( void )
{
	if (prMemoria)
	{
		int i;

		if (Bloques_asignados)
			log_msj ("Bloques asignados: %d\n",  Bloques_asignados );

		for ( i=0; i<LIM_MEM; i++ )
		{
			if (prMemoria[i].iDes > -1)
			{
				prMemoria[i].iDes = -1;
				if (prMemoria[i].pSig)  free(prMemoria[i].pSig);
				prMemoria[i].pSig = NULL;
				if (prMemoria[i].pSig)  free(prMemoria[i].pMem);
				prMemoria[i].pMem = NULL;
				log_msj (" %2d [%s]\n", i, prMemoria[i].sChivato);
			}
		}

		free(prMemoria);
		prMemoria = NULL;
	}
}



//===========================================================================
//  Fin de memoria.c
//===========================================================================
