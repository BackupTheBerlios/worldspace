/***************************************************************************
                          madivs.cpp  -  description
                             -------------------
    begin                : jue jun 6 2002
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


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <paragui.h>

#include <pgapplication.h>
#include <pgbutton.h>
#include <pgscrollbar.h>
#include <pglabel.h>
#include <pgcheckbutton.h>
#include <pglineedit.h>
#include <pgwindow.h>


#include "pgglwidget.h"

    float color[8][3]= {{ 1.0,  1.0,  0.0},
			    { 1.0,  0.0,  0.0},
			    { 0.0,  0.0,  0.0},
			    { 0.0,  1.0,  0.0},
			    { 0.0,  1.0,  1.0},
			    { 1.0,  1.0,  1.0},
			    { 1.0,  0.0,  1.0},
			    { 0.0,  0.0,  1.0}};
	float cube[8][3]= {{ 0.5,  0.5, -0.5},
			   { 0.5, -0.5, -0.5},
			   {-0.5, -0.5, -0.5},
			   {-0.5,  0.5, -0.5},
			   {-0.5,  0.5,  0.5},
			   { 0.5,  0.5,  0.5},
			   { 0.5, -0.5,  0.5},
			   {-0.5, -0.5,  0.5}};

class GLWidget : public PG_GLWidget {
public:
	GLWidget(PG_Widget* parent, const PG_Rect& rect) : PG_GLWidget(parent, rect) {
	};

protected:
	void eventBlit(SDL_Surface* srf, const PG_Rect& src, const PG_Rect& dst) {
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   		glBegin( GL_QUADS );

		glColor3fv(color[0]);
		glVertex3fv(cube[0]);
		glColor3fv(color[1]);
		glVertex3fv(cube[1]);
		glColor3fv(color[2]);
		glVertex3fv(cube[2]);
		glColor3fv(color[3]);
		glVertex3fv(cube[3]);
		
		glColor3fv(color[3]);
		glVertex3fv(cube[3]);
		glColor3fv(color[4]);
		glVertex3fv(cube[4]);
		glColor3fv(color[7]);
		glVertex3fv(cube[7]);
		glColor3fv(color[2]);
		glVertex3fv(cube[2]);
			
		glColor3fv(color[0]);
		glVertex3fv(cube[0]);
		glColor3fv(color[5]);
		glVertex3fv(cube[5]);
		glColor3fv(color[6]);
		glVertex3fv(cube[6]);
		glColor3fv(color[1]);
		glVertex3fv(cube[1]);
			
		glColor3fv(color[5]);
		glVertex3fv(cube[5]);
		glColor3fv(color[4]);
		glVertex3fv(cube[4]);
		glColor3fv(color[7]);
		glVertex3fv(cube[7]);
		glColor3fv(color[6]);
		glVertex3fv(cube[6]);

		glColor3fv(color[5]);
		glVertex3fv(cube[5]);
		glColor3fv(color[0]);
		glVertex3fv(cube[0]);
		glColor3fv(color[3]);
		glVertex3fv(cube[3]);
		glColor3fv(color[4]);
		glVertex3fv(cube[4]);

		glColor3fv(color[6]);
		glVertex3fv(cube[6]);
		glColor3fv(color[1]);
		glVertex3fv(cube[1]);
		glColor3fv(color[2]);
		glVertex3fv(cube[2]);
		glColor3fv(color[7]);
		glVertex3fv(cube[7]);

		glEnd( );
	};

	void eventMouseEnter() {
		SetBackgroundColor(0.2,0,0.1);
		PG_Widget::eventMouseEnter();
	}

	void eventMouseLeave() {
		SetBackgroundColor(0.1,0.1,0.1);
		PG_Widget::eventMouseLeave();
	}

};

PG_Application app;

int main(int argc, char *argv[])
{

  app.SetEmergencyQuit(true);
  app.LoadTheme("default");
	int i;
	int rgb_size[3];
	int w = 640;
	int h = 480;
  int bpp=16;

	Uint32 video_flags;
	int value;

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		fprintf(stderr,"Couldn't initialize SDL: %s\n",SDL_GetError());
		exit( 1 );
  }


	/* Set the flags we want to use for setting the video mode */
	video_flags = SDL_OPENGLBLIT;

	for ( i=1; argv[i]; ++i ) {
		if ( strcmp(argv[i], "-fullscreen") == 0 ) {
			video_flags |= SDL_FULLSCREEN;
		}
	}

	/* Initialize the display */
	switch (bpp) {
	    case 8:
		rgb_size[0] = 2;
		rgb_size[1] = 3;
		rgb_size[2] = 3;
		break;
	    case 15:
	    case 16:
		rgb_size[0] = 5;
		rgb_size[1] = 6;
		rgb_size[2] = 5;
		break;
		default:
		rgb_size[0] = 8;
		rgb_size[1] = 8;
		rgb_size[2] = 8;
		break;
	}
	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, rgb_size[0] );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, rgb_size[1] );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, rgb_size[2] );
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );



  if (!app.InitScreen(640, 480, 0, video_flags)) {
      fprintf(stderr, "Couldn't set GL mode: %s\n", SDL_GetError());
     exit(1);
  }
	app.EnableBackground();
 	SDL_WM_SetCaption( "MadIVS", "madivs" );




  GLWidget gl_view1(NULL, PG_Rect(100,100,200,200));
	new PG_Label(&gl_view1, PG_Rect(0,0,90,20), "GL View 1");


    // now we have to make the button visible

  gl_view1.Show();

	PG_Button* btn1 = new PG_Button(NULL, 1, PG_Rect(30,30,100,50), "Quit");
	btn1->Show();


	PG_Rect rs(0,0, PG_Application::GetScreenWidth(), PG_Application::GetScreenHeight());
  PG_Widget::UpdateRect(rs);
  SDL_UpdateRects(SDL_GetVideoSurface(), 1, &rs);
	
  int done=0;	
	while( !done ) {
		GLenum gl_error;
		char* pg_error;
		SDL_Event event;


		gl_view1.Update();

		glRotatef(1, 1.0, 1.0, 1.0);

		SDL_GL_SwapBuffers( );

		/* Check for error conditions. */
		gl_error = glGetError( );

		if( gl_error != GL_NO_ERROR ) {
			fprintf( stderr, "testgl: OpenGL error: %d\n", gl_error );
		}

		pg_error = SDL_GetError( );

		if( pg_error[0] != '\0' ) {
			fprintf(stderr, "testgl: SDL error '%s'\n", pg_error);
			SDL_ClearError();
		}


		/* Check if there's a pending event. */
/*		if ( SDL_PollEvent( &event ) ) {
			HandleEvent(&event, &app);
		}*/
		

	}


	return(0);
}







