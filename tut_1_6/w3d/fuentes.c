// fuentes.c	Cosas relativas a las fuentes....



#include "opengl.h"					/*! Incluye cabeceras y definiciones de OpenGL*/

#include "sys.h"					/*! Prototipos de funciones dependientes del sistema */

#include "init_sys.h"				/*! Blah, blah, blah.....*/

#include "carga_tga.h"

#include "fuentes.h"

#include <string.h>
#include <stdarg.h>
#include <stdlib.h>



/*! Tabla de almacenamiento de las coordenadas */
float tipo1[128][4];				




/*! Carga en una textura el mapa de fuentes, y rellena una estructura FUENTE. Se crea una
textura y un mapa de coordenadas de 128*4 elementos donde se almacenan las coordenadas
para cada carácter. El mapa de fuentes es un TGA de 256x256 con canal ALPHA. Mirar en
el directorio fuentes */

FUENTE *carga_fuente(char *fichero,	int tam_base,int espacio_base) {
	
	int tam_x,tam_y;		/* Tamaño del mapa*/
	char *textura_datos;	/* Temporal; para guardar el bitmap */
	int i,j,k;				/* Indices */
	FUENTE *fuente_x;		/* Fuente a crear */


	
	/* Lo primero, reservar memoria para la estructura FUENTE */

	fuente_x=(FUENTE *)malloc(sizeof(FUENTE));
	if (fuente_x==NULL)  {
			fprintf(logs,"No pude reservar memoria\n");
			return NULL;
	}
	
	/* Fuentes texturizadas */
	
	glGenTextures (1, &(fuente_x->mapabits));	

    /* Creación de la ruta completa, tenemos en cuenta el base_dir */


	textura_datos=(char *)CargaTGA(fichero,&tam_x,&tam_y);
    if ((textura_datos == NULL)||(tam_x!=tam_y))  {
        return NULL;
    }
	 
	glBindTexture (GL_TEXTURE_2D, fuente_x->mapabits);
	
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, tam_x, tam_y, 0, GL_RGBA, GL_UNSIGNED_BYTE,  textura_datos);

	
	/* Ahora establecemos las coordenadas */

	k=0;
	for (j=1;j<(tam_y/2);j+=16) {
		for (i=0;i<tam_x;i+=16) {
			tipo1[k][0]=(float)i/(float)tam_x;
			tipo1[k][1]=(float)j/(float)tam_y;
			tipo1[k][2]=(float)i/(float)tam_x+(float)15/(float)tam_x;
			tipo1[k][3]=(float)j/(float)tam_y+(float)15/(float)tam_y;
			k++;
		}
	}
	
	fuente_x->tam_base=tam_base;
	fuente_x->espacio_base=espacio_base;
	fuente_x->inicializado=1;


	free(textura_datos);  

	return fuente_x;
}

/*! Imprime un texto con la fuente que se le pasa. Como vemos, esta función
admite un número indeterminado de parámetros que se parsean al principio. Los 
últimos parametros son los de formato de cadenas, como el printf*/

int print(FUENTE *fuente,float x, float y,float tam,char *texto, ...) {

	char		text[1024];			// almacena el texto a escribir
	va_list		ap;					// puntero a la lista de argumentos (los ...)
	int i;
	if (texto == NULL)				// si no hay texto
		return 0;					// nos vamos
	va_start(ap, texto);			// Busca variables en el texto
	vsprintf(text, texto, ap);		// y las sustituye por su valor
	va_end(ap);						// almacenando el resultado en text

	
	if (fuente->inicializado!=1)
		return -1;

	glBindTexture(GL_TEXTURE_2D, fuente->mapabits);
	i=strlen(text);
	
	
	/* Aquí se renderiza el plano y su textura */

	for (i=0;i<(int)strlen(text);i++) {
		glBegin(GL_QUADS);
			
		glTexCoord2f(tipo1[(text[i]-32)][0],tipo1[(text[i]-32)][3]);
			glVertex2f(x,y-fuente->tam_base*tam);
		
		glTexCoord2f(tipo1[(text[i]-32)][2],tipo1[(text[i]-32)][3]);
			glVertex2f(x+fuente->tam_base*tam,y-fuente->tam_base*tam);

		glTexCoord2f(tipo1[(text[i]-32)][2],tipo1[(text[i]-32)][1]);
			glVertex2f(x+fuente->tam_base*tam,y);

		glTexCoord2f(tipo1[(text[i]-32)][0],tipo1[(text[i]-32)][1]);
			glVertex2f(x,y);
		
			

			

			

		glEnd();
		x+=fuente->tam_base*tam+fuente->espacio_base*tam;
	}
return 0;
}	
			

			
