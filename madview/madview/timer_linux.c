// Timer en Linux





#include "opengl.h"
#include <SDL/SDL.h>
#include <unistd.h>
#include <stdarg.h>

/* Tiempos de inicio y el total */

unsigned int past = 0;


/*! Inicializa el timer */

int ini_timer(void)
{
    past = SDL_GetTicks();
    return 0;

}

/*! devuelve el numero de milisegundos transcurridos desde la inicializacion del timer (Qué facil con SDL)*/

float get_timer(void)
{

    return (SDL_GetTicks() - past);

}

