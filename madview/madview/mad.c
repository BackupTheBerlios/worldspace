#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mad.h"
#include "init_sys.h"



modelo *carga_mad(char *file)
{

    FILE *f_object;
    int j;
    cara *tri;
    char *filename_etereal;
    char filename[1024];
    char skin[1024];
    char magic;

    modelo *modelo_1;


    modelo_1 = (modelo *) malloc(sizeof(modelo));
    strcpy(filename, file);


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

    memset(modelo_1->base, 0, (sizeof(vertice) * 3));
    modelo_1->x = 0.0;
    modelo_1->y = 0.0;
    modelo_1->z = 0.0;

    tri = (cara *) malloc(sizeof(cara) * modelo_1->n_caras);
    modelo_1->triangulos = tri;
    for (j = 0; j < modelo_1->n_caras; j++) {
        fread(&(modelo_1->triangulos[j]), sizeof(cara), 1, f_object);
    }
    fprintf(logs, "Modelo cargado con %d caras\n", j);


    /* Debemos encontrar el fichero de textura */
    filename_etereal = &filename[0];
    for (j = strlen(filename) - 1; j >= 0; j--)
        if (filename_etereal[j] == '/')
            break;

    strcpy(skin, filename);     // 1 <dir_mad>/
    skin[j + 1] = '\0';

    strcat(skin, modelo_1->id_textura);
    fprintf(logs, "Probando : %s \n", skin);
    f_object = fopen(skin, "rb");
    if (f_object == NULL) {
        fprintf(logs, "Textura/Skin : %s no encontrada\n", skin);
        strcpy(skin, filename); // 2 <dir_mad>../texturas/
        skin[j + 1] = '\0';
        strcat(skin, "../texturas/");
        strcat(skin, modelo_1->id_textura);
        fprintf(logs, "Probando : %s \n", skin);
        f_object = fopen(skin, "rb");
        if (f_object == NULL) {
            fprintf(logs, "Textura/Skin : %s no encontrada\n", skin);
            return -1;
        }


    }
    fprintf(logs, "Textura/Skin  %s encontrada\n", skin);
    strcpy(modelo_1->id_textura, skin);
    return modelo_1;
}
