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
#include "gli_window.h"
#include "gli_button.h"
#include "string"


//==///////////////////////////////////////////////////////////////////////////////==
//                           CGLI_Window2D class
//==///////////////////////////////////////////////////////////////////////////////==


// Constructor
CGLI_Window2D::CGLI_Window2D()
{
    SetDimensions(10, 10, 1);
    SetWindowColor(0.5f, 0.5f, 0.5f, 1);
    SetCaptionColor(0.6f, 0.6f, 0.6f, 1);
    SetCaptionTextColor(1.0f, 1.0f, 1.0f, 1);
    SetCaptionHeight(1);

    SetObjectName("Window");
    //m_button_minimize.SetObjectName("Minimize Button");
    //m_button_close.SetObjectName("Close Button");
    //AddObject(&m_button_minimize);
    //AddObject(&m_button_close);

    //m_button_minimize.SetButtonText("_");
    //m_button_minimize.SetTextColor(0, 0, 1, 1);
    //m_button_close.SetButtonText("x");
    //m_button_close.SetTextColor(0, 0, 1, 1);
    //m_button_minimize_id = m_button_minimize.GetID();
    //m_button_close_id = m_button_close.GetID();

    m_win_type = GLI_WINDOW_FILLED;
    SetCaptionText("");
    m_font_type = GLI_FONT_VECTOR;
    m_in_minimization = GL_FALSE;
}

// Destructor
CGLI_Window2D::~CGLI_Window2D()
{
    if (m_caption_text)
        delete[]m_caption_text;
}


void CGLI_Window2D::SetWindowColor(GLfloat r, GLfloat g, GLfloat b,
                                   GLfloat a)
{
    m_win_r = r;
    m_win_g = g;
    m_win_b = b;
    m_win_a = a;

    UpdateObject();
}

void CGLI_Window2D::SetCaptionColor(GLfloat r, GLfloat g, GLfloat b,
                                    GLfloat a)
{
    m_cap_r = r;
    m_cap_g = g;
    m_cap_b = b;
    m_cap_a = a;

    UpdateObject();
}

void CGLI_Window2D::SetCaptionHeight(GLfloat height)
{
    m_cap_height = height;

    UpdateObject();
}



void CGLI_Window2D::SetCaptionText(char *text)
{
    m_caption_text = new char[strlen(text) + 1];
    strcpy(m_caption_text, text);
}

void CGLI_Window2D::SetCaptionTextColor(GLfloat r, GLfloat g, GLfloat b,
                                        GLfloat a)
{
    m_cap_tr = r;
    m_cap_tg = g;
    m_cap_tb = b;
    m_cap_ta = a;

    UpdateObject();
}


void CGLI_Window2D::SetWindowType(GLuint win_type)
{
    m_win_type = win_type;
}

void CGLI_Window2D::SetFontType(GLuint font_type)
{
    if ((font_type == GLI_FONT_VECTOR) || (font_type == GLI_FONT_BITMAP))
        m_font_type = font_type;
}

void CGLI_Window2D::Draw()
{
    GLboolean temp;
    GLboolean texture2d;

    glGetBooleanv(GL_TEXTURE_2D, &texture2d);

    if (texture2d == GL_TRUE)
        glDisable(GL_TEXTURE_2D);

    // Draw frame
    CGLI_Frame::Draw();

    // Draw window

    // Draw main window
    glColor4f(m_win_r, m_win_g, m_win_b, m_win_a);
    if (m_win_type == GLI_WINDOW_FILLED)
        glBegin(GL_QUADS);
    else
        glBegin(GL_LINE_LOOP);
    glVertex3f(-m_width / 2, -m_height / 2, 0);
    glVertex3f(m_width / 2, -m_height / 2, 0);
    glVertex3f(m_width / 2, m_height / 2 - m_cap_height, 0);
    glVertex3f(-m_width / 2, m_height / 2 - m_cap_height, 0);
    glEnd();

    // Draw caption text
    glPushMatrix();

    // Color of text
    glColor4f(m_cap_tr, m_cap_tg, m_cap_tb, m_cap_ta);

    if (m_font_type == GLI_FONT_VECTOR) {
        glTranslatef(0, m_height / 2 - m_cap_height / 2, 0.15f);
        glScalef(m_cap_height / 2, m_cap_height / 2, 1);
        // Save old centering and set text centering
        temp = m_pVectorFont->glfGetStringCentering();
        m_pVectorFont->glfStringCentering(GL_TRUE);
        m_pVectorFont->glfDrawSolidString(m_caption_text);
        m_pVectorFont->glfStringCentering(temp);
    } else {
        temp = m_pBitmapFont->glfGetStringCentering();
        m_pBitmapFont->glfStringCentering(GL_TRUE);
        glTranslatef(0, m_height / 2 - m_cap_height, -0.1f);
        glScalef(m_cap_height, m_cap_height, 1);
        m_pBitmapFont->glfStartBitmapDrawing();
        m_pBitmapFont->glfDrawBString(m_caption_text);
        m_pBitmapFont->glfStopBitmapDrawing();
        m_pBitmapFont->glfStringCentering(temp);

    }
    glPopMatrix();

    // Draw caption
    glColor4f(m_cap_r, m_cap_g, m_cap_b, m_cap_a);
    glBegin(GL_QUADS);
    glVertex3f(-m_width / 2, m_height / 2 - m_cap_height, 0);
    glVertex3f(m_width / 2, m_height / 2 - m_cap_height, 0);
    glVertex3f(m_width / 2, m_height / 2, 0);
    glVertex3f(-m_width / 2, m_height / 2, 0);
    glEnd();

    if (texture2d == GL_TRUE)
        glEnable(GL_TEXTURE_2D);


}

// This method should update all sub objects in object
// Must be called, when some info is sended to object
void CGLI_Window2D::UpdateObject()
{
    // Set buttons parameters
    //m_button_minimize.SetDimensions(m_cap_height*0.8f, m_cap_height*0.8f, 1);
    //m_button_minimize.SetBorderSize(m_cap_height/16);
    //m_button_minimize.SetPosition(-m_width/2+m_cap_height*0.5f, m_height/2-m_cap_height/2, 0.1f);

    //m_button_close.SetDimensions(m_cap_height*0.8f, m_cap_height*0.8f, 1);
    //m_button_close.SetBorderSize(m_cap_height/16);
    //m_button_close.SetPosition(m_width/2-m_cap_height*0.5f, m_height/2-m_cap_height/2, 0.1f);
}

void CGLI_Window2D::DoAnimationTick()
{
    if (m_in_minimization) {
        m_scaling_factor -= 0.05f;
        if (m_scaling_factor < 0) {
            m_scaling_factor = 0;
            m_in_minimization = GL_FALSE;
        }
    }
}

void CGLI_Window2D::DoMinimize()
{
    m_in_minimization = GL_TRUE;
}

void CGLI_Window2D::ProcessInternalCallBack(GLuint obj_id)
{

    //if (obj_id == m_button_minimize_id) 
    //{
    //printf("Minimize button is pressed!\n");
    //}
    //if (obj_id == m_button_close_id)
    //{
    //printf("Close button is pressed!\n");
    //}
}
