//==========================================================================
//  util.h - Cabecera del Módulo de funciones utiles.
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

#ifndef _UTIL_H_
#define _UTIL_H_
//==========================================================================
void uMayusculas(char *sCad);
char *uCopia_cadena(char *sCadena);
void uStrtoken(char *sDestino, char *sOrigen, char *sSep);
//==========================================================================
void uGuardarEstado(void);
void uRecuperarEstado(void);
void uRecuperarPila(void);
//==========================================================================
#endif                          // _UTIL_H_

//==========================================================================
//  Fin de util.h
//==========================================================================
