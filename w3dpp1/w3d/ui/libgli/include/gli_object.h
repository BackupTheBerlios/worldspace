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
#ifndef __GLI_OBJECT_H__
#define __GLI_OBJECT_H__

#if defined (WIN32)
#include <windows.h>
#endif

#ifdef MACOSX
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#include "gli_types.h"
#include "gli_glf.h"

//==///////////////////////////////////////////////////////////////////////////////==
//                           CGLI_Object class
//==///////////////////////////////////////////////////////////////////////////////==


// Main CGLI_Object class
class CGLI_Object
{
public:

	CGLI_Object();
	virtual ~CGLI_Object();

	GLuint GetID(); // Get ID of object

	void SetObjectName(char *name);
	char *GetObjectName();

	void SetPosition(GLfloat x, GLfloat y, GLfloat z);
	void SetDimensions(GLfloat width, GLfloat height, GLfloat depth);
	void SetRotation(GLfloat x, GLfloat y, GLfloat z);
	void SetScalingFactor(GLfloat scaling_factor);
	
	// Set mosue state for object (ID must be defined, because object can manage some objects)
	GLuint SetMouseState(GLuint type, GLuint id, int button, int state);
	// Set key
	GLuint HandleKeyEvent(unsigned char key, GLuint id);

	void SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

	// Draw current object
	virtual void Draw();

	// Hide this object
	void Hide();
	// Show this object
	void Show();
	
	// Draw current object (when in selection mode)
	virtual void DrawSelection();

	void SetVectorFontObject(CGLI_VectorFont *font);
	void SetBitmapFontObject(CGLI_BitmapFont *font);
	void SetCurrentVectorFont(GLuint font);
	void SetCurrentBitmapFont(GLuint font);
	
	// Set callback function
	void SetCallBackFunction(void (*funct)(GLuint id, GLuint event_type));
	
	// Set callback function with event specify
	void SetCallBackFunctionByEvent(void (*funct)(GLuint id), GLuint event_type);
	
	// Send event ID to object (if this event ID is not match with object(s) ID then ignore this message)
	virtual GLboolean SetEventID(GLuint id);

	// Connect new object with this (add to objects queue)
	void AddObject(CGLI_Object *object);
	// Delete all attached objects
	void DeleteAllObjects();

	// This method should update all sub objects in object
	// Must be called, when some info is sended to object
	virtual void UpdateObject();

	virtual void DoAnimationTick();

	CGLI_Object *m_pNext; // Next Object

protected:

	static GLuint m_ID_Counter; // ID counter
	GLuint m_ID; // Object ID
	
	char *m_name; // Object name (string)

	CGLI_Object *m_pObjects; // Objects, that connected with this object (children)

	GLboolean m_is_visible; // This object is visible?
	GLfloat m_x, m_y, m_z; // Object coordinates
	GLfloat m_width, m_height, m_depth; // Object dimensions
	GLfloat m_rot_x, m_rot_y, m_rot_z; // Object rotation
	GLfloat m_scaling_factor; // Scaling factor
	GLint m_mouse_button, m_mouse_state;
	GLint m_prev_mouse_button, m_prev_mouse_state;
	GLuint m_event_type, m_event_type_prev;
	unsigned char m_key;
	GLfloat m_r, m_g, m_b, m_a; // Color r, g, b, a

	GLuint m_vec_font; // Current vector font
	GLuint m_bmf_font; // Current bitmapped font
	CGLI_VectorFont *m_pVectorFont; // Pointer to Vector font object (in Interface)
	CGLI_BitmapFont *m_pBitmapFont; // Pointer to Bitmap font object (in Interface)
	GLfloat m_tr, m_tg, m_tb, m_ta; // Text r, g, b, a color

	void (*m_funct)(GLuint id, GLuint event_type); // Event callback function
	void (*m_funct_event)(GLuint id); // Event callback function by event
	GLuint m_callback_event_type; // For SetCallBackEventByEvent

	// Protected functions
	virtual void ProcessInternalCallBack(GLuint obj_id) = 0;
};

#endif

