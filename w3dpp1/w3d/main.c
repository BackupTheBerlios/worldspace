/***************************************************************************
                          main.c  -  Flujo principal de la aplicación
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


#include "global.h"
#include "display/display.h"
#include "gfx/fuentes.h"
#include "ui/w3d_ui.h"
#include "engine/engine.h"


/*!
int main(void)

Punto de entrada a la aplicación. Controla el flujo principal de
la misma

*/

int main(void)
{
    /*
       Lo primero, inicializar el sistema básico (bios) del sistema.

     */
    if (!init_bios())
        return NO;
    else
        _sis_msj("[OK]\tSistema básico inicializado\n");

    if (!sis_ini_display()) {
        _sis_msj("[KO]\tNo se pudo iniciar el Sistema gráfico\n");
        cerrar_bios();
        return NO;
    } else
        _sis_msj("[OK]\tSistema gráfico inicializado\n");

    if (!ini_fuente()) {
        _sis_msj
            ("[KO]\tNo se pudo iniciar el sistema de renderizado de fuentes");
        cerrar_bios();
        return NO;
    } else
        _sis_msj("[OK]\tSistema de renderizado de fuentes inicializado");



    _sis_msj("\n\t\tEntrando en el modo UI - Inicializando libGUI");
    if (init_ui()) {
        _sis_msj("\n[OK]\tGui Inicializado");
        ui_loop();
    }

    _sis_msj("\n\t\tInicializando Engine");
    if (init_engine()) {
        _sis_msj("\n[OK]\tEngine Inicializado");
        game_loop();
    } else
        _sis_msj("\n[KO]\tLa cagamos Luis, no se inicializó el engine");



    _sis_msj("\n\nNotificación de cierre\n");
    /* Salida de la aplicación */
    if (!sis_cerrar_display()) {
        _sis_msj("[KO]\tError al cerrar el Sistema gráfico\n");
        cerrar_bios();
        return NO;
    } else
        _sis_msj("[OK]\tSistema gráfico cerrado\n");

    cerrar_bios();

    return SI;
}
