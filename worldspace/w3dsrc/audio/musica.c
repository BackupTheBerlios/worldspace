//==========================================================================
//  musica.c  -  Carga los ficheros de musica en sus distintos
//                     formatos
//
//  begin     : jue 1 may 2003 / jue 1 may 2003
//  copyright : (C) 2003 by Grupo WorldSpace
//  email     : lordloki@users.berlios.de
//==========================================================================
//                                                                         *
//   This program is free software; you can redistribute it and/or modify  *
//   it under the terms of the GNU General Public License as published by  *
//   the Free Software Foundation; either version 2 of the License, or     *
//   (at your option) any later version.                                   *
//                                                                         *
//==========================================================================

#include <string.h>
#include <stdarg.h>
#include "sdl_gl.h"
#include "musica_ogg.h"
#include "musica_mod.h"
#include "util.h"
#include "globales.h"
#include "w3d_base.h"
#include "audio.h"

//==========================================================================
// Extensiones de ficheros de imagenes
//==========================================================================
static char * vsFicMusica [] = {
	"OGG" ,     // FOGG
	"MOD" ,     // FMOD
	"S3M" ,     // FS3M
	"IT"  ,     // FIT   // A lo peor con este no funciona por la longitud diferente
	"XM"  ,     // FXM   // A lo peor con este no funciona por la longitud diferente
};

int iTipo = 0; // 1--> Ogg y 2--> los demas

//==========================================================================
// Funcion de carga de ficheros.
// El nombre del fichero debe tener una extensión reconocida por el programa
// Si todo va bien devuelve 0
// Si no devuelve -1
//==========================================================================
// Este módulo está relacionado con las texturas, por ello tampoco voy a
// utilizar las devoluciones de SI(1) y NO(0)
//==========================================================================
int cargar_musica  ( char *sMusica )
{

	char   sCadena  [LON_BUFF/4];
	char   sColaFic [8];
	int    i;

	//---------------------------------------------------
	// Primero extraemos la extension del fichero
	//---------------------------------------------------
	mInicio (sColaFic);
	mInicio (sCadena);
	strcpy  (sColaFic, sMusica + strlen(sMusica)-7);  // Extraemos la cola del nombre del fichero
	uStrtoken (sCadena, sColaFic, ".");    // El primero se queda con la izquierda
	uStrtoken (sCadena, NULL    , ".");    // El segundo se queda con la extensión
	//---------------------------------------------------
	uMayusculas (sCadena);
	for ( i=0; i<5; i++ )
	{
		if ( ! strcmp(sCadena, vsFicMusica[i]) ) break;
	}
	//---------------------------------------------------
	switch (i)
	{
		case OGG:
			iTipo = 1;
			cargar_ogg ( sMusica );
			break;

		case MOD:
			iTipo = 2;
			cargar_mod ( sMusica );
			break;

		case S3M:
			iTipo = 2;
			cargar_mod ( sMusica );
			break;

		case IT :
			iTipo = 2;
			cargar_mod ( sMusica );
			break;

		case XM :
			iTipo = 2;
			cargar_mod ( sMusica );
			break;

		default:// Fichero no reconocido
			log_msj ("Extensión de fichero de musica no reconocida: %s\n", sCadena);
			return NO;
	}

	return SI;  // Todo ha ido bien.
}


int pausar_musica (int pausa) {

	if (iTipo == 1){
		pausar_ogg ( pausa );
		return SI;
	}
	else if (iTipo == 2){
		pausar_mod ( pausa );
		return SI;
	}
	else{
		log_msj("Fichero de musica no reconocido\n");
	}
	return NO;
}


int reproducir_musica ( int repetir ) {

	if (iTipo == 1){
		reproducir_ogg ( repetir );
		return SI;
	}
	else if (iTipo == 2){
		reproducir_mod ( repetir );
		return SI;
	}
	else{
		log_msj("Fichero de musica no reconocido\n");
	}
	return NO;
}


int resetear_musica (void) {

	if (iTipo == 1){
		resetear_ogg ( );
		iTipo = 0;
		return SI;
	}
	else if (iTipo == 2){
		resetear_mod ( );
		iTipo = 0;
		return SI;
	}
	else{
		log_msj("Fichero de musica no reconocido\n");
	}
	return NO;
}

//==========================================================================
//  Fin de musica.c
//==========================================================================
