#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// En este fichero se definen estructuras nuevas que utilizaremos. Como es un fichero que se incluirá en muchos ficheros
// fuente, se "defiende" con el comando de preprocesador ifndef. Esto lo que hace es que si el compilador ya ha leído estas
// estructuras, no las vuelva a leer.





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


const char nombre[]="Importador mad";
const char autor[]="Augusto Beiro Salanova";
const char info[]="Importador de ficheros MAD nativos de WorldSpace 3D";
const int version[3]={0,0,1};
const int fecha[3]={12,6,2002};
const char extension[]="*.mad";


extern char *mostrar_autor(void){
	return (char *)&autor[0];
}
extern char *mostrar_nombre(void){
        return (char *)&nombre[0];
}
extern char *mostrar_info(void){
        return (char *)&info[0];
}
extern int *mostrar_version(void){
        return (int *)&version[0];
}
extern int *mostrar_fecha(void){
        return (int *)&fecha[0];
}
extern char *mostrar_extension(void){
        return (char *)&extension[0];
}
extern int importar_modelo(char *fichero,void **model_tag){


    FILE *f_object;
    int j;
    cara *tri;
    char magic;

    modelo *modelo_1;

    
    modelo_1 = (modelo *) malloc(sizeof(modelo));
    if (modelo_1==NULL)
	{
	printf("Error alojando memoria\n");
	return -1;
	}
	
    printf("Dirección mem. %d\n",(int)model_tag);
	 printf("Dirección mem. %d\n",(int)modelo_1);
    printf("------------------------\n");

	printf("Cargando modelo %s\n", fichero);

    f_object = fopen(fichero, "rb");
    if (f_object == NULL) {
        printf("No pude encontrar %s\n", fichero);
        return -1;
    }

    fread(&magic, 1, 1, f_object);

    if (magic != MAD_MAGIC) {
        printf("Fichero no válido\n");
        return -1;
    }

    fread(modelo_1, sizeof(modelo), 1, f_object);

    memset(modelo_1->base, 0, (sizeof(vertice) * 3));
    modelo_1->x = 0.0;
    modelo_1->y = 0.0;
    modelo_1->z = 0.0;

    tri = (cara *) malloc(sizeof(cara) * modelo_1->n_caras);
    modelo_1->triangulos = tri;
    for (j = 0; j < modelo_1->n_caras; j++) {
        fread(&(modelo_1->triangulos[j]), sizeof(cara), 1, f_object);
    }
    printf("Modelo cargado con %d caras\n", j);
    fichero[0]='\0';	
    *model_tag=modelo_1;
     printf("Dirección mem nueva. %d\n",(int)model_tag);
    
	fclose(f_object);
    return 1;

}

