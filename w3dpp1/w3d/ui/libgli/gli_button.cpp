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

#include <stdio.h>
#include <string.h>

#ifdef MACOSX
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#include "gli_button.h"


//==///////////////////////////////////////////////////////////////////////////////==
//                           CGLI_Button class
//==///////////////////////////////////////////////////////////////////////////////==

CGLI_Button::CGLI_Button()
{
	// Standard pressed color
	m_pr = 0.5f;
	m_pg = 0.5f;
	m_pb = 0.5f;
	m_pa = 1.0f;
	
	// Standard mouse over color
	m_mor = 0.6f;
	m_mog = 0.6f;
	m_mob = 0.9f;
	m_moa = 1.0f;
	m_text = new char;
	*m_text = 0;

	// Standard text color
	m_tr = 1;
	m_tg = 1;
	m_tb = 1;
	m_ta = 1;

	m_text_height = 0;
}

CGLI_Button::~CGLI_Button()
{
	if (m_text) delete [] m_text;
}

// Set button text, which is showed on button
void CGLI_Button::SetButtonText(char *text)
{
	if (m_text) delete [] m_text;
	
	m_text = new char [strlen(text)+1];
	strcpy(m_text, text);
}

// Set button text color
void CGLI_Button::SetTextColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	m_tr = r;
	m_tg = g;
	m_tb = b;
	m_ta = a;
}

void CGLI_Button::SetTextHeight(GLfloat text_height)
{
	m_text_height = text_height;
}

// Set button color, when mouse is on button (but button is not pressed yet)
void CGLI_Button::SetOnMouseColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	m_mor = r;
	m_mog = g;
	m_mob = b;
	m_moa = a;
}

// Internal callback....Under development
void CGLI_Button::ProcessInternalCallBack(GLuint obj_id)
{
}

void CGLI_Button::UpdateObject()
{

}

void CGLI_Button::DoAnimationTick()
{

}

//==///////////////////////////////////////////////////////////////////////////////==
//                           CGLI_ButtonOBJ class
//==///////////////////////////////////////////////////////////////////////////////==

//!!!!!!!!!!!!! THIS CLASS IS UNDER DEVELOPMENT !!!!!!!!!!!!!!
//!!!!!!!!!!!!! THIS CLASS IS UNDER DEVELOPMENT !!!!!!!!!!!!!!
//!!!!!!!!!!!!! THIS CLASS IS UNDER DEVELOPMENT !!!!!!!!!!!!!!

CGLI_ButtonOBJ::CGLI_ButtonOBJ()
{
	m_vert_n = NULL;
	m_norm_n = NULL;
	m_textur_n = NULL;
	
	m_vert_p = NULL;
	m_norm_p = NULL;
	m_textur_p = NULL;

	m_vert_total_n = 0;
	m_norm_total_n = 0;
	m_textur_total_n = 0;
	
	m_vert_total_p = 0;
	m_norm_total_p = 0;
	m_textur_total_p = 0;

	m_triangles_n = NULL;
	m_tr_type_n = 0;

	m_triangles_p = NULL;
	m_tr_type_p = 0;
}

CGLI_ButtonOBJ::~CGLI_ButtonOBJ()
{

}

void CGLI_ButtonOBJ::SetVertexInfo(GLuint type, GLuint total, GLfloat *vertexes)
{
	if (type == GLI_BUTTON_NORMAL)
	{
		m_vert_total_n = total;
		m_vert_n = vertexes;
	}
	else
	{
		m_vert_total_p = total;
		m_vert_p = vertexes;
	}
}

void CGLI_ButtonOBJ::SetNormalInfo(GLuint type, GLuint total, GLfloat *normals)
{
	if (type == GLI_BUTTON_NORMAL)
	{
		m_norm_total_n = total;
		m_norm_n = normals;
	}
	else
	{
		m_norm_total_p = total;
		m_norm_p = normals;
	}
}

