//==========================================================================
//  texturas.c  -  Tratamiento de texturas
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

#include <string.h>

#include "globales.h"
#include "memoria.h"
#include "conf_parser.h"
#include "carga_imagen.h"
#include "sdl_gl.h"
#include "textura.h"

//==========================================================================
//  Variables internas del módulo
//==========================================================================
static char sDirTexturas [LON_BUFF] = { WDIR_TEXTURAS };
//==========================================================================

//==========================================================================
//  Se pretende generar una lista de texturas a cargar con
//  encola_textura, que devuelve el indice de esa textura.
//  Se comprueba que la textura no haya sido solicitada previamente,
//  es decir: Si  dos modelos usan la textura a.tga, encola_textura
//  detecta esta situación y asigna el mismo identificador de textura
//  a las dos peticiones, de tal manera que cuando se llame a 
//  genera_textura sólo se cargue una vez y se genere una textura.
//
//  Solo debo devolver el valor asigando a las texturas, y estas van desde 
//  0 a n. No puedo utilizar los defines SI (1) o NO (0). El 0 debe ser un
//  valor válido.
//
//  Por lo tanto, no voy a utilizar SI y NO en este módulo.
//==========================================================================
//  Partimos de un puntero que representa el principio de una lista
//  de nombres.
//==========================================================================
static miTextura *		prColaTexturas = NULL;
static int				iNumTexturas  = 0;
static miLTexturas *	prListaTexturas = NULL;
//==========================================================================
int  encola_textura       ( miTextura * prTextura )
{
	miTextura * prNomActual = prColaTexturas;
	miTextura * prNomAnt;
	int         iNum = 0;

	T_FUNC_IN

	if (prColaTexturas == NULL)			// Iniciamos la lista, no hay ningún
	{									// nombre guardado.
		prColaTexturas = (miTextura *) dar_m(sizeof(miTextura));
		if (prColaTexturas==NULL)
		{ _return -1; }					// Debo devolver error
		prNomActual = prColaTexturas;
	}
	else
	{
		prNomActual = prColaTexturas;
		for ( iNum=0; prNomActual!=NULL; iNum++ )
		{
			if ( !strcmp(prNomActual->sFichero, prTextura->sFichero) )
			{ _return iNum; }			// Devuelve el indice que le corresponde
			prNomAnt    = prNomActual;
			prNomActual = prNomActual->pSig;
		}
		prNomActual = (miTextura *) dar_m(sizeof(miTextura));
		if (prNomActual==NULL)
		{ _return -1; }					// Debo devolver error
		prNomAnt->pSig = prNomActual;
	}
	prNomActual->pSig   = NULL;
	prNomActual->iNText = iNum;
	prNomActual->iAlto  = prNomActual->iAncho = 0;
	prNomActual->iTipo  = prTextura->iTipo;
	strcpy(prNomActual->sFichero, prTextura->sFichero);

	prTextura->iNText   = iNum;

	iNumTexturas = iNum + 1;

	_return iNum;
}


//==========================================================================
//  Función de que libera la lista general de nombres de textura
//  generada por 'encola_textura'.
//==========================================================================
void cerrar_texturas  ( void )
{
	miTextura * prNomActual = prColaTexturas;
	miTextura * prNomAnterior;

	if (prColaTexturas!=NULL)
	{
		prNomActual = prNomActual->pSig;
		prColaTexturas = liberar_m(prColaTexturas);

		for ( ; prNomActual!=NULL; )
		{
			prNomAnterior = prNomActual;
			prNomActual   = prNomActual->pSig;
			prNomAnterior = liberar_m (prNomAnterior);
		}

		prListaTexturas = liberar_m (prListaTexturas);
	}
}


//==========================================================================
//  Función de prueba para ver si funciona la lista/cola de texturas
//==========================================================================
void muestra_texturas ( void )
{
	miTextura * prNomActual = prColaTexturas;

	T_FUNC_IN

	for ( ; prNomActual!=NULL; )
	{
		log_msj( "\n %2d %s", prNomActual->iNText, prNomActual->sFichero );
		prNomActual = prNomActual->pSig;
	}

	prListaTexturas = liberar_m (prListaTexturas);

	T_FUNC_OUT
}


//==========================================================================
//  Función general de Carga de todas las texturas de una lista
//  de texturas.
//==========================================================================
//  Se modifica la función para llamar a 'encola_textura'
//  Dejaremos para antes de empezar a 'dibujar' la generación real
//  de las texturas.
//==========================================================================
int carga_listaTexturas ( miLTexturas * vLisTexturas )
{
    int i, iTex;

	T_FUNC_IN

	for ( i=0; i<vLisTexturas->iNtexturas; i++ )
	{
		iTex = encola_textura (&vLisTexturas->vTextura[i]);
		if (iTex<0)
		{	_return -1;	}	// Algo ha ido mal.
		vLisTexturas->vTextura[i].iNText = iTex;
	}

	_return 0;
}


