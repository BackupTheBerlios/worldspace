/***************************************************************************
                          memoria.h
                             -------------------
    begin                : sat apr 12 2003 / sab 12 abr 2003
    copyright            : (C) 2003 by Grupo WorldSpace
    email                : eric@users.berlios.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef _Memoria_h_
#define _Memoria_h_
//==========================================================================
void * dar_m              ( int iSize );
void * liberar_m          ( void * );
int    bloques_asignados  ( void );
//==========================================================================
#endif // _Memoria_h_

//==========================================================================
//  Fin de memoria.h
//==========================================================================
