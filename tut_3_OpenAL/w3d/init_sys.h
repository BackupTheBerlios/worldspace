//	Aquí están contenidas las cabeceras de las funciones de inicialización global. Estas funciones son comunes para Linuxy 
//	Windows.
//	También están declaradas las variables globales para que se puedan utilizar en otros módulos



#include "estructuras.h"
#include <stdio.h>






/*! Inicialización del sistema */

extern int system_init(void);					

/*! Variables */

/*! Variable para almacenar la configuración */
extern configuracion config;	
extern lista_sprites_spc *sprites_spc;				
extern unsigned int FPS;

/*! Salida de mensajes */
extern FILE *logs;		

extern float intervalo;
