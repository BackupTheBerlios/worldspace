#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// En este fichero se definen estructuras nuevas que utilizaremos. Como es un fichero que se incluirá en muchos ficheros
// fuente, se "defiende" con el comando de preprocesador ifndef. Esto lo que hace es que si el compilador ya ha leído estas
// estructuras, no las vuelva a leer.

#ifdef W3DWIN32
#include <windows.h>
#define DLLExport __declspec(dllexport) __cdecl
#define DLLExport_ DLLExport
#endif

#ifdef LINUX
#define DLLExport 
#define DLLExport_
#endif

DLLExport char* mostrar_autor(void);
DLLExport char* mostrar_nombre(void);
DLLExport char* mostrar_info(void);
DLLExport int*  mostrar_version(void);
DLLExport int * mostrar_fecha(void);
DLLExport char* mostrar_extension(void);
DLLExport_ int importar_modelo(char *fichero,void **model_tag);


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




const char nombre[]="Importador obj";
const char autor[]="Augusto Beiro Salanova";
const char info[]="Importador de ficheros OBJ";
const int version[3]={0,0,1};
const int fecha[3]={12,6,2002};
const char extension[]="*.obj *.OBJ";


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


    FILE *file;
    int j;
    cara *tri;
    char magic;
    modelo *modelo_1;
 		int aux_size;
    int n_puntos,n_normales,n_coords_uv,n_caras;

    struct p3f {
        float x,y,z;
    };
    struct p2f  {
        float x,y;
    } ;

    struct  p3i{
        int v1,vt1,vn1;
        int v2,vt2,vn2;
        int v3,vt3,vn3;

    } ;

    struct p3f *lista_puntos;
    struct p3f *lista_normales;
    struct p2f *lista_uv;
    struct p3i *lista_caras;

    char linea[1025];
    char linea2[1025];

   	/* Alojamos memoria para el modelo */
    modelo_1 = (modelo *) malloc(sizeof(modelo));
    if (modelo_1==NULL)
	{
	printf("Error alojando memoria\n");
	return -1;
	}

