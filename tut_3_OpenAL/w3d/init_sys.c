//	Este fichero se utilizar� para inicializar algunas variables. Es com�n.



#include "estructuras.h"
#include "timer.h"
#include <stdio.h>
#include <string.h>

/*! Controla el tiempo entre iteracciones */

float intervalo;


/*! Variable global para almacenar la configuraci�n */
configuracion config;

/*! Salida para el fichero de logs */
FILE *logs;


/*! Inicializaci�n del sistema. Aqu� se cargan los datos del fichero w3_cfg.txt, y si
no existe se crea con los datos por defecto */

int system_init(void){

	FILE *conf;

	
	
	/* Carga de la configuraci�n */

	conf=fopen("w3_cfg.txt","rt");				// Abre el fichero de configuraci�n
	
	if (conf==NULL) {							// Si no existe lo crea con la configuraci�n por defecto
		config.SCREEN_SIZE_X=640;		
		config.SCREEN_SIZE_Y=480;
		config.FULLSCREEN=0;
		strcpy(config.dir,"ws_datos");
		conf=fopen("w3_cfg.txt","wt");
		fprintf(conf,"Fichero generado por WorldSpace3D. Modificar con cuidado\n\n");
		fprintf(conf,"Resoluci�n horz.(X)\t %d\n",config.SCREEN_SIZE_X);
		fprintf(conf,"Resoluci�n vert.(Y)\t %d\n",config.SCREEN_SIZE_Y);
		fprintf(conf,"Pantalla completa\t %d\n",config.FULLSCREEN);
		fprintf(conf,"Directorio base\t %s\n",config.dir);
		fclose(conf);
	}
	else {
		fscanf(conf,"Fichero generado por WorldSpace3D. Modificar con cuidado\n\n");
		fscanf(conf,"Resoluci�n horz.(X)\t %d\n",&config.SCREEN_SIZE_X);
		fscanf(conf,"Resoluci�n vert.(Y)\t %d\n",&config.SCREEN_SIZE_Y);
		fscanf(conf,"Pantalla completa\t %d\n",&config.FULLSCREEN);
		fscanf(conf,"Directorio base\t %s\n",&config.dir);
		fclose(conf);
	}


	/* Abrimos el fichero de logs (mensajes y errores no cr�ticos) */
	/* Para errores cr�ticos se usa sys_msg */
	logs=fopen("w3d_logs.txt","wt");

	fprintf(logs,"Inicalizando fichero de logs...ok\n");

	/* Inicializamos el timer */

	return 0;



}
