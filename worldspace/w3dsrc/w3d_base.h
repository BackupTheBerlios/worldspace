/***************************************************************************
                          w3d_base.h  -  Defines y estructuras básicas.
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


#ifndef _W3D_BASE_
#define _W3D_BASE_

/*!
============================================== DEFINE
!*/

/*!
Valor devuelto por las funciones
!*/
#define SI 1
#define NO 0


/*!
Longitud por defecto de los buffer (arrays)
!*/
#define LON_BUFF      1024


/*!
============================================== MACROS
!*/

/*!
Control de indentacion de las trazas
!*/
#define T_FUNC_IN nivel_traza++;
#define T_FUNC_OUT nivel_traza--;


/*!
Estructura para guardar la configuración
!*/
typedef struct config_tag {
    int Xtam;
    int Ytam;
    int FullScreen;
    int bpp;
    char sDirGeneral[LON_BUFF];
    char sDirTexturas[LON_BUFF];
    char sDirFuentes[LON_BUFF];
    char sDirModelos[LON_BUFF];
    char sDirEspacios[LON_BUFF];
} estr_config;


#endif

