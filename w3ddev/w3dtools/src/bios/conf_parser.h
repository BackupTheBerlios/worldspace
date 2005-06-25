/***************************************************************************
                          conf_parser.h  -  Parsing del fichero de
                          			configuracion
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

#ifndef _CONF_PARSER_H_
#define _CONF_PARSER_H_
//==========================================================================
#include <stdio.h>


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
#define WDIR_SONIDOS  "sonidos"
#define WDIR_ESPACIOS "espacios"
#define WDIR_NODIR    "no_hay_directorio"
/*!
Patrones para leer la configuracion inicial del fichero ini.
!*/
#define PXSCREEN      "Xtam"
#define PYSCREEN      "Ytam"
#define PNBITS        "bpp"
#define PALLSCREEN    "FullScreen"
#define PDIR_GENERAL  "DirGeneral"
#define PDIR_TEXTURAS "DirTexturas"
#define PDIR_FUENTES  "DirFuentes"
#define PDIR_MODELOS  "DirModelos"
#define PDIR_SONIDOS  "DirSonidos"
#define PDIR_ESPACIOS "DirEspacios"


extern int establece_var_conf_numero(FILE * fl_fichero, char *s_token);
extern char *establece_var_conf_cadena(FILE * fl_fichero, char *s_token);
//==========================================================================
#endif				// _CONF_PARSER_H_


//==========================================================================
//  Fin de conf_parser.h
//==========================================================================
