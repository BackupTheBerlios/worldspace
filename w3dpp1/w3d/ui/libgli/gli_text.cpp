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
#include <string.h>
#include <math.h>
#include "gli_text.h"

//==///////////////////////////////////////////////////////////////////////////////==
//                           CGLI_String class
//==///////////////////////////////////////////////////////////////////////////////==

CGLI_String::CGLI_String()
{
    m_string = NULL;
    m_center = GL_FALSE;
    m_font_type = GLI_FONT_VECTOR;
}

CGLI_String::~CGLI_String()
{
    if (m_string)
        delete[]m_string;
}

void CGLI_String::Draw()
{
    GLboolean temp;

    glColor4f(m_r, m_g, m_b, m_a);
    glPushMatrix();
    glScalef(m_width, m_height, m_depth);

    if (m_font_type == GLI_FONT_VECTOR) {
        temp = m_pVectorFont->glfGetStringCentering();
        m_pVectorFont->glfStringCentering(m_center);
        m_pVectorFont->glfDrawSolidString(m_string);
        m_pVectorFont->glfStringCentering(temp);
    } else {
        temp = m_pBitmapFont->glfGetStringCentering();
        m_pBitmapFont->glfStringCentering(m_center);
        m_pBitmapFont->glfStartBitmapDrawing();
        m_pBitmapFont->glfDrawBString(m_string);
        m_pBitmapFont->glfStopBitmapDrawing();
        m_pBitmapFont->glfStringCentering(temp);
    }
    glPopMatrix();
}

void CGLI_String::SetString(char *string)
{
    // First, delete old string
    if (m_string)
        delete[]m_string;
    m_string = NULL;

    // Allocate space for new string
    if (string) {
        m_string = new char[strlen(string) + 1];
        strcpy(m_string, string);
    }
}

char *CGLI_String::GetString()
{
    return m_string;
}

void CGLI_String::TranslatePosition(GLfloat some_constant)
{
    float minx, miny, maxx, maxy;

    if (m_font_type == GLI_FONT_VECTOR) {
        m_pVectorFont->glfGetStringBounds(m_string, &minx, &miny, &maxx,
                                          &maxy);
        glTranslatef(0,
                     -(((float) fabs(miny) +
                        (float) fabs(maxy)) * m_height + some_constant),
                     0);
    } else {
        glTranslatef(0,
                     -(m_pBitmapFont->glfGetMaxHeight() * m_height +
                       some_constant), 0);
    }
}

void CGLI_String::SetStringCentering(GLboolean center)
{
    m_center = center;
}


void CGLI_String::SetFontType(GLuint font_type)
{
    if ((font_type == GLI_FONT_VECTOR) || (font_type == GLI_FONT_BITMAP))
        m_font_type = font_type;
}

void CGLI_String::ProcessInternalCallBack(GLuint obj_id)
{

}

void CGLI_String::UpdateObject()
{

}

void CGLI_String::DoAnimationTick()
{

}

//==///////////////////////////////////////////////////////////////////////////////==
//                           CGLI_Text class
//==///////////////////////////////////////////////////////////////////////////////==

CGLI_Text::CGLI_Text()
{
    m_pStrings = NULL;
    m_str_space = 1.0f;
    m_font_type = GLI_FONT_VECTOR;
}

CGLI_Text::~CGLI_Text()
{
    DeleteAllStrings();
}

// Insert new string to the head of text
void CGLI_Text::InsertNewString(char *string)
{
    CGLI_String *temp;

    if (!string)
        return;

    temp = new CGLI_String();
    temp->SetString(string);

    temp->m_pNext = m_pStrings;
    m_pStrings = temp;
    temp->SetFontType(m_font_type);
    temp->SetStringCentering(m_center);
    UpdateObject();
}

// Add new string to the end of text
void CGLI_Text::AddNewString(char *string)
{
    CGLI_String *temp, *cur;

    if (!string)
        return;

    temp = new CGLI_String();
    temp->SetString(string);

    if (!m_pStrings) {
        m_pStrings = temp;
    } else {
        cur = m_pStrings;
        while (cur->m_pNext)
            cur = cur->m_pNext;
        cur->m_pNext = temp;
    }
    temp->m_pNext = NULL;
    temp->SetFontType(m_font_type);
    temp->SetStringCentering(m_center);
    UpdateObject();
}

void CGLI_Text::DeleteAllStrings()
{
    CGLI_String *cur, *temp;

    cur = m_pStrings;
    while (cur) {
        temp = cur->m_pNext;
        delete cur;
        cur = temp;
    }
    m_pStrings = NULL;
}

void CGLI_Text::SetStringSpaceLength(GLfloat space)
{
    m_str_space = space;
}

void CGLI_Text::SetTextCentering(GLboolean center)
{
    CGLI_String *cur;

    m_center = center;

    cur = m_pStrings;
    while (cur) {
        cur->SetStringCentering(m_center);
        cur = cur->m_pNext;
    }
}

void CGLI_Text::Draw()
{
    CGLI_String *cur;

    cur = m_pStrings;
    while (cur) {
        cur->Draw();
        cur->TranslatePosition(m_str_space);
        cur = cur->m_pNext;
    }
}


void CGLI_Text::SetFontType(GLuint font_type)
{
    if ((font_type == GLI_FONT_VECTOR) || (font_type == GLI_FONT_BITMAP))
        m_font_type = font_type;

    CGLI_String *cur;

    cur = m_pStrings;
    while (cur) {
        cur->SetFontType(font_type);
        cur = cur->m_pNext;
    }
}

void CGLI_Text::ProcessInternalCallBack(GLuint obj_id)
{

}

void CGLI_Text::UpdateObject()
{
    CGLI_String *cur;

    cur = m_pStrings;
    while (cur) {
        cur->SetBitmapFontObject(m_pBitmapFont);
        cur->SetVectorFontObject(m_pVectorFont);
        cur->SetDimensions(m_width, m_height, m_depth);
        cur->SetPosition(m_x, m_y, m_z);
        cur->SetColor(m_r, m_g, m_b, m_a);
        cur = cur->m_pNext;
    }
}

void CGLI_Text::DoAnimationTick()
{

}
