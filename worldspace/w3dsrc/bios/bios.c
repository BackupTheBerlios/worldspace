/***************************************************************************
                          bios.c  -  Inicialización de sistemas básicos
                             -------------------
    begin                : dom feb 9 2003
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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <errno.h>

#include "w3d_base.h"
#include "globales.h"
#include "conf_parser.h"

#ifdef _LINUX
#define FICH_LOG "/.w3d.log"
#define FICH_INI "/.w3d.ini"
#endif
#ifdef _WIN32
#define FICH_LOG "w3d.log"
#define FICH_INI "w3d.ini"
#endif

/*!
========================= DECLARACION DE VARIABLES
!*/

/*
Cadena vacía de 80 espacios, la usaremos para la traza
*/
char cad_traza[80];

/*!
Variable para guardar la configuracion
!*/
estr_config configuracion;

/*!
Descriptor del fichero de logs
!*/
FILE *salida_log = NULL;

/*!
Nivel de traza
*/
char nivel_traza = 0;

/*!
Hora a la que inicio el programa
*/
time_t hora_inicio;
/*!
================================== FUNCIONES
!*/

/*!
Salida de logs
*/
int log_msj(char *cadena, ...)
{

    char texto[LON_BUFF];       // almacena el texto a escribir
    va_list ap;                 // puntero a la lista de argumentos (los ...)

    va_start(ap, cadena);       // Busca variables en el texto
    vsprintf(texto, cadena, ap);// y las sustituye por su valor
    va_end(ap);                 // almacenando el resultado en text

	if (salida_log==NULL)
		salida_log = stdout;

    fprintf(salida_log, &cad_traza[79 - nivel_traza * 2]);
    fprintf(salida_log, texto);

    fflush(salida_log);

    return SI;
}

/*!
Esta función inicializa el sistema de logs
*/
int ini_sis_log()
{
    int i, estado;
    char c_fich_log[LON_BUFF];

    for (i = 0; i < 79; i++)
        cad_traza[i] = ' ';

    cad_traza[i] = '\0';

#ifdef _LINUX
    strcpy(c_fich_log, getenv("HOME"));
    strcat(c_fich_log, FICH_LOG);
#endif
#ifdef _WIN32
    strcpy(c_fich_log, FICH_LOG);
#endif

    if (!(salida_log = fopen(c_fich_log, "wa"))) {

        salida_log = stdout;
        estado = NO;
    } else
        estado = SI;

    log_msj
        ("           WorldSpace 3D. copyright 2003 Grupo WorldSpace            \n");
    log_msj
        ("=====================================================================\n");
    log_msj
        ("              Distribuido bajo/Distributed under GNU GPL             \n");
    log_msj
        ("=====================================================================\n");
    log_msj
        ("This program is free software; you can redistribute it and/or modify \n");
    log_msj
        ("it under the terms of the GNU General Public License as published by \n");
    log_msj
        ("the Free Software Foundation; either version 2 of the License, or    \n");
    log_msj
        ("(at your option) any later version.                                  \n");
    log_msj
        ("=====================================================================\n");

    return estado;

}

/*!
Guarda de la configuracion actual
*/
int graba_conf()
{

    FILE *fl_conf;
    char c_fich[LON_BUFF];

    T_FUNC_IN;

#ifdef _LINUX
    strcpy(c_fich, getenv("HOME"));
    strcat(c_fich, FICH_INI);
#endif
#ifdef _WIN32
    strcpy(c_fich, FICH_INI);
#endif

    if ((fl_conf = fopen(c_fich, "wt"))) {
        fprintf(fl_conf, "# Generado por WorldSpace 3D a %s\n",
                ctime(&hora_inicio));
        fprintf(fl_conf, "%s\t\t\t%d\n", PXSCREEN, configuracion.Xtam);
        fprintf(fl_conf, "%s\t\t\t%d\n", PYSCREEN, configuracion.Ytam);
        fprintf(fl_conf, "%s\t\t\t%d\n", PNBITS, configuracion.bpp);
        fprintf(fl_conf, "%s\t\t\t%d\n", PALLSCREEN,
                configuracion.FullScreen);
        fprintf(fl_conf, "%s\t\t\t%s\n", PDIR_GENERAL,
                configuracion.sDirGeneral);
        fclose(fl_conf);
    }

    T_FUNC_OUT return SI;

}

