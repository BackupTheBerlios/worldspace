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
    }
  else
      _sis_msj("[OK]\tSistema gráfico inicializado\n");
	
	
	return SI;
}

