/* md22mad conversor de ficheros md2 a ficheros mad */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* Estas normales fueron definidas por los chicos de id. Las he sacado
de un pack de utilidades que sacaron. Todos los modelos del Quake2 las utilizan,
solo éstas */

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



#include "estructuras.h"

int main(int argc, char *argv[])
{
    FILE *file, *mad_out;
    model_t file_header;
    frame_t frame0;
    vertex_t *vertices;
    triangle_t *faces;
    textureCoordinate_t *coords;
    float CONF;
    char skinname[64];
    char *pointer;
    char madname[256];
	char magic=MAD_MAGIC;

    modelo mad;
    cara aux_face;
	char *aux;

    int aux_size,j;


	printf("md22mad version %d. variante GL_BACK\n",FECHA);
	printf("Distribuido bajo la licencia GPL. Proyecto WorldSpace 3d\n");
    if (argc < 2) {
	printf("Usa md22mad <fich.md2> [factor_de_conversion]\n");
    getchar();
	return -1;
    }

	aux = argv[1];
	for (j = strlen(argv[1]) - 1; j >= 0; j--)
	    if (aux[j] == '.')
		break;
	sprintf(madname, "%s", argv[1]);
	
   if (j!=-1)
	madname[j]='\0';
   strcat(madname,".mad");


    file = fopen(argv[1], "rb");
    if (file == NULL) {
	
	return -1;
    }
    if (argc>2)
        CONF=atof(argv[2]);
	else
  		CONF=200;

    /* Cargamos la cabecera */

    fread(&file_header, sizeof(model_t), 1, file);

    printf("Magic number : %u\n", file_header.magic);
    if (file_header.magic!=MAGIC) {
        printf("Fichero corrupto\n");
        getchar();
        return -1;
    }
    printf("Version : %u\n", file_header.version);
    printf("Tamaño de Skin %u-%u\n", file_header.skinWidth,
	   file_header.skinHeight);
    printf("tamaño de frame %u  Nº de Skins %u \n", file_header.frameSize,
	   file_header.numSkins);
    printf("Vertices %u  Triangulos (caras) %u\n", file_header.numVertices,
	   file_header.numTriangles);
    printf("Total (frames) %u\n", file_header.numFrames);
    printf("Total (tamaño) %u\n", file_header.offsetEnd);

    /* reserva de memoria para la lista de vertices */

    aux_size = sizeof(vertex_t) * file_header.numVertices;
    printf("Reservando memoria para la lista de vertices... (%u bytes)\n", aux_size);
    vertices = (vertex_t *) malloc(aux_size);
    if (vertices == NULL) {
	perror(NULL);
	return -1;
    }

    /* Cargamos y usamos sólo el 1er frame */

    printf("Cargando frame uno... ");
    fseek(file, file_header.offsetFrames, SEEK_SET);
    fread(&frame0, sizeof(frame_t), 1, file);
    printf("%s\n", frame0.name);
    fread(vertices, sizeof(vertex_t) * file_header.numVertices, 1, file);



    /* reserva de memoria para la lista de triangulos */

    aux_size = sizeof(triangle_t) * file_header.numTriangles;
    printf("Reservando memoria para la lista de triangulos... (%u bytes)\n",
	   aux_size);
    faces = (triangle_t *) malloc(aux_size);
    if (faces == NULL) {
	perror(NULL);
	return -1;
    }
    fseek(file, file_header.offsetTriangles, SEEK_SET);
    fread(faces, aux_size, 1, file);


    /* Sólo queda la lista de coordenadas de las texturas */

    aux_size = sizeof(textureCoordinate_t) * file_header.numTexCoords;
    printf("Reservando memoria para la lista de coordenadas de texturas...(%u bytes)\n",
	 aux_size);
    coords = (textureCoordinate_t *) malloc(aux_size);
    if (coords == NULL) {
	perror(NULL);
	return -1;
    }
    fseek(file, file_header.offsetTexCoords, SEEK_SET);
    fread(coords, aux_size, 1, file);

    /* El modelo ya se ha cargado
       Ahora vamos a jugar un poco con el skin */

    if (file_header.numSkins == 0) {
	printf("Hey: Modelo sin skin definido, se usará el skin por defecto\n");
	strcpy(mad.id_textura, "default.tga");
    } else {
	fseek(file, file_header.offsetSkins, SEEK_SET);
	fread(&skinname[0], 64, 1, file);
	printf("Skin %s (caracteres) %d\n", skinname,
	       strlen(skinname));
	pointer = &skinname[0];
	for (aux_size = strlen(skinname) - 1; aux_size >= 0; aux_size--)
	    if (pointer[aux_size] == '/')
		break;

	pointer = (&skinname[aux_size]) + 1;
	printf("Usamos solo el 1er skin...%s\n", pointer);
	strcpy(mad.id_textura, pointer);
	mad.id_textura[strlen(mad.id_textura) - 3] = '\0';
	strcat(mad.id_textura, "tga");
    }

    /* Y empezamos la conversión */

    mad_out = fopen(madname, "wb");
	fwrite(&magic,1,1,mad_out);
    mad.n_caras = file_header.numTriangles;

    mad.x = 0;
    mad.y = 0;
    mad.z = 0;
    mad.base[0].x = 1;
    mad.base[0].y = 0;
    mad.base[0].z = 0;
    mad.base[1].x = 0;
    mad.base[1].y = 1;
    mad.base[1].z = 0;
    mad.base[2].x = 0;
    mad.base[2].y = 0;
    mad.base[2].z = 1;

    
	
	fwrite(&mad, sizeof(modelo), 1, mad_out);

    printf("Conversión de caras\n");
    for (aux_size = 0; aux_size < file_header.numTriangles; aux_size++) {

	aux_face.vertices[2].x =
	    (vertices[faces[aux_size].vertexIndices[0]].vertex[0] *
	     frame0.scale[0] + frame0.translate[0]) / CONF;
	aux_face.vertices[2].y =
	    (vertices[faces[aux_size].vertexIndices[0]].vertex[1] *
	     frame0.scale[1] + frame0.translate[1]) / CONF;
	aux_face.vertices[2].z =
	    (vertices[faces[aux_size].vertexIndices[0]].vertex[2] *
	     frame0.scale[2] + frame0.translate[2]) / CONF;
	aux_face.vertices[2].u =
	    (float) (coords[faces[aux_size].textureIndices[0]].s) * 256 /
	    (file_header.skinWidth * 255);
	aux_face.vertices[2].v =
	    (float) (coords[faces[aux_size].textureIndices[0]].t) * 256 /
	    (file_header.skinHeight * 255);

	aux_face.vertices[1].x =
	    (vertices[faces[aux_size].vertexIndices[1]].vertex[0] *
	     frame0.scale[0] + frame0.translate[0]) / CONF;
	aux_face.vertices[1].y =
	    (vertices[faces[aux_size].vertexIndices[1]].vertex[1] *
	     frame0.scale[1] + frame0.translate[1]) / CONF;
	aux_face.vertices[1].z =
	    (vertices[faces[aux_size].vertexIndices[1]].vertex[2] *
	     frame0.scale[2] + frame0.translate[2]) / CONF;
	aux_face.vertices[1].u =
	    (float) (coords[faces[aux_size].textureIndices[1]].s) * 256 /
	    (file_header.skinWidth * 255);
	aux_face.vertices[1].v =
	    (float) (coords[faces[aux_size].textureIndices[1]].t) * 256 /
	    (file_header.skinHeight * 255);

	aux_face.vertices[0].x =
	    (vertices[faces[aux_size].vertexIndices[2]].vertex[0] *
	     frame0.scale[0] + frame0.translate[0]) / CONF;
	aux_face.vertices[0].y =
	    (vertices[faces[aux_size].vertexIndices[2]].vertex[1] *
	     frame0.scale[1] + frame0.translate[1]) / CONF;
	aux_face.vertices[0].z =
	    (vertices[faces[aux_size].vertexIndices[2]].vertex[2] *
	     frame0.scale[2] + frame0.translate[2]) / CONF;
	aux_face.vertices[0].u =
	    (float) (coords[faces[aux_size].textureIndices[2]].s) * 256 /
	    (file_header.skinWidth * 255);
	aux_face.vertices[0].v =
	    (float) (coords[faces[aux_size].textureIndices[2]].t) * 256 /
	    (file_header.skinHeight * 255);

	/* Ponemos las normales */



	aux_face.vertices[2].Nx=avertexnormals[vertices[faces[aux_size].vertexIndices[0]].lightNormalIndex][0];
	aux_face.vertices[2].Ny=avertexnormals[vertices[faces[aux_size].vertexIndices[0]].lightNormalIndex][1];
    aux_face.vertices[2].Nz=avertexnormals[vertices[faces[aux_size].vertexIndices[0]].lightNormalIndex][2];
    
    aux_face.vertices[1].Nx =avertexnormals[vertices[faces[aux_size].vertexIndices[1]].lightNormalIndex][0];
	aux_face.vertices[1].Ny=avertexnormals[vertices[faces[aux_size].vertexIndices[1]].lightNormalIndex][1];
    aux_face.vertices[1].Nz=avertexnormals[vertices[faces[aux_size].vertexIndices[1]].lightNormalIndex][2];

    aux_face.vertices[0].Nx =avertexnormals[vertices[faces[aux_size].vertexIndices[2]].lightNormalIndex][0];
	aux_face.vertices[0].Ny=avertexnormals[vertices[faces[aux_size].vertexIndices[2]].lightNormalIndex][1];
    aux_face.vertices[0].Nz=avertexnormals[vertices[faces[aux_size].vertexIndices[2]].lightNormalIndex][2];
    
    



	fwrite(&aux_face, sizeof(cara), 1, mad_out);

    }
    printf("Recuerda: Re-escala %s a 256x256\n", mad.id_textura);
    getchar();
    return 0;
}
