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
#include "gli_editbox.h"
#include "string.h"

CGLI_EditBox2D::CGLI_EditBox2D(){ /* {{{ */
	// Standard border-color
	m_r = 0.5f;
	m_g = 0.5f;
	m_b = 0.5f;
	m_a = 1.0f;

	// Standard background-color
	m_br = 0.2f;
	m_bg = 0.2f;
	m_bb = 0.2f;
	m_ba = 1.0f;

	// Standard text color
	m_tr = 1;
	m_tg = 1;
	m_tb = 1;
	m_ta = 1;

	// Standard mouse over border-color
	m_mor = 0.6f;
	m_mog = 0.6f;
	m_mob = 0.9f;
	m_moa = 1.0f;
	m_text = new char;
	*m_text = 0;

	// Stadard mouse over background-color
	m_mobr = 0.3f;
	m_mobg = 0.3f;
	m_mobb = 0.6f;
	m_moba = 1.0f;

	// Standard mouse over text-color
	m_motr = 1;
	m_motg = 1;
	m_motb = 1;
	m_mota = 1;

	m_text_height = 1;
	AddObject(&m_string);
	m_text = (char *)malloc(256);	// TODO Should be changed to something
					// TODO dynamic
	m_string.AddNewString("");
	m_string.SetPosition(-m_width/2, 0, 0.1);
	m_string.SetDimensions(3, 3, 1);
} /* }}} */

CGLI_EditBox2D::~CGLI_EditBox2D(){ /* {{{ */
	if (m_text) delete [] m_text;
} /* }}} */

char *CGLI_EditBox2D::GetText(){ /* {{{ */
	char *dum = (char *)malloc(strlen(m_text)+1);

	memset(dum, 0x0, strlen(m_text)+1);
	memcpy(dum, m_text, strlen(m_text));
	return dum;
} /* }}} */

void CGLI_EditBox2D::SetTextColor(GLfloat r, GLfloat g, GLfloat b){ /* {{{ */
	m_tr = r;
	m_tg = g;
	m_tb = b;
} /* }}} */

void CGLI_EditBox2D::SetTextColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a){ /* {{{ */
	m_tr = r;
	m_tg = g;
	m_tb = b;
	m_ta = a;
} /* }}} */

void CGLI_EditBox2D::SetMouseOverTextColor(GLfloat r, GLfloat g, GLfloat b){ /* {{{ */
	m_motr = r;
	m_motg = g;
	m_motb = b;
} /* }}} */

void CGLI_EditBox2D::SetMouseOverTextColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a){ /* {{{ */
	m_motr = r;
	m_motg = g;
	m_motb = b;
	m_mota = a;
} /* }}} */

void CGLI_EditBox2D::SetBackgroundColor(GLfloat r, GLfloat g, GLfloat b){ /* {{{ */
	m_br = r;
	m_bg = g;
	m_bb = b;
} /* }}} */

void CGLI_EditBox2D::SetBackgroundColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a){ /* {{{ */
	m_br = r;
	m_bg = g;
	m_bb = b;
	m_ba = a;
} /* }}} */

void CGLI_EditBox2D::SetMouseOverBackgroundColor(GLfloat r, GLfloat g, GLfloat b){ /* {{{ */
	m_mobr = r;
	m_mobg = g;
	m_mobb = b;
} /* }}} */

void CGLI_EditBox2D::SetMouseOverBackgroundColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a){ /* {{{ */
	m_mobr = r;
	m_mobg = g;
	m_mobb = b;
	m_moba = a;
} /* }}} */

void CGLI_EditBox2D::SetBorderColor(GLfloat r, GLfloat g, GLfloat b){ /* {{{ */
	m_r = r;
	m_g = g;
	m_b = b;
} /* }}} */

void CGLI_EditBox2D::SetBorderColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a){ /* {{{ */
	m_r = r;
	m_g = g;
	m_b = b;
	m_a = a;
} /* }}} */

void CGLI_EditBox2D::SetMouseOverBorderColor(GLfloat r, GLfloat g, GLfloat b){ /* {{{ */
	m_mor = r;
	m_mog = g;
	m_mob = b;
} /* }}} */

void CGLI_EditBox2D::SetMouseOverBorderColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a){ /* {{{ */
	m_mor = r;
	m_mog = g;
	m_mob = b;
	m_moa = a;
} /* }}} */

void CGLI_EditBox2D::Draw(){ /* {{{ */
	if (m_event_type == GLI_ONOVER)	{
		glColor4f(m_mor, m_mog, m_mob, m_moa);
	} else {
		glColor4f(m_r, m_g, m_b, m_a);
	}
	// Drawing Frame
	glBegin(GL_LINE_LOOP);
		glVertex3f(-m_width/2, -m_height/2, 0);
		glVertex3f(m_width/2, -m_height/2, 0);
		glVertex3f(m_width/2, m_height/2, 0);
		glVertex3f(-m_width/2, m_height/2, 0);
	glEnd();
	if (m_event_type == GLI_ONOVER){
		glColor4f(m_mobr, m_mobg, m_mobb, m_moba);
	} else {
		glColor4f(m_br, m_bg, m_bb, m_ba);
	}
	// Drawing Background
	glBegin(GL_QUADS);
		glVertex3f(-m_width/2, -m_height/2, 0);
		glVertex3f(m_width/2, -m_height/2, 0);
		glVertex3f(m_width/2, m_height/2, 0);
		glVertex3f(-m_width/2, m_height/2, 0);
	glEnd();
} /* }}} */

void CGLI_EditBox2D::UpdateObject(){ /* {{{ */
	m_string.SetPosition(-m_width/2+4, 0, 0.1);
} /* }}} */

void CGLI_EditBox2D::DoAnimationTick(){ /* {{{ */

} /* }}} */

void CGLI_EditBox2D::ProcessInternalCallBack(GLuint obj_id){ /* {{{ */
	// Handling the keyboard
	if (m_event_type == GLI_KEYBOARD)
	{
		if (m_key == 8){ // Backspace
			memset(m_text+strlen(m_text)-1, 0x0, 1);
			m_string.DeleteAllStrings();
			m_string.AddNewString(m_text);
		} else if ((m_key >= 32) && (m_key <= 254)){ // typeable
			m_string.DeleteAllStrings();
			sprintf(m_text, "%s%c", m_text, m_key);
			m_string.AddNewString(m_text);
		} else {
			printf("Unhandled key exception:: %i == '%c'\n", m_key, m_key);
		}
		m_event_type = GLI_ONOVER;
	}
} /* }}} */
