//==========================================================================
//  texturas.c - Tratamiento de texturas
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
#include "memoria.h"
#include "conf_parser.h"
#include "carga_imagen.h"
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
//  1 a n. Puedo utilizar los defines SI (1) o NO (0). El 0 es un valor de
//  no valido. Pero como ya había utilizado -1 continuo con ello, hasta que
//  aclaremos lo de los valores a devolver.
//
//  Por lo tanto, no voy a utilizar SI y NO en este módulo (Por ahora).
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

	T_FUNC_IN;

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
			{
				prTextura->iNText  = prNomActual->iNText;
				_return prNomActual->iNText;	// Devuelve el indice que le corresponde
			}
			prNomAnt    = prNomActual;
			prNomActual = prNomActual->pSig;
		}
		prNomActual = (miTextura *) dar_m(sizeof(miTextura));
	    if (prNomActual==NULL)
		{ _return -1; }					// Debo devolver error
		prNomAnt->pSig = prNomActual;
	}
	glGenTextures (1, (uint *) &prNomActual->iNText);

	strcpy(prNomActual->sFichero, prTextura->sFichero);
	prNomActual->iAlto = prNomActual->iAncho = 0;
	prNomActual->iTipo = prTextura->iTipo;
	prNomActual->pSig  = NULL;

	prTextura->iNText  = prNomActual->iNText;

	iNumTexturas = iNum + 1;

	_return prNomActual->iNText;
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

		if (prListaTexturas)
		{
			prListaTexturas->vTextura = liberar_m(prListaTexturas->vTextura);
			prListaTexturas = liberar_m(prListaTexturas);
		}
	}
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
    int i;
	miTextura rTextura;

	T_FUNC_IN;

	mInicio(sDirTexturas);
	sprintf(sDirTexturas,"%s/", configuracion.sDirTexturas);

	for ( i=0; i<vLisTexturas->iNtexturas; i++ )
	{
		rTextura.iAlto = rTextura.iAncho = 0;
		rTextura.iNText = vLisTexturas->vTextura[i].iTipo;
		mInicio(rTextura.sFichero);
		sprintf(rTextura.sFichero,
			"%s%s", sDirTexturas, vLisTexturas->vTextura[i].sFichero);
		rTextura.iNText = encola_textura (&rTextura);
		if (rTextura.iNText<0)
		{ _return -1;	}	// Algo ha ido mal.
		vLisTexturas->vTextura[i].iNText = rTextura.iNText;
	}

	_return 0;
}


//==========================================================================
//  genera_texturas carga todas la texturas de una sola vez.
//
//  Todas las texturas de la cola de texturas 'prColaTexturas', que se han
//  ido introduciendo con 'encola_textura', pasan a una lista mas manejable
//  por indices 'prListaTexturas'.
//
//  Hecho esto, se llama a 'carga_texturas' que será la función que se pueda
//  llamar cada vez que se redefinan las texturas.
//==========================================================================
int  genera_texturas  ( void )
{
	int i;
	miTextura * prNomActual = prColaTexturas;
	miTextura   rTextura;

	T_FUNC_IN;

	if (prColaTexturas==NULL)  // Como no hay nada
		return 0;              // tampoco hay error

	mInicio (rTextura.sFichero);

	if (prListaTexturas==NULL)
	{
		prListaTexturas = dar_m(sizeof(miLTexturas));
		if (prListaTexturas==NULL)
		{ _return -1; }
		prListaTexturas->iNtexturas = iNumTexturas;
		prListaTexturas->vTextura = dar_m(sizeof(miTextura)*iNumTexturas);
	}

	log_msj ("# Pasamos la Cola a la Lista ..\n");
	for ( i=0; prNomActual!=NULL && i<iNumTexturas; i++ )
	{
		// Estos valores se conocen con 'encola_textura'.
		prListaTexturas->vTextura[i].iTipo  = prNomActual->iTipo;
		prListaTexturas->vTextura[i].iNText = prNomActual->iNText;
		prListaTexturas->vTextura[i].pSig   = prNomActual->pSig;
		strcpy(prListaTexturas->vTextura[i].sFichero,prNomActual->sFichero);
		// Valores que desconocemos hasta la 'carga_imagen'.
		prListaTexturas->vTextura[i].iAlto  =
		prListaTexturas->vTextura[i].iAncho = 0;

		log_msj( " %2d %s\n", prNomActual->iNText, prNomActual->sFichero );
		// Pasamos al siguiente en la cola.
		prNomActual = prNomActual->pSig;
	}
	log_msj ("# Lista de texturas generada ..\n");

	_return carga_texturas();
}


//===========================================================================
// Realiza la carag de las texturas a partir de la lista general de texturas.
// Es la función que se utiliza para la recarga.
//===========================================================================
int carga_texturas ( void )
{
	int i;

	T_FUNC_IN;

	// Cargamos la textura
	glEnable(GL_TEXTURE_2D);
	glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
	glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	for ( i=0; i<prListaTexturas->iNtexturas; i++ )
	{
		if (carga_textura (&prListaTexturas->vTextura[i]))
		{ _return -1; }
    }
	glDisable(GL_TEXTURE_2D);
	log_msj ("# Texturas cargadas y generadas ..\n");

	_return 0;
}


// ==================================================================
//  Realiza la carga de una textura
// ==================================================================
int carga_textura ( miTextura * prTextura )
{
    miFic_imagen rFic_imagen;

	T_FUNC_IN;

	rFic_imagen.iAlto  = 0;
	rFic_imagen.iAncho = 0;
	rFic_imagen.iTipo  = 0;
	rFic_imagen.pDatos = NULL;
	strcpy(rFic_imagen.sFichero, prTextura->sFichero);

	if ( carga_imagen (&rFic_imagen) )
	{
		prTextura->iNText = -1;  // Valor de textura invalida.
		// El mensaje sobra si ya se da el mensaje en carga_imagen.
   		log_msj ("Error al cargar %s\n",	prTextura->sFichero);
   		_return -1;
	}

	// Esto creo que sobra, ya se realiza en 'carga_tga'
    if (rFic_imagen.iTipo==FTGA && rFic_imagen.iAncho!=rFic_imagen.iAlto)
	{
   		log_msj ("Ancho y Alto distinto en Textura: %s\n", prTextura->sFichero);
		rFic_imagen.pDatos = (char *) liberar_m(rFic_imagen.pDatos);
   		_return -1;
	}

	prTextura->iAlto  = rFic_imagen.iAlto;
	prTextura->iAncho = rFic_imagen.iAncho;

	//---------------------------------------------------------
	//  Ahora esto se realiza en 'encola_textura'
	// glGenTextures (1, (unsigned int *) &prTextura->iNText);
	//---------------------------------------------------------
	log_msj ("%3d [%s]\n", prTextura->iNText, prTextura->sFichero);

	glBindTexture (GL_TEXTURE_2D, prTextura->iNText);
	switch(prTextura->iTipo)
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

	_return 0;
}


// ==================================================================
//  Activa la textura pasada por parámetro, si es un textura correcta
// ==================================================================
void activa_textura  ( int iTextura )
{
	if (iTextura>0)
	{
		if ( !glIsEnabled(GL_TEXTURE_2D) )
			glEnable(GL_TEXTURE_2D);
		glBindTexture (GL_TEXTURE_2D, iTextura );
	}
}


// ==================================================================
//  Fin de wTextura.c
// ==================================================================