void CGLI_ButtonOBJ::SetTextureCoordInfo(GLuint type, GLuint total, GLfloat *tex_coord)
{
	if (type == GLI_BUTTON_NORMAL)
	{
		m_textur_total_n = total;
		m_textur_n = tex_coord;
	}
	else
	{
		m_textur_total_p = total;
		m_textur_p = tex_coord;
	}
}

void CGLI_ButtonOBJ::SetTriangleInfo(GLuint type, GLuint total, GLuint *triangles, GLuint tr_type)
{
	if (type == GLI_BUTTON_NORMAL)
	{
		m_triangle_total_n = total;
		m_triangles_n = triangles;
		m_tr_type_n = tr_type;
	}
	else
	{
		m_triangle_total_p = total;
		m_triangles_p = triangles;
		m_tr_type_p = tr_type;
	}
}

void CGLI_ButtonOBJ::Draw()
{
	GLfloat *temp_vert, *temp_norm, *temp_tex;
	GLuint *temp_tr;
	GLuint temp_vert_total, temp_norm_total, temp_tex_total, temp_tr_total, temp_tr_type;
	GLuint components;
	GLuint *temp;

//	if ((m_active_msg) && (m_mouse_state == GLI_MOUSE_BUTTON_DOWN)) // if object pressed
	if (m_event_type == GLI_PRESSED) // if object pressed
	{
		//glColor4f(m_pr, m_pg, m_pb, m_pa);

		temp_vert = m_vert_p;
		temp_norm = m_norm_p;
		temp_tex = m_textur_p;
		temp_tr = m_triangles_p;

		temp_vert_total = m_vert_total_p;
		temp_norm_total = m_norm_total_p;
		temp_tex_total = m_textur_total_p;
		temp_tr_total = m_triangle_total_p;
			
		temp_tr_type = m_tr_type_p;
	}
	else
	{
		//glColor4f(m_r, m_g, m_b, m_a);

		temp_vert = m_vert_n;
		temp_norm = m_norm_n;
		temp_tex = m_textur_n;
		temp_tr = m_triangles_n;

		temp_vert_total = m_vert_total_n;
		temp_norm_total = m_norm_total_n;
		temp_tex_total = m_textur_total_n;
		temp_tr_total = m_triangle_total_n;

		temp_tr_type = m_tr_type_n;

	}
	
	if (temp_tr_type == GLI_VERTEX) components = 1;
	else if (temp_tr_type == GLI_VERTEX_NORMAL_TEXTURE) components = 3;
	else components = 2;


	temp = temp_tr;

	glBegin(GL_TRIANGLES);
	for (GLuint i=0; i<temp_tr_total; i++)
	{
		for (int j=0; j<3; j++)
		{
			glVertex3f(temp_vert[(*temp)*3], temp_vert[(*temp)*3+1], temp_vert[(*temp)*3+2]); temp++;
			glNormal3f(temp_norm[(*temp)*3], temp_norm[(*temp)*3+1], temp_norm[(*temp)*3+2]); temp++;
		}
	}
	
	glEnd();
}


//==///////////////////////////////////////////////////////////////////////////////==
//                           CGLI_Button2D class
//==///////////////////////////////////////////////////////////////////////////////==

CGLI_Button2D::CGLI_Button2D()
{
	// Set default demensions and border
	SetDimensions(5, 5, 1);
	SetBorderSize(0.5);

	// Set default color
	m_r = 0.7f;
	m_g = 0.7f;
	m_b = 0.7f;
	m_a = 1;

	// Set default border (on the sun)
	m_br = 1;
	m_bg = 1;
	m_bb = 1;
	m_ba = 1;

	// Set default shadow border color
	m_sr = 0.4f;
	m_sg = 0.4f;
	m_sb = 0.4f;
	m_sa = 1.0f;

}

CGLI_Button2D::~CGLI_Button2D()
{

}

