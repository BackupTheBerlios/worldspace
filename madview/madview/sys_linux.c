//      Función principal y de intercambio de buffers para el sistema linux
//      Nota; He quitado las funciones SDL y las he sustituido por funciones nativas de XFree.





#include <stdio.h>
#include <stdlib.h>



#include "estructuras.h"
#include "render.h"
#include "init_sys.h"
#include "opengl.h"
#include "timer.h"
#include "teclado.h"


float tiempo_antiguo, taux;
SDL_Event event;

extern unsigned int FPS;
modelo *model;


/*! salida de los mensajes de error */

void sys_msg(char *msg)
{
    fprintf(stderr, "%s", msg);
}



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
            fprintf(stderr, "Couldn't set GL video mode: %s\n",
                    SDL_GetError());
            SDL_Quit();
            exit(2);
        }
    } else {
        screen = SDL_SetVideoMode(x_size, y_size, 16, SDL_OPENGL);
        if (!screen) {
            fprintf(stderr, "Couldn't set GL video mode: %s\n",
                    SDL_GetError());
            SDL_Quit();
            exit(2);
        }
    }
    SDL_ShowCursor(0);
    SDL_WM_SetCaption("WorldSpace", "WorldSpace");
    SDL_WarpMouse(320, 240);
    SDL_WM_GrabInput(SDL_GRAB_OFF);


    fprintf(logs, "Viewport ok!!!\n");
    init_gl();
    return 0;
}


/*! Básicamente, el bucle principal.Usamos SDL */


void main_loop(void)
{
    int done;


    done = 0;
    while (!done) {
        taux = get_timer();
        intervalo = (taux - tiempo_antiguo) / 1000.0f;
        tiempo_antiguo = taux;
        if (tecla_pulsada() == -1)
            done = 1;
        gl_renderiza_escena();
    }

    SDL_Quit();


    return;



}

/*! El comienzo de todo.... */
#ifdef _WIN32W3D
int WINAPI WinMain(HINSTANCE hInstance, 
                    HINSTANCE hPrevInstance, 
                    LPSTR lpCmdLine, 
 int nCmdShow) 
{
    char f_model[1024];

    MessageBox(NULL, lpCmdLine, "Error",
                    MB_OK | MB_ICONEXCLAMATION);

    system_init();
    strcpy(f_model,lpCmdLine);
	model = carga_mad(f_model);


#endif
#ifdef _LINUX
int main(int argc, char *argv[])
{


    printf("madview version %d variante GL_BACK\n",FECHA);
    system_init();
    if (argc==1)
				return -1;

		model = carga_mad(argv[1]);
#endif
    if (model==NULL)
			return -1;
		if (sys_init_display() != 0) {
        sys_msg("Bleep, no se pudo iniciar el sistema :-P\n");
        return -1;
    }
    ini_timer();
    main_loop();
    printf("Total frames %d en %f segundos: %f FPS\n", FPS,
           get_timer() / 1000.0f, FPS / (get_timer() / 1000.0f));
    return 0;
}


/*! Intercambio de buffers usando SDL*/

void sys_swapbuffers(void)
{
    SDL_GL_SwapBuffers();
}


