//      Función principal y de intercambio de buffers para el sistema linux
//			Basado en la librería SDL





#include <stdio.h>
#include <stdlib.h>



#include "estructuras.h"
#include "render.h"
#include "init_sys.h"
#include "opengl.h"
#include "timer.h"
#include "teclado.h"
#include "audio.h"


unsigned int tiempo_antiguo, taux;
SDL_Event event;


/*! salida de los mensajes de error */

void sys_msg(char *msg)
{
    fprintf(stderr, "%s", msg);
}



/* Inicialización del contexto OpenGL mediante SDL */

int sys_init_display(void)
{


    unsigned short int x_size, y_size;
    SDL_Surface *screen;


    x_size = config.SCREEN_SIZE_X;
    y_size = config.SCREEN_SIZE_Y;


    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    if (config.FULLSCREEN == 1) {
        screen =
            SDL_SetVideoMode(x_size, y_size, 16,
                             SDL_OPENGL | SDL_FULLSCREEN);
        if (!screen) {
            fprintf(stderr, "No se pudo inicializar OpenGL: %s\n",
                    SDL_GetError());
            SDL_Quit();
            exit(2);
        }
    } else {
        screen = SDL_SetVideoMode(x_size, y_size, 16, SDL_OPENGL);
        if (!screen) {
            fprintf(stderr, "No se pudo inicializar OpenGL: %s\n",
                    SDL_GetError());
            SDL_Quit();
            exit(2);
        }
    }

		/* Cursor fuera */
    SDL_ShowCursor(0);
	
		/* Título dela ventana */
    SDL_WM_SetCaption("WorldSpace", "WorldSpace");
		
		/* Podemos fijar el ratón a nuestra aplicación aquí */
		SDL_WM_GrabInput(SDL_GRAB_OFF);

    /* Hacemos que el ratón se ponga en el centro de la pantalla */
		SDL_WarpMouse(config.SCREEN_SIZE_X/2, config.SCREEN_SIZE_Y/2);

    fprintf(logs, "Creación del contexto OpenGL correcto.Viewport ok!!!\n");

    /* Inicializamos OpenGL */

		init_gl();
    return 0;
}


/*! Básicamente, el bucle principal.Usamos SDL */


void main_loop(void)
{
    int done;
    done = 0;
    while (done==0) {
        taux = get_timer();
        intervalo = (taux - tiempo_antiguo)/1000.0f;
        tiempo_antiguo = taux;


        if (SDL_PollEvent(&event))

            if (event.type == SDL_QUIT)
                done = 1;


            if (tecla_pulsada() == -1)
                done = 1;
						
            input_mouse();
        gl_renderiza_escena();
    }

    fprintf(logs,"Total frames %d en %d milisegundos con %f FPS \n",FPS,get_timer(),(float)(FPS/(get_timer()/1000.0f)));

    /* Cerramos audio */
    if ( audio_on == 1 ){
          fprintf(logs,"Cerrando OpenAL\n");
          FinalizarAudio ();
    }
	
	fprintf(logs,"Cerrando contexto OpenGL y SDL\n");
   	SDL_Quit();


    return;



}

/*! El comienzo de todo.... */

#ifdef _LINUX
int main(int argc, char *argv[])
{
#endif
#ifdef _WIN32W3D
int WINAPI WinMain( HINSTANCE	hInstance,
					HINSTANCE	hPrevInstance,
					LPSTR		lpCmdLine,
					int 		nCmdShow)
{
#endif



    /* Inicialización del sistema de logs y configuración */
		system_init();
    fprintf(logs,"WorldSpace 3D. Tutorial 1.6. Versión %d.\n",FECHA);
    fprintf(logs,"Iniciando sistema básico...consulte el fichero de logs para más información\n");



		
    if (sys_init_display() != 0) {
        sys_msg("No se pudo iniciar el sistema gráfico\n");
        return -1;
    }


		fprintf(logs,"Inicializando timer\n");
		ini_timer();

		fprintf(logs,"Comienza el espectáculo!\n");

    main_loop();

		fprintf(logs,"Cierre satisfactorio\n");

    return 0;
}


/*! Intercambio de buffers usando SDL*/

void sys_swapbuffers(void)
{
    SDL_GL_SwapBuffers();
}


