#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mad.h"
#include "init_sys.h"
#include "opengl.h"
#include "carga_tga.h"



modelo *carga_mad(char *file)
{

    FILE *f_object;
    int j;
    cara *tri;
    char *filename_etereal,*textura_datos;
    char filename[1024];
    char skin[1024];
    char magic;
		unsigned int tam_x,tam_y;

    modelo *modelo_1;


    modelo_1 = (modelo *) malloc(sizeof(modelo));
    strcpy(filename, config.dir);
    strcat(filename, "/");
    strcat(filename, file);


    fprintf(logs, "Cargando modelo %s\n", filename);
    f_object = fopen(filename, "rb");
    if (f_object == NULL) {
        fprintf(logs, "No pude encontrar %s\n", filename);
        return NULL;
    }

    fread(&magic, 1, 1, f_object);

    if (magic != MAD_MAGIC) {
        fprintf(logs, "Fichero no válido\n");
        return NULL;
    }

    fread(modelo_1, sizeof(modelo), 1, f_object);

    //memset(modelo_1->base, 0, (sizeof(vertice) * 3));
    modelo_1->x = 0.0;
    modelo_1->y = 0.0;
    modelo_1->z = 0.0;

    tri = (cara *) malloc(sizeof(cara) * modelo_1->n_caras);
    modelo_1->triangulos = tri;
    for (j = 0; j < modelo_1->n_caras; j++) {
        fread(&(modelo_1->triangulos[j]), sizeof(cara), 1, f_object);
    }
    fprintf(logs, "Modelo cargado con %d caras\n", j);


    fprintf(logs, "Skin  %s\n", modelo_1->id_textura);

		
		glGenTextures (1,&modelo_1->n_textura);	
		strcpy(skin,"texturas/");
		strcat(skin,modelo_1->id_textura);

	  textura_datos=(char *)CargaTGA(skin,&tam_x,&tam_y);
	    if (tam_x!=tam_y)
				return NULL;
   if (textura_datos == NULL)  {
      	fprintf(logs, "Error al cargar %s\n",skin);
       	return NULL;
 	  }
		
		glBindTexture (GL_TEXTURE_2D,modelo_1->n_textura );
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
	       GL_LINEAR_MIPMAP_NEAREST);

		gluBuild2DMipmaps (GL_TEXTURE_2D, 4, tam_x, tam_y, GL_RGBA,
		     GL_UNSIGNED_BYTE, textura_datos);
		free(textura_datos);

    return modelo_1;
}
