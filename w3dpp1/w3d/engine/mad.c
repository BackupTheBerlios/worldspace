/***************************************************************************
                          mad.c  -  description
                             -------------------
    begin                : sáb ene 11 2003
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
    
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
    
#include "mad.h"
#include "../global.h"
#include "../opengl.h"
#include "texturas.h"
extern GLuint *matriz_texturas;
modelo * carga_mad(char *file) 
{
    FILE * f_object;
    int j;
    cara * tri;
    char *filename_etereal, *textura_datos;
    char filename[3024];
    char skin[3024];
    char magic;
    unsigned int tam_x, tam_y;
    modelo * modelo_1;
    modelo_1 = (modelo *) malloc(sizeof(modelo));
    strcpy(filename, "modelos");
    strcat(filename, "/");
    strcat(filename, file);
    _sis_msj("\n\t\t[mad.c]Cargando modelo ");
    _sis_msj(filename);
    f_object = abre_fichero(filename, "rb");
    if (f_object == NULL) {
        _sis_msj("\n\t\t[KO]No pude encontrar\n");
        return NULL;
    }
    fread(&magic, 1, 1, f_object);
    if (magic != MAD_MAGIC) {
        _sis_msj("\t\t\t[KO]Fichero no válido\n");
        return NULL;
    }
    fread(modelo_1, sizeof(modelo), 1, f_object);
    modelo_1->x = 0.0;
    modelo_1->y = 0.0;
    modelo_1->z = 0.0;
    tri = (cara *) malloc(sizeof(cara) * modelo_1->n_caras);
    modelo_1->triangulos = tri;
    for (j = 0; j < modelo_1->n_caras; j++) {
        fread(&(modelo_1->triangulos[j]), sizeof(cara), 1, f_object);
    }
    sprintf(skin, "\n\t\t\tModelo cargado con %d caras", j);
    _sis_msj(skin);
    if (strlen(modelo_1->id_textura) == 0)
        strcpy(modelo_1->id_textura, "(nullfile)");
    sprintf(skin, "\n\t\t\tSkin  -%s-", modelo_1->id_textura);
    _sis_msj(skin);
    modelo_1->n_textura = encola_textura(modelo_1->id_textura, GL_RGBA);
    sprintf(skin, "\n\t\t\tTextura_id  %d", modelo_1->n_textura);
    _sis_msj(skin);
    return modelo_1;
}
int render_mad(modelo * mad) 
{
    int j;
    for (j = 0; j < mad->n_caras; j++) {
        if (mad->n_textura != 0)
            glBindTexture(GL_TEXTURE_2D, matriz_texturas[mad->n_textura]);
        glBegin(GL_TRIANGLES);
        glTexCoord2f(mad->triangulos[j].vertices[0].u,
                        mad->triangulos[j].vertices[0].v);
        glNormal3f(mad->triangulos[j].vertices[0].Nx,
                      mad->triangulos[j].vertices[0].Ny,
                      mad->triangulos[j].vertices[0].Nz);
        glVertex3f(mad->triangulos[j].vertices[0].x * 30,
                     mad->triangulos[j].vertices[0].y * 30,
                     mad->triangulos[j].vertices[0].z * 30);
        glTexCoord2f(mad->triangulos[j].vertices[1].u,
                         mad->triangulos[j].vertices[1].v);
        glNormal3f(mad->triangulos[j].vertices[1].Nx,
                      mad->triangulos[j].vertices[1].Ny,
                      mad->triangulos[j].vertices[1].Nz);
        glVertex3f(mad->triangulos[j].vertices[1].x * 30,
                     mad->triangulos[j].vertices[1].y * 30,
                     mad->triangulos[j].vertices[1].z * 30);
        glTexCoord2f(mad->triangulos[j].vertices[2].u,
                         mad->triangulos[j].vertices[2].v);
        glNormal3f(mad->triangulos[j].vertices[2].Nx,
                      mad->triangulos[j].vertices[2].Ny,
                      mad->triangulos[j].vertices[2].Nz);
        glVertex3f(mad->triangulos[j].vertices[2].x * 30,
                     mad->triangulos[j].vertices[2].y * 30,
                     mad->triangulos[j].vertices[2].z * 30);
        glEnd();
    }
    return SI;
}


