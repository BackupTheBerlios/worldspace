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

#ifdef MACOSX
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include "gli_object.h"
#include "gli_interface.h"
#include "gli_standard_font.h"


//==///////////////////////////////////////////////////////////////////////////////==
//                           CGLI_Interface class
//==///////////////////////////////////////////////////////////////////////////////==

CGLI_Interface::CGLI_Interface() /* {{{ */
{
	m_pObjects = NULL;
	m_pTextures = NULL;
	m_set_matrix_flag = GL_FALSE;

	m_vfonts.glfLoadFontFromMemory(gli_arial1_font);
} /* }}} */

CGLI_Interface::~CGLI_Interface() /* {{{ */
{
	DeleteAllTextures();
} /* }}} */

void CGLI_Interface::AddObject(CGLI_Object *object) /* {{{ */
{
	// Add object to the head of list
	object->m_pNext = m_pObjects;
	m_pObjects = object;
	m_pObjects->SetVectorFontObject(&m_vfonts);
	m_pObjects->SetBitmapFontObject(&m_bfonts);
	m_pObjects->CGLI_Object::UpdateObject();
} /* }}} */

void CGLI_Interface::Draw() /* {{{ */
{	
	m_set_matrix_flag = GL_TRUE;
	glGetFloatv(GL_PROJECTION_MATRIX, (GLfloat *)m_Projection_Matrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat *)m_ModelView_Matrix); // Get current modelview matrix
	
	DrawByMode(GL_RENDER);
} /* }}} */

void CGLI_Interface::DrawByMode(GLint mode) /* {{{ */
{
	CGLI_Object *cur;
//	GLuint id;

	cur = m_pObjects;
	if (mode == GL_RENDER)
	{
		while (cur)
		{
			cur->CGLI_Object::Draw();
			cur = cur->m_pNext;
		}
	}
	else
	{
		// Init names of objects
		glInitNames();
		glPushName(0);
		while (cur)
		{
//			id = cur->GetID();
//			glLoadName(id);
			cur->DrawSelection();
			cur = cur->m_pNext;
		}
	}
} /* }}} */

void CGLI_Interface::SendMouseParameters(GLuint type, int button, int state, int x, int y) /* {{{ */
{
	GLuint selectBuff[64];
	GLint hits, viewport[4];
	GLboolean Lighting;
	GLuint obj_id;

	if (m_set_matrix_flag == GL_FALSE)
		glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat *)m_ModelView_Matrix); // Get current modelview matrix

	// Select buffer parameters
	glSelectBuffer(64, selectBuff);
	glGetIntegerv(GL_VIEWPORT, viewport);
	
	// Enter to selection mode
	glGetBooleanv(GL_LIGHTING, &Lighting);
	glDisable(GL_LIGHTING);
	
	glMatrixMode(GL_PROJECTION);

	if (m_set_matrix_flag == GL_FALSE)
		glGetFloatv(GL_PROJECTION_MATRIX, (GLfloat *)m_Projection_Matrix); // Get current projection matrix

	glPushMatrix();

	glRenderMode(GL_SELECT);
	glLoadIdentity();
	
	// Set-up pick matrix
	gluPickMatrix(x, y, 1, 1, viewport);
	// Multiply by projection matrix
	glMultMatrixf((GLfloat *)m_Projection_Matrix);

	// Render our all objects into selection buffer
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMultMatrixf((GLfloat *)m_ModelView_Matrix);

	DrawByMode(GL_SELECT);

	// Get hits and go back to normal rendering
	hits = glRenderMode(GL_RENDER);

	// Get first object, in selection buffer stack
	//if (hits > 0) printf("Object selected: %i\n", selectBuff[3]);
	if (hits > 0) obj_id = selectBuff[3];

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	
	if (Lighting) glEnable(GL_LIGHTING);
	
	CGLI_Object *cur;

	cur = m_pObjects;
	if (hits <= 0)
	{
		while (cur)
		{
			cur->SetMouseState(GLI_MOUSE_CLICK, -1, button, state);
			cur = cur->m_pNext;
		}	
		return;
	}

	if (type == GLI_MOUSE_MOTION_BUTTON)
	{
		while (cur)
		{
			cur->SetMouseState(GLI_MOUSE_MOTION_BUTTON, obj_id, button, state);
			cur = cur->m_pNext;
		}	
		return;
	}
	
	// Now search for object ID
	while (cur)
	{
		cur->SetMouseState(GLI_MOUSE_CLICK, obj_id, button, state);
		cur = cur->m_pNext;
	}
} /* }}} */

