#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "paragui.h"

#include "pgapplication.h"
#include "pgbutton.h"
#include "pgscrollbar.h"
#include "pglabel.h"
#include "pgcheckbutton.h"
#include "pglineedit.h"
#include "pgwindow.h"

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

class MyGLWidget : public PG_GLWidget {
public:
	MyGLWidget(PG_Widget* parent, const PG_Rect& rect) : PG_GLWidget(parent, rect) {
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

float speed = 0.5;
Uint32 start_time, this_time;
Uint32 last_time_stamp;
int frames = 0;
int done = 0;


PARAGUI_CALLBACK(handle_exit) {
	done = 1;
	return true;
}

PARAGUI_CALLBACK(handle_rotate_speed) {
	PG_Label* label = static_cast<PG_Label*>(clientdata);

	speed = 0.5 + (float)data / 10;
	label->SetTextFormat("Speed: %0.1f", speed);

	return true;
}

void HotKey_ToggleFullScreen(void)
{
	SDL_Surface *screen;

	screen = SDL_GetVideoSurface();
	if ( SDL_WM_ToggleFullScreen(screen) ) {
		printf("Toggled fullscreen mode - now %s\n",
		    (screen->flags&SDL_FULLSCREEN) ? "fullscreen" : "windowed");
	} else {
		printf("Unable to toggle fullscreen mode\n");
	}
}

void HotKey_Iconify(void)
{
	printf("Ctrl-Z: iconifying window!\n");
	SDL_WM_IconifyWindow();
}

int HandleEvent(SDL_Event *event, PG_Application* app)
{
	switch( event->type ) {
	    case SDL_ACTIVEEVENT:
		/* See what happened */
		printf( "app %s ", event->active.gain ? "gained" : "lost" );
		if ( event->active.state & SDL_APPACTIVE ) {
			printf( "active " );
		} else if ( event->active.state & SDL_APPMOUSEFOCUS ) {
			printf( "mouse " );
		} else if ( event->active.state & SDL_APPINPUTFOCUS ) {
			printf( "input " );
		}
		printf( "focus\n" );
		break;
		
	    case SDL_KEYDOWN:
		if ( event->key.keysym.sym == SDLK_ESCAPE ) {
			done = 1;
		}
		if ( (event->key.keysym.sym == SDLK_z) &&
		     (event->key.keysym.mod & KMOD_CTRL) ) {
			HotKey_Iconify();
		}
		if ( (event->key.keysym.sym == SDLK_RETURN) &&
		     (event->key.keysym.mod & KMOD_ALT) ) {
			HotKey_ToggleFullScreen();
		}
		printf("key '%s' pressed\n", 
			SDL_GetKeyName(event->key.keysym.sym));
		break;

	    case SDL_QUIT:
		done = 1;
		break;
	}
	
	app->PumpIntoEventQueue(event);
	
	return(0);
}

int RunGLTest( int argc, char* argv[],
               int logo, int slowly, int bpp, float gamma )
{
	app.LoadTheme("simple");

	int i;
	int rgb_size[3];
	int w = 640;
	int h = 480;

	Uint32 video_flags;
	int value;

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		fprintf(stderr,"Couldn't initialize SDL: %s\n",SDL_GetError());
		exit( 1 );
	}

	/* See if we should detect the display depth */
	if ( bpp == 0 ) {
		if ( SDL_GetVideoInfo()->vfmt->BitsPerPixel <= 8 ) {
			bpp = 8;
		}
		else if ( SDL_GetVideoInfo()->vfmt->BitsPerPixel <= 16) {
			bpp = 16;
		}
		else {
			bpp = 32;
		}
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
	if (!app.InitScreen( w, h, bpp, video_flags )) {
		fprintf(stderr, "Couldn't set GL mode: %s\n", SDL_GetError());
		exit(1);
	}

	app.EnableBackground();

	printf("\n");
	printf( "Vendor     : %s\n", glGetString( GL_VENDOR ) );
	printf( "Renderer   : %s\n", glGetString( GL_RENDERER ) );
	printf( "Version    : %s\n", glGetString( GL_VERSION ) );
	printf( "Extensions : %s\n", glGetString( GL_EXTENSIONS ) );
	printf("\n");

	SDL_GL_GetAttribute( SDL_GL_RED_SIZE, &value );
	printf( "SDL_GL_RED_SIZE: requested %d, got %d\n", rgb_size[0],value);
	SDL_GL_GetAttribute( SDL_GL_GREEN_SIZE, &value );
	printf( "SDL_GL_GREEN_SIZE: requested %d, got %d\n", rgb_size[1],value);
	SDL_GL_GetAttribute( SDL_GL_BLUE_SIZE, &value );
	printf( "SDL_GL_BLUE_SIZE: requested %d, got %d\n", rgb_size[2],value);
	SDL_GL_GetAttribute( SDL_GL_DEPTH_SIZE, &value );
	printf( "SDL_GL_DEPTH_SIZE: requested %d, got %d\n", bpp, value );
	SDL_GL_GetAttribute( SDL_GL_DOUBLEBUFFER, &value );
	printf( "SDL_GL_DOUBLEBUFFER: requested 1, got %d\n", value );

	/* Set the window manager title bar */
	SDL_WM_SetCaption( "GL test", "testgl" );

	/* Set the gamma for the window */
	if ( gamma != 0.0 ) {
		SDL_SetGamma(gamma, gamma, gamma);
	}

	//glViewport( 0, 0, w, h );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );

	glOrtho( -1, 1, -1, 1, -10.0, 10.0 );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );

	glEnable(GL_DEPTH_TEST);

	glDepthFunc(GL_LESS);

	glShadeModel(GL_SMOOTH);

	/* Loop until done. */
	start_time = SDL_GetTicks();
	frames = 0;

	MyGLWidget glwidget1(NULL, PG_Rect(100,100,200,200));
	new PG_Label(&glwidget1, PG_Rect(0,0,90,20), "GL View 1");

	MyGLWidget glwidget2(NULL, PG_Rect(310,100,200,200));
	new PG_Label(&glwidget2, PG_Rect(0,0,90,20), "GL View 2");

	glwidget1.Show();
	glwidget2.Show();

	PG_Button* btn1 = new PG_Button(NULL, 1, PG_Rect(30,30,100,50), "Quit");
	btn1->SetEventCallback(MSG_BUTTONCLICK, handle_exit);
	btn1->Show();

	PG_Label* labelfps = new PG_Label(
					NULL,
					PG_Rect(270,380,100,25),
					"FPS: ?"
					);
	labelfps->SetAlignment(PG_TA_CENTER);
	labelfps->Show();

	PG_Label* label = new PG_Label(
					NULL,
					PG_Rect(270,350,100,25),
					"Speed: 0.5"
					);
	label->SetAlignment(PG_TA_CENTER);
	label->Show();
		
	PG_ScrollBar* scroll = new PG_ScrollBar(
					NULL,
					2,
					PG_Rect(620,5,20,350));

	scroll->SetRange(0,50);
	scroll->SetEventCallback(MSG_SCROLLTRACK, handle_rotate_speed, label);
	scroll->SetEventCallback(MSG_SCROLLPOS, handle_rotate_speed, label);
	scroll->Show();

	PG_LineEdit* le = new PG_LineEdit(NULL, PG_Rect(270,410,100,25));
	le->SetValidKeys("0123456789");
	le->Show();

	PG_Window wnd(NULL, PG_Rect(25,310,200,130), "Window");
	MyGLWidget glwidget3(&wnd, PG_Rect(5,30,190,95));
	PG_Label* label3 = new PG_Label(&glwidget3, PG_Rect(0,0,190,95), "ParaGUI rocks!");
	label3->SetAlignment(PG_TA_CENTER);
	label3->SetFontColor(0xFF0000);

	wnd.Show();

	PG_Rect rs(0,0, PG_Application::GetScreenWidth(), PG_Application::GetScreenHeight());
	PG_Widget::UpdateRect(rs);
	SDL_UpdateRects(SDL_GetVideoSurface(), 1, &rs);
		
	while( !done ) {
		GLenum gl_error;
		char* pg_error;
		SDL_Event event;

		this_time = SDL_GetTicks();
		if ( (this_time - last_time_stamp)> 1000) {
			last_time_stamp = this_time;
			double fps = ((float)frames/(this_time-start_time))*1000.0;
			labelfps->SetTextFormat("FPS: %0.1f", fps);
		}

		glwidget1.Update();
		glwidget2.Update();
		glwidget3.Update();

		glRotatef(speed, 1.0, 1.0, 1.0);

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

		/* Allow the user to see what's happening */
		if ( slowly ) {
			SDL_Delay( 20 );
		}

		/* Check if there's a pending event. */
		if ( SDL_PollEvent( &event ) ) {
			HandleEvent(&event, &app);
		}
		
		++frames;
	}

	/* Print out the frames per second */
	this_time = SDL_GetTicks();
	if ( this_time != start_time ) {
		printf("%2.2f FPS\n",
			((float)frames/(this_time-start_time))*1000.0);
	}

	return(0);
}

int main(int argc, char *argv[])
{
	int i, logo;
	int numtests;
	int bpp = 0;
	int slowly;
	float gamma = 0.0;

	logo = 1;
	slowly = 0;
	numtests = 1;
	for ( i=1; argv[i]; ++i ) {
		if ( strcmp(argv[i], "-twice") == 0 ) {
			++numtests;
		}
		if ( strcmp(argv[i], "-slow") == 0 ) {
			slowly = 1;
		}
		if ( strcmp(argv[i], "-bpp") == 0 ) {
 		       bpp = atoi(argv[++i]);
		}
		if ( strcmp(argv[i], "-gamma") == 0 ) {
 		       gamma = (float)atof(argv[++i]);
		}
		if ( strncmp(argv[i], "-h", 2) == 0 ) {
 		       printf(
"Usage: %s [-twice] [-slow] [-bpp n] [-gamma n]\n",
 			      argv[0]);
			exit(0);
		}
	}
	

	RunGLTest(argc, argv, logo, slowly, bpp, gamma);
	return 0;
}
