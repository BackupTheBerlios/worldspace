#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// En este fichero se definen estructuras nuevas que utilizaremos. Como es un fichero que se incluirá en muchos ficheros
// fuente, se "defiende" con el comando de preprocesador ifndef. Esto lo que hace es que si el compilador ya ha leído estas
// estructuras, no las vuelva a leer.

#ifdef W3DWIN32
#include <windows.h>
#define DLLExport __declspec(dllexport) __cdecl
#define DLLExport_ __declspec(dllexport) __cdecl
#endif

#ifdef LINUX
#define DLLExport *
#define DLLExport_ 
#endif

char DLLExport mostrar_autor(void);
char DLLExport mostrar_nombre(void);
char DLLExport mostrar_info(void);
int  DLLExport mostrar_version(void);
int  DLLExport mostrar_fecha(void);
char DLLExport mostrar_extension(void);
int  DLLExport_ importar_modelo(char *fichero,void **model_tag);






#ifndef _ESTRUCTOK
#define _ESTRUCTOK
#define MAD_MAGIC 20


/* Estas normales fueron definidas por los chicos de id. Las he sacado

de un pack de utilidades que sacaron. Todos los modelos del Quake2 las utilizan,

solo éstas */






typedef unsigned char byte;



typedef struct {

    int magic;			// Char IDP2

    int version;		// 8

    int skinWidth;

    int skinHeight;

    int frameSize;

    int numSkins;

    int numVertices;

    int numTexCoords;

    int numTriangles;

    int numGlCommands;

    int numFrames;

    int offsetSkins;

    int offsetTexCoords;

    int offsetTriangles;

    int offsetFrames;

    int offsetGlCommands;

    int offsetEnd;

} model_t;







typedef struct			// Coordenadas no reales

{

    byte vertex[3];

    byte lightNormalIndex;

} vertex_t;



typedef struct			// real_coord=vertex*scale+translate



{

    float scale[3];

    float translate[3];

    char name[16];

//triangleVertex_t vertices[1]; // Up to num_triangles

} frame_t;



typedef struct {

    short vertexIndices[3];

    short textureIndices[3];

} triangle_t;



typedef struct {

    short s, t;

} textureCoordinate_t;



#define MAGIC 844121161

#define MD2VERSION 8




typedef struct vector_tag {

float x, y, z;

float u, v;

float Nx, Ny, Nz;          // Normales

} vertice;



typedef struct tag_face {

vertice vertices[3];       // Puntos del triángulo
} cara;



typedef struct tag_object {

    unsigned int n_caras;       // Numero de caras
    cara *triangulos;           // Matriz de caras
    char id_textura[16];        // Fichero de textura
    unsigned int n_textura;     // Identificación de textura
    float x, y, z;              // Posición en el espacio
    vertice base[3];            // Base;
} modelo;


#endif


const char nombre[]="Importador md2";
const char autor[]="Augusto Beiro Salanova";
const char info[]="Importador de ficheros MD2 nativos del Quake2";
const int version[3]={0,0,1};
const int fecha[3]={17,6,2002};
const char extension[]="*.md2";


