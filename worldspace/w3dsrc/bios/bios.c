/***************************************************************************
                          bios.c  -  Inicializaci�n de sistemas b�sicos
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
#include <stdarg.h>

#include "w3d_base.h"
#include "globales.h"

/*!
Valores de configuracion inicial.
!*/
#define WXSCREEN      640
#define WYSCREEN      480
#define WNBITS        16
#define WALLSCREEN    0
#define WDIR_GENERAL  "ws_datos"
#define WDIR_TEXTURAS "texturas"
#define WDIR_FUENTES  "fuentes"
#define WDIR_MODELOS  "modelos"
#define WDIR_ESPACIOS "espacios"
#define WDIR_NODIR    "no_hay_directorio"
/*!
Patrones para leer la configuracion inicial del fichero ini.
!*/
#define PXSCREEN      "Xtam  = "
#define PYSCREEN      "Ytam  = "
#define PNBITS        "bpp    = "
#define PALLSCREEN    "FullScreen = "
#define PDIR_GENERAL  "DirGeneral  = "
#define PDIR_TEXTURAS "DirTexturas = "
#define PDIR_FUENTES  "DirFuentes  = "
#define PDIR_MODELOS  "DirModelos  = "
#define PDIR_ESPACIOS "DirEspacios = "

/*!
================================== DECLARACION DE VARIABLES
!*/

/*
Cadena vac�a de 80 espacios, la usaremos para la traza
*/
char cad_traza[80];

/*!
Variable para guardar la configuracion
!*/
estr_config configuracion;

/*!
Descriptor del fichero de logs
!*/
FILE *salida_log;

/*!
Nivel de traza
*/
char nivel_traza = 0;

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
    vsprintf(texto, cadena, ap);        // y las sustituye por su valor
    va_end(ap);                 // almacenando el resultado en text

    fprintf(salida_log, &cad_traza[79 - nivel_traza * 2]);
    fprintf(salida_log, texto);

    fflush(salida_log);

    return SI;
}

/*!
Esta funci�n inicializa el sistema de logs
*/
int ini_sis_log()
{
    int i;

    for (i = 0; i < 79; i++)
        cad_traza[i] = ' ';

    cad_traza[i] = '\0';

    if (!(salida_log = fopen("w3d.log", "wt")))
        return NO;
    else {
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
    }

    return SI;

}

/*!
Establecemos la configuraci�n carg�ndola desde un fichero, que si
o existe se crea y se establece la de por defecto
*/
int establece_conf()
{

    FILE *f_conf;

    T_FUNC_IN;

    if ((f_conf = abre_fichero("w3d.ini", "rt"))) {
        /*
           Por Hacer: Parsear este fichero
           y establecer las variables de configuracion
         */
    } else {
        /* Cargamos la configuraci�n por defecto */
        configuracion.Xtam = WXSCREEN;
        configuracion.Ytam = WYSCREEN;
        configuracion.bpp = WNBITS;
        configuracion.FullScreen = WALLSCREEN;
        strcpy(configuracion.sDirGeneral, WDIR_GENERAL);
        strcpy(configuracion.sDirTexturas, WDIR_TEXTURAS);
        strcpy(configuracion.sDirFuentes, WDIR_FUENTES);
        strcpy(configuracion.sDirModelos, WDIR_MODELOS);
        strcpy(configuracion.sDirEspacios, WDIR_ESPACIOS);

    }

    T_FUNC_OUT return SI;

}

/*!
Esta funci�n inicializa los sistemas b�sicos de salida de errores y warnings.
Abre un fichero en modo de escritura, y ah� es donde se van depositando los
mensajes del sistema.
*/
int ini_bios(int iArg, char **cArg)
{
    T_FUNC_IN if (!ini_sis_log())
         return NO;
    else
        log_msj("[OK] Sistema de logs abierto\n");

    if (establece_conf())
        log_msj("[OK] Configuraci�n establecida\n");
    else {
        log_msj("[KO] Fallo al establecer configuraci�n\n");
        return NO;
    }

    log_msj("[OK] Sistema b�sico inicializado\n");

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

    T_FUNC_IN char nombre_completo[LON_BUFF];

    strcpy(nombre_completo, configuracion.sDirGeneral);
    strcat(nombre_completo, "/");
    strcat(nombre_completo, nombre);
    log_msj("[bios.c] Abriendo %s\n", nombre);
    tmp = fopen(nombre_completo, modo);
    if (!tmp)
        log_msj("[KO] Error abriendo %s\n", nombre);
    else
        log_msj("[OK] %s abierto \n", nombre);

    T_FUNC_OUT return tmp;

}
