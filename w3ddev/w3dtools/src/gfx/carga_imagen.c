//==========================================================================
//  carga_imagen.c  -  Carga los ficheros de imagen en sus distintos
//                     formatos
//
//  begin     : sat apr 12 2003 / sab 12 abr 2003
//  copyright : (C) 2003 by Grupo WorldSpace
//  email     : eric@users.berlios.de
//==========================================================================
//                                                                         *
//   This program is free software; you can redistribute it and/or modify  *
//   it under the terms of the GNU General Public License as published by  *
//   the Free Software Foundation; either version 2 of the License, or     *
//   (at your option) any later version.                                   *
//                                                                         *
//==========================================================================

#include <string.h>
#include <stdarg.h>
#include "sdl_gl.h"
#include "op_bmp.h"
#include "op_tga.h"
#include "util.h"
#include "globales.h"
#include "w3d_base.h"
#include "carga_imagen.h"

//==========================================================================
// Extensiones de ficheros de imagenes
//==========================================================================
static char *vsFicImagen[] = {
    "BMP",                      // FBMP
    "TGA",                      // FTGA
    "RGB",                      // FRGB
    "BW",                       // FBW   // A lo peor con este no funciona por la longitud diferente
};

//==========================================================================
static char sAux1[LON_BUFF];    // Buffer auxiliar.
static char sAux2[LON_BUFF];    // Buffer auxiliar.
//==========================================================================

//==========================================================================
// Funcion de carga de ficheros.
// El nombre del fichero debe tener una extensión reconocida por el programa
// Si todo va bien devuelve 0
// Si no devuelve -1
//==========================================================================
// Este módulo está relacionado con las texturas, por ello tampoco voy a
// utilizar las devoluciones de SI(1) y NO(0)
//==========================================================================
int carga_imagen(miFic_imagen * prFic_imagen)
{
    T_FUNC_IN;

    if (prFic_imagen->sFichero == NULL) {
        _return - 1;
    } else {
        char sCadena[LON_BUFF / 4];
        char sColaFic[8];
        int i, iAncho, iAlto;
        void *imagen = NULL;

        //---------------------------------------------------
        // Primero extraemos la extension del fichero
        //---------------------------------------------------
        mInicio(sColaFic);
        mInicio(sCadena);
        strcpy(sColaFic, prFic_imagen->sFichero + strlen(prFic_imagen->sFichero) - 7);  // Extraemos la cola del nombre del fichero
        uStrtoken(sCadena, sColaFic, ".");      // El primero se queda con la izquierda
        uStrtoken(sCadena, NULL, ".");  // El segundo se queda con la extensión
        //---------------------------------------------------
        uMayusculas(sCadena);
        for (i = 0; i < NUM_FICIMAGEN; i++) {
            if (!strcmp(sCadena, vsFicImagen[i]))
                break;
        }
        //---------------------------------------------------
        switch (i) {
        case FBMP:
            imagen = carga_bmp(prFic_imagen->sFichero, &iAncho, &iAlto);
            break;

        case FTGA:
            imagen = carga_tga(prFic_imagen->sFichero, &iAncho, &iAlto);
            break;

            // Tenemos que crear la funcion y tener ficheros de prueba
        case FRGB:
            // imagen = read_rgb_texture(prFic_imagen->sNomfic, &iAncho, &iAlto);
            break;

        case FBW:
            // imagen = read_alpha_texture(prFic_imagen->sNomfic, &iAncho, &iAlto);
            break;

        default:               // Fichero no reconocido
            log_msj("\n Extensión de fichero de imagen no reconocida: %s",
                    sCadena);
            _return - 1;
        }
        //---------------------------------------------------
        if (imagen == NULL) {
            _return - 1;
        }
        //---------------------------------------------------
        prFic_imagen->iTipo = i;
        prFic_imagen->iAncho = iAncho;
        prFic_imagen->iAlto = iAlto;
        prFic_imagen->pDatos = imagen;
    }

    _return 0;                  // Todo ha ido bien.
}

//==========================================================================
//  Devuelve el nombre del tipo de fichero de imagen
//==========================================================================
char *tipo_imagen(int iTipo)
{
    return vsFicImagen[iTipo];
}

//==========================================================================
//  Devuelve el directorio que inicia el nombre de un fichero
//  Si alguno de los directorios que se pasan están vacíos,
//  se eliminan las '/' de la cadena final.
//==========================================================================
//  Esta función es casi lo mismo que 'sprintf'.
//
//      directorio (sDest, "%s/%s", Config.sDirGeneral,Config.sDirFuente );
//
//==========================================================================
char *directorio(char *sDir, char *sFormat, ...)
{
    va_list lista;
    int i;
    char *sCad;

    mInicio(sAux1);
    mInicio(sAux2);

    va_start(lista, sFormat);
    vsprintf(sAux1, sFormat, lista);
    va_end(lista);

    // Debemos recorrer la cadena limpiando valores tipo '//'
    // supongo también si el primero es '/' pero no estoy seguro.
    sCad = strtok(sAux1, "/");
    for (i = 0; i < 10 && sCad != NULL; i++)    // Establecemos un límite por si 'overflow'
    {
        strcat(sAux2, sCad);
        strcat(sAux2, "/");
        sCad = strtok(NULL, "/");
    }
    strcpy(sDir, sAux2);

    return sDir;
}

//==========================================================================
//  Fin de carga_imagen.c
//==========================================================================
