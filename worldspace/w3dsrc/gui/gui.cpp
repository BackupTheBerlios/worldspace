/***************************************************************************
                          w3d_ui.cpp  -  description
                             -------------------
    begin                : vie 17 2003
    copyright            : (C) 2003 by lordloki
    email                : lordloki@users.berlios.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "sdl_gl.h"
#include "w3d_base.h"
#include "mesgui.h"
#include "misc.h"
#include "scancodes.h"

using namespace std;

extern "C" {
    int ini_ui(void);
}
extern "C" {
    int log_msj(char *cadena, ...);
}
extern "C" {
    estr_config configuracion;
}

int done = 0;

void redibujar()
{
    glClear(GL_COLOR_BUFFER_BIT );
    DrawMESGUI();
    SDL_GL_SwapBuffers();
}

void CallBack()
{
    done = 1;
}
void pantalla_inicial()
{

	/* Frame principal */
	ggFrame *base = new ggFrame("                                              WorldSpace 3D");
        mainframe->AddControl(base,300,80,420,490);
        base->SetFrameColor(0,0,0,0);

	/* Añadimos una caja multitexto */
        ggText *caja = new ggText("This program is free software; you can redistribute it and/or modify\nit under the terms of the GNU General Public License as published by\nthe Free Software Foundation; either version 2 of the License, or\n(at your option) any later version.\n\nBasado en tecnologia OpenGL\n\nUsa SDL - Simple DirectMedia Layer - licencia LGPL\nWeb: http://www.libsdl.org\n\nUsa OpenAL - Open Audio Library - Licencia LGPL\nWeb:http://www.openal.org\n\nUsa Ogg Vorbis - Licencia BSD-like\nWeb:http://www.xiph.org\n\nUsa internamente MesGUI - Eric Maxey - licencia LPGL\nWeb:http://sourceforge.net/projects/mesgui\n\nUsa internamente MikMod - Jean-Paul Mikkers - Licencia LGPL\nWeb:http://www.mikmod.org\n\nCodigo disponible bajo licencia GPL. CopyRight Grupo WorldSpace");
        caja->SetFlags(GGFLAG_MULTILINE);
        caja->RemoveFlags(GGFLAG_DONT_DRAW_BORDER | GGFLAG_SIZETOCONTENT);
        caja->SetColor(0.2f,0.1f,0.4f);

	/* Añadimos la caja multitexto al frame principal */
	base->AddControl(caja,10,10,420-10-10,490-10-10-COL_HEIGHT);//COL_HEIGHT se define en InitMESGUI

	/* Añadimos un pulsador */
	base->AddControl(new ggButton("Cerrar",CallBack) ,(int)(420/2)-(int)(48/2),400,40);
}

void ui_loop()
{

int mouse_x, mouse_y;
SDL_Event event;
Uint8 *keys;

while (done == 0) {
		while (SDL_PollEvent(&event)) {
			switch(event.type)
			{
			case SDL_QUIT:
				done=1;
				break;

			case SDL_ACTIVEEVENT:
//				active=event.active.gain?true:false;
				break;

			case SDL_KEYDOWN:
			case SDL_KEYUP:
				if (event.key.keysym.sym < 128) {
					char c = event.key.keysym.sym;
					if (event.key.keysym.mod & KMOD_LSHIFT || event.key.keysym.mod & KMOD_RSHIFT)
						c = shiftize(c);
					GG_KeyboardEvent(c, event.key.state);
				} else {
					switch (event.key.keysym.sym) {
					case SDLK_RIGHT:
						GG_SKeyboardEvent(SC_RIGHT, event.key.state);
						break;
					case SDLK_LEFT:
						GG_SKeyboardEvent(SC_LEFT, event.key.state);
						break;
					default:
						break;
					}
				}
				break;

			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
				GG_MouseButton(event.button.button,event.button.state);
				break;
			}
		}

		keys= SDL_GetKeyState(NULL);
		if (keys[SDLK_ESCAPE])
			done=1;

		/* Actualizamos la posicion del raton */
		SDL_GetMouseState(&mouse_x, &mouse_y);
		GG_SetMouseState(mouse_x,mouse_y);

		/* Redibujamos */
		redibujar();
	}

	return;
}

int ini_ui()
{
    /* Establecemos los valores para la correcta representacion del GUI */
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_CULL_FACE);
    glViewport(0, 0, configuracion.Xtam, configuracion.Ytam);

    /* Inicializamos GUI, pasando la fuente y el cursor */
    InitMESGUI(&configuracion.Xtam,&configuracion.Ytam,"ws_datos/fuentes/Vera.ttf",7,16);
    SDL_ShowCursor(0);
    SetCursorTexture("ws_datos/texturas/cursor.bmp");
    log_msj("[w3d_ui.cpp] Inicializando GUI\n");

    /* Mostramos la ventana de presentacion */
    pantalla_inicial();
    /* bucle de eventos */
    ui_loop();
    return 1;
}
