/*
	libgli - A library assisting in the creation of OpenGL User Interfaces
	Copyright (C) 2002 Benjamin Schieder <blindcoder@scavenger.homeip.net>

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/
#ifndef __GLI_WINDOW_H__
#define __GLI_WINDOW_H__

#include "gli_frame.h"
#include "gli_button.h"

//==///////////////////////////////////////////////////////////////////////////////==
//                           CGLI_Window2D class
//==///////////////////////////////////////////////////////////////////////////////==

// Flat window (2D) class
class CGLI_Window2D : public CGLI_Frame
{
public:
	CGLI_Window2D();
	virtual ~CGLI_Window2D();

	void SetWindowColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a); // Main window color
	void SetCaptionColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a); // Caption color
	void SetCaptionHeight(GLfloat height); // Caption height
	void SetWindowType(GLuint win_type); // Window type (filled, framed)
	void SetCaptionText(char *text); // Caption height
	void SetCaptionTextColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a); // Caption text color
	void SetFontType(GLuint font_type); // Font type 

	virtual void Draw();

	// This method should update all sub objects in object
	// Must be called, when some info is sended to object
	virtual void UpdateObject();
	virtual void DoAnimationTick();


	void DoMinimize();

protected:

	virtual void ProcessInternalCallBack(GLuint obj_id);

	GLuint m_button_minimize_id, m_button_close_id; // Window buttons - Minimize and Close

	CGLI_Button2D m_button_minimize, m_button_close;
	GLfloat m_win_r, m_win_g, m_win_b, m_win_a; // Window background color r,g,b,a
	GLfloat m_cap_r, m_cap_g, m_cap_b, m_cap_a; // Window caption color r,g,b,a
	GLfloat m_cap_height; // Caption height

	GLuint m_win_type; // Type of the window
	char *m_caption_text; // Caption text
	GLfloat m_cap_tr, m_cap_tg, m_cap_tb, m_cap_ta; // Window caption text color r,g,b,a

	GLuint m_font_type;
	GLboolean m_in_minimization;

};

#endif

