#include <stdio.h>

#include "estructuras.h"
#include "opengl.h"
#include "init_sys.h"
#include "carga_tga.h"

#include <math.h>
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

	fprintf(logs,"Cargando sprites del escenario...%s\n",fichero_spc);
  strcpy(fichero,config.dir);
	strcat(fichero,"/espacios/");
	strcat(fichero,fichero_spc);

	fprintf(logs,"Cargando sprites del escenario...%s\n",fichero);

	fich=fopen(fichero, "rt");					
	
	if (fich == NULL) {
			fprintf(logs,"No pude cargar fichero %s (tal vez no exista)\n",fichero);
			return -1;					
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
	fprintf(logs,"Encontrados %d sprites\n",contador);

	fclose(fich);
	fich=fopen(fichero, "rt");					
	
	if (fich == NULL) {
			fprintf(logs,"No pude cargar fichero %s (tal vez no exista)\n",fichero);
			return -1;					
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

    /* Otras incializaciones */

		lista_aux.matriz[0][3]=0.0f;
		lista_aux.matriz[1][3]=0.0f;
		lista_aux.matriz[2][3]=0.0f;
		lista_aux.matriz[3][3]=1.0f;

		if (strcmp(textura_f,textura_f_old)!=0) {
				glGenTextures (1,&lista_aux.textura);	
	  textura_datos=(char *)CargaTGA(textura_f,&tam_x,&tam_y);
	    if (tam_x!=tam_y)
				return -1;
   if (textura_datos == NULL)  {
      	fprintf(logs, "Error al cargar %s\n",textura_f);
       	return -1;
 	  }
		
		glBindTexture (GL_TEXTURE_2D,lista_aux.textura );
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
	       GL_LINEAR_MIPMAP_NEAREST);

		gluBuild2DMipmaps (GL_TEXTURE_2D, 4, tam_x, tam_y, GL_RGBA,
		     GL_UNSIGNED_BYTE, textura_datos);


		strcpy(textura_f_old,textura_f);
		free(textura_datos);

		numero_texturas++;
		}
		memcpy(&sprites_spc[contador2],&lista_aux,sizeof(lista_sprites_spc));

		contador2++;
		}

		fprintf(logs,"Número de texturas cargadas en este proceso: %d\n",numero_texturas);


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
