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
    Update Date:      $Date: 2002/06/06 17:03:26 $
    Source File:      $Source: /home/xubuntu/berlios_backup/github/tmp-cvs/worldspace/Repository/madivs/madivs/Attic/pgglwidget.h,v $
    CVS/RCS Revision: $Revision: 1.1 $
    Status:           $State: Exp $
*/

#ifndef PG_GLWIDGET_H
#define PG_GLWIDGET_H

#include "paragl.h"
#include <pgwidget.h>

class DECLSPEC PG_GLWidget : public PG_Widget {
public:

	PG_GLWidget(PG_Widget* parent, const PG_Rect& rect);
	~PG_GLWidget();

	void Blit(bool recursive = true, bool restore = true);
	bool RestoreBackground(PG_Rect* clip);
	void Update();

	void SetBackgroundColor(double r, double g, double b);

private:
	double backcolor[3];
};

#endif	// PG_GLWIDGET_H
