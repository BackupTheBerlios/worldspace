/***************************************************************************
                          fuentes.h  -  Carga e inicialización de las fuentes
                             -------------------
    begin                : Thu Nov 14 2002
    copyright            : (C) 2002 by neuralgya
    email                : neuralgya@users.berlios.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "../opengl.h"

#ifndef _FUENTES_STR          
#define _FUENTES_STR


/*! Estructura de las fuentes */
typedef struct FUENTE_tag {
	GLuint mapabits;
	int tam_base;
	int espacio_base;
	char inicializado;				
} FUENTE;

#endif 

/*!
tam_base es el tamaño base para esa fuente. Cuando se
utilice la función print, el tamaño que se especifique ahí
será en función de como se inicializó 
espacio_base es el espacio entre letras de cada fuente,
es bastante dependiente del tipo de fuente
*/

extern FUENTE *carga_fuente(char *fichero, int tam_base,int espacio_base);

/*!
Especificamos el tipo de fuente (previamente creado), su
posisición (-1,-1 a 1,1), el tamaño y el texto. Se pueden 
utilizar cadenas las cadenas de formato como printf(etc)
*/								
				
extern int print(FUENTE *fuente,float x, float y,float tam,char *texto, ...);

/*!
Adivina para que sirve esta función
*/

extern int ini_fuente(void);

									