void CGLI_Button2D::SetBorderSize(GLfloat border)
{
	m_border = border;
}

void CGLI_Button2D::SetBorderColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	m_br = r;
	m_bg = g;
	m_bb = b;
	m_ba = a;
}

void CGLI_Button2D::SetShadowBorderColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	m_sr = r;
	m_sg = g;
	m_sb = b;
	m_sa = a;
}

void CGLI_Button2D::Draw()
{
	GLboolean temp;
	
	// Draw button
	if (m_event_type == GLI_PRESSED) // if object has message
	{
		// Draw pressed button
		glBegin(GL_QUADS);

		glColor4f(m_r, m_g, m_b, m_a);
		glVertex3f(-m_width/2+m_border, -m_height/2+m_border, 0.1f);
		glVertex3f(m_width/2-m_border, -m_height/2+m_border, 0.1f);
		glVertex3f(m_width/2-m_border, m_height/2-m_border, 0.1f);
		glVertex3f(-m_width/2+m_border, m_height/2-m_border, 0.1f);

		glColor4f(m_br, m_bg, m_bb, m_ba);
		glVertex3f(-m_width/2, -m_height/2, 0);
		glVertex3f(m_width/2, -m_height/2, 0);
		glVertex3f(m_width/2-m_border, -m_height/2+m_border, 0.1f);
		glVertex3f(-m_width/2+m_border, -m_height/2+m_border, 0.1f);

		glColor4f(m_br, m_bg, m_bb, m_ba);
		glVertex3f(m_width/2, -m_height/2, 0);
		glVertex3f(m_width/2, m_height/2, 0);
		glVertex3f(m_width/2-m_border, m_height/2-m_border, 0.1f);
		glVertex3f(m_width/2-m_border, -m_height/2+m_border, 0.1f);

		glColor4f(m_sr, m_sg, m_sb, m_sa);
		glVertex3f(-m_width/2, -m_height/2, 0);
		glVertex3f(m_width/2, -m_height/2, 0);
		glVertex3f(m_width/2, m_height/2, 0);
		glVertex3f(-m_width/2, m_height/2, 0);

		glEnd();
	}
	else
	{
		// Draw unpressed button
		glBegin(GL_QUADS);

		if (m_event_type == GLI_ONOVER)	glColor4f(m_mor, m_mog, m_mob, m_moa);
		else glColor4f(m_r, m_g, m_b, m_a);
		glVertex3f(-m_width/2+m_border, -m_height/2+m_border, 0.1f);
		glVertex3f(m_width/2-m_border, -m_height/2+m_border, 0.1f);
		glVertex3f(m_width/2-m_border, m_height/2-m_border, 0.1f);
		glVertex3f(-m_width/2+m_border, m_height/2-m_border, 0.1f);

		glColor4f(m_sr, m_sg, m_sb, m_sa);
		glVertex3f(-m_width/2, -m_height/2, 0);
		glVertex3f(m_width/2, -m_height/2, 0);
		glVertex3f(m_width/2-m_border, -m_height/2+m_border, 0.1f);
		glVertex3f(-m_width/2+m_border, -m_height/2+m_border, 0.1f);

		glColor4f(m_sr, m_sg, m_sb, m_sa);
		glVertex3f(m_width/2, -m_height/2, 0);
		glVertex3f(m_width/2, m_height/2, 0);
		glVertex3f(m_width/2-m_border, m_height/2-m_border, 0.1f);
		glVertex3f(m_width/2-m_border, -m_height/2+m_border, 0.1f);

		glColor4f(m_br, m_bg, m_bb, m_ba);
		glVertex3f(-m_width/2, -m_height/2, 0);
		glVertex3f(m_width/2, -m_height/2, 0);
		glVertex3f(m_width/2, m_height/2, 0);
		glVertex3f(-m_width/2, m_height/2, 0);
		
		glEnd();
	}

	// Draw button text
	glPushMatrix();
	
	// Color of text
	glColor4f(m_tr, m_tg, m_tb, m_ta);
//	if ((m_active_msg) && (m_mouse_state == GLI_MOUSE_BUTTON_DOWN)) // if object pressed
	if (m_event_type == GLI_PRESSED) // if object pressed
		glTranslatef(m_border, -m_border, 0.15f); // Shift the text
	else
		glTranslatef(0, 0, 0.15f);
	
	if (m_text_height == 0) glScalef(m_height/2, m_height/2, 1);
	else glScalef(m_text_height, m_text_height, 1);
	
	// Save old centering and set text centering
	temp = m_pVectorFont->glfGetStringCentering();
	m_pVectorFont->glfStringCentering(GL_TRUE);
	m_pVectorFont->glfDrawSolidString(m_text);
	m_pVectorFont->glfStringCentering(temp);
	glPopMatrix();
}

