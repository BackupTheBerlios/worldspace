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
#include "gli_object.h"


// Static members initialization
GLuint CGLI_Object::m_ID_Counter = 1;


//==///////////////////////////////////////////////////////////////////////////////==
//                           CGLI_Object class
//==///////////////////////////////////////////////////////////////////////////////==

CGLI_Object::CGLI_Object() /* {{{ */
{
	// Calculate ID of object
	m_ID = m_ID_Counter;
	m_ID_Counter++;

	m_is_visible = GL_TRUE; // By default this object is visible
	m_x = 0;
	m_y = 0;
	m_z = 0;

	m_width = 3;
	m_height = 1;
	m_depth = 1;

	m_rot_x = 0.0f;
	m_rot_y = 0.0f;
	m_rot_z = 0.0f;

	m_r = 1;
	m_g = 1;
	m_b = 1;
	m_a = 1;

	m_event_type = GLI_NONE;
	m_event_type_prev = GLI_NONE;
	m_pVectorFont = NULL;

	m_tr = 1;
	m_tg = 0;
	m_tb = 0;
	m_ta = 1;
	m_funct = NULL;

	m_pObjects = NULL;
	m_name = NULL;

	m_callback_event_type = 65535; // By default all events are 

	m_scaling_factor = 1.0f;
} /* }}} */

CGLI_Object::~CGLI_Object() /* {{{ */
{
//	DeleteAllObjects(); // You really need this?????? Check later
	if (m_name) delete [] m_name;
} /* }}} */

// Get object ID
GLuint CGLI_Object::GetID() /* {{{ */
{

	return m_ID;
} /* }}} */

// Set object name
void CGLI_Object::SetObjectName(char *name) /* {{{ */
{
	if (m_name) delete [] m_name;
	m_name = NULL;

	if (strlen(name) > 0)
	{
		m_name = new char [strlen(name)+1];
		strcpy(m_name, name);
	}
} /* }}} */

// Returns name of current object
char *CGLI_Object::GetObjectName() /* {{{ */
{
	return m_name;
} /* }}} */

// Set position of object (in world space)
void CGLI_Object::SetPosition(GLfloat x, GLfloat y, GLfloat z) /* {{{ */
{
	m_x = x;
	m_y = y;
	m_z = z;

	UpdateObject();
} /* }}} */

// Set rotation of object
void CGLI_Object::SetRotation(GLfloat x, GLfloat y, GLfloat z) /* {{{ */
{
	m_rot_x = x;
	m_rot_y = y;
	m_rot_z = z;

	UpdateObject();
} /* }}} */

// Dimenstions of object
void CGLI_Object::SetDimensions(GLfloat width, GLfloat height, GLfloat depth) /* {{{ */
{
	m_width = width;
	m_height = height;
	m_depth = depth;

	UpdateObject();
} /* }}} */

// Scaling factor (scaling value)
void CGLI_Object::SetScalingFactor(GLfloat scaling_factor) /* {{{ */
{
	m_scaling_factor = scaling_factor;
} /* }}} */

// Set mouse state for object (by default it called automatically from Interface)
GLuint CGLI_Object::SetMouseState(GLuint type, GLuint id, int button, int state) /* {{{ */
{
	GLuint object_ID=0;

	m_prev_mouse_button = m_mouse_button;
	m_prev_mouse_state = m_mouse_state;
	
	m_mouse_button = button;
	m_mouse_state = state;

	// Else search for this ID in attached objects
	CGLI_Object *temp;

	temp = m_pObjects;
	while (temp)
	{
		object_ID = temp->SetMouseState(type, id, button, state);
		temp = temp->m_pNext;
	}

	m_event_type_prev = m_event_type;
	if (type == GLI_MOUSE_MOTION_BUTTON)
	{
		if (!((m_event_type == GLI_PRESSED) && (id == m_ID))) m_event_type = GLI_NONE;
		return m_ID;
	}
	else m_event_type = GLI_NONE;

	if (id == m_ID)
	{
				if (m_mouse_state == GLI_MOUSE_BUTTON_DOWN) m_event_type = GLI_PRESSED;
				else
				if (m_mouse_state == GLI_MOUSE_BUTTON_NONE) m_event_type = GLI_ONOVER;
				else
				{
					if (m_mouse_state == GLI_MOUSE_BUTTON_UP)
					{	
						if (m_event_type_prev == GLI_PRESSED) m_event_type = GLI_CLICKED;
						else m_event_type = GLI_RELEASED;
					}
				}
				
				if ((m_funct_event) && (m_callback_event_type == m_event_type))
				{
					(*m_funct_event)(m_ID);
				}
		
		// Call callback function (if present)
		if ((m_funct) && (m_event_type != GLI_NONE))
		{
			(*m_funct)(m_ID, m_event_type);
		}
		ProcessInternalCallBack(m_ID);
		return m_ID;
	}

	ProcessInternalCallBack(object_ID);
	return 0;
} /* }}} */

// Set keyboard handler for object (by default it called automatically from Interface)
GLuint CGLI_Object::HandleKeyEvent(unsigned char key, GLuint id) /* {{{ */
{
	GLuint object_ID=0;

	CGLI_Object *temp;

	temp = m_pObjects;
	while (temp)
	{
		object_ID = temp->HandleKeyEvent(key, id);
		temp = temp->m_pNext;
	}

	if (id == m_ID)
	{
		m_event_type = GLI_KEYBOARD;
		m_key = key;
		// Call callback function (if present)
		if (m_funct)
		{
			(*m_funct)(m_ID, key);
		}
		ProcessInternalCallBack(m_ID);
		return m_ID;
	}

	ProcessInternalCallBack(object_ID);
	return 0;
} /* }}} */

