// Tratamiento de los eventos del teclado

#include <SDL/SDL.h>
#include <stdio.h>

#include "teclado.h"
#include "opengl.h"
#include "timer.h"
#include "init_sys.h"



extern float camara[4][4];      /* Matriz de la camara */
extern SDL_Event event;

/*!         |
			| Y+
			|
			|
			|
X+	--------o
	       /
		  /
		 / Z+

*/
/* Esta matriz esta en modo Vx,Vy,Vz,O */


int tecla_pulsada(void)
{

    Uint8 *keys;
    int mouse_x, mouse_y;
    float x, y, z;

///* Actualización según ratón */
//        SDL_GetMouseState(&mouse_x,&mouse_y);
//              glMatrixMode(GL_PROJECTION);
//              x=camara[0][3];
//              y=camara[1][3];
//              z=camara[2][3];
//              camara[0][3]=0;
//              camara[1][3]=1.0f;
//              camara[2][3]=0;
//              camara[3][3]=1;
//              glLoadMatrixf(&camara[0][0]);
//              glRotatef((mouse_x-320)*intervalo/2,camara[1][0],camara[1][1],camara[1][2]);
//              glRotatef((mouse_y-240)*intervalo/2.0f,camara[0][0],camara[0][1],camara[0][2]);
//
//
//              glGetFloatv(GL_PROJECTION_MATRIX,&camara[0][0]);
//              camara[0][3]=x;
//              camara[1][3]=y;
//              camara[2][3]=z;
//

    if (SDL_PollEvent(&event))

        if (event.type == SDL_QUIT)
            return -1;

    keys = SDL_GetKeyState(NULL);

    if (keys[SDLK_ESCAPE]) {
        return -1;
    }
    if (keys[SDLK_w]) {
//                              camara[2][3] += (10.1f * intervalo* camara[2][2]);
//                                                                              camara[1][3] += (10.1f * intervalo* camara[1][2]);
//                                                                              camara[0][3] += (10.1f * intervalo* camara[0][2]);

    }
    if (keys[SDLK_s]) {
//                                                              camara[2][3] -= (10.1f * intervalo* camara[2][2]);
//                                                              camara[1][3] -= (10.1f * intervalo* camara[1][2]);
//                                                              camara[0][3] -= (10.1f * intervalo* camara[0][2]);
    }
    if (keys[SDLK_e])
        SDL_WarpMouse(320, 240);



}
