// Carga y tratamiento de ficheros TGA.



#include "opengl.h"
#include "init_sys.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>




/*! Utilizamos esta estructura para cargar TGA. */

typedef	struct										
{
	GLubyte	*imageData;								
	GLuint	bpp;									
	GLuint	width;									
	GLuint	height;									
	GLuint	texID;									
} Imagen;										

/*! Carga un TGA en memoria. El TGA debe cumplir las siguientes características:
Ser de 24 bits + Canal ALPHA. (32 bits) y SIN COMPRIMIR
El tamaño debe ser cuadrado (x=y) y 32x32 o 64x64 o 128x128 o 256x256
Devuelve un puntero a la imagen y el tamaño (variable tam) de la imagen.*/

void *CargaTGA(char filename[],int *tam_x,int *tam_y)					
{    
	GLubyte		TGAheader[12]={0,0,2,0,0,0,0,0,0,0,0,0};			
	GLubyte		TGAcompare[12];							
	GLubyte		header[6];							
	GLuint		bytesPerPixel;						
	GLuint		imageSize;							
	GLuint		temp,i;								
	GLuint		type=GL_RGBA;						
    Imagen		texture;
	GLubyte		*aux;      
	
	char aux2[2048];
	FILE *fichero;

	
	strcpy(aux2,config.dir);
	strcat(aux2,"/");
	strcat(aux2,filename);
	
	fichero= fopen(aux2, "rb");					

	fprintf(logs,"Cargando fichero TGA...%s\n",aux2);
	
	if (fichero == NULL) {
			fprintf(logs,"No pude cargar fichero %s (tal vez no exista)\n",filename);
			return NULL;					
	}
	/* Esto abre y comprueba que es un TGA */

	fread(TGAcompare,1,sizeof(TGAcompare),fichero);

	if (memcmp(TGAheader,TGAcompare,sizeof(TGAheader))!=0)			
		return NULL;

    /* Leemos la cabecera*/

	fread(header,1,sizeof(header),fichero);

	/* Determinamos el tamaño */

	texture.width  = header[1] * 256 + header[0];		
	texture.height = header[3] * 256 + header[2];		
    	

	/* Vemos las características y comprobamos si son correctas*/
 	if(	texture.width	<=0	||					
		texture.height	<=0	||	
		texture.width >256 ||
		texture.height !=texture.width ||
		( header[4]!=32))					
	{
		fclose(fichero);								
		return NULL;								
	}

      
	/* Calculamos la memoria que será necesaria */
	
	texture.bpp	= header[4];						
	bytesPerPixel	= texture.bpp/8;				
	imageSize	= texture.width*texture.height*bytesPerPixel;	

    
	/* Reservamos memoria */
	texture.imageData=(GLubyte *)malloc(imageSize);				

	/* Cargamos y hacemos alguna comprobaciones */

	if(	texture.imageData==NULL ||						
		fread(texture.imageData, 1, imageSize, fichero)!=imageSize)
	{
		if(texture.imageData!=NULL)					
			free(texture.imageData);				

		fclose(fichero);								
		return NULL;								
	} 

      
    /* El TGA viene en formato BGR, lo pasamos a RGB */
	for(i=0; i<(GLuint)(imageSize); i+=bytesPerPixel)	
	{										
		temp=texture.imageData[i];			
		texture.imageData[i] = texture.imageData[i + 2];
		texture.imageData[i + 2] = temp;					
	}


	fclose (fichero);								
    
	/* Ahora, cambiamos el orden de las líneas, como si hiciesemos
	un flip vertical. */

	aux=(GLubyte *)malloc(imageSize);
	for(i=0; i<texture.height; i++)			
			memcpy(&aux[imageSize-((i+1)*texture.width*4)],&texture.imageData[i*texture.width*4],texture.width*4);
		
	

//	aux=texture.imageData;

	/* tam devolverá el tamaño */
	*tam_x=texture.width;
	*tam_y=texture.height;
	/* Liberamos memoria */
	free(texture.imageData);
	
	/* Todo fue bien!*/
	return aux;
}

