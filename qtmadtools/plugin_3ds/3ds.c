/***************************************************************************
                          3ds.c  -  description
                             -------------------
    begin                : mié jul 17 2002
    copyright            : (C) 2002 by neuralgya
    email                : neuralgya@mail.berlios.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// En este fichero se definen estructuras nuevas que utilizaremos. Como es un fichero que se incluirá en muchos ficheros
// fuente, se "defiende" con el comando de preprocesador ifndef. Esto lo que hace es que si el compilador ya ha leído estas
// estructuras, no las vuelva a leer.



#ifdef W3DWIN32
#include <windows.h>
#define DLLExport __declspec(dllexport) __cdecl
#define DLLExport_ __declspec(dllexport) __cdecl
#endif

#ifdef LINUX
#define DLLExport
#define DLLExport_
#endif

extern "C" {

DLLExport char* mostrar_autor(void);
DLLExport char* mostrar_nombre(void);
DLLExport char* mostrar_info(void);
DLLExport int* mostrar_version(void);
DLLExport int* mostrar_fecha(void);
DLLExport char* mostrar_extension(void);
DLLExport_ int importar_modelo(char *fichero,void **model_tag);

}

extern int import_model(char *fichero,struct LTriangle2 *tri_3ds);

#ifndef _ESTRUCTOK
#define _ESTRUCTOK
#define MAD_MAGIC 20

/*! Estructura de la variable de configuración */


typedef struct vector_tag {

float x, y, z;

float u, v;

float Nx, Ny, Nz;          // Normales

} vertice;



typedef struct tag_face {

vertice vertices[3];       // Puntos del triángulo
} cara;



typedef struct tag_object {

    unsigned int n_caras;      // Numero de caras
    cara *triangulos;           // Matriz de caras
    char id_textura[16];        // Fichero de textura
    unsigned int n_textura;     // Identificación de textura
    float x, y, z;              // Posición en el espacio
    vertice base[3];            // Base;
} modelo;


#endif

struct LVector4
{
    float x;
    float y;
    float z;
    float w;
};

struct LVector3
{
    float x;
    float y;
    float z;
};

struct LVector2
{
    float x;
    float y;
};



struct LTriangle2
{
    struct     LVector4 vertices[3];
    struct     LVector3 vertexNormals[3];
    struct     LVector2 textureCoords[3];
    struct     LVector3 faceNormal;
    unsigned int materialId;
};





const char nombre[]="Importador 3DS";
const char autor[]="Augusto Beiro Salanova adaptado de L3DS de Lev Povalahev";
const char info[]="Importador de ficheros 3DS del 3DStudio";
const int version[3]={0,0,2};
const int fecha[3]={12,6,2002};
const char extension[]="*.3ds *.3DS";


DLLExport char * mostrar_autor(void){
	return (char *)&autor[0];
}
DLLExport char *mostrar_nombre(void){
        return (char *)&nombre[0];
}
DLLExport char *mostrar_info(void){
        return (char *)&info[0];
}
DLLExport int * mostrar_version(void){
        return (int *)&version[0];
}
DLLExport int * mostrar_fecha(void){
        return (int *)&fecha[0];
}
DLLExport char *mostrar_extension(void){
        return (char *)&extension[0];
}
DLLExport_ int importar_modelo(char *fichero,void **model_tag){

        struct LTriangle2 tri_3ds;
        int n,j,z;
        cara *tri;
        modelo *modelo_1;

/*      struct LTriangle2
            {
            LVector4 vertices[3];
            LVector3 vertexNormals[3];
            LVector2 textureCoords[3];
            LVector3 faceNormal;
            uint materialId;
            };
*/
        n=import_model(fichero,&tri_3ds);
        printf("Importando %d triangulos\n",n);

        modelo_1 = (modelo *) malloc(sizeof(modelo));
        if (modelo_1==NULL)
      	{
        	printf("Error alojando memoria\n");
      	return -1;
	      }
        memset(modelo_1->base, 0, (sizeof(vertice) * 3));
        modelo_1->x = 0.0;
        modelo_1->y = 0.0;
        modelo_1->z = 0.0;
        modelo_1->n_caras=n;
        modelo_1->triangulos = (cara *) malloc(sizeof(cara) * modelo_1->n_caras);


        fflush(stdout);
        j=0;
        while (import_model(fichero,&tri_3ds)!=-1) {
          for (z=0;z<3;z++) {
            modelo_1->triangulos[j].vertices[z].x=tri_3ds.vertices[z].x/100.0f;
            modelo_1->triangulos[j].vertices[z].y=tri_3ds.vertices[z].y/100.0f;
            modelo_1->triangulos[j].vertices[z].z=tri_3ds.vertices[z].z/100.0f;
            modelo_1->triangulos[j].vertices[z].u=tri_3ds.textureCoords[z].x;
            modelo_1->triangulos[j].vertices[z].v=tri_3ds.textureCoords[z].y;
            modelo_1->triangulos[j].vertices[z].Nx=tri_3ds.vertexNormals[z].x;
            modelo_1->triangulos[j].vertices[z].Ny=tri_3ds.vertexNormals[z].y;
            modelo_1->triangulos[j].vertices[z].Nz=tri_3ds.vertexNormals[z].z;
          }
        j++;
        }


        *model_tag=modelo_1;
        return 1;


}


