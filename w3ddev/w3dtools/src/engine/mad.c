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

#include "globales.h"
#include "w3d_base.h"
#include "sdl_gl.h"

#define MAD_MAGIC 20
modelo *carga_mad(char *file)
{
    FILE *f_object;
    uint j;
    cara *tri;
    char filename[LON_BUFF];
    char magic;
    modelo *modelo_1;

    modelo_1 = (modelo *) malloc(sizeof(modelo));
    strcpy(filename, "modelos");
    strcat(filename, "/");
    strcat(filename, file);
    log_msj("[mad.c] Cargando modelo %s\n", filename);
    f_object = abre_fichero(filename, "rb");
    if (f_object == NULL) {
        log_msj("[KO] No pude encontrar %s\n", filename);
        return NULL;
    }
    fread(&magic, 1, 1, f_object);
    if (magic != MAD_MAGIC) {
        log_msj("[KO] Fichero no válido\n");
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
    log_msj("[mad.c] Modelo cargado con %d caras\n", j);
    if (strlen(modelo_1->id_textura) == 0)
        strcpy(modelo_1->id_textura, "(nullfile)");
    log_msj("[mad.c] Skin  %s\n", modelo_1->id_textura);

//modelo_1->n_textura = encola_textura(modelo_1->id_textura, GL_RGBA);
    log_msj("[mad.c] Textura_id  %d\n", modelo_1->n_textura);
    return modelo_1;
}

int render_mad(modelo * mad)
{
    uint j;

    T_FUNC_IN;

    for (j = 0; j < mad->n_caras; j++) {

/*if (mad->n_textura != 0)
            
glBindTexture(GL_TEXTURE_2D, matriz_texturas[mad->n_textura]);*/
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
    _return SI;
}
