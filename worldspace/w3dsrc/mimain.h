//==========================================================================
//  mimain.h - Declaración de la estructura que simula la estructura de 
//             SDL_main.
//
//  begin     : jue may 15 2003
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

#ifndef _mimain_h_
#define _mimain_h_
//==========================================================================

#ifdef main
#undef main
#endif // main

#define main MiMain

int MiMain ( int iArg, char ** vArg );

//==================================================================
//  Para Win32 con MingW32 sin sdlmain.lib
//==================================================================

static char    sAux[LON_BUFF];
static int     iArg, iLonW;
static char ** vArg;
static char  * pCadW;

int WINAPI WinMain( HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine, int nCmdShow )
{
    //==============================================================
	//  Construcción de los argumentos en : iArg y vArg.
    //==============================================================
	mInicio(sAux);
	strcpy(sAux,lpCmdLine);

	for ( iArg=0, pCadW=strtok(lpCmdLine, " "); pCadW; iArg++ )
		pCadW=strtok(NULL, " ");

	vArg = (char **) dar_m( sizeof(char *) * (iArg+1), "Linea de argumentos");
	miNulo(vArg);

	vArg[0]=(char *) dar_m( strlen("Programa")+1, "Nombre Programa");
	miNulo(vArg[0]);

	strcpy(vArg[0],"Programa");

	for ( iArg=1, pCadW=strtok(sAux, " "); pCadW; iArg++ )
	{
		iLonW = strlen(pCadW);

		vArg[iArg]= (char *) dar_m( iLonW+1, "Argumento");
		miNulo(vArg[iArg]);

		strcpy(vArg[iArg],pCadW);
		pCadW=strtok(NULL, " ");
	}
    //==============================================================

	return MiMain (iArg, vArg);
}

//==========================================================================
#endif  // _mimain_h_

//==========================================================================
//  Fin de mimain.h
//==========================================================================