char DLLExport mostrar_autor(void){
	return (char *)&autor[0];
}
char DLLExport mostrar_nombre(void){
        return (char *)&nombre[0];
}
char DLLExport mostrar_info(void){
        return (char *)&info[0];
}
int  DLLExport mostrar_version(void){
        return (int *)&version[0];
}
int  DLLExport  mostrar_fecha(void){
        return (int *)&fecha[0];
}
char DLLExport mostrar_extension(void){
        return (char *)&extension[0];
}
int  DLLExport_ importar_modelo(char *fichero,void **model_tag){


    float avertexnormals[162][3] = {

    {-0.525731, 0.000000, 0.850651},

    {-0.442863, 0.238856, 0.864188},

    {-0.295242, 0.000000, 0.955423},

    {-0.309017, 0.500000, 0.809017},

    {-0.162460, 0.262866, 0.951056},

    {0.000000, 0.000000, 1.000000},

    {0.000000, 0.850651, 0.525731},

    {-0.147621, 0.716567, 0.681718},

    {0.147621, 0.716567, 0.681718},

    {0.000000, 0.525731, 0.850651},

    {0.309017, 0.500000, 0.809017},

    {0.525731, 0.000000, 0.850651},

    {0.295242, 0.000000, 0.955423},

    {0.442863, 0.238856, 0.864188},

    {0.162460, 0.262866, 0.951056},

    {-0.681718, 0.147621, 0.716567},

    {-0.809017, 0.309017, 0.500000},

    {-0.587785, 0.425325, 0.688191},

    {-0.850651, 0.525731, 0.000000},

    {-0.864188, 0.442863, 0.238856},

    {-0.716567, 0.681718, 0.147621},

    {-0.688191, 0.587785, 0.425325},

    {-0.500000, 0.809017, 0.309017},

    {-0.238856, 0.864188, 0.442863},

    {-0.425325, 0.688191, 0.587785},

    {-0.716567, 0.681718, -0.147621},

    {-0.500000, 0.809017, -0.309017},

    {-0.525731, 0.850651, 0.000000},

    {0.000000, 0.850651, -0.525731},

    {-0.238856, 0.864188, -0.442863},

    {0.000000, 0.955423, -0.295242},

    {-0.262866, 0.951056, -0.162460},

    {0.000000, 1.000000, 0.000000},

    {0.000000, 0.955423, 0.295242},

    {-0.262866, 0.951056, 0.162460},

    {0.238856, 0.864188, 0.442863},

    {0.262866, 0.951056, 0.162460},

    {0.500000, 0.809017, 0.309017},

    {0.238856, 0.864188, -0.442863},

    {0.262866, 0.951056, -0.162460},

    {0.500000, 0.809017, -0.309017},

    {0.850651, 0.525731, 0.000000},

    {0.716567, 0.681718, 0.147621},

    {0.716567, 0.681718, -0.147621},

    {0.525731, 0.850651, 0.000000},

    {0.425325, 0.688191, 0.587785},

    {0.864188, 0.442863, 0.238856},

    {0.688191, 0.587785, 0.425325},

    {0.809017, 0.309017, 0.500000},

    {0.681718, 0.147621, 0.716567},

    {0.587785, 0.425325, 0.688191},

    {0.955423, 0.295242, 0.000000},

    {1.000000, 0.000000, 0.000000},

    {0.951056, 0.162460, 0.262866},

    {0.850651, -0.525731, 0.000000},

    {0.955423, -0.295242, 0.000000},

    {0.864188, -0.442863, 0.238856},

    {0.951056, -0.162460, 0.262866},

    {0.809017, -0.309017, 0.500000},

    {0.681718, -0.147621, 0.716567},

    {0.850651, 0.000000, 0.525731},

    {0.864188, 0.442863, -0.238856},

    {0.809017, 0.309017, -0.500000},

    {0.951056, 0.162460, -0.262866},

    {0.525731, 0.000000, -0.850651},

    {0.681718, 0.147621, -0.716567},

    {0.681718, -0.147621, -0.716567},

    {0.850651, 0.000000, -0.525731},

    {0.809017, -0.309017, -0.500000},

    {0.864188, -0.442863, -0.238856},

    {0.951056, -0.162460, -0.262866},

    {0.147621, 0.716567, -0.681718},

    {0.309017, 0.500000, -0.809017},

    {0.425325, 0.688191, -0.587785},

    {0.442863, 0.238856, -0.864188},

    {0.587785, 0.425325, -0.688191},

    {0.688191, 0.587785, -0.425325},

    {-0.147621, 0.716567, -0.681718},

    {-0.309017, 0.500000, -0.809017},

    {0.000000, 0.525731, -0.850651},

    {-0.525731, 0.000000, -0.850651},

    {-0.442863, 0.238856, -0.864188},

    {-0.295242, 0.000000, -0.955423},

    {-0.162460, 0.262866, -0.951056},

    {0.000000, 0.000000, -1.000000},

    {0.295242, 0.000000, -0.955423},

    {0.162460, 0.262866, -0.951056},

    {-0.442863, -0.238856, -0.864188},

    {-0.309017, -0.500000, -0.809017},

    {-0.162460, -0.262866, -0.951056},

    {0.000000, -0.850651, -0.525731},

    {-0.147621, -0.716567, -0.681718},

    {0.147621, -0.716567, -0.681718},

    {0.000000, -0.525731, -0.850651},

    {0.309017, -0.500000, -0.809017},

    {0.442863, -0.238856, -0.864188},

    {0.162460, -0.262866, -0.951056},

    {0.238856, -0.864188, -0.442863},

    {0.500000, -0.809017, -0.309017},

    {0.425325, -0.688191, -0.587785},

    {0.716567, -0.681718, -0.147621},

    {0.688191, -0.587785, -0.425325},

    {0.587785, -0.425325, -0.688191},

    {0.000000, -0.955423, -0.295242},

    {0.000000, -1.000000, 0.000000},

    {0.262866, -0.951056, -0.162460},

    {0.000000, -0.850651, 0.525731},

    {0.000000, -0.955423, 0.295242},

    {0.238856, -0.864188, 0.442863},

    {0.262866, -0.951056, 0.162460},

    {0.500000, -0.809017, 0.309017},

    {0.716567, -0.681718, 0.147621},

    {0.525731, -0.850651, 0.000000},

    {-0.238856, -0.864188, -0.442863},

    {-0.500000, -0.809017, -0.309017},

    {-0.262866, -0.951056, -0.162460},

    {-0.850651, -0.525731, 0.000000},

    {-0.716567, -0.681718, -0.147621},

    {-0.716567, -0.681718, 0.147621},

    {-0.525731, -0.850651, 0.000000},

    {-0.500000, -0.809017, 0.309017},

    {-0.238856, -0.864188, 0.442863},

    {-0.262866, -0.951056, 0.162460},

    {-0.864188, -0.442863, 0.238856},

    {-0.809017, -0.309017, 0.500000},

    {-0.688191, -0.587785, 0.425325},

    {-0.681718, -0.147621, 0.716567},

    {-0.442863, -0.238856, 0.864188},

    {-0.587785, -0.425325, 0.688191},

    {-0.309017, -0.500000, 0.809017},

    {-0.147621, -0.716567, 0.681718},

    {-0.425325, -0.688191, 0.587785},

    {-0.162460, -0.262866, 0.951056},

    {0.442863, -0.238856, 0.864188},

    {0.162460, -0.262866, 0.951056},

    {0.309017, -0.500000, 0.809017},

    {0.147621, -0.716567, 0.681718},

    {0.000000, -0.525731, 0.850651},

    {0.425325, -0.688191, 0.587785},

    {0.587785, -0.425325, 0.688191},

    {0.688191, -0.587785, 0.425325},

    {-0.955423, 0.295242, 0.000000},

    {-0.951056, 0.162460, 0.262866},

    {-1.000000, 0.000000, 0.000000},

    {-0.850651, 0.000000, 0.525731},

    {-0.955423, -0.295242, 0.000000},

    {-0.951056, -0.162460, 0.262866},

    {-0.864188, 0.442863, -0.238856},

    {-0.951056, 0.162460, -0.262866},

    {-0.809017, 0.309017, -0.500000},

    {-0.864188, -0.442863, -0.238856},

    {-0.951056, -0.162460, -0.262866},





    {-0.809017, -0.309017, -0.500000},

    {-0.681718, 0.147621, -0.716567},

    {-0.681718, -0.147621, -0.716567},

    {-0.850651, 0.000000, -0.525731},

    {-0.688191, 0.587785, -0.425325},

    {-0.587785, 0.425325, -0.688191},

    {-0.425325, 0.688191, -0.587785},

    {-0.425325, -0.688191, -0.587785},

    {-0.587785, -0.425325, -0.688191},

    {-0.688191, -0.587785, -0.425325},

};


    FILE *file;
    int j;
    cara *tri;



    model_t file_header;

    frame_t frame0;

    vertex_t *vertices;

    triangle_t *faces;

    textureCoordinate_t *coords;



    char *pointer;


    modelo *mad;
    cara *aux_face;
	char *aux;
    int aux_size;

    file = fopen(fichero, "rb");

    if (file == NULL) {
		return -1;

    }



    /* Cargamos la cabecera */



    fread(&file_header, sizeof(model_t), 1, file);





    if (file_header.magic!=MAGIC) {

        return -1;

    }

	    

    aux_size = sizeof(vertex_t) * file_header.numVertices;

    

    vertices = (vertex_t *) malloc(aux_size);

    if (vertices == NULL) {

	

	return -1;

    }



    /* Cargamos y usamos sólo el 1er frame */



    fseek(file, file_header.offsetFrames, SEEK_SET);

    fread(&frame0, sizeof(frame_t), 1, file);

    fread(vertices, sizeof(vertex_t) * file_header.numVertices, 1, file);


    /* reserva de memoria para la lista de triangulos */



    aux_size = sizeof(triangle_t) * file_header.numTriangles;


    faces = (triangle_t *) malloc(aux_size);

    if (faces == NULL) {

		return -1;

    }

    fseek(file, file_header.offsetTriangles, SEEK_SET);

    fread(faces, aux_size, 1, file);





    /* Sólo queda la lista de coordenadas de las texturas */



    aux_size = sizeof(textureCoordinate_t) * file_header.numTexCoords;

    coords = (textureCoordinate_t *) malloc(aux_size);

    if (coords == NULL) {

		return -1;

    }

    fseek(file, file_header.offsetTexCoords, SEEK_SET);

    fread(coords, aux_size, 1, file);



    /* El modelo ya se ha cargado */

   mad=(modelo *)malloc(sizeof(modelo));

	printf("Dirección mem. %d\n",(int)model_tag);
	printf("Dirección mem. %d\n",(int)mad);
    printf("------------------------\n");

    

    /* Y empezamos la conversión */



    mad->n_caras = file_header.numTriangles;
	printf("Caras %d\n",mad->n_caras);

    mad->x = 0;

    mad->y = 0;

    mad->z = 0;

    mad->base[0].x = 1;

    mad->base[0].y = 0;

    mad->base[0].z = 0;

    mad->base[1].x = 0;

    mad->base[1].y = 1;

    mad->base[1].z = 0;

    mad->base[2].x = 0;

    mad->base[2].y = 0;

    mad->base[2].z = 1;

	aux_face=(cara *) malloc(sizeof(cara) * mad->n_caras);
    mad->triangulos=aux_face;


    for (aux_size = 0; aux_size < file_header.numTriangles; aux_size++) {



	aux_face[aux_size].vertices[2].x =

	    (vertices[faces[aux_size].vertexIndices[0]].vertex[0] *

	     frame0.scale[0] + frame0.translate[0]) /600 ;

	aux_face[aux_size].vertices[2].y =

	    (vertices[faces[aux_size].vertexIndices[0]].vertex[1] *

	     frame0.scale[1] + frame0.translate[1])/600 ;

	aux_face[aux_size].vertices[2].z =

	    (vertices[faces[aux_size].vertexIndices[0]].vertex[2] *

	     frame0.scale[2] + frame0.translate[2]) /600;

	aux_face[aux_size].vertices[2].u =

	    (float) (coords[faces[aux_size].textureIndices[0]].s) * 256 /

	    (file_header.skinWidth * 255);

	aux_face[aux_size].vertices[2].v =

	    (float) (coords[faces[aux_size].textureIndices[0]].t) * 256 /

	    (file_header.skinHeight * 255);



	aux_face[aux_size].vertices[1].x =

	    (vertices[faces[aux_size].vertexIndices[1]].vertex[0] *

	     frame0.scale[0] + frame0.translate[0])/600 ;

	aux_face[aux_size].vertices[1].y =

	    (vertices[faces[aux_size].vertexIndices[1]].vertex[1] *

	     frame0.scale[1] + frame0.translate[1])/600 ;

	aux_face[aux_size].vertices[1].z =

	    (vertices[faces[aux_size].vertexIndices[1]].vertex[2] *

	     frame0.scale[2] + frame0.translate[2]) /600;

	aux_face[aux_size].vertices[1].u =

	    (float) (coords[faces[aux_size].textureIndices[1]].s) * 256 /

	    (file_header.skinWidth * 255);

	aux_face[aux_size].vertices[1].v =

	    (float) (coords[faces[aux_size].textureIndices[1]].t) * 256 /

	    (file_header.skinHeight * 255);



	aux_face[aux_size].vertices[0].x =

	    (vertices[faces[aux_size].vertexIndices[2]].vertex[0] *

	     frame0.scale[0] + frame0.translate[0]) /600;

	aux_face[aux_size].vertices[0].y =

	    (vertices[faces[aux_size].vertexIndices[2]].vertex[1] *

	     frame0.scale[1] + frame0.translate[1]) /600;

	aux_face[aux_size].vertices[0].z =

	    (vertices[faces[aux_size].vertexIndices[2]].vertex[2] *

	     frame0.scale[2] + frame0.translate[2]) /600;

	aux_face[aux_size].vertices[0].u =

	    (float) (coords[faces[aux_size].textureIndices[2]].s) * 256 /

	    (file_header.skinWidth * 255);

	aux_face[aux_size].vertices[0].v =

	    (float) (coords[faces[aux_size].textureIndices[2]].t) * 256 /

	    (file_header.skinHeight * 255);



	/* Ponemos las normales */



	aux_face[aux_size].vertices[2].Nx=avertexnormals[vertices[faces[aux_size].vertexIndices[0]].lightNormalIndex][0];

	aux_face[aux_size].vertices[2].Ny=avertexnormals[vertices[faces[aux_size].vertexIndices[0]].lightNormalIndex][1];

    aux_face[aux_size].vertices[2].Nz=avertexnormals[vertices[faces[aux_size].vertexIndices[0]].lightNormalIndex][2];

    

    aux_face[aux_size].vertices[1].Nx =avertexnormals[vertices[faces[aux_size].vertexIndices[1]].lightNormalIndex][0];

	aux_face[aux_size].vertices[1].Ny=avertexnormals[vertices[faces[aux_size].vertexIndices[1]].lightNormalIndex][1];

    aux_face[aux_size].vertices[1].Nz=avertexnormals[vertices[faces[aux_size].vertexIndices[1]].lightNormalIndex][2];



    aux_face[aux_size].vertices[0].Nx =avertexnormals[vertices[faces[aux_size].vertexIndices[2]].lightNormalIndex][0];

	aux_face[aux_size].vertices[0].Ny=avertexnormals[vertices[faces[aux_size].vertexIndices[2]].lightNormalIndex][1];

    aux_face[aux_size].vertices[0].Nz=avertexnormals[vertices[faces[aux_size].vertexIndices[2]].lightNormalIndex][2];

    }
	
    *model_tag=mad;
     printf("Dirección mem nueva. %d\n",(int)model_tag);
    
	fclose(file);
    return 1;

}

