/***************************************************************************
                          display.h  -  Contexto gr�fico
                             -------------------
    begin                : Thu Nov 14 2002
    copyright            : (C) 2002 by neuralgya
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

#ifndef _INC_DISPLAY
#define _INC_DISPLAY


 
/*!
int sis_ini_display(void)
Inicializaci�n del contexto OpenGL mediante SDL.
Abrir� la ventana SDL y le asignar� un contexto OpenGL.
A su vez, llamar� a la inicializaci�n de OpenGL.
*/
extern int sis_ini_display(void);


/*!
Cierre el contexto gr�fico
*/
extern int sis_cerrar_display(void);

#endif