/***************************************************************************
                          display.h  -  Contexto gráfico
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

#ifndef _DISPLAY_
#define _DISPLAY_



/*!
int sis_ini_display(void)
Inicialización del contexto OpenGL mediante SDL.
Abrirá la ventana SDL y le asignará un contexto OpenGL.
A su vez, llamará a la inicialización de OpenGL.
*/
extern int ini_display(void);

/*!
Cierre el contexto gráfico
*/
extern int cerrar_display(void);

/*!
Cambia la resolucion del contexto gráfico
*/
extern int cambia_display(int xdis, int ydis, int pan_completa);

#endif
