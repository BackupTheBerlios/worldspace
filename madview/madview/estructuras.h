// En este fichero se definen estructuras nuevas que utilizaremos. Como es un fichero que se incluirá en muchos ficheros
// fuente, se "defiende" con el comando de preprocesador ifndef. Esto lo que hace es que si el compilador ya ha leído estas
// estructuras, no las vuelva a leer.

 



#ifndef _ESTRUCTOK
#define _ESTRUCTOK
#define MAD_MAGIC 20
    
/*! Estructura de la variable de configuración */ 
    
typedef struct config_tag {
    
short int SCREEN_SIZE_X;
    
short int SCREEN_SIZE_Y;
    
char FULLSCREEN;
    
char dir[1024];

} configuracion;



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


#endif                          /* 
 */
