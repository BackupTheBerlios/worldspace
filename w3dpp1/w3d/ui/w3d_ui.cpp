/***************************************************************************
                          w3d_ui.cpp  -  description
                             -------------------
    begin                : sáb ene 11 2003
    copyright            : (C) 2003 by neuralgya
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

#include "libgli/include/gli.h"
#include "../opengl.h"
#include "../global.h"


extern "C" {
  int init_ui(void);
}
extern "C" {
  int ui_loop(void);
}

extern "C" {
  char *prepara_apertura(char *nombre);
}



CGLI_Interface iface,wall;
CGLI_Text text;
CGLI_Button2D bexit;
CGLI_Window2D win1;
CGLI_Image img;


int done=0;
  
void CallBack(GLuint id)
{
    done=1;
} 


void setup()
{

    GLuint a;
    char *fuente;
    _sis_msj("\n\t\tCOnfigurando UI");
    fuente=prepara_apertura("fuentes/ui_chicago.bmf");
    iface.LoadBitmapFont(fuente);

 



    win1.SetDimensions(200, 180, 1);
  	win1.SetCaptionHeight(8);
  	win1.SetWindowColor(0, 0, 0, 1);
  	win1.SetCaptionColor(0.1, 0.1, 0.1, 0.99);
  	win1.SetCaptionTextColor(0.9, 0.9, 0.9, 0.99);
	  win1.SetCaptionText("WorldSpace 3D");
  	win1.SetFontType(GLI_FONT_BITMAP);
    

    

    
    text.SetStringSpaceLength(0.1);
    text.AddNewString("");
   	text.AddNewString("");
   	text.AddNewString("");
    text.AddNewString("                                                                      ");
    text.AddNewString(" This program is free software; you can redistribute it and/or modify  ");
    text.AddNewString(" it under the terms of the GNU General Public License as published by  ");
    text.AddNewString(" the Free Software Foundation; either version 2 of the License, or     ");
    text.AddNewString(" (at your option) any later version.                                   ");
    text.AddNewString("                                                                      ");
    text.AddNewString("");
  	text.AddNewString(" Basado en tecnologia OpenGL");
  	text.AddNewString(" ");
  	text.AddNewString(" Usa SDL - Simple DirectMedia Layer - licencia LGPL");
   	text.AddNewString(" Web: http://www.libsdl.org");
   	text.AddNewString(" ");
  	text.AddNewString(" Usa internamente GLI - Benjamin Schieder - licencia LPGL");
   	text.AddNewString(" Web: http://www.crash-override.net");
  	text.AddNewString(" ");
  	text.AddNewString(" Codigo disponible bajo licencia GPL. CopyRight Grupo WorldSpace");
    text.SetDimensions(5, 5, 1);
    text.SetPosition(-100,80, 2);
    text.SetFontType(GLI_FONT_BITMAP);
    
    
    bexit.SetCallBackFunctionByEvent(CallBack, GLI_CLICKED);
   	bexit.SetPosition(0, -40, 3);
    bexit.SetButtonText("Ok");
    bexit.SetDimensions(18, 6, 1);
    bexit.SetBorderSize(0.5);

    iface.AddObject(&win1);

    win1.AddObject(&bexit);
    win1.AddObject(&text);

    fuente=prepara_apertura("img/fondo_1.tga");
    a=iface.LoadTextureFromFile(fuente);
  	iface.AddObject(&img);
	  img.SetDimensions(640, 480, 0);
  	img.SetTexture(a);
       
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glClearColor(0, 0, 0, 0);
    glColor3f(1, 1, 1);
    _sis_msj("\n[OK]\t\tConfiguración de Interfaz de Usuario libGUI");

}

void redraw()
{

   
    static Uint32 past_time = 0;
    static int pos=90;
    Uint32 now;

    /*now = SDL_GetTicks();
    if ( now-past_time>100)
    {
      pos++;
      past_time=now;
    } */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
/*    glLoadIdentity();
    wall.Draw();
    glClear(GL_DEPTH_BUFFER_BIT);*/
    glLoadIdentity();
    iface.Draw();
    glFlush();
    SDL_GL_SwapBuffers();
}

int init_ui() {

    glViewport(0, 0, config.SCREEN_SIZE_X, config.SCREEN_SIZE_Y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//    glOrtho(-100*1.33, 100*1.33, -100, 100, -100, 100);
    glOrtho(-100.0*(GLfloat)config.SCREEN_SIZE_X/(GLfloat)config.SCREEN_SIZE_Y, 100.0*(GLfloat)config.SCREEN_SIZE_X/(GLfloat)config.SCREEN_SIZE_Y, -100.0, 100.0, -100.0, 100.0);
    glMatrixMode(GL_MODELVIEW);

  setup();
  SDL_ShowCursor(1);
	SDL_WarpMouse(config.SCREEN_SIZE_X/2, config.SCREEN_SIZE_Y/2);
	SDL_WM_GrabInput(SDL_GRAB_OFF);
  _sis_msj("\n[OK]\t\tInterfaz de Usuario libGUI inicializado");
  return SI;
}

int ui_loop() {

  int mouse_x,mouse_y;
  SDL_Event event;

  Uint8 *keys;
	// Enter to the main ui loop
  


    while (done==0) {

        if (SDL_PollEvent(&event))
            if (event.type == SDL_QUIT)
                done = 1;
        if ( event.type == SDL_MOUSEMOTION ) 
               iface.SendMouseParameters(GLI_MOUSE_MOTION, GLI_MOUSE_BUTTON_NONE, GLI_MOUSE_BUTTON_NONE, event.motion.x, config.SCREEN_SIZE_Y-event.motion.y);
        if ( event.type == SDL_MOUSEBUTTONDOWN )
               iface.SendMouseParameters(GLI_MOUSE_CLICK, GLI_MOUSE_BUTTON_LEFT, GLI_MOUSE_BUTTON_DOWN, event.button.x, config.SCREEN_SIZE_Y-event.button.y);
        if ( event.type == SDL_MOUSEBUTTONDOWN )
        				    iface.SendMouseParameters(GLI_MOUSE_CLICK, GLI_MOUSE_BUTTON_LEFT, GLI_MOUSE_BUTTON_UP, event.button.x, config.SCREEN_SIZE_Y-event.button.y);


        keys = SDL_GetKeyState(NULL);
          if (keys[SDLK_ESCAPE])
            done=1;

    redraw();    
    }

return SI;
}

