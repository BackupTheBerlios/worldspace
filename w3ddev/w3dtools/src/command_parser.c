/***************************************************************************
                          command_parser.v  -  
                             -------------------
    begin                : lun feb 10 2003
    copyright            : (C) 2003 by Grupo WorldSpace
    email                : neuralgya@users.berlios.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#include <math.h>
#include <stdlib.h>

#include "sdl_gl.h"
#include "w3d_base.h"
#include "globales.h"
#include "mad.h"

#include <stdio.h>

#include <fcntl.h>

char data[1024];
int EXIT_FLAG=NO;

int parse_command() {

        if (strcmp(data,"exit\n")==0)
            EXIT_FLAG=SI;
            

    return SI;
}

int read_command() {

  int fd;


    T_FUNC_IN;

  fd=read(0,&data,1023);
  if  (fd==0) {
          T_FUNC_OUT ;return NO;
    }
        else if  (fd>0) {
          printf(">>%s\n",data);
            T_FUNC_OUT ;return SI;
        }
    

}

int resetView()
{

    GLfloat Ambient0[] = { 0.0f, 0.0f, 1.0f, 0.0f };
    GLfloat LightPosition0[] = { 1.0f, -1.0f, 1.0f, 0.0f };
    GLfloat Diffuse0[4];

    T_FUNC_IN;

    glClearColor(fFondo[0], fFondo[1], fFondo[2], fFondo[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glLightfv(GL_LIGHT0, GL_DIFFUSE, Diffuse0);
    Diffuse0[3] = 1.0f;
    glLightfv(GL_LIGHT0, GL_AMBIENT, Ambient0);
    glLightfv(GL_LIGHT0, GL_POSITION, LightPosition0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);

	T_FUNC_OUT ;
    return SI;

} 



int command_parser()
{

    SDL_Event event;
    Uint8 *keys;
    int taux, iAlto, iAncho;
    int intervalo;
    modelo *logo;
    float fAngulo, fSize, fInc, fIter;

    T_FUNC_IN;

    log_msj("[%s:%d] Command parser...\n", __FILE__, __LINE__);
    if (fcntl(0, F_SETFL,O_NONBLOCK)>-1)
        log_msj("[%s:%d] %s\n", __FILE__, __LINE__,_("Entrada puesta a no bloqueo"));

    

    logo = carga_mad("logo.mad");

  

    while (EXIT_FLAG==NO) {
	   SDL_PollEvent(&event);
	   keys = SDL_GetKeyState(NULL);
	 
	   if (event.type == SDL_QUIT) {
	       log_msj(">>Abortado<<<");
	       exit(0);
	   }
    
	   /* Painting the scene */
    
	   SDL_Delay(15);
	   resetView();
	   if (logo != NULL)
	       render_mad(logo);
    
	   w_begin();
    
	   imprime(vFuente[eDef], (float) 1 * 0.32f,
		  (float) 1 * 0.9f, 2.0f, "WorldSpace");
	   w_end();
    
	   SDL_GL_SwapBuffers();

       if (read_command())
            parse_command();
        
    }

    T_FUNC_OUT return SI;

}
