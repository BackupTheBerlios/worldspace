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
#ifndef __GLI_EDITBOX_H__
#define __GLI_EDITBOX_H__

#include <stdio.h>
#include <stdlib.h>
#include "gli_object.h"
#include "gli_text.h"

//==///////////////////////////////////////////////////////////////////////////////==
//                           CGLI_EditBox2D class
//==///////////////////////////////////////////////////////////////////////////////==

// Class for edit boxes
class CGLI_EditBox2D : public CGLI_Object
{
public:
	CGLI_EditBox2D();
	virtual ~CGLI_EditBox2D();

	virtual void Draw();
	virtual void UpdateObject();
	virtual void DoAnimationTick();
	virtual char *GetText();
	virtual void SetTextColor(GLfloat r, GLfloat g, GLfloat b);
	virtual void SetTextColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
	virtual void SetMouseOverTextColor(GLfloat r, GLfloat g, GLfloat b);
	virtual void SetMouseOverTextColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
	virtual void SetBackgroundColor(GLfloat r, GLfloat g, GLfloat b);
	virtual void SetBackgroundColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
	virtual void SetMouseOverBackgroundColor(GLfloat r, GLfloat g, GLfloat b);
	virtual void SetMouseOverBackgroundColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
	virtual void SetBorderColor(GLfloat r, GLfloat g, GLfloat b);
	virtual void SetBorderColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
	virtual void SetMouseOverBorderColor(GLfloat r, GLfloat g, GLfloat b);
	virtual void SetMouseOverBorderColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

protected:

	virtual void ProcessInternalCallBack(GLuint obj_id);
	GLfloat m_mobr, m_mobg, m_mobb, m_moba; // Color of button-background when "mouse over"
	GLfloat m_br, m_bg, m_bb, m_ba; // Color of button-background
	GLfloat m_mor, m_mog, m_mob, m_moa; // Color of button-border, when "mouse over"
	GLfloat m_motr, m_motg, m_motb, m_mota; // Color of text, when "mouse over"
	GLfloat m_tr, m_tg, m_tb, m_ta; // Color of text
	GLuint HandleKeyEvent(unsigned char key, GLuint id);

	CGLI_Text m_string;
	char *m_text; // Button text
	GLfloat m_text_height;
};

#endif

