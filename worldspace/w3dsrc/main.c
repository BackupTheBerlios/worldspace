/***************************************************************************
                          main.c  -  Inicio de la aplicación
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

#include "w3d_base.h"
#include "bios.h"
#include "display.h"
#include "engine.h"
#include "audio.h"

/*!
==================================================================
Inicio de la aplicación. Punto de entrada.
==================================================================
!*/

int main(int iArg, char **vArg)
{

    if (!ini_bios(iArg, vArg))
        return NO;

    if (!ini_display())
        return NO;

    if (!ini_audio())
        return NO;

    if (!ini_gl(SI))
        return NO;

    cerrar_audio();
    cerrar_display();
    cerrar_bios();

    return SI;
}
