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
#include <stdlib.h>

#ifdef MACOSX
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include "gli_texture.h"
#include "gli_texture_rgb.h"
#include "gli_texture_tga.h"

//==///////////////////////////////////////////////////////////////////////////////==
//                           CGLI_TextureLoader class
//==///////////////////////////////////////////////////////////////////////////////==

// Constructor
CGLI_TextureLoader::CGLI_TextureLoader()
{
    m_image = NULL;
}

// Destructor
CGLI_TextureLoader::~CGLI_TextureLoader()
{
    FreeMemory();
}

// Load image from file
GLubyte *CGLI_TextureLoader::LoadTexture(char *lpszName)
{
    GLubyte Magic[2];
    int magic_int;

    // First we find, what type is image
    FILE *f;
    if (!(f = fopen(lpszName, "rb"))) {
        // Error in opening file
        fclose(f);
        return NULL;
    }
    // Read magic from file
    if (fread(Magic, 1, 2, f) != 2) {
        // Error in file
        fclose(f);
        return NULL;
    }
    fclose(f);

    magic_int = (int) Magic[0] * 256 + Magic[1];

    if (magic_int == 474)
        m_image =
            read_texture_rgb(lpszName, &m_width, &m_height, &m_comps);
    else
        m_image =
            read_texture_tga(lpszName, &m_width, &m_height, &m_comps);

    return m_image;
}

// Get image parameters
void CGLI_TextureLoader::GetImageParameters(GLint * width, GLint * height,
                                            GLint * components)
{
    *width = m_width;
    *height = m_height;
    *components = m_comps;
}

// Free memory
void CGLI_TextureLoader::FreeMemory()
{
    if (m_image)
        free(m_image);
    m_image = NULL;
}


//==///////////////////////////////////////////////////////////////////////////////==
//                           CGLI_Texture class
//==///////////////////////////////////////////////////////////////////////////////==
CGLI_Texture::CGLI_Texture()
{
    m_texture_number = 0;
}

CGLI_Texture::~CGLI_Texture()
{
    DeleteTexture();
}

// Make texture from image pointer
GLuint CGLI_Texture::MakeTexture(GLubyte * image, GLint width,
                                 GLint height, GLint components)
{
    GLenum type = GL_RGBA;

    if (!image)
        return 0;               // Image is not present

    glGenTextures(1, &m_texture_number);
    glBindTexture(GL_TEXTURE_2D, m_texture_number);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    if (components == 3)
        type = GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, type,
                 GL_UNSIGNED_BYTE, image);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return m_texture_number;
}

void CGLI_Texture::DeleteTexture()
{
    if (m_texture_number > 0)
        glDeleteTextures(1, &m_texture_number);
}

GLuint CGLI_Texture::GetTextureNumber()
{
    return m_texture_number;
}
