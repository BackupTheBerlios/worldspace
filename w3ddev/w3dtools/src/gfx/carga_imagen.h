//==========================================================================
//  carga_imagen.h  -  Cabecera de carga de imagenes
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

#ifndef _Carga_Imagen_
#define _Carga_Imagen_
//==========================================================================
enum { FBMP = 0,
	   FTGA    ,
	   FRGB    ,
	   FBW     ,
	   NUM_FICIMAGEN
};

typedef struct {
	int    iTipo;          // Tipo que indica con que extensión se abre.
	int    iAncho, iAlto;  // Ancho x Alto en pixeles de la imagen.
	char   sFichero[256];  // Nombre del fichero.
	void * pDatos;         // Puntero Buffer donde guarda contenido fichero.
} miFic_imagen;

int    carga_imagen        ( miFic_imagen * pFic_imagen );
char * tipo_imagen         ( int iTipo );
char * directorio          ( char * sDir, char * sFormat, ... );
//==========================================================================
#endif //_Carga_Imagen_

//==========================================================================
//  Fin de carga_Imagen.h.
//==========================================================================