//==///////////////////////////////////////////////////////////////////////////////==
//                           CGLI_ButtonTexture class
//==///////////////////////////////////////////////////////////////////////////////==

CGLI_ButtonTexture::CGLI_ButtonTexture()
{
	m_normal = 0;
	m_pressed = 0;
	m_onover = 0;
	
	// Set standard texture coordinates (template)
	for (int i=0; i<8; i++) m_standard_coord[i] = 0;
	m_standard_coord[2] = 1;
	m_standard_coord[4] = 1;
	m_standard_coord[5] = 1;
	m_standard_coord[7] = 1;
	
	// Set texture coordinates for normal, pressed, onover textures
	SetCoord(m_standard_coord, m_standard_coord, m_standard_coord);

	m_but_shift = GL_FALSE;
}

CGLI_ButtonTexture::~CGLI_ButtonTexture()
{

}

void CGLI_ButtonTexture::SetTexture(GLuint normal, GLuint pressed, GLuint onover)
{
	m_normal = normal;
	m_pressed = pressed;
	m_onover = onover;
}

void CGLI_ButtonTexture::SetNormalTexture(GLuint texture_number)
{
	m_normal = texture_number;
}

void CGLI_ButtonTexture::SetPressedTexture(GLuint texture_number)
{
	m_pressed = texture_number;
}

void CGLI_ButtonTexture::SetOnOverTexture(GLuint texture_number)
{
	m_onover = texture_number;
}

void CGLI_ButtonTexture::SetCoord(GLfloat *normal, GLfloat *pressed, GLfloat *onover)
{
	m_normal_coord = normal;
	m_pressed_coord = pressed;
	m_onover_coord = onover;
}

void CGLI_ButtonTexture::SetNormalCoord(GLfloat *coord)
{
	m_normal_coord = coord;
}

void CGLI_ButtonTexture::SetPressedCoord(GLfloat *coord)
{
	m_pressed_coord = coord;
}

void CGLI_ButtonTexture::SetOnOverCoord(GLfloat *coord)
{
	m_onover_coord = coord;
}

// Shift button in space (if needed)
void CGLI_ButtonTexture::SetButtonShift(GLfloat x, GLfloat y, GLfloat z)
{
	m_but_shift = GL_TRUE;
	m_but_shift_x = x;
	m_but_shift_y = y;
	m_but_shift_z = z;
}


