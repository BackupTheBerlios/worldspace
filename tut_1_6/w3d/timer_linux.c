// Timer en Linux




#include "opengl.h"
#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include "init_sys.h"

/* Tiempos de inicio y el total */



unsigned int past=0;



/*! Inicializa el timer */

int ini_timer(void) {

		past = SDL_GetTicks();
		past = SDL_GetTicks();
		fprintf(logs,"Timer inicializado en %u\n",past);

		return 0;
}

/*! devuelve el numero de milisegundos transcurridos desde la inicializacion del timer (Qué facil con SDL)*/

unsigned int get_timer(void) {


		return ((unsigned int)SDL_GetTicks()-past);

	
	
}