//==========================================================================
//  genera_texturas carga todas la texturas de una sola vez.
//  Con esto se consigue que en los logs queden agrupados todos los
//  mensajes referentes a la carga de ficheros de texturas.
//  Por lo tanto se llamará tantas veces como se reinicien las
//  texturas
//==========================================================================
int  genera_texturas  ( void )
{
	int i;
	miTextura * prNomActual = prColaTexturas;
	miTextura   rTextura;

	T_FUNC_IN

	mInicio(rTextura.sFichero);
	if (prListaTexturas==NULL)
	{
		prListaTexturas = dar_m(sizeof(miLTexturas));
		if (prListaTexturas==NULL)
		{	_return -1; }
		prListaTexturas->iNtexturas = iNumTexturas;
		prListaTexturas->vTextura = dar_m(sizeof(miTextura)*iNumTexturas);
	}

	mInicio(sDirTexturas);
	directorio(sDirTexturas,"%s/%s/", configuracion.sDirGeneral, configuracion.sDirTexturas );

	// Cargamos las texturas
	glEnable(GL_TEXTURE_2D);
	glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
	glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	for ( i=0; prNomActual!=NULL && i<iNumTexturas; i++ )
	{
		log_msj( " %2d %s\n", prNomActual->iNText, prNomActual->sFichero );
		prNomActual = prNomActual->pSig;
	}

	for ( i=0; i<prListaTexturas->iNtexturas; i++ )
	{
		rTextura.iNText = rTextura.iAlto = rTextura.iAncho = 0;
		rTextura.iTipo = prListaTexturas->vTextura[i].iTipo;
		sprintf(rTextura.sFichero,
			"%s/%s",
			sDirTexturas, prListaTexturas->vTextura[i].sFichero );
		if (carga_textura (&rTextura))
		{	_return -1; }
		prListaTexturas->vTextura[i].iNText = rTextura.iNText;
    }

	_return 0;	// Todo ha ido bien.
}


// ==================================================================
//  Realiza la carga de una textura
// ==================================================================
int carga_textura ( miTextura * pTextura )
{
    miFic_imagen rFic_imagen;

	T_FUNC_IN;

	rFic_imagen.iAlto  = 0;
	rFic_imagen.iAncho = 0;
	rFic_imagen.iTipo  = 0;
	rFic_imagen.pDatos = NULL;
	strcpy(rFic_imagen.sFichero, pTextura->sFichero);

	if ( carga_imagen (&rFic_imagen) )
	{
		pTextura->iNText = -1;  // Valor de textura invalida.
   		log_msj ("\n Error al cargar %s",	pTextura->sFichero);
   		_return -1;
	}

    if (rFic_imagen.iTipo==FTGA && rFic_imagen.iAncho!=rFic_imagen.iAlto)
	{
   		log_msj ("\n Ancho y Alto distinto en Textura: %s", pTextura->sFichero);
		rFic_imagen.pDatos = (char *) liberar_m(rFic_imagen.pDatos);
   		_return -1;
	}

	pTextura->iAlto  = rFic_imagen.iAlto;
	pTextura->iAncho = rFic_imagen.iAncho;

	glGenTextures (1, (unsigned int *) &pTextura->iNText);
	glBindTexture (GL_TEXTURE_2D, pTextura->iNText);
	switch(pTextura->iTipo)
	{
		case AT0:  // Texturas BMP sin canal Alpha
			 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
             glTexImage2D (GL_TEXTURE_2D, 0, 3,
					       rFic_imagen.iAncho, rFic_imagen.iAlto,
						   0, GL_RGB, GL_UNSIGNED_BYTE,rFic_imagen.pDatos);
			 break;

		case AT1:  // Fuentes BMP sin canal Alpha
			 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //GL_NEAREST
			 glTexImage2D (GL_TEXTURE_2D, 0, 3,
		                   rFic_imagen.iAncho, rFic_imagen.iAlto,
		                   0, GL_RGB, GL_UNSIGNED_BYTE, rFic_imagen.pDatos);
			 break;

		case FT0:  // Fuentes y Texturas TGA
			 glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
			 glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
			 gluBuild2DMipmaps (GL_TEXTURE_2D, 4,
							    rFic_imagen.iAncho, rFic_imagen.iAlto,
							    GL_RGBA, GL_UNSIGNED_BYTE, rFic_imagen.pDatos);
			break;

		case FT1: // Por ahora es el mismo que el de FT0
			 glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
			 glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
			 gluBuild2DMipmaps (GL_TEXTURE_2D, 4,
							    rFic_imagen.iAncho, rFic_imagen.iAlto,
							    GL_RGBA, GL_UNSIGNED_BYTE, rFic_imagen.pDatos);
			break;

		case FT2:  // Fuentes TGA con canal Alpha
			 glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			 glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			 glTexImage2D (GL_TEXTURE_2D, 0, 4,
						   rFic_imagen.iAncho, rFic_imagen.iAlto,
						   0, GL_RGBA, GL_UNSIGNED_BYTE, rFic_imagen.pDatos);
			break;
	}
	rFic_imagen.pDatos = (char *) liberar_m(rFic_imagen.pDatos);
	log_msj ("\t\t\t%d", pTextura->iNText);
	_return 0;
}


// ==================================================================
//  Activa la textura pasada por parámetro, si es un textura correcta
// ==================================================================
void activa_textura  ( int iTextura )
{
	if (iTextura>-1)
	{
		if ( !glIsEnabled(GL_TEXTURE_2D) )
			glEnable(GL_TEXTURE_2D);
		glBindTexture (GL_TEXTURE_2D,
			prListaTexturas->vTextura[iTextura].iNText);
	}
}


// ==================================================================
//  Fin de wTextura.c
// ==================================================================
