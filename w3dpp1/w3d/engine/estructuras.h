// En este fichero se definen estructuras nuevas que utilizaremos. Como es un fichero que se incluirá en muchos ficheros
// fuente, se "defiende" con el comando de preprocesador ifndef. Esto lo que hace es que si el compilador ya ha leído estas
// estructuras, no las vuelva a leer.





#ifndef _ESTRUCTOK
#define _ESTRUCTOK
#define MAD_MAGIC 20


/* Estructura del array en memoria de los sprites del fondo */

typedef struct lista_sprites_spc_tag {
    unsigned int textura;
		float matriz[4][4];
		float tam_x;
		float tam_y;
} lista_sprites_spc;



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


typedef struct laser_tag {
        float color[4];
        float posicion[3];
        float direccion[3];
        unsigned int ttl;
} laser_struct;


#endif