void CGLI_ButtonTexture::Draw()
{	
	GLfloat *text_coord;

	text_coord = m_normal_coord;
	// Choose texture, depending of button state
	if (m_event_type == GLI_PRESSED)
	{
		if (m_pressed > 0)
		{
			glBindTexture(GL_TEXTURE_2D, m_pressed);
			text_coord = m_pressed_coord;
		}
	}
	else
		if (m_event_type == GLI_ONOVER)
		{
			if (m_onover > 0)
			{
				glBindTexture(GL_TEXTURE_2D, m_onover);
				text_coord = m_onover_coord;
			}
		}
		else { if (m_normal > 0) glBindTexture(GL_TEXTURE_2D, m_normal); }

	if ((m_but_shift == GL_TRUE) && (m_event_type == GLI_PRESSED))
	{
		glPushMatrix();
		glTranslatef(m_but_shift_x, m_but_shift_y, m_but_shift_z);
	}

	glColor4f(m_r, m_g, m_b, m_a);

	// Draw button
	glBegin(GL_QUADS);
	
	glTexCoord2f(text_coord[0], text_coord[1]);
	glVertex3f(-m_width/2, -m_height/2, 0);
	
	glTexCoord2f(text_coord[2], text_coord[3]);
	glVertex3f(m_width/2, -m_height/2, 0);
	
	glTexCoord2f(text_coord[4], text_coord[5]);
	glVertex3f(m_width/2, m_height/2, 0);
	
	glTexCoord2f(text_coord[6], text_coord[7]);
	glVertex3f(-m_width/2, m_height/2, 0);
	
	glEnd();

	if ((m_but_shift == GL_TRUE) && (m_event_type == GLI_PRESSED)) glPopMatrix();

}

//==///////////////////////////////////////////////////////////////////////////////==
//                           CGLI_CheckBox2D class
//==///////////////////////////////////////////////////////////////////////////////==

CGLI_CheckBox2D::CGLI_CheckBox2D()
{
	m_checked = GL_FALSE;
	m_cr = 1;
	m_cg = 1;
	m_cb = 1;
	m_ca = 1;
	SetType(GLI_CHECKBOX_COLOR);
}

CGLI_CheckBox2D::~CGLI_CheckBox2D()
{

}

void CGLI_CheckBox2D::SetCheckedColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	m_cr = r;
	m_cg = g;
	m_cb = b;
	m_ca = a;
}

GLboolean CGLI_CheckBox2D::isChecked()
{
	return m_checked;
}

void CGLI_CheckBox2D::SetType(GLuint type)
{
	m_checkbox_type = type;
}


void CGLI_CheckBox2D::Draw()
{
	GLboolean temp;
	
	if (m_checked)
	{
		glColor4f(m_cr, m_cg, m_cb, m_ca);
		if (m_checkbox_type == GLI_CHECKBOX_CROSS)
		{
			glPushAttrib(GL_LINE_BIT);
			glLineWidth(2.0f);
			glBegin(GL_LINES);
				glVertex3f(-m_width/3, -m_height/3, 0.1f);
				glVertex3f(m_width/3, m_height/3, 0.1f);
				glVertex3f(-m_width/3, m_height/3, 0.1f);
				glVertex3f(m_width/3, -m_height/3, 0.1f);
			glEnd();	
			glPopAttrib();
		} 
		else
		if (m_checkbox_type == GLI_CHECKBOX_SQUARE)
		{
			glBegin(GL_QUADS);
				glVertex3f(-m_width/4, -m_height/4, 0);
				glVertex3f(m_width/4, -m_height/4, 0);
				glVertex3f(m_width/4, m_height/4, 0);
				glVertex3f(-m_width/4, m_height/4, 0);
			glEnd();
		} 
	}

	if (m_checked && m_checkbox_type == GLI_CHECKBOX_COLOR) glColor4f(m_cr, m_cg, m_cb, m_ca);
	else glColor4f(m_r, m_g, m_b, m_a);

	glBegin(GL_QUADS);
		glVertex3f(-m_width/2, -m_height/2, 0);
		glVertex3f(m_width/2, -m_height/2, 0);
		glVertex3f(m_width/2, m_height/2, 0);
		glVertex3f(-m_width/2, m_height/2, 0);
	glEnd();

	glColor4f(m_br, m_bg, m_bb, m_ba);
	glBegin(GL_LINE_LOOP);
		glVertex3f(-m_width/2, -m_height/2, 0.1f);
		glVertex3f(m_width/2, -m_height/2, 0.1f);
		glVertex3f(m_width/2, m_height/2, 0.1f);
		glVertex3f(-m_width/2, m_height/2, 0.1f);
	glEnd();

	// Draw text
	glPushMatrix();
	
	// Color of text
	glColor4f(m_tr, m_tg, m_tb, m_ta);
	glTranslatef(m_width+m_width/2, 0, 0);
	
	if (m_text_height == 0) glScalef(m_height/2, m_height/2, 1);
	else glScalef(m_text_height, m_text_height, 1);
	
	// Save old centering and set text centering
	temp = m_pVectorFont->glfGetStringCentering();
	m_pVectorFont->glfStringCentering(GL_FALSE);
	m_pVectorFont->glfDrawSolidString(m_text);
	m_pVectorFont->glfStringCentering(temp);
	
	glPopMatrix();
}

