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
#if defined (WIN32)
#include <windows.h>
#endif

#ifdef MACOSX
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#include "gli_frame.h"

//==///////////////////////////////////////////////////////////////////////////////==
//                           CGLI_Frame class
//==///////////////////////////////////////////////////////////////////////////////==


CGLI_Frame::CGLI_Frame()
{
	// Set default parameters
	m_width = 5;
	m_height = 5;
}

CGLI_Frame::~CGLI_Frame()
{

}

void CGLI_Frame::UpdateObject()
{


}

void CGLI_Frame::Draw()
{
	glColor4f(m_r, m_g, m_b, m_a);
	glBegin(GL_LINE_LOOP);
		glVertex3f(-m_width/2, -m_height/2, 0);
		glVertex3f(m_width/2, -m_height/2, 0);
		glVertex3f(m_width/2, m_height/2, 0);
		glVertex3f(-m_width/2, m_height/2, 0);
	glEnd();
}

void CGLI_Frame::DoAnimationTick()
{

}
