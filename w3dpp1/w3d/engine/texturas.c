/***************************************************************************
                          texturas.c  -  description
                             -------------------
    begin                : sáb ene 18 2003
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

#include <stdlib.h>
#include <string.h>

#include "../global.h"
#include "../opengl.h"
#include "../gfx/gfx_carga_img.h"

 
GLuint *matriz_texturas;
char matriz_texturas_nombre[1024][256];
unsigned short int indice_texturas=1;

int encola_textura(char *nombre) {

    FILE *tmp_f;
    int lon;
    
    char f_text[1024];
    strcpy(f_text,"texturas/");
    strcat(f_text,nombre);
    tmp_f=abre_fichero(f_text,"rb");
    if (tmp_f==NULL) {
        _sis_msj(" Se usará textura nula");
	return 0;
    }

    for (lon=1;lon<indice_texturas;lon++)  
	if (strcmp(nombre, matriz_texturas_nombre[lon])==0)
	    break;

  
    strcpy(matriz_texturas_nombre[lon],nombre);
     _sis_msje("\t\t\t\t%s",matriz_texturas_nombre[lon]);
    if (lon==indice_texturas)
	indice_texturas++;
    return (lon);
}

int genera_texturas(void) {

    int tam_x,tam_y,i;
    char f_text[1024];
    char *textura_datos;

    matriz_texturas=(GLuint)malloc(indice_texturas*sizeof(GLuint));
    glGenTextures (indice_texturas,matriz_texturas);


   _sis_msj("\n\t\tGenerando texturas...............\n ");

    for (i=1;i<indice_texturas;i++) {
	    strcpy(f_text,"texturas/");
	    strcat(f_text,matriz_texturas_nombre[i]);
	    textura_datos=(char *)carga_tga(f_text,&tam_x,&tam_y);
	    if (tam_x!=tam_y)
		return NO;
            if (textura_datos == NULL)  {
		_sis_msj("Error al cargar textura");
		return NO;
  	  }

	glBindTexture (GL_TEXTURE_2D, matriz_texturas[i]);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_NEAREST);
	gluBuild2DMipmaps (GL_TEXTURE_2D, 4, tam_x, tam_y, GL_RGBA,
	GL_UNSIGNED_BYTE, textura_datos);

	free(textura_datos);

    }


    return SI;
}

