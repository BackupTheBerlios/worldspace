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
#include <stdio.h>
#include "gli_progress.h"

//==///////////////////////////////////////////////////////////////////////////////==
//                           CGLI_ProgressBar class
//==///////////////////////////////////////////////////////////////////////////////==

CGLI_ProgressBar::CGLI_ProgressBar()
{				/* {{{ */
    SetPercent(0.0);
    m_width = 50;
    m_height = 5;
    m_text_height = 0;
    SetColor(0, 0, 0.6f, 1);
    SetTextColor(1, 1, 1, 1);
    SetBorderColor(1, 1, 1, 1);
}				/* }}} */

CGLI_ProgressBar::~CGLI_ProgressBar()
{				/* {{{ */

}				/* }}} */

void CGLI_ProgressBar::SetTextColor(GLfloat r, GLfloat g, GLfloat b,
				    GLfloat a)
{				/* {{{ */
// Set button text color
    m_tr = r;
    m_tg = g;
    m_tb = b;
    m_ta = a;
}				/* }}} */

void CGLI_ProgressBar::SetBorderColor(GLfloat r, GLfloat g, GLfloat b,
				      GLfloat a)
{				/* {{{ */
// Color of border
    m_br = r;
    m_bg = g;
    m_bb = b;
    m_ba = a;
}				/* }}} */

void CGLI_ProgressBar::SetTextHeight(GLfloat text_height)
{				/* {{{ */
    m_text_height = text_height;
}				/* }}} */

void CGLI_ProgressBar::SetPercent(GLfloat percent)
{				/* {{{ */
    if (percent > 100.0)
	m_percent = 100.0;
    else if (percent < 0.0)
	m_percent = 0.0;
    else
	m_percent = percent;
}				/* }}} */

void CGLI_ProgressBar::AddPercent(GLfloat percent)
{				/* {{{ */
    m_percent += percent;
    if (m_percent > 100.0)
	m_percent = 100.0;
    if (m_percent < 0.0)
	m_percent = 0.0;
}				/* }}} */

void CGLI_ProgressBar::Draw()
{				/* {{{ */
    glColor4f(m_r, m_g, m_b, m_a);

    glTranslatef(-m_width / 2, -m_height / 2, -m_depth / 2);
    // Draw standard background
    glBegin(GL_QUADS);
    glVertex3f(0, 0, 0);
    glVertex3f(m_width * (m_percent / 100.0f), 0, 0);
    glVertex3f(m_width * (m_percent / 100.0f), m_height, 0);
    glVertex3f(0, m_height, 0);
    glEnd();

    if (m_depth > 0) {		// Check if we're 3D
	glBegin(GL_QUADS);
	glVertex3f(0, 0, -m_depth);
	glVertex3f(m_width * (m_percent / 100.0f), 0, -m_depth);
	glVertex3f(m_width * (m_percent / 100.0f), m_height, -m_depth);
	glVertex3f(0, m_height, -m_depth);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, -m_depth);
	glVertex3f(0, m_height, -m_depth);
	glVertex3f(0, m_height, 0);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(m_width * (m_percent / 100.0f), 0, 0);
	glVertex3f(m_width * (m_percent / 100.0f), 0, -m_depth);
	glVertex3f(m_width * (m_percent / 100.0f), m_height, -m_depth);
	glVertex3f(m_width * (m_percent / 100.0f), m_height, 0);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 0);
	glVertex3f(m_width * (m_percent / 100.0f), 0, 0);
	glVertex3f(m_width * (m_percent / 100.0f), 0, -m_depth);
	glVertex3f(0, 0, -m_depth);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(0, m_height, 0);
	glVertex3f(m_width * (m_percent / 100.0f), m_height, 0);
	glVertex3f(m_width * (m_percent / 100.0f), m_height, -m_depth);
	glVertex3f(0, m_height, -m_depth);
	glEnd();
    }

    glColor4f(m_br, m_bg, m_bb, m_ba);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-0.1f, -0.1f, -0.1f);
    glVertex3f(m_width + 0.1f, -0.1f, -0.1f);
    glVertex3f(m_width + 0.1f, m_height + 0.1f, -0.1f);
    glVertex3f(-0.1f, m_height + 0.1f, -0.1f);
    glEnd();
    if (m_depth > 0) {
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1f, -0.1f, -m_depth - 0.1f);
	glVertex3f(m_width + 0.1, -0.1f, -m_depth - 0.1f);
	glVertex3f(m_width + 0.1, m_height + 0.1f, -m_depth - 0.1f);
	glVertex3f(-0.1f, m_height + 0.1f, -m_depth - 0.1f);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1f, -0.1f, -0.1f);
	glVertex3f(-0.1f, -0.1f, -m_depth - 0.1f);
	glVertex3f(-0.1f, m_height + 0.1f, -m_depth - 0.1f);
	glVertex3f(-0.1f, m_height + 0.1f, -0.1f);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex3f(m_width + 0.1f, -0.1f, -0.1f);
	glVertex3f(m_width + 0.1f, -0.1f, -m_depth - 0.1f);
	glVertex3f(m_width + 0.1f, m_height + 0.1f, -m_depth - 0.1f);
	glVertex3f(m_width + 0.1f, m_height + 0.1f, -0.1f);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1f, -0.1f, -0.1f);
	glVertex3f(m_width + 0.1f, -0.1f, -0.1f);
	glVertex3f(m_width + 0.1f, -0.1f, -m_depth - 0.1f);
	glVertex3f(-0.1f, -0.1f, -m_depth - 0.1f);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1f, m_height + 0.1f, -0.1f);
	glVertex3f(m_width + 0.1f, m_height + 0.1f, -0.1f);
	glVertex3f(m_width + 0.1f, m_height + 0.1f, -m_depth - 0.1f);
	glVertex3f(-0.1f, m_height + 0.1f, -m_depth - 0.1f);
	glEnd();
    }
    // Draw percents
    glPushMatrix();

    // Color of text
    glColor4f(m_tr, m_tg, m_tb, m_ta);

    glTranslatef(m_width / 2, m_height / 2, 0.1f);

    if (m_text_height == 0)
	glScalef(m_height / 2, m_height / 2, 1);
    else
	glScalef(m_text_height, m_text_height, 1);

    char temp_str[64];
    sprintf(temp_str, "%i%%", (int) m_percent);

    GLboolean temp;

    // Save old centering and set text centering
    temp = m_pVectorFont->glfGetStringCentering();
    m_pVectorFont->glfStringCentering(GL_TRUE);
    m_pVectorFont->glfDrawSolidString(temp_str);
    m_pVectorFont->glfStringCentering(temp);
    glPopMatrix();

}				/* }}} */

void CGLI_ProgressBar::UpdateObject()
{				/* {{{ */

}				/* }}} */

void CGLI_ProgressBar::DoAnimationTick()
{				/* {{{ */

}				/* }}} */

void CGLI_ProgressBar::ProcessInternalCallBack(GLuint obj_id)
{				/* {{{ */

}				/* }}} */
