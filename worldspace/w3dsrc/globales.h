/***************************************************************************
                          globales.h  -  variables y estructuras globales
                             -------------------
    begin                : lun feb 10 2003
    copyright            : (C) 2003 by Grupo WorldSpace
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


#ifndef _GLOBALES_
#define _GLOBALES_
 
#include "w3d_base.h"
#include <stdio.h>


/*!
Variable para guardar la configuración
!*/
extern estr_config configuracion;

/*!
Nivel de traza
*/
extern char nivel_traza;


/*!
Salida de logs
*/
extern int log_msj(char *cadena,...);

/*!
Wrapper para fopen, que inserta al nombre del fichero
el directorio de los datos
*/
extern FILE *abre_fichero(char *nombre,char *modo);



#endif
