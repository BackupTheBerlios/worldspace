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
#include "textura.h"
#include "globales.h"

#ifdef _MSVC
#include "sdl_gl.h"
#endif // _MSVC

/*!
=============================================================================
Inicio de la aplicación. Punto de entrada.
=============================================================================
  Modifico el main para probar que la carga de las texturas funciona
  correctamente.
=============================================================================
  Generalmente los sistemas identifican que todo ha ido bien en un programa
  si devuelve 0. Si devuelve distinto de cero, alguna incidencia ha ocurrido.
  Voy a establecer que si hay algun error devuelvo 1, y si todo ha ido bien
  el programa devolverá 0.
  Y no  SI=1  y  NO=0.
=============================================================================
  Y al final me he tenido que rendir y meter las líneas de WinMain para
  el compilador Ming32.
  El caso es que para VC estaba funcionando lo del SDLmain,incluso también
  para Ming32, pero cuando quería ampliar unas pequeñas modificaciones
  no me dejaba.
=============================================================================
!*/
#ifdef _LINUX
int main(int iArg, char *vArg[])
{
#endif  // _LINUX
//==================================================================
#ifdef _WIN32
#ifndef _MSVC
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow)
{
	int     iArg = sizeof(lpCmdLine)/sizeof(LPSTR);
	char ** vArg = (char **) lpCmdLine;
#else
//==================================================================
int main(int iArg, char *vArg[])
{
#endif  // _MSVC
#endif  // _WIN32
//==================================================================
	int iError = 0;

    if (ini_bios(iArg, vArg))
	{
        if (ini_display())
		{
            if (ini_audio())
            {
	            if (
                       ( carga_listaFuentes(&vListaFuentes)   )
                  /*|| ( carga_listaTexturas(&vListaTexturas) ) Lista de texturas */
                  /*|| ( carga_listaModelos(&vListaModelos)   ) Lista de modelos  Las texturas deben de pasarse antes */
                    || ( genera_texturas()                    )
                   )
	                iError = 1;
				else
				{
	                if (ini_gl(SI))           ;  // Bucle principal
					else            iError = 1;
				}
	            cerrar_texturas();
                cerrar_audio();
			}
			else iError = 1;
            cerrar_display();
		}
		else iError = 1;
        cerrar_bios();
	}
	else iError = 1;

    return iError;
}
