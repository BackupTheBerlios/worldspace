/***************************************************************************
                          espacio.c  -  description
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


#include <stdio.h>
#include <math.h>
#include<stdlib.h>


#include "../global.h"
#include "estructuras.h"
#include "../opengl.h"
#include "../gfx/gfx_carga_img.h"
#include <stdlib.h>



extern lista_sprites_spc *sprites_spc;
extern unsigned int n_sprites_spc;

extern float *estrellas;
extern unsigned int n_estrellas;

extern float *polvo_espacial;   /* Nada de connotaciones pornográficas eh? */
extern unsigned int n_polvo_espacial;


/*
int carga_espacio(char *fichero_spc)

Carga los sky-boxes
*/
int carga_espacio(char *fichero_spc)
{

    int contador = 0;
    int contador2 = 0;
    char fichero[1024];
    FILE *fich;
    char textura_f[1024];
    char textura_f_old[1024];

    char *textura_datos;
    int tam_x, tam_y;
    unsigned int numero_texturas = 0;
    char sky_box[6][1024] = {
        "def_sky_front.tga",
        "def_sky_back.tga",
        "def_sky_top.tga",
        "def_sky_bottom.tga",
        "def_sky_left.tga",
        "def_sky_right.tga"
    };


    lista_sprites_spc lista_aux;


    sprites_spc =
        (lista_sprites_spc *) malloc(sizeof(lista_sprites_spc) * 6);
    /* Otras inicializaciones */
    for (contador = 0; contador < 6; contador++) {
        lista_aux.textura = encola_textura(sky_box[contador], GL_RGB);
        _sis_msje("\tSky Box Blues %d", lista_aux.textura);
        memcpy(&sprites_spc[contador], &lista_aux,
               sizeof(lista_sprites_spc));

    }

    return SI;

}

int crea_estrellas(unsigned int numero)
{

    float z, y, x;
    unsigned int i;
    /* Punto aleatorio de una esfera de radio 6000 */

    estrellas = (float *) malloc(sizeof(float) * 4 * numero);

    for (i = 0; i < numero * 4; i += 4) {

        z = (float) (rand() % 6000);
//              z=(float)(i/8);

        y = rand() % ((int) sqrt(pow(6000, 2) - pow(z, 2)));
        x = sqrt(pow(6000, 2) - pow(y, 2) - pow(z, 2));
        if (rand() % 2 == 0)

            z = z * -1;
        if (rand() % 2 == 0)
            x = x * -1;
        if (rand() % 2 == 0)
            y = y * -1;
        estrellas[i] = x;
        estrellas[i + 1] = y;
        estrellas[i + 2] = z;
        estrellas[i + 3] = (float) (rand() % 2 + 1);
    }
    n_estrellas = numero;
}

int crea_polvo_espacial(unsigned int numero)
{

    float z, y, x;
    unsigned int i;
    /* Punto aleatorio de una esfera de radio 60 */

    polvo_espacial = (float *) malloc(sizeof(float) * 4 * numero);

    for (i = 0; i < numero * 4; i += 4) {

        z = (float) (rand() % 10);
        z = z - 5;

        y = (float) (rand() % 10);
        y = y - 5;
        x = (float) (rand() % 10);
        x = x - 5;
        polvo_espacial[i] = x;
        polvo_espacial[i + 1] = y;
        polvo_espacial[i + 2] = z;
        polvo_espacial[i + 3] = (float) (rand() % 2 + 1);
    }
    n_polvo_espacial = numero;
}