void CGLI_CheckBox2D::ProcessInternalCallBack(GLuint obj_id)
{
	if (m_event_type == GLI_CLICKED)
	{
		m_checked = !m_checked;
	}
}

//==///////////////////////////////////////////////////////////////////////////////==
//                           CGLI_CheckBoxTexture class
//==///////////////////////////////////////////////////////////////////////////////==

CGLI_CheckBoxTexture::CGLI_CheckBoxTexture()
{
	m_checked = GL_FALSE;
}

CGLI_CheckBoxTexture::~CGLI_CheckBoxTexture()
{

}

GLboolean CGLI_CheckBoxTexture::isChecked()
{
	return m_checked;
}


void CGLI_CheckBoxTexture::Draw()
{
	GLfloat *text_coord;
	GLboolean temp;

	text_coord = m_normal_coord;
	
	// Choose texture, depending of button state
	if (m_checked == GL_TRUE)
	{
		if (m_pressed > 0)
		{
			glBindTexture(GL_TEXTURE_2D, m_pressed);
			text_coord = m_pressed_coord;
		}
	} else { if (m_normal > 0) glBindTexture(GL_TEXTURE_2D, m_normal); }

	if (m_event_type == GLI_ONOVER)
	{
		if (m_onover > 0)
		{
			glBindTexture(GL_TEXTURE_2D, m_onover);
			text_coord = m_onover_coord;
		}
	}

	glColor4f(m_r, m_g, m_b, m_a);

	// Draw box
	glBegin(GL_QUADS);
	
	glTexCoord2f(text_coord[0], text_coord[1]);
	glVertex3f(-m_width/2, -m_height/2, 0);
	
	glTexCoord2f(text_coord[2], text_coord[3]);
	glVertex3f(m_width/2, -m_height/2, 0);
	
	glTexCoord2f(text_coord[4], text_coord[5]);
	glVertex3f(m_width/2, m_height/2, 0);
	
	glTexCoord2f(text_coord[6], text_coord[7]);
	glVertex3f(-m_width/2, m_height/2, 0);
	
	glEnd();


	// Draw text
	glPushMatrix();
	
	// Color of text
	glColor4f(m_tr, m_tg, m_tb, m_ta);
	glTranslatef(m_width/2+m_width/4, -m_height/2, 0);
	
	if (m_text_height == 0) glScalef(m_height, m_height, 1);
	else glScalef(m_text_height, m_text_height, 1);
	
	// Save old centering and set text centering
	temp = m_pBitmapFont->glfGetStringCentering();
	m_pBitmapFont->glfStringCentering(GL_FALSE);
	m_pBitmapFont->glfStartBitmapDrawing();
	m_pBitmapFont->glfDrawBString(m_text);
	m_pBitmapFont->glfStopBitmapDrawing();
	m_pBitmapFont->glfStringCentering(temp);
	
	glPopMatrix();

}

void CGLI_CheckBoxTexture::ProcessInternalCallBack(GLuint obj_id)
{
	if (m_event_type == GLI_CLICKED) m_checked = !m_checked;
}
