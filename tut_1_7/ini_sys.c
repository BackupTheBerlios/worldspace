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
#include "w3d_api.h"
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
		conf=fopen("w3_cfg.txt","at");
		fprintf(conf,"Fichero generado por WorldSpace3D. Modificar con cuidado\n\n");
		fprintf(conf,"Resolución horz.(X)\t %d\n",config.SCREEN_SIZE_X);
		fprintf(conf,"Resolución vert.(Y)\t %d\n",config.SCREEN_SIZE_Y);
		fprintf(conf,"Pantalla completa\t %d\n",config.FULLSCREEN);
		fprintf(conf,"Directorio base\t %s\n",config.dir);
		fclose(conf);
	}
	else {
		fscanf(conf,"Fichero generado por WorldSpace3D. Modificar con cuidado\n\n");
		fscanf(conf,"Resolución horz.(X)\t %d\n",&config.SCREEN_SIZE_X);
		fscanf(conf,"Resolución vert.(Y)\t %d\n",&config.SCREEN_SIZE_Y);
		fscanf(conf,"Pantalla completa\t %d\n",&config.FULLSCREEN);
		fscanf(conf,"Directorio base\t %s\n",&config.dir);
		fclose(conf);
	}


	/* Abrimos el fichero de logs (mensajes y errores no críticos) */
	/* Para errores críticos se usa sys_err */

	logs=fopen("w3d_logs.txt","wt");

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
  printf(logs,"\tFichero generado por WorldSpace3D. Modificar con cuidado\n\n");
	fprintf(logs,"\tResolución horz.(X)\t %d\n",config.SCREEN_SIZE_X);
	fprintf(logs,"\tResolución vert.(Y)\t %d\n",config.SCREEN_SIZE_Y);
	fprintf(logs,"\tPantalla completa\t %d\n",config.FULLSCREEN);
	fprintf(logs,"\tDirectorio base\t %s\n\n",config.dir);




	return 0;


}
