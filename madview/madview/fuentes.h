//      Cosas relativas a las fuentes....

 


#include "opengl.h"
    
#ifndef _FUENTES_STR          
#define _FUENTES_STR
    

/*! Estructura de las fuentes */ 
typedef struct FUENTE_tag {
	GLuint mapabits;
	int tam_base;
	int espacio_base;
	char inicializado;				// 0=NO 1=SI
} FUENTE;


#endif                          /* 
 */
    
/*! tam_base es el tama�o base para esa fuente. Cuando se
utilice la funci�n print, el tama�o que se especifique ah�
ser� en funci�n de como se inicializ� 
espacio_base es el espacio entre letras de cada fuente,
es bastante dependiente del tipo de fuente */ 

extern FUENTE *carga_fuente(char *fichero, int tam_base,
                             int espacio_base);


/*! Especificamos el tipo de fuente (previamente creado), su
posisici�n (-1,-1 a 1,1), el tama�o y el texto. Se pueden 
utilizar cadenas las cadenas de formato como printf(etc) */ 

extern int print(FUENTE * fuente, float x, float y, float tam,
                  char *texto, ...);






