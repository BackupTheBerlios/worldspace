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
#ifndef __GLI_TEXT_H__
#define __GLI_TEXT_H__

#include "gli_object.h"


//==///////////////////////////////////////////////////////////////////////////////==
//                           CGLI_String class
//==///////////////////////////////////////////////////////////////////////////////==


// String class, string support
class CGLI_String : public CGLI_Object
{
public:

	CGLI_String();
	virtual ~CGLI_String();

	void SetString(char *string); // Set string
	char *GetString(); // Get string
	
	virtual void Draw();
	
	void TranslatePosition(GLfloat some_constant);
	void SetStringCentering(GLboolean center); // Set string centering for string

	void SetFontType(GLuint font_type); // Font type: GLI_FONT_VECTOR or GLI_FONT_BITMAP
	
	virtual void UpdateObject();
	virtual void DoAnimationTick();
	
	CGLI_String *m_pNext;

protected:

	void ProcessInternalCallBack(GLuint obj_id);

	char *m_string;
	GLboolean m_center; // Center the string?
	GLuint m_font_type; // Font type
};


//==///////////////////////////////////////////////////////////////////////////////==
//                           CGLI_Text class
//==///////////////////////////////////////////////////////////////////////////////==

// Text class, text support
class CGLI_Text : public CGLI_Object
{

public:
	
	CGLI_Text();
	virtual ~CGLI_Text();

	// Insert new string to the head of text
	void InsertNewString(char *string);
	// Insert new string to the end of text
	void AddNewString(char *string);
	// Delete all strings from text
	void DeleteAllStrings();

	// Set space length between two strings
	void SetStringSpaceLength(GLfloat space);

	void SetTextCentering(GLboolean center); // Set text centering

	void SetFontType(GLuint font_type); // Set font type for all font

	virtual void Draw();

	virtual void UpdateObject();
	virtual void DoAnimationTick();

protected:

	void ProcessInternalCallBack(GLuint obj_id);

	CGLI_String *m_pStrings; // All strings (lines) in the text
	GLfloat m_str_space; // Lenght between two strings
	GLuint m_font_type; // Text font type
	GLboolean m_center; // Text centering
};

#endif

