/***************************************************************************
                          init_gl.h  -   inicializaciones de opengl
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



/*! Inicializaci�n propia de OpenGL

Este c�digo es un poco complejo...glMatrixMode srive para indicar que vamos a modificar la matriz de proyecci�n.
glLoadIndentity() la resetea. Con gluPerspective lo que hacemos es indicar a OpenGL que vamos a utilizar perspectiva.
Esto hace que a medida que las cosas est�n m�s lejos se van haciendo m�s peque�as y tienden al centro. Esta perspectiva
har� que lo que veamos sea m�s realista. Adem�s, los dos �ltimos par�metros sirven para indicar que el rango de visivilidad
va desde .1 a 100. Es decir, lo que est� situado a m�s de 100 unidades de la c�mara no se ver

Esta versi�n de inicializaci�n es una versi�n b�sica.
*/
extern int gl_basic_ini(char show_logo);