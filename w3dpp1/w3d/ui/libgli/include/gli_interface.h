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
#ifndef __GLI_INTERFACE_H__
#define __GLI_INTERFACE_H__

#include "gli_object.h"
#include "gli_glf.h"
#include "gli_texture.h"


//==///////////////////////////////////////////////////////////////////////////////==
//                           CGLI_Interface class
//==///////////////////////////////////////////////////////////////////////////////==

// Main interface
class CGLI_Interface
{
public:
	CGLI_Interface();
	virtual ~CGLI_Interface();
	
	void AddObject(CGLI_Object *object); // Add new object to the interface

	void Draw(); // Draw all objects in the interface

	void SetAllMatrixes(); // Sets current projection matrix for Interface
	void SendMouseParameters(GLuint type, int button, int state, int x, int y);
	void SendKeyEvent(unsigned char key, int x, int y);

	// Work with fonts
	int LoadVectorFont(char *lpszName);
	int LoadBitmapFont(char *lpszName);

	// Work with textures
	int LoadTextureFromFile(char *lpszName);
//	int LoadTextureFromMemory(GLubyte *data, GLuint width, GLuint height, GLuint components);
	void DeleteAllTextures();

	void DoAnimationTick();

protected:

	void DrawByMode(GLint mode); // Draw all objects in the interface (in selected mode)

	CGLI_Object *m_pObjects; // Objects, that contain this interface
	CGLI_VectorFont m_vfonts; // Vector fonts
	CGLI_BitmapFont m_bfonts; // Bitmap fonts

	CGLI_TextureLoader m_texture_loader; // Texture loader object
	CGLI_Texture *m_pTextures; // All textures list
	
	GLfloat m_ModelView_Matrix[16]; // Copy of modelview matrix
	GLfloat m_Projection_Matrix[16]; // Copy of projection matrix
	
	GLboolean m_set_matrix_flag;

};

#endif

