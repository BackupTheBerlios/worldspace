/***************************************************************************
                          engine.h  -  Funciones y variables exportadas por
                          				engine.c
                             -------------------
    begin                : s�b ene 11 2003
    copyright            : (C) 2003 by neuralgya
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



/*!
Esta matriz es una de las m�s importantes, ya que referenciar� siempre la
posici�n del observador, osea, nosotros
!*/

extern float camara[4][4];

/*!
Inicializaci�n propia de OpenGL
!*/
extern int ini_gl(char show_logo);
