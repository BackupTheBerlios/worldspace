/***************************************************************************
                          bios.h  -  description
                             -------------------
    begin                : dom feb 9 2003
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


#include <stdio.h>

/*!
Esta función inicializa los sistemas básicos de salida de errores y warnings.
Abre un fichero en modo de escritura, y ahí es donde se van depositando los
mensajes del sistema. Además llama a la función para cargar la configuración
por defecto.

*/

extern int ini_bios(int iArg, char **cArg);
extern int cerrar_bios(void);

/*!
Wrapper para fopen, que inserta al nombre del fichero
el directorio de los datos
*/
extern FILE *abre_fichero(char *nombre,char *modo);

