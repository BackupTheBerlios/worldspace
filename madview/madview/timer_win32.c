// funciones del timer para Windows 
 
// Estas funciones son Windoze totales, haced un acto de fe 
// EL MM (Multimedia timer) está desactivado, a mi no me compila 
#ifdef _WIN32
    
#include <windows.h>
#include <stdio.h>
#include <mmsystem.h>
    
#include "init_sys.h"
    
/*! numero de ticks por segundo */ 
    __int64 timer_frecuencia;

    /*!segundos por tick */ 
float timer_periodo;

/*! momento de comienzo del Performance Timer */ 
    __int64 timer_comienzo_PerformanceTimer;

/*! Inicializa el timer */ 
void ini_timer(void) 
{
    if (!QueryPerformanceFrequency((LARGE_INTEGER *) & timer_frecuencia)) {
        sys_msg("Error inicilizando timer");
        exit(-1);
    }
    
    else
         {
        QueryPerformanceCounter((LARGE_INTEGER *) &
                                timer_comienzo_PerformanceTimer);
        timer_periodo = ((float) 1.0) / ((float) timer_frecuencia);
} } 

/*! devuelve el numero de segundos transcurridos desde la inicializacion del timer */ 
float get_timer(void) 
{
    __int64 time;
    QueryPerformanceCounter((LARGE_INTEGER *) & time);
    return ((float) (time - timer_comienzo_PerformanceTimer) *
             timer_periodo);
} 
#endif  /*  */
