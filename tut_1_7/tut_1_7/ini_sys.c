/***************************************************************************
                          ini_sys.c  -  Inicialización de sistemas
                             -------------------
    begin                : mié jul 10 2002
    copyright            : (C) 2002 by neuralgya
    email                : neuralgya@mail.berlios.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


//	Este fichero se utilizará para inicializar algunas variables. Es común.



#include "estructuras.h"
#include "render.h"
#include "w3d_api.h"
#include "opengl.h"
#include <stdio.h>
#include <string.h>


/*! Variable global para almacenar la configuración */
configuracion config;

/*! Salida para el fichero de logs */
FILE *logs;


/*! Inicialización del sistema. Aquí se cargan los datos del fichero w3_cfg.txt, y si
no existe se crea con los datos por defecto */

int system_close(void) {
  fflush(logs);
  fclose(logs);
  return 0;
}

int system_init(void){

	FILE *conf;

	
	
	/* Carga de la configuración */

	conf=fopen("w3_cfg.txt","rt");				// Abre el fichero de configuración
	
	if (conf==NULL) {							// Si no existe lo crea con la configuración por defecto
		config.SCREEN_SIZE_X=640;		
		config.SCREEN_SIZE_Y=480;
		config.FULLSCREEN=0;
		strcpy(config.dir,"ws_datos");
		conf=fopen("w3_cfg.txt","wt");
		fprintf(conf,"Fichero generado por WorldSpace3D. Modificar con cuidado\n\n");
		fprintf(conf,"Resolución horz.(X)\t %d\n",config.SCREEN_SIZE_X);
		fprintf(conf,"Resolución vert.(Y)\t %d\n",config.SCREEN_SIZE_Y);
		fprintf(conf,"Pantalla completa\t %d\n",config.FULLSCREEN);
		fprintf(conf,"Directorio base\t %s\n",config.dir);
		fclose(conf);
	}
	else {
		fscanf(conf,"Fichero generado por WorldSpace3D. Modificar con cuidado\n\n");
		fscanf(conf,"Resolución horz.(X)\t %d\n",&(short int)config.SCREEN_SIZE_X);
		fscanf(conf,"Resolución vert.(Y)\t %d\n",&(short int)config.SCREEN_SIZE_Y);
		fscanf(conf,"Pantalla completa\t %d\n",&(char)config.FULLSCREEN);
		fscanf(conf,"Directorio base\t %s\n",config.dir);
		fclose(conf);
	}


	/* Abrimos el fichero de logs (mensajes y errores no críticos) */
	/* Para errores críticos se usa sys_err */

	logs=fopen("w3d_logs.txt","at");

	sys_msg("\n\n\n\n
 ***************************************************************************
 *                 Hello World! WorldSpace has just arrived!               *
 *                        Tutorial 1.7 by neuralgya                        *
 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************
\n");
  sys_msg("Configuración:\n");
	fprintf(logs,"\tResolución horz.(X)\t %d\n",config.SCREEN_SIZE_X);
	fprintf(logs,"\tResolución vert.(Y)\t %d\n",config.SCREEN_SIZE_Y);
	fprintf(logs,"\tPantalla completa\t %d\n",config.FULLSCREEN);
	fprintf(logs,"\tDirectorio base\t %s\n\n",config.dir);




	return 0;


}

/* Inicialización del contexto OpenGL mediante SDL */

int sys_init_display(void)
{


    unsigned short int x_size, y_size;
    SDL_Surface *screen;


    x_size = config.SCREEN_SIZE_X;
    y_size = config.SCREEN_SIZE_Y;


    if (SDL_Init(SDL_INIT_VIDEO)!=1)
      	sys_msg("[OK]\t\tSubsistema SDL_video inicializado\n");
    else {
       	sys_msg("[KO]\\ttError inesperado en SDL_Init\n");
        sys_msg(SDL_GetError());
        return -1;
    }


    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    if (config.FULLSCREEN == 1) {
        screen =
            SDL_SetVideoMode(x_size, y_size, 16,
                             SDL_OPENGL | SDL_FULLSCREEN);
        if (!screen) {
            sys_err("No se pudo inicializar OpenGL en pantalla completa\n");
            sys_err(SDL_GetError());
            SDL_Quit();
            return -1;
        }
    } else {
        screen = SDL_SetVideoMode(x_size, y_size, 16, SDL_OPENGL);
        if (!screen) {
            sys_err("No se pudo inicializar OpenGL en ventana\n");
            sys_err(SDL_GetError());
            SDL_Quit();
            return -1;
        }
    }
	
    sys_msg("[OK]\t\tSubsistema de video inicializado\n");

		/* Cursor fuera */
    SDL_ShowCursor(0);
	
		/* Título dela ventana */
    SDL_WM_SetCaption("WorldSpace", "WorldSpace");
		
		/* Podemos fijar el ratón a nuestra aplicación aquí */
		SDL_WM_GrabInput(SDL_GRAB_OFF);

    /* Hacemos que el ratón se ponga en el centro de la pantalla */
		SDL_WarpMouse(config.SCREEN_SIZE_X/2, config.SCREEN_SIZE_Y/2);

    sys_msg("[OK]\t\tContexto OpenGL preparado\n");


    /* Inicializamos OpenGL */

		if (inicializa_gl()!=0) {
      sys_msg("[KO]\t\t\tError inesperado inicializando OpenGL");
      return -1;
    }
    else {
      sys_msg("[OK]\t\t\tOpenGL inicializado con éxito\n");

    }

      /* Logo */

    if (logo()==0)
			sys_msg("[OK]\t\t\tLogo W3D. ¿Has visto eso?\n");

		return 0;


}