/* Abrimos en file el fichero fuente exportado por el anim8or */
    file = fopen(fichero, "rt");
    if (file == NULL)
    	return -1;



    printf("Primer paso: Calculando tamaños\n");
    /*  PUNTOS */
    aux_size=0;        //Contador auxiliar
    rewind(file);
    while(!(feof(file))) {
        fgets(linea,1024,file);
        if (strstr(linea,"v ")!=NULL)
                     aux_size++;
    }


    printf("He encontrado un total de %d puntos\n",aux_size);

    /* ya tenemos el número de puntos */
    n_puntos=aux_size;

    /*  NORMALES */

    aux_size=0;        //Contador auxiliar
    rewind(file);
    while(!(feof(file))) {
        fgets(linea,1024,file);
        if (strstr(linea,"vn ")!=NULL)

                aux_size++;
    }


    printf("He encontrado un total de %d normales\n",aux_size);

    /* ya tenemos el número de puntos */
    n_normales=aux_size;

    /*  Coordenadas UV de mapeo de texturas */

    aux_size=0;        //Contador auxiliar
    rewind(file);
    while(!(feof(file))) {
        fgets(linea,1024,file);
        if (strstr(linea,"vt ")!=NULL)
          aux_size++;
    }


    printf("He encontrado un total de %d coordenadas uv\n",aux_size);

    /* ya tenemos el número de puntos */
    n_coords_uv=aux_size;

    /*  Caras */

    aux_size=0;        //Contador auxiliar
    rewind(file);

    while(!(feof(file))) {
        if (fgets(linea,1024,file)==NULL)
            break;
        if (strstr(linea,"f ")!=NULL)
                aux_size++;
    }


    printf("He encontrado un total de %d caras\n",aux_size);

    /* ya tenemos el número de caras*/
    n_caras=aux_size;


    /* Ahora ya tenemos datos para almacenar memoria*/
    /* int n_puntos,n_normales,n_coords_uv,n_caras */
    lista_puntos=(struct p3f *)malloc(sizeof(struct p3f)*n_puntos);
		if (lista_puntos==NULL)
			return -1;
    printf ("Matriz de puntos %d bytes \n",sizeof(struct p3f)*n_puntos);

    lista_normales=(struct p3f *)malloc(sizeof(struct p3f)*n_normales);
		if (lista_normales==NULL)
			return -1;
    printf ("Matriz de normales %d bytes \n",sizeof(struct p3f)*n_normales);

    lista_uv=(struct p2f *)malloc(sizeof(struct p2f)*n_coords_uv);
		if (lista_uv==NULL)
			return -1;
    printf ("Matriz de coords. uv %d bytes \n",sizeof(struct p2f)*n_coords_uv);

    lista_caras=(struct p3i *)malloc(sizeof(struct p3i)*n_caras);
		if (lista_caras==NULL)
			return -1;
    printf ("Matriz de caras %d bytes \n",sizeof(struct p3i)*n_caras);

    /* Cerramos fichero y volvemos a empezar */
    fclose(file);

    /* Abrimos en file el fichero OBJ*/
    file = fopen(fichero, "rt");
    if (file == NULL)
    	return -1;

    printf("Segundo paso: Alojando estructuras en memoria\n");
    /*  PUNTOS */
    aux_size=0;        //Contador auxiliar
    while(!(feof(file))) {
        if (fgets(linea,1024,file)==NULL)
					break;
        if (strstr(linea,"v ")!=NULL)  {
 								//printf("%d - %s",aux_size,linea);fflush(stdout);
                sscanf(linea,"v %f %f %f",&lista_puntos[aux_size].x,&lista_puntos[aux_size].y,&lista_puntos[aux_size].z);
                aux_size++;

        }
    }



		printf("Puntos fuera\n");fflush(stdout);
    /*  NORMALES */

    aux_size=0;        //Contador auxiliar
    rewind(file);
    while(!(feof(file))) {
         if (fgets(linea,1024,file)==NULL)
					break;
        if (strstr(linea,"vn ")!=NULL)
        {
                sscanf(linea,"vn %f %f %f",&lista_normales[aux_size].x,&lista_normales[aux_size].y,&lista_normales[aux_size].z);
 								//printf("%d - %s",aux_size,linea);fflush(stdout);
                aux_size++;
        }

    }

		printf("Normales fuera\n");fflush(stdout);
    /*  Coordenadas UV de mapeo de texturas */

    aux_size=0;        //Contador auxiliar
    rewind(file);
    while(!(feof(file))) {
                if (fgets(linea,1024,file)==NULL)
					break;
        if (strstr(linea,"vt ")!=NULL)
         {
                sscanf(linea,"vt %f %f",&lista_uv[aux_size].x,&lista_uv[aux_size].y);
 								//printf("%d - %s",aux_size,linea);fflush(stdout);

                aux_size++;
        }
    }

 		printf("Mapeo UV fuera\n");fflush(stdout);

    /*  Caras */

    aux_size=0;        //Contador auxiliar
    rewind(file);
    while(!(feof(file))) {
                if (fgets(linea,1024,file)==NULL)
					break;
        if (strstr(linea,"f ")!=NULL)
        {
 							//printf("%d - %s",aux_size,linea);fflush(stdout);
                sscanf(linea,"f %d/%d/%d %d/%d/%d %d/%d/%d",
                &lista_caras[aux_size].v1,&lista_caras[aux_size].vt1,&lista_caras[aux_size].vn1,
                &lista_caras[aux_size].v2,&lista_caras[aux_size].vt2,&lista_caras[aux_size].vn2,
                &lista_caras[aux_size].v3,&lista_caras[aux_size].vt3,&lista_caras[aux_size].vn3);
								aux_size++;
        }
    }
		printf("Caras fuera\n");fflush(stdout);
       /* Y empezamos la conversión */

    fclose(file);
    modelo_1->n_caras = n_caras;
    modelo_1->x = 0;
    modelo_1->y = 0;
    modelo_1->z = 0;
    modelo_1->base[0].x = 1;
    modelo_1->base[0].y = 0;
    modelo_1->base[0].z = 0;
    modelo_1->base[1].x = 0;
    modelo_1->base[1].y = 1;
    modelo_1->base[1].z = 0;
    modelo_1->base[2].x = 0;
    modelo_1->base[2].y = 0;
    modelo_1->base[2].z = 1;
	  strcpy(modelo_1->id_textura, "");
    tri = (cara *) malloc(sizeof(cara) * modelo_1->n_caras);
    modelo_1->triangulos = tri;
		printf("Empezamos la conversion\n",linea);fflush(stdout);
	
	for (aux_size=0;aux_size<n_caras;aux_size++)
    {
    modelo_1->triangulos[aux_size].vertices[0].x=lista_puntos[lista_caras[aux_size].v1-1].x/100.0f;
    modelo_1->triangulos[aux_size].vertices[0].y=lista_puntos[lista_caras[aux_size].v1-1].y/100.0f;
    modelo_1->triangulos[aux_size].vertices[0].z=lista_puntos[lista_caras[aux_size].v1-1].z/100.0f;

    modelo_1->triangulos[aux_size].vertices[0].u=lista_uv[lista_caras[aux_size].vt1-1].x;
    modelo_1->triangulos[aux_size].vertices[0].v=lista_uv[lista_caras[aux_size].vt1-1].y;

    modelo_1->triangulos[aux_size].vertices[0].Nx=lista_normales[lista_caras[aux_size].vn1-1].x;
    modelo_1->triangulos[aux_size].vertices[0].Ny=lista_normales[lista_caras[aux_size].vn1-1].y;
    modelo_1->triangulos[aux_size].vertices[0].Nz=lista_normales[lista_caras[aux_size].vn1-1].z;

    modelo_1->triangulos[aux_size].vertices[1].x=lista_puntos[lista_caras[aux_size].v2-1].x/100.0f;
    modelo_1->triangulos[aux_size].vertices[1].y=lista_puntos[lista_caras[aux_size].v2-1].y/100.0f;
    modelo_1->triangulos[aux_size].vertices[1].z=lista_puntos[lista_caras[aux_size].v2-1].z/100.0f;

    modelo_1->triangulos[aux_size].vertices[1].u=lista_uv[lista_caras[aux_size].vt2-1].x;
    modelo_1->triangulos[aux_size].vertices[1].v=lista_uv[lista_caras[aux_size].vt2-1].y;

    modelo_1->triangulos[aux_size].vertices[1].Nx=lista_normales[lista_caras[aux_size].vn2-1].x;
    modelo_1->triangulos[aux_size].vertices[1].Ny=lista_normales[lista_caras[aux_size].vn2-1].y;
    modelo_1->triangulos[aux_size].vertices[1].Nz=lista_normales[lista_caras[aux_size].vn2-1].z;

    modelo_1->triangulos[aux_size].vertices[2].x=lista_puntos[lista_caras[aux_size].v3-1].x/100.0f;
    modelo_1->triangulos[aux_size].vertices[2].y=lista_puntos[lista_caras[aux_size].v3-1].y/100.0f;
    modelo_1->triangulos[aux_size].vertices[2].z=lista_puntos[lista_caras[aux_size].v3-1].z/100.0f;

    modelo_1->triangulos[aux_size].vertices[2].u=lista_uv[lista_caras[aux_size].vt3-1].x;
    modelo_1->triangulos[aux_size].vertices[2].v=lista_uv[lista_caras[aux_size].vt3-1].y;

    modelo_1->triangulos[aux_size].vertices[2].Nx=lista_normales[lista_caras[aux_size].vn3-1].x;
    modelo_1->triangulos[aux_size].vertices[2].Ny=lista_normales[lista_caras[aux_size].vn3-1].y;
    modelo_1->triangulos[aux_size].vertices[2].Nz=lista_normales[lista_caras[aux_size].vn3-1].z;
  	}

  	printf("Conversión hecha con éxito (espero...)\n");


    *model_tag=modelo_1;
     printf("Dirección mem nueva. %d\n",(int)model_tag);

		return 1;

}

