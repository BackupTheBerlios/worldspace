/***************************************************************************
                          bios.h  -  Inicialización de sistemas básicos (cabeceras)
                             -------------------
    begin                : mié jul 10 2002
    copyright            : (C) 2002 by neuralgya
    email                : neuralgya@mail.berlios.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <stdio.h>

/*! 
Estructura de la variable de configuración 
*/

typedef struct config_tag {
    short int SCREEN_SIZE_X;
    short int SCREEN_SIZE_Y;
    char FULLSCREEN;
	  char dir[1024];
} configuracion;


/*! Variables globales */


configuracion config; 			/*! Variable global para almacenar la configuración */
FILE *logs;						      /*! Salida para el fichero de logs */


/*! 
Macros que exportamos al sistema
*/

#define _sis_msj(c) fprintf(logs,"%s",c)

/*! 
Funciones que exportamos al sistema
*/

/*!
int cerrar_bios(void)
Cierra los fichero de logs, y graba el fichero de configuración.
*/
extern int cerrar_bios(void);

/*!
extern int init_bios(void);
Esta función inicializa los sistemas básicos de salida de errores y warnings.
Abre un fichero en modo de escritura, y ahí es donde se van depositando los
mensajes del sistema. Además llama a la función para cargar la configuración
por defecto
*/
extern int init_bios(void);

/*!

FILE *abre_fichero(char *nombre, char *modo)

Abre un fichero preponiendo el path por defecto

*/

FILE *abre_fichero(char *nombre, char *modo);


