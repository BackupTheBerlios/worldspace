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
#ifndef __GLI_PROGRESS_H__
#define __GLI_PROGRESS_H__

#include "gli_object.h"

//==///////////////////////////////////////////////////////////////////////////////==
//                           CGLI_ProgressBar class
//==///////////////////////////////////////////////////////////////////////////////==

// Progress bar class ()
class CGLI_ProgressBar : public CGLI_Object
{

public:

	CGLI_ProgressBar();
	virtual ~CGLI_ProgressBar();

	void SetPercent(GLfloat percent); // Set progress bar percent (0..100)
	void AddPercent(GLfloat percent); // Add to current percent counter 

	void SetTextColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a); // Color of percent text
	void SetBorderColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a); // Color of border
	void SetTextHeight(GLfloat text_height); // Set height of percent text

	virtual void Draw();
	virtual void UpdateObject();
	virtual void DoAnimationTick();

protected:

	virtual void ProcessInternalCallBack(GLuint obj_id);

	GLfloat m_percent;
	GLfloat m_tr, m_tg, m_tb, m_ta; // Color of percent text
	GLfloat m_br, m_bg, m_bb, m_ba; // Color of border
	GLfloat m_text_height; // Percent text height

};

#endif

