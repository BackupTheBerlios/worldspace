/***************************************************************************
                          bios.c  -  Inicialización de sistemas básicos
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
#include <string.h>

#include "w3d_base.h"

/*!
Valores de configuracion inicial.
!*/
#define WXSCREEN      640
#define WYSCREEN      480
#define WNBITS        16
#define WALLSCREEN    0
#define WDIR_GENERAL  "ws_datos"
#define WDIR_TEXTURAS "texturas"
#define WDIR_FUENTES  "fuentes"
#define WDIR_MODELOS  "modelos"
#define WDIR_ESPACIOS "espacios"
#define WDIR_NODIR    "no_hay_directorio"
/*!
Patrones para leer la configuracion inicial del fichero ini.
!*/
#define PXSCREEN      "Xtam  = "
#define PYSCREEN      "Ytam  = "
#define PNBITS        "bpp    = "
#define PALLSCREEN    "FullScreen = "
#define PDIR_GENERAL  "DirGeneral  = "
#define PDIR_TEXTURAS "DirTexturas = "
#define PDIR_FUENTES  "DirFuentes  = "
#define PDIR_MODELOS  "DirModelos  = "
#define PDIR_ESPACIOS "DirEspacios = "

/*!
================================== DECLARACION DE VARIABLES
!*/

/*!
Variable para guardar la configuracion
!*/
estr_config configuracion;



/*!
Esta función inicializa los sistemas básicos de salida de errores y warnings.
Abre un fichero en modo de escritura, y ahí es donde se van depositando los
mensajes del sistema.

*/
int ini_bios(int iArg, char **cArg)
{

    configuracion.Xtam = WXSCREEN;
    configuracion.Ytam = WYSCREEN;
    configuracion.bpp = WNBITS;
    configuracion.FullScreen = WALLSCREEN;
    strcpy(configuracion.sDirGeneral, WDIR_GENERAL);
    strcpy(configuracion.sDirTexturas, WDIR_TEXTURAS);
    strcpy(configuracion.sDirFuentes, WDIR_FUENTES);
    strcpy(configuracion.sDirModelos, WDIR_MODELOS);
    strcpy(configuracion.sDirEspacios, WDIR_ESPACIOS);

    
    return SI;

}