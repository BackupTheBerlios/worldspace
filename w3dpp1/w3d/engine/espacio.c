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


int carga_espacio(char *fichero_spc) {

	int contador=0;
	int contador2=0;
	char fichero[1024];
	FILE *fich;
	char textura_f[1024];
	char textura_f_old[1024];

	char *textura_datos;
	int tam_x,tam_y;
	unsigned int numero_texturas=0;


	lista_sprites_spc	lista_aux;
	

	strcpy(fichero,"/espacios/");
	strcat(fichero,fichero_spc);
	
	_sis_msje("\n\t\t\tCargando sprites del escenario...%s",fichero);

	fich=abre_fichero(fichero, "rt");

	if (fich == NULL) {
			_sis_msje("\n\t\t\tNo pude cargar fichero %s [KO])\n",fichero);
			return NO;
	}

	while (!feof(fich)) {
		fscanf(fich,"<TIPO>SPRITE\n");
		fscanf(fich,"<TEXTURA>%s\n",&textura_f);
		fscanf(fich,"<POSICION>%f,%f,%f\n",&lista_aux.matriz[0][3],&lista_aux.matriz[1][3],&lista_aux.matriz[2][3]);
		fscanf(fich,"<EJE_X>%f,%f,%f\n",&lista_aux.matriz[0][0],&lista_aux.matriz[1][0],&lista_aux.matriz[2][0]);
		fscanf(fich,"<EJE_Y>%f,%f,%f\n",&lista_aux.matriz[0][1],&lista_aux.matriz[1][1],&lista_aux.matriz[2][1]);
		fscanf(fich,"<EJE_Z>%f,%f,%f\n",&lista_aux.matriz[0][2],&lista_aux.matriz[1][2],&lista_aux.matriz[2][2]);
		fscanf(fich,"<TAMA_X>%f\n",&lista_aux.tam_x);
		fscanf(fich,"<TAMA_Y>%f\n",&lista_aux.tam_y);
		contador++;
    }
    n_sprites_spc=contador;

    fclose(fich);
    fich=abre_fichero(fichero, "rt");

	if (fich == NULL) {
			_sis_msje("\n\t\t\tNo pude cargar fichero %s (tal vez no exista)[KO]",fichero);
			return NO;
	}
	sprites_spc=(lista_sprites_spc *)malloc(sizeof(lista_sprites_spc)*contador);

	while (!feof(fich)) {
		fscanf(fich,"<TIPO>SPRITE\n");
		fscanf(fich,"<TEXTURA>%s\n",&textura_f);
		fscanf(fich,"<POSICION>%f,%f,%f\n",&lista_aux.matriz[3][0],&lista_aux.matriz[3][1],&lista_aux.matriz[3][2]);
		fscanf(fich,"<EJE_X>%f,%f,%f\n",&lista_aux.matriz[0][0],&lista_aux.matriz[0][1],&lista_aux.matriz[0][2]);
		fscanf(fich,"<EJE_Y>%f,%f,%f\n",&lista_aux.matriz[1][0],&lista_aux.matriz[1][1],&lista_aux.matriz[1][2]);
		fscanf(fich,"<EJE_Z>%f,%f,%f\n",&lista_aux.matriz[2][0],&lista_aux.matriz[2][1],&lista_aux.matriz[2][2]);
		fscanf(fich,"<TAMA_X>%f\n",&lista_aux.tam_x);
		fscanf(fich,"<TAMA_Y>%f\n",&lista_aux.tam_y);

    /* Otras inicializaciones */

		lista_aux.matriz[0][3]=0.0f;
		lista_aux.matriz[1][3]=0.0f;
		lista_aux.matriz[2][3]=0.0f;
		lista_aux.matriz[3][3]=1.0f;
		lista_aux.textura=encola_textura(textura_f);
		_sis_msje(" %d",lista_aux.textura);
		memcpy(&sprites_spc[contador2],&lista_aux,sizeof(lista_sprites_spc));

		contador2++;
		}
		return SI;

}

int crea_estrellas(unsigned int numero) {

    float z,y,x;
    unsigned int i;
	/* Punto aleatorio de una esfera de radio 6000 */

		estrellas=(float *)malloc(sizeof(float)*4*numero);

	for (i=0;i<numero*4;i+=4) {

		z=(float)(rand() % 6000);
//		z=(float)(i/8);

		y=rand()%((int)sqrt(pow(6000,2)-pow(z,2)));
		x=sqrt(pow(6000,2)-pow(y,2)-pow(z,2));
		if (rand()%2==0)

			z=z*-1;
		if (rand()%2==0)
			x=x*-1;
		if (rand()%2==0)
			y=y*-1;
		estrellas[i]=x;
		estrellas[i+1]=y;
		estrellas[i+2]=z;
		estrellas[i+3]=(float)(rand()%2+1);
	}
	n_estrellas=numero;
}