// Set color of object
void CGLI_Object::SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) /* {{{ */
{
	m_r = r;
	m_g = g;
	m_b = b;
	m_a = a;

	UpdateObject();
} /* }}} */

// By default this function called automatically from Interface
void CGLI_Object::SetVectorFontObject(CGLI_VectorFont *font) /* {{{ */
{
	m_pVectorFont = font;

	// Update also all attached objects
	CGLI_Object *temp;

	temp = m_pObjects;
	while (temp)
	{
		temp->SetVectorFontObject(font);
		temp = temp->m_pNext;
	}
} /* }}} */

// By default this function called automatically from Interface
void CGLI_Object::SetBitmapFontObject(CGLI_BitmapFont *font) /* {{{ */
{
	m_pBitmapFont = font;

	// Update also all attached objects
	CGLI_Object *temp;

	temp = m_pObjects;
	while (temp)
	{
		temp->SetBitmapFontObject(font);
		temp = temp->m_pNext;
	}
} /* }}} */

// Current vector font
void CGLI_Object::SetCurrentVectorFont(GLuint font) /* {{{ */
{
	if (font >= 0) m_vec_font = font;
} /* }}} */

// Current bitmapped font
void CGLI_Object::SetCurrentBitmapFont(GLuint font) /* {{{ */
{
	if (font >= 0) m_bmf_font = font;
} /* }}} */

// Do hide this object (do not draw on the screen)
void CGLI_Object::Hide() /* {{{ */
{
	m_is_visible = GL_FALSE;
} /* }}} */

// Show this object (object now is visible, if previously was invisible)
void CGLI_Object::Show() /* {{{ */
{
	m_is_visible = GL_TRUE;
} /* }}} */

// Draw current object and all subobjects
void CGLI_Object::Draw() /* {{{ */
{
	if (m_is_visible)
	{
		glPushMatrix();
		glTranslatef(m_x, m_y, m_z);
		glRotatef(m_rot_x, 1, 0, 0);
		glRotatef(m_rot_y, 0, 1, 0);
		glRotatef(m_rot_z, 0, 0, 1);
		if (m_scaling_factor != 1.0f)
			glScalef(m_scaling_factor, m_scaling_factor, m_scaling_factor);
	
		// Draw all attached objects
		CGLI_Object *temp;

		temp = m_pObjects;
		while (temp)
		{
			temp->CGLI_Object::Draw();
			temp = temp->m_pNext;
		}
		Draw();
		glPopMatrix();
	}
} /* }}} */

// Draw this objects and all subobjects in selection mouse
void CGLI_Object::DrawSelection() /* {{{ */
{
	if (m_is_visible)
	{
		glPushMatrix();
		glTranslatef(m_x, m_y, m_z);
		glRotatef(m_rot_x, 1, 0, 0);
		glRotatef(m_rot_y, 0, 1, 0);
		glRotatef(m_rot_z, 0, 0, 1);
		if (m_scaling_factor != 1.0f)
			glScalef(m_scaling_factor, m_scaling_factor, m_scaling_factor);
	
		// Draw all attached objects
		CGLI_Object *temp;
	
		temp = m_pObjects;
		while (temp)
		{
			temp->CGLI_Object::DrawSelection();
			temp = temp->m_pNext;
		}

		glLoadName(m_ID);
		Draw();

		glPopMatrix();
	}
} /* }}} */

// Set callback function for this object (all events)
void CGLI_Object::SetCallBackFunction(void (*funct)(GLuint id, GLuint event_type)) /* {{{ */
{
	m_funct = funct;
} /* }}} */

// Set callback function for this object, (only event_type events are processed)
void CGLI_Object::SetCallBackFunctionByEvent(void (*funct)(GLuint id), GLuint event_type) /* {{{ */
{
	m_funct_event = funct;
	m_callback_event_type = event_type;
} /* }}} */

// Return TRUE - if id is present in object and all subobjects
GLboolean CGLI_Object::SetEventID(GLuint id) /* {{{ */
{
	
	if (id == m_ID) return GL_TRUE;

	// Else search for this ID in attached objects
	CGLI_Object *temp;

	temp = m_pObjects;
	while (temp)
	{
		if (temp->SetEventID(id)) return GL_TRUE;
		temp = temp->m_pNext;
	}
	
	return GL_FALSE;
} /* }}} */

// Add new subobject to current object
void CGLI_Object::AddObject(CGLI_Object *object) /* {{{ */
{
	// Add object to the head of the queue
	object->m_pNext = m_pObjects;
	m_pObjects = object;

	object->m_pVectorFont = m_pVectorFont;
	object->m_pBitmapFont = m_pBitmapFont;

	object->UpdateObject();

} /* }}} */

// Delete all attached objects from objects queue
void CGLI_Object::DeleteAllObjects() /* {{{ */
{
	CGLI_Object *temp;

	while (m_pObjects)
	{
		temp = m_pObjects->m_pNext;
		delete m_pObjects;
		m_pObjects = temp;
	}
} /* }}} */

void CGLI_Object::UpdateObject() /* {{{ */
{
	CGLI_Object *temp;

	temp = m_pObjects;
	while (temp)
	{
		temp->CGLI_Object::UpdateObject();
		temp = temp->m_pNext;
	}
	UpdateObject();
} /* }}} */

// Do one animation tick for current object (for example - object animation)
void CGLI_Object::DoAnimationTick() /* {{{ */
{
	CGLI_Object *temp;

	temp = m_pObjects;
	while (temp)
	{
		temp->CGLI_Object::DoAnimationTick();
		temp = temp->m_pNext;
	}
	DoAnimationTick();
} /* }}} */

