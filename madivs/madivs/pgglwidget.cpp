/*
    ParaGL - an OpenGL extension for ParaGUI
    Copyright (C) 2001  Alexander Pipelka

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public
    License along with this library; if not, write to the Free
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Alexander Pipelka
    pipelka@teleweb.at

    Last Update:      $Author: neuralgya $
    Update Date:      $Date: 2002/06/06 17:03:29 $
    Source File:      $Source: /home/xubuntu/berlios_backup/github/tmp-cvs/worldspace/Repository/madivs/madivs/Attic/pgglwidget.cpp,v $
    CVS/RCS Revision: $Revision: 1.1 $
    Status:           $State: Exp $
*/

#include "pgglwidget.h"
#include "pgapplication.h"

#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/gl.h>

PG_GLWidget::PG_GLWidget(PG_Widget* parent, const PG_Rect& rect) : PG_Widget(parent, rect) {
	backcolor[0] = 0.1;
	backcolor[1] = 0.1;
	backcolor[2] = 0.1;
}

PG_GLWidget::~PG_GLWidget() {
}

void PG_GLWidget::Blit(bool recursive, bool restore) {
	glViewport(x, PG_Application::GetScreenHeight()-y-h, w, h);
	glClearColor( backcolor[0], backcolor[1], backcolor[2], 0 );

	glScissor(x, PG_Application::GetScreenHeight()-y-h, w, h);
	glEnable(GL_SCISSOR_TEST);
	
	PG_Rect src(0,0,w,h);
	PG_Rect dst = *this;
	eventBlit(NULL, src, dst);

	glDisable(GL_SCISSOR_TEST);
}

bool PG_GLWidget::RestoreBackground(PG_Rect* clip) {
	return true;
}

void PG_GLWidget::Update() {
	static Uint32 color_black = SDL_MapRGBA(my_srfScreen->format, 0,0,0,0);

	if(!IsVisible()) {
		return;
	}

	Blit();

	RecalcClipRect();
	
	PG_RectList* list = GetChildList();
	PG_RectList::iterator i;

	if(list) {

		SDL_SetClipRect(my_srfScreen, GetClipRect());

		i = list->begin();

		while(i != list->end()) {
			if(!(*i)->IsVisible()) {
				i++;
				continue;
			}
	
			PG_Rect* rect = (*i)->GetClipRect();
			SDL_FillRect(my_srfScreen, rect, color_black);

			(*i)->Blit(true, false);
			(*i)->Update(false);
			i++;
		}

		SDL_SetClipRect(my_srfScreen, NULL);
	}

	// find the toplevel widget
	PG_Widget* obj = this;
	while(obj->GetParent()) {
		obj = obj->GetParent();
	}

	// find my index
	int index = GetWidgetList()->FindIndexOf(obj);

	if(index != -1) {
		// get a list with all objects in front of me
		PG_RectList frontlist = GetWidgetList()->Intersect(GetClipRect(), index+1, -1);

		i = frontlist.begin();

		SDL_SetClipRect(my_srfScreen, GetClipRect());

		while(i != frontlist.end()) {
			if(!(*i)->IsVisible()) {
				i++;
				continue;
			}
	
			PG_Rect* rect = (*i)->GetClipRect();
			SDL_FillRect(my_srfScreen, rect, color_black);
			(*i)->Blit(true, false);
			(*i)->Update(false);
			i++;
		}

		SDL_SetClipRect(my_srfScreen, NULL);

	}

}

void PG_GLWidget::SetBackgroundColor(double r, double g, double b) {
	backcolor[0] = r;
	backcolor[1] = g;
	backcolor[2] = b;
}
