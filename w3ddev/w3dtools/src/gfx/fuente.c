//==========================================================================
//  fuente.c  -  Módulo de carga de las fuentes, para poder mandar mensajes
//               y escribir.
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

#include "globales.h"
#include "conf_parser.h"
#include "carga_imagen.h"
#include "textura.h"
#include "fuente.h"
#include "util.h"
#include "memoria.h"
#include <stdarg.h>
#include <string.h>

//==========================================================================
//  Variables internas del módulo
//==========================================================================
static char sDirFuentes[LON_BUFF] = { WDIR_FUENTES };
//==========================================================================


//==========================================================================
//  Llama a carga_fuente para cada fuente especificada.
//==========================================================================
int carga_listaFuentes ( miLFuentes * vLisFuentes )
{
	int i;

	T_FUNC_IN;

	log_msj ("# Cargando fuentes..\n");

	mInicio(sDirFuentes);
	sprintf(sDirFuentes,"%s/", configuracion.sDirFuentes );

	for ( i=0; i<vLisFuentes->iNfuentes; i++ )
	{
		if (carga_fuente (&vLisFuentes->vFuente[i]))
		{
			_return -1;
		}
	}
   
	log_msj ("# Fuentes cargadas..\n");

	_return 0;
}


//==========================================================================
//  Carga en una textura el mapa de fuentes, y rellena una
//  estructura miFuente. Se crea una textura y un mapa de coordenadas
//  de 128*4 elementos donde se almacenan las coordenadas para cada
//  carácter. El mapa de fuentes es un TGA de 256x256 con canal
//  ALPHA. Mirar en el directorio fuentes.
//==========================================================================
//  He añadido la carga de una fuente en un fichero BMP, por ahora
//  asociada a una textura sin canal ALPHA.
//==========================================================================
int  carga_fuente   ( miFuente * prFuente )
{
	int          i, j, k;          // Indices.
	miFic_imagen rFic_imagen;

	T_FUNC_IN;

	mInicio(rFic_imagen.sFichero);
	sprintf(rFic_imagen.sFichero,"%s%s", sDirFuentes, prFuente->sFichero);

	prFuente->mapabits = encola_textura (rFic_imagen.sFichero, prFuente->iTipo);
	if (prFuente->mapabits < 0)
	{ _return -1; }

	rFic_imagen.iAlto  = rFic_imagen.iAncho = rFic_imagen.iTipo  = 0;
	rFic_imagen.pDatos = NULL;

	if ( carga_imagen (&rFic_imagen) )
	{ _return -1; }

	prFuente->iAncho   = rFic_imagen.iAncho;
	prFuente->iAlto    = rFic_imagen.iAlto;
    rFic_imagen.pDatos = liberar_m(rFic_imagen.pDatos);
 
	// Ahora establecemos las coordenadas.
	for ( k=0, j=1; j<(prFuente->iAlto/2); j+=16 )
	{
		for ( i=0; i<prFuente->iAncho; i+=16 )
		{
			switch (prFuente->iTipo)
			{
				case FT2:   // Fuente TGA
					prFuente->fCoord[k][0] = (float) i / (float) prFuente->iAncho;
					prFuente->fCoord[k][1] = (float) j / (float) prFuente->iAlto;
					prFuente->fCoord[k][2] = (float) i / (float) prFuente->iAncho + (float) 15/(float)prFuente->iAncho;
					prFuente->fCoord[k][3] = (float) j / (float) prFuente->iAlto  + (float) 15/(float)prFuente->iAlto;
					break;
				case AT1:   // Fuente BMP
					prFuente->fCoord[k][0] = (float) i / (float) prFuente->iAncho;
					prFuente->fCoord[k][1] = 0.5f - ((float) j / (float) prFuente->iAlto);
					prFuente->fCoord[k][2] = (float) i / (float) prFuente->iAncho + (float) 15/(float)prFuente->iAncho;
					prFuente->fCoord[k][3] = 0.5f - ((float) j / (float) prFuente->iAlto  + (float) 15/(float)prFuente->iAlto);
					break;
			}
			k++;
		}
	}
	
	prFuente->inicializado = 1;

	_return 0;
}


//==========================================================================
// Imprime un texto con la fuente que se le pasa. Como vemos, esta
// función admite un número indeterminado de parámetros que se
// parsean al principio. Los últimos parametros son los de
// formato de cadenas, como el printf
//==========================================================================
int imprime ( miFuente rFuente, float x, float y, float tam, char *texto, ... )
{
	char	text[1024];		// almacena el texto a escribir
	va_list	ap;				// puntero a la lista de argumentos (los ...)
	int     i, iLon;
	float   fGrupo;

	if (texto == NULL)			// si no hay texto
		return 0;				// nos vamos

	if (rFuente.inicializado!=1) // si la fuente no está cargada
		return 0;               // tambien nos vamos

	va_start(ap, texto);		// Busca variables en el texto
	vsprintf(text, texto, ap);	// y las sustituye por su valor
	va_end(ap);					// almacenando el resultado en text

	iLon=strlen(text);
	fGrupo = (rFuente.iGrupo)? 0.5f: 0.0f;

	if (rFuente.iTipo==AT1)  // Fuente BMP sin canal Alpha
	{
		uGuardarEstado ();
		glEnable    (GL_BLEND);				// Transparencia activada. ¿Función por defecto?
		glBlendFunc (GL_SRC_ALPHA,GL_ONE);	// Seleccionamos la función de transparencia.
	}
	glBindTexture(GL_TEXTURE_2D, rFuente.mapabits);

	// Aquí se renderiza el plano y su textura.
	for ( i=0; i<iLon; i++ )
	{
		glBegin(GL_QUADS);
			glTexCoord2f( rFuente.fCoord[(text[i]-32)][0], rFuente.fCoord[(text[i]-32)][3] + fGrupo);	glVertex2f(x                     , y-rFuente.tam_base*tam );
			glTexCoord2f( rFuente.fCoord[(text[i]-32)][2], rFuente.fCoord[(text[i]-32)][3] + fGrupo);	glVertex2f(x+rFuente.tam_base*tam, y-rFuente.tam_base*tam );
			glTexCoord2f( rFuente.fCoord[(text[i]-32)][2], rFuente.fCoord[(text[i]-32)][1] + fGrupo);	glVertex2f(x+rFuente.tam_base*tam, y                      );
			glTexCoord2f( rFuente.fCoord[(text[i]-32)][0], rFuente.fCoord[(text[i]-32)][1] + fGrupo);	glVertex2f(x                     , y                      );
		glEnd();
		x += rFuente.tam_base * tam + rFuente.espacio_base * tam;
	}
	if (rFuente.iTipo==AT1) uRecuperarEstado ();  // Fuente BMP sin canal Alpha
	return 0;
}	


