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
#ifndef __GLI_TEXTURE_H__
#define __GLI_TEXTURE_H__

#if defined (WIN32)
#include <windows.h>
#endif

#ifdef MACOSX
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#include "gli_texture.h"


//==///////////////////////////////////////////////////////////////////////////////==
//                           CGLI_TextureLoader class
//==///////////////////////////////////////////////////////////////////////////////==


class CGLI_TextureLoader
{
public:

	CGLI_TextureLoader();
	virtual ~CGLI_TextureLoader();

	GLubyte *LoadTexture(char *lpszName); // Load texture from file (automatic recognition of image type)
	void GetImageParameters(GLint *width, GLint *height, GLint *components);
	void FreeMemory();

protected:

	GLubyte *m_image; // Pointer to image
	GLint m_width, m_height; // Image width and height
	GLint m_comps; // Total of image components
};


//==///////////////////////////////////////////////////////////////////////////////==
//                           CGLI_Texture class
//==///////////////////////////////////////////////////////////////////////////////==

class CGLI_Texture
{

public:

	CGLI_Texture();
	virtual ~CGLI_Texture();

	// Make texture from image pointer
	GLuint MakeTexture(GLubyte *image, GLint width, GLint height, GLint components);
	GLuint GetTextureNumber();
	void DeleteTexture();
	
	CGLI_Texture *m_pNext;

protected:
	
	GLuint m_texture_number;
};

#endif

