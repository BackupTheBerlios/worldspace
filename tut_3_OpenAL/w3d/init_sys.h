//	Aqu� est�n contenidas las cabeceras de las funciones de inicializaci�n global. Estas funciones son comunes para Linuxy 
//	Windows.
//	Tambi�n est�n declaradas las variables globales para que se puedan utilizar en otros m�dulos



#include "estructuras.h"
#include <stdio.h>






/*! Inicializaci�n del sistema */

extern int system_init(void);					

/*! Variables */

/*! Variable para almacenar la configuraci�n */
extern configuracion config;	
extern lista_sprites_spc *sprites_spc;				
extern unsigned int FPS;

/*! Salida de mensajes */
extern FILE *logs;		

extern float intervalo;
