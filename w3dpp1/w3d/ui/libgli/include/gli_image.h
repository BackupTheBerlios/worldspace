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
#ifndef __GLI_IMAGE_H__
#define __GLI_IMAGE_H__

#include "gli_object.h"

//==///////////////////////////////////////////////////////////////////////////////==
//                           CGLI_Image class
//==///////////////////////////////////////////////////////////////////////////////==

// Image class (polygon with texture)
class CGLI_Image : public CGLI_Object
{
public:

	CGLI_Image();
	virtual ~CGLI_Image();

	void SetTexture(GLuint texture); // Set all texture to button
	void SetCoord(GLfloat *coord); // Set texture coordinates

	virtual void Draw(); // Drawing method
	virtual void UpdateObject();
	virtual void DoAnimationTick();

protected:

	virtual void ProcessInternalCallBack(GLuint obj_id);

	// Texture numbers
	GLuint m_texture; // Texture number
	GLfloat m_standard_coord[8]; // Standard texture coordinates
	GLfloat *m_text_coord; // Texture coordinates
};
		

#endif

