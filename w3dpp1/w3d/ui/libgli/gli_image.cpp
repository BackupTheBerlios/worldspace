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
#include "gli_image.h"

//==///////////////////////////////////////////////////////////////////////////////==
//                           CGLI_Image class
//==///////////////////////////////////////////////////////////////////////////////==

CGLI_Image::CGLI_Image()
{
    m_texture = 0;

    // Set standard texture coordinates ((0, 0) (1, 0) (1, 1) (0, 1))
    for (int i = 0; i < 8; i++)
        m_standard_coord[i] = 0;
    m_standard_coord[2] = 1;
    m_standard_coord[4] = 1;
    m_standard_coord[5] = 1;
    m_standard_coord[7] = 1;

    // Set texture coordinates for normal, pressed, onover textures
    SetCoord(m_standard_coord);
}

CGLI_Image::~CGLI_Image()
{

}

// Set all texture to button
void CGLI_Image::SetTexture(GLuint texture)
{
    m_texture = texture;
}

// Set texture coordinates
void CGLI_Image::SetCoord(GLfloat * coord)
{
    m_text_coord = coord;
}

void CGLI_Image::Draw()
{
    if (m_texture > 0) {
        glBindTexture(GL_TEXTURE_2D, m_texture);

        glColor4f(m_r, m_g, m_b, m_a);

        // Draw image
        glBegin(GL_QUADS);

        glTexCoord2f(m_text_coord[0], m_text_coord[1]);
        glVertex3f(-m_width / 2, -m_height / 2, 0);

        glTexCoord2f(m_text_coord[2], m_text_coord[3]);
        glVertex3f(m_width / 2, -m_height / 2, 0);

        glTexCoord2f(m_text_coord[4], m_text_coord[5]);
        glVertex3f(m_width / 2, m_height / 2, 0);

        glTexCoord2f(m_text_coord[6], m_text_coord[7]);
        glVertex3f(-m_width / 2, m_height / 2, 0);

        glEnd();
    }
}

void CGLI_Image::UpdateObject()
{

}

void CGLI_Image::DoAnimationTick()
{

}

void CGLI_Image::ProcessInternalCallBack(GLuint obj_id)
{

}