//==========================================================================
//  Es igual que la anterior, pero para las fuentes BMP para
//  introducirles distinto color en un nuevo parámetro.
//==========================================================================
int imprimeC ( miFuente rFuente, int Color, float x, float y, float tam, char *texto, ... )
{
	char	text[1024];		// almacena el texto a escribir
	va_list	ap;				// puntero a la lista de argumentos (los ...)
	int     i, iLon;
	float   fGrupo;

	if (texto == NULL)			// si no hay texto
		return 0;				// nos vamos

	if (rFuente.inicializado!=1) // si la fuente no está cargada
		return 0;               // tambien nos vamos

	va_start(ap, texto);		// Busca variables en el texto
	vsprintf(text, texto, ap);	// y las sustituye por su valor
	va_end(ap);					// almacenando el resultado en text

	iLon=strlen(text);
	fGrupo = (rFuente.iGrupo)? 0.5f: 0.0f;

	uGuardarEstado ();
	muColor(Color);
	glEnable     (GL_BLEND);			  // Transparencia activada. ¿Función por defecto?
	glBlendFunc  (GL_SRC_ALPHA,GL_ONE);	  // Seleccionamos la función de transparencia.
	glBindTexture(GL_TEXTURE_2D, rFuente.mapabits);

	// Aquí se renderiza el plano y su textura.
	for ( i=0; i<iLon; i++ )
	{
		glBegin(GL_QUADS);
			glTexCoord2f( rFuente.fCoord[(text[i]-32)][0], rFuente.fCoord[(text[i]-32)][3] + fGrupo);	glVertex2f(x                     , y-rFuente.tam_base*tam );
			glTexCoord2f( rFuente.fCoord[(text[i]-32)][2], rFuente.fCoord[(text[i]-32)][3] + fGrupo);	glVertex2f(x+rFuente.tam_base*tam, y-rFuente.tam_base*tam );
			glTexCoord2f( rFuente.fCoord[(text[i]-32)][2], rFuente.fCoord[(text[i]-32)][1] + fGrupo);	glVertex2f(x+rFuente.tam_base*tam, y                      );
			glTexCoord2f( rFuente.fCoord[(text[i]-32)][0], rFuente.fCoord[(text[i]-32)][1] + fGrupo);	glVertex2f(x                     , y                      );
		glEnd();
		x += rFuente.tam_base * tam + rFuente.espacio_base * tam;
	}
	uRecuperarEstado ();
	return 0;
}	


//===========================================================================
//  Generalmente, los 'imprime' están pensados para realizar en proyección
//  ortogonal y con una serie de estados determinados de OpenGL.
//  Suministramos las funciones wBenginE y wEndE para que nos faciliten
//  estas operaciones.
//
//	w_begin();
//		...
//		imprime (fuente, X, Y, "formato printf", variables );
//		..
//  w_end();
//
//	De igual manera nos serviría para dibujar cualquier cosa en primer plano.
//
//===========================================================================
//  Lo utilizamos para poder iniciar las escrituras de las fuentes.
//  Utilizo la variable bEscritura para decidir si está iniciada el bloque
//  de escritura.
//  Con wEndE se restablece la situación anterior.
//===========================================================================
static byte bEscritura = NO;				// No = 0 = false
static int  iMatrizAct = GL_MODELVIEW;
//===========================================================================
void w_begin ( void )
{
	if (bEscritura == NO)		// Si NO está activo
	{
		bEscritura = SI;
		glGetIntegerv(GL_MATRIX_MODE, &iMatrizAct);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();			//
		uGuardarEstado ();		// Guardamos estado y matriz de proyección.
		glLoadMatrixd(&matriz_proyeccion_ortogonal[0][0]);		// Matriz en primer plano.
		glEnable(GL_TEXTURE_2D);
 		glDisable(GL_LIGHTING);
  		glDisable(GL_DEPTH_TEST);
	}
}


//===========================================================================
void w_end ( void )
{
	if (bEscritura == SI)			// Si SI que está activo
	{
		bEscritura = NO;
		uRecuperarEstado ();			// Recuperamos estado openGL anterior
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();					// Recupera la que hubiera antes.
		glMatrixMode(iMatrizAct);		// Dejamos la matriz que estuviese.
	}
}



//==========================================================================
//  Fin de fuente.c
//==========================================================================
