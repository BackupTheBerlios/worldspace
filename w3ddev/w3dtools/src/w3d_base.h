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
Aqui definimos el nº de sonidos, musicas, entornos y listeners que vamos a utilizar 
*/
#define NUM_SONIDOS     1
#define NUM_LISTENER    1
#ifdef _LINUX
#define NUM_ENTORNOS    1
#endif
#define NUM_MUSICAS   1

/*!
============================================== MACROS
!*/

/*!
Control de indentacion de las trazas
!*/
#define T_FUNC_IN   nivel_traza++;
#define T_FUNC_OUT  nivel_traza--;
#define _return     T_FUNC_OUT return

#define mInicio(s)  memset((s), 0, sizeof(s))

#ifdef WIN32
typedef unsigned int uint;
#endif				// WIN32
typedef unsigned char byte;


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
    char sDirSonidos[LON_BUFF];
    char sDirEspacios[LON_BUFF];
} estr_config;


/*!
Estructura de un vector
!*/

typedef struct vector_tag {
    float x, y, z;
    float u, v;
    float Nx, Ny, Nz;		// Normales
} vertice;


/*!
Estructura de un triangulo o cara
!*/

typedef struct tag_face {
    vertice vertices[3];	// Puntos del triángulo
} cara;


/*!
Estructura de un modelo
!*/

typedef struct tag_object {
    unsigned int n_caras;	// Numero de caras
    cara *triangulos;		// Matriz de caras
    char id_textura[16];	// Fichero de textura
    unsigned int n_textura;	// Identificación de textura
    float x, y, z;		// Posición en el espacio
    vertice base[3];		// Base;
} modelo;



#endif
