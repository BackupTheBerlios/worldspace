/***************************************************************************
                          bios.c  -  Inicialización de sistemas básicos
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

#include "../global.h"



/*! 
extern int init_bios(void);

Esta función inicializa los sistemas básicos de salida de errores y warnings.
Abre un fichero en modo de escritura, y ahí es donde se van depositando los
mensajes del sistema. Además llama a la función para cargar la configuración
por defecto

*/


int init_bios(void)
{

    logs = fopen("w3d_logs.txt", "at");

    fprintf(logs, "\n\n\n\n
 ***************************************************************************
 *                 Hello World! WorldSpace has just arrived!               *
 ***************************************************************************
 *                                                                         *
 *                               BUILD: %d                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************
\n", BUILD);
    if (carga_conf()) {
	fprintf(logs, "Configuración:\n");
	fprintf(logs, "\tResolución horz.(X)\t %d\n",
		config.SCREEN_SIZE_X);
	fprintf(logs, "\tResolución vert.(Y)\t %d\n",
		config.SCREEN_SIZE_Y);
	fprintf(logs, "\tPantalla completa\t %d\n", config.FULLSCREEN);
	fprintf(logs, "\tDirectorio base\t %s\n\n", config.dir);
    } else {
	fprintf(logs, "Imposible cargar configuración:\n");
	return NO;
    }


    return SI;

}

/*!
int carga_conf(void)

carga_conf se encarga de la carga o creación del fichero de configuración (en caso
de que éste no existiese). El fichero del configuración va a definir el comportamiento
de la aplicación en muchos sentidos, por lo que es necesario cargarlo al principio.
*/

int carga_conf(void)
{

    FILE *conf;

    /* Carga de la configuración */

    conf = fopen("w3_cfg.txt", "rt");	// Abre el fichero de configuración

    if (conf == NULL) {		// Si no existe lo crea con la configuración por defecto
	config.SCREEN_SIZE_X = 640;
	config.SCREEN_SIZE_Y = 480;
	config.FULLSCREEN = 0;
	strcpy(config.dir, "ws_datos");
	conf = fopen("w3_cfg.txt", "wt");
	fprintf(conf,
		"Fichero generado por WorldSpace3D. Modificar con cuidado\n\n");
	fprintf(conf, "Resolución horz.(X)\t %d\n", config.SCREEN_SIZE_X);
	fprintf(conf, "Resolución vert.(Y)\t %d\n", config.SCREEN_SIZE_Y);
	fprintf(conf, "Pantalla completa\t %d\n", config.FULLSCREEN);
	fprintf(conf, "Directorio base\t %s\n", config.dir);
	fclose(conf);
    } else {
	fscanf(conf,
	       "Fichero generado por WorldSpace3D. Modificar con cuidado\n\n");
	fscanf(conf, "Resolución horz.(X)\t %d\n",
	       &(short int) config.SCREEN_SIZE_X);
	fscanf(conf, "Resolución vert.(Y)\t %d\n",
	       &(short int) config.SCREEN_SIZE_Y);
	fscanf(conf, "Pantalla completa\t %d\n",
	       &(char) config.FULLSCREEN);
	fscanf(conf, "Directorio base\t %s\n", config.dir);
	fclose(conf);
    }



    return SI;


}

/*!
int cerrar_bios(void)

Cierra los fichero de logs, y graba el fichero de configuración.

*/

int cerrar_bios(void)
{

    FILE *conf;
    conf = fopen("w3_cfg.txt", "wt");
    fprintf(conf,
	    "Fichero generado por WorldSpace3D. Modificar con cuidado\n\n");
    fprintf(conf, "Resolución horz.(X)\t %d\n", config.SCREEN_SIZE_X);
    fprintf(conf, "Resolución vert.(Y)\t %d\n", config.SCREEN_SIZE_Y);
    fprintf(conf, "Pantalla completa\t %d\n", config.FULLSCREEN);
    fprintf(conf, "Directorio base\t %s\n", config.dir);
    fclose(conf);
    fprintf(logs, "\n....Guardada la configuración\n");
    fprintf(logs, "\n\nWorldSpace 3D se cerró correctamente");
    fclose(logs);

    return SI;

}


/*!

FILE abre_fichero(char *nombre, char *modo)

Abre un fichero preponiendo el path por defecto

*/

FILE *abre_fichero(char *nombre, char *modo)
{

    FILE *aux;
    char f_fich[1024];
    strcpy(f_fich, config.dir);
    strcat(f_fich, "/");
    strcat(f_fich, nombre);
    _sis_msj("\n\t\t[bios]bios.c -> Cargando fichero ");
    _sis_msj(f_fich);
    aux = fopen(f_fich, modo);
    if (aux!=NULL)
	return aux;
    else {
	_sis_msj(" error abriendo ");
	_sis_msj(f_fich);
	_sis_msj(" ");
	return NULL;
    }
    return NULL;



}

/*!

char prepara_apertura(char *nombre)

Prepara una cadena anteponiendole el PATH por defecto.
Se usa en el caso de que no queramos alterar el código de abrir fichero

*/


char *prepara_apertura(char *nombre)
{


    char *f_fich;
    f_fich = (char *) malloc(1024);
    strcpy(f_fich, config.dir);
    strcat(f_fich, "/");
    strcat(f_fich, nombre);
    _sis_msj("\n\t\t[bios]bios.c -> Preparando PATH para fichero ");
    _sis_msj(f_fich);
    return f_fich;

}