void CGLI_Interface::SendKeyEvent(unsigned char key, int x, int y) /* {{{ */
{
	GLuint selectBuff[64];
	GLint hits, viewport[4];
	GLboolean Lighting;
	GLuint obj_id;

	if (m_set_matrix_flag == GL_FALSE)
		glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat *)m_ModelView_Matrix); // Get current modelview matrix

	// Select buffer parameters
	glSelectBuffer(64, selectBuff);
	glGetIntegerv(GL_VIEWPORT, viewport);
	
	// Enter to selection mode
	glGetBooleanv(GL_LIGHTING, &Lighting);
	glDisable(GL_LIGHTING);
	
	glMatrixMode(GL_PROJECTION);

	if (m_set_matrix_flag == GL_FALSE)
		glGetFloatv(GL_PROJECTION_MATRIX, (GLfloat *)m_Projection_Matrix); // Get current projection matrix

	glPushMatrix();

	glRenderMode(GL_SELECT);
	glLoadIdentity();
	
	// Set-up pick matrix
	gluPickMatrix(x, y, 1, 1, viewport);
	// Multiply by projection matrix
	glMultMatrixf((GLfloat *)m_Projection_Matrix);

	// Render our all objects into selection buffer
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMultMatrixf((GLfloat *)m_ModelView_Matrix);

	DrawByMode(GL_SELECT);

	// Get hits and go back to normal rendering
	hits = glRenderMode(GL_RENDER);

	// Get first object, in selection buffer stack
	//if (hits > 0) printf("Object selected: %i\n", selectBuff[3]);
	if (hits > 0) obj_id = selectBuff[3];

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	
	if (Lighting) glEnable(GL_LIGHTING);
	
	CGLI_Object *cur;

	cur = m_pObjects;
	
	// Now search for object ID
	while (cur)
	{
		cur->HandleKeyEvent(key, obj_id);
		cur = cur->m_pNext;
	}
} /* }}} */

int CGLI_Interface::LoadVectorFont(char *lpszName) /* {{{ */
{
	return m_vfonts.glfLoadFont(lpszName);
} /* }}} */

int CGLI_Interface::LoadBitmapFont(char *lpszName) /* {{{ */
{
	return m_bfonts.glfLoadBMFFont(lpszName);
} /* }}} */

int CGLI_Interface::LoadTextureFromFile(char *lpszName) /* {{{ */
{
// Load texture to the interface from file
	GLint width, height, comps;
	CGLI_Texture *temp;
	GLubyte *image;

	// Load image from file
	image = m_texture_loader.LoadTexture(lpszName);	
	m_texture_loader.GetImageParameters(&width, &height, &comps);
	
	// Make new texture object
	temp = new CGLI_Texture;
	// Make texture from image
	temp->MakeTexture(image, width, height, comps);
	m_texture_loader.FreeMemory();

	// Add this texture object to the texture queue
	temp->m_pNext = m_pTextures;
	m_pTextures = temp;

	// Return texture number
	return temp->GetTextureNumber();
} /* }}} */

void CGLI_Interface::DeleteAllTextures() /* {{{ */
{
// Delete all textures from interface
	CGLI_Texture *temp;	
	
	while (m_pTextures)
	{
		temp = m_pTextures->m_pNext;
		delete m_pTextures;
		m_pTextures = temp;
	}
} /* }}} */

void CGLI_Interface::DoAnimationTick() /* {{{ */
{
	CGLI_Object *cur;

	// Do ticks in all objects
	cur = m_pObjects;
	while (cur)
	{
		cur->CGLI_Object::DoAnimationTick();
		cur = cur->m_pNext;
	}
} /* }}} */