/*!
Establecemos la configuración cargándola desde un fichero, que si
o existe se crea y se establece la de por defecto
*/
int establece_conf()
{

    FILE *f_conf;
    char c_fich[LON_BUFF];

    T_FUNC_IN;

#ifdef _LINUX
    strcpy(c_fich, getenv("HOME"));
    strcat(c_fich, FICH_INI);
#endif
#ifdef _WIN32
    strcpy(c_fich, FICH_INI);
#endif

    if ((f_conf = fopen(c_fich, "rt"))) {
        /*
           Por Hacer: Parsear este fichero
           y establecer las variables de configuracion
         */
        configuracion.Xtam = establece_var_conf_numero(f_conf, PXSCREEN);
        if (!configuracion.Xtam)
            configuracion.Xtam = WXSCREEN;
        configuracion.Ytam = establece_var_conf_numero(f_conf, PYSCREEN);
        if (!configuracion.Ytam)
            configuracion.Ytam = WYSCREEN;
        configuracion.bpp = establece_var_conf_numero(f_conf, PNBITS);
        if (!configuracion.bpp)
            configuracion.bpp = WNBITS;
        configuracion.FullScreen =
            establece_var_conf_numero(f_conf, PALLSCREEN);
        if (!configuracion.FullScreen)
            configuracion.FullScreen = WALLSCREEN;

        strcpy(configuracion.sDirGeneral,
               establece_var_conf_cadena(f_conf, PDIR_GENERAL));
        if (!configuracion.sDirGeneral[0])
            strcpy(configuracion.sDirGeneral, WDIR_GENERAL);

        strcpy(configuracion.sDirTexturas,
               establece_var_conf_cadena(f_conf, PDIR_TEXTURAS));
        if (!configuracion.sDirTexturas[0])
            strcpy(configuracion.sDirTexturas, WDIR_TEXTURAS);

        strcpy(configuracion.sDirFuentes,
               establece_var_conf_cadena(f_conf, PDIR_FUENTES));
        if (!configuracion.sDirFuentes[0])
            strcpy(configuracion.sDirFuentes, WDIR_FUENTES);

        strcpy(configuracion.sDirModelos,
               establece_var_conf_cadena(f_conf, PDIR_MODELOS));
        if (!configuracion.sDirModelos[0])
            strcpy(configuracion.sDirModelos, WDIR_MODELOS);

        strcpy(configuracion.sDirSonidos,
               establece_var_conf_cadena(f_conf, PDIR_SONIDOS));
        if (!configuracion.sDirSonidos[0])
            strcpy(configuracion.sDirSonidos, WDIR_SONIDOS);

        strcpy(configuracion.sDirEspacios,
               establece_var_conf_cadena(f_conf, PDIR_ESPACIOS));
        if (!configuracion.sDirEspacios)
            strcpy(configuracion.sDirEspacios, WDIR_ESPACIOS);

        fclose(f_conf);

    } else {
        /* Cargamos la configuración por defecto */
        configuracion.Xtam = WXSCREEN;
        configuracion.Ytam = WYSCREEN;
        configuracion.bpp = WNBITS;
        configuracion.FullScreen = WALLSCREEN;
        strcpy(configuracion.sDirGeneral , WDIR_GENERAL );
        strcpy(configuracion.sDirTexturas, WDIR_TEXTURAS);
        strcpy(configuracion.sDirFuentes , WDIR_FUENTES );
        strcpy(configuracion.sDirModelos , WDIR_MODELOS );
        strcpy(configuracion.sDirSonidos , WDIR_SONIDOS );
        strcpy(configuracion.sDirEspacios, WDIR_ESPACIOS);
        graba_conf();

    }

    T_FUNC_OUT return SI;

}

/*!
Esta función inicializa los sistemas básicos de salida de errores y warnings.
Abre un fichero en modo de escritura, y ahí es donde se van depositando los
mensajes del sistema.
*/
int ini_bios(int iArg, char **cArg)
{
    T_FUNC_IN hora_inicio = time(NULL);

    if (!ini_sis_log())
        log_msj
            ("[KO] Sistema de logs no abierto, usando salida estandar\n");

    else
        log_msj("[OK] Sistema de logs abierto\n");

    if (establece_conf())
        log_msj("[OK] Configuración establecida\n");
    else {
        log_msj("[KO] Fallo al establecer configuración\n");
        return NO;
    }

    log_msj("[OK] Sistema básico inicializado\n");

    T_FUNC_OUT return SI;

}

int cerrar_bios()
{
    T_FUNC_IN log_msj("[bios.c] Cerrando bios....\n");
    fclose(salida_log);
    T_FUNC_OUT return SI;

}

/*!
Wrapper para fopen, que inserta al nombre del fichero
el directorio de los datos
*/
FILE *abre_fichero(char *nombre, char *modo)
{

    FILE *tmp;
	char nombre_completo[LON_BUFF];

    T_FUNC_IN

    strcpy(nombre_completo, configuracion.sDirGeneral);
    strcat(nombre_completo, "/");
    strcat(nombre_completo, nombre);
    log_msj("[bios.c] Abriendo %s\n", nombre_completo);
    tmp = fopen(nombre_completo, modo);
    if (!tmp)
        log_msj("[KO] Error abriendo %s\n", nombre);
    else
        log_msj("[OK] %s abierto \n", nombre);

    T_FUNC_OUT return tmp;

}
