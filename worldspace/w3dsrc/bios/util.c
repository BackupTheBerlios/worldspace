//==========================================================================
//  util.c - Módulo de fucniones utiles. Deberían estar desplegadas en
//           el resto de los módulos, pero no se donde poner cada una.
//           Para saber que estas funciones vienen de este módulo la
//           letra inicial será la 'u' seguida por la inicial de la funcion
//           en mayusculas.
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
#include <ctype.h>
#include <string.h>

#include "sdl_gl.h"
#include "memoria.h"
#include "util.h"

//==========================================================================
//    email : eric@users.berlios.de
//==========================================================================
//  Pasamos una cadena a Mayusculas. Si estuvieramos en C++ debería ser una
//  función 'inline'.
//==========================================================================
void uMayusculas ( char * sCad )
{
	int i;
	for (i=0; sCad[i]!='\0'; i++ )
		sCad[i] = toupper(sCad[i]);
}


//==========================================================================
//    email : eric@users.berlios.de
//==========================================================================
//  Función de copia de cadenas. A diferencia de 'strcpy' asigna
//  memoria al destino. 'sCadena' debe de tener fin de cadena '\0'
//  para calcular bien su longitud.
//==========================================================================
char * uCopia_cadena ( char * sCadena )
{
	char * sDestino;

	sDestino = (char *) dar_m (strlen(sCadena)+1);
	strcpy (sDestino, sCadena);

	return sDestino;
}


//==========================================================================
//    email : eric@users.berlios.de
//==========================================================================
//  Función strtoken, al igual que 'strtok' separa una cadena
//  por separadores. Con dos diferencias:
//  - no modifica la cadena origen.
//  - 'strtok' toma dos separadores como uno solo, aquí se toman como
//    dos tokens.
//  Por esta última diferencia no se utiliza 'strtok'.
//==========================================================================
static char * sCadOrigen = NULL;   // Debería liberarse al final. ¿ Cómo ?
static int    iLonOrigen = 0;      // Longitud de 'sOrigen'
static int    iCurOrigen = 0;      // Posicion en 'sOrigen'
//==========================================================================
void uStrtoken ( char * sDestino, char * sOrigen, char * sSep )
{
	if (sOrigen != NULL)
	{
		iLonOrigen = strlen (sOrigen);
		iCurOrigen = 0;
		sCadOrigen = (char *) liberar_m (sCadOrigen);
		sCadOrigen = (char *) uCopia_cadena (sOrigen);
	}

	if (sCadOrigen != NULL)
	{
		int iLonSep, i, k, iCurAnterior;
		iLonSep = strlen(sSep);
		iCurAnterior = iCurOrigen;
		for ( i=iCurOrigen, k=0; i<iLonOrigen; i++, k++ )
		{
			if ( !strncmp(sCadOrigen+i, sSep, iLonSep) )
			{
				//if (!strcmp(sSep,"\n"))  k = ((k==0)? 0: k-1);
				strncpy (sDestino, sCadOrigen + iCurOrigen, k );
				iCurOrigen = i + iLonSep;
				break;
			}
		}
		if (iCurOrigen == iCurAnterior) // Si no cambia es que no lo encuentra.
		{
			strcpy(sDestino,sCadOrigen+iCurOrigen);  // Toda la cadena o el resto de ella.
		}
	}
}


//==========================================================================
//    email : eric@users.berlios.de
//==========================================================================
//  Funciones para salvar el estado de generación OpenGL en pila.
//==========================================================================
void uGuardarEstado ( void )
{
	int iNivelPilaEstados;
	int iMaxNivelPilaEstados;
	glGetIntegerv(GL_ATTRIB_STACK_DEPTH, &iNivelPilaEstados);
	glGetIntegerv(GL_MAX_ATTRIB_STACK_DEPTH, &iMaxNivelPilaEstados);
	if (iMaxNivelPilaEstados > iNivelPilaEstados)
		glPushAttrib (GL_ALL_ATTRIB_BITS);
}


void uRecuperarEstado ( void )
{
	int iNivelPilaEstados;
	glGetIntegerv(GL_ATTRIB_STACK_DEPTH, &iNivelPilaEstados);
	if (iNivelPilaEstados>0)
		glPopAttrib ();
}


void uRecuperarPila ( void )	// Dejamos la pila de estados vacía recuperando
{								// el estado original
	int iNivelPilaEstados;
	for ( glGetIntegerv(GL_ATTRIB_STACK_DEPTH, &iNivelPilaEstados);
	      iNivelPilaEstados>0 ;
		  glGetIntegerv(GL_ATTRIB_STACK_DEPTH, &iNivelPilaEstados)
		)
	{
		glPopAttrib ();
	}
}


//==========================================================================
//  Fin de util.c
//==========================================================================
