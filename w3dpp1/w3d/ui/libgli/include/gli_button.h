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
#ifndef __GLI_BUTTON_H__
#define __GLI_BUTTON_H__

#include "gli_object.h"
#include "gli_glf.h"
#include "gli_text.h"


//==///////////////////////////////////////////////////////////////////////////////==
//                           CGLI_Button class
//==///////////////////////////////////////////////////////////////////////////////==


// Base class for buttons
class CGLI_Button : public CGLI_Object
{
public:

	CGLI_Button();
	virtual ~CGLI_Button();
	
	void SetButtonText(char *text); // Set button text
	void SetTextColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a); // Color of button text
	void SetTextHeight(GLfloat text_height); // Set height of button text
	void SetOnMouseColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a); // Color, when MouseOver

	virtual void Draw() = 0; // Draw method

	virtual void UpdateObject();
	virtual void DoAnimationTick();


protected:

	virtual void ProcessInternalCallBack(GLuint obj_id);

	GLfloat m_pr, m_pg, m_pb, m_pa; // Color of pressed button
	GLfloat m_mor, m_mog, m_mob, m_moa; // Color of button, when "mouse over"
	GLfloat m_tr, m_tg, m_tb, m_ta; // Color of text

	char *m_text; // Button text
	GLfloat m_text_height;
};


//==///////////////////////////////////////////////////////////////////////////////==
//                           CGLI_ButtonOBJ class
//==///////////////////////////////////////////////////////////////////////////////==

//!!!!!!!!!!!!! THIS CLASS IS UNDER DEVELOPMENT !!!!!!!!!!!!!!
//!!!!!!!!!!!!! THIS CLASS IS UNDER DEVELOPMENT !!!!!!!!!!!!!!
//!!!!!!!!!!!!! THIS CLASS IS UNDER DEVELOPMENT !!!!!!!!!!!!!!

// Button based on object data (vertex, polygon, normal)
class CGLI_ButtonOBJ : public CGLI_Button
{

public:
	CGLI_ButtonOBJ();
	virtual ~CGLI_ButtonOBJ();

	// type = GLI_BUTTON_NORMAL or GLI_BUTTON_PRESSED
	// tr_type = GLI_VERTEX or GLI_VERTEX_NORMAL or GLI_VERTEX_TEXTURE or GLI_VERTEX_NORMAL_TEXTURE
	void SetVertexInfo(GLuint type, GLuint total, GLfloat *vertexes); // Set vertex data
	void SetNormalInfo(GLuint type, GLuint total, GLfloat *normals); // Set normals for object
	void SetTextureCoordInfo(GLuint type, GLuint total, GLfloat *tex_coord); // Set texture coordinates for object
	void SetTriangleInfo(GLuint type, GLuint total, GLuint *triangles, GLuint tr_type); // Set triangle info for object

	virtual void Draw(); // Draw method

protected:

	GLfloat *m_vert_n, *m_norm_n, *m_textur_n; // Pointers to vertex, normal, texture_coord info (For normal state)
	GLfloat *m_vert_p, *m_norm_p, *m_textur_p; // Pointers to vertex, normal, texture_coord info (For "pressed" state)
	
	GLuint m_vert_total_n, m_norm_total_n, m_textur_total_n, m_triangle_total_n; // Total of vertexes, normals, texture coords (For normal state)
	GLuint m_vert_total_p, m_norm_total_p, m_textur_total_p, m_triangle_total_p; // Total of vertexes, normals, texture coords (For "pressed" state)

	GLuint *m_triangles_n; // Pointer to triangles (For normal state)
	GLuint *m_triangles_p; // Pointer to triangles (For "pressed" state)

	GLuint m_tr_type_n; // Type of triangles (Simply, with Normals, Textured, with Normals and Textured) (For normal state)
	GLuint m_tr_type_p; // Type of triangles (Simply, with Normals, Textured, with Normals and Textured) (For "pressed" state)
};


//==///////////////////////////////////////////////////////////////////////////////==
//                           CGLI_Button2D class
//==///////////////////////////////////////////////////////////////////////////////==


// 2D Button class
class CGLI_Button2D : public CGLI_Button
{

public:
	CGLI_Button2D();
	~CGLI_Button2D();

	void SetBorderSize(GLfloat border); // Ser button border size
	void SetBorderColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a); // Set button border color
	void SetShadowBorderColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a); // Set shadow border color

	virtual void Draw(); // Draw method

protected:

	GLfloat m_border;

	GLfloat m_br, m_bg, m_bb, m_ba; // Color of border (on the sun)
	GLfloat m_sr, m_sg, m_sb, m_sa; // Color of shadow border

};

//==///////////////////////////////////////////////////////////////////////////////==
//                           CGLI_ButtonTexture class
//==///////////////////////////////////////////////////////////////////////////////==


// Texture button class
class CGLI_ButtonTexture : public CGLI_Button
{

public:
	CGLI_ButtonTexture();
	~CGLI_ButtonTexture();

	void SetTexture(GLuint normal, GLuint pressed, GLuint onover); // Set all texture to button
	void SetNormalTexture(GLuint texture_number); // Set only normal texture to button
	void SetPressedTexture(GLuint texture_number); // Set only pressed texture to button
	void SetOnOverTexture(GLuint texture_number); // Set onover texture

	void SetCoord(GLfloat *normal, GLfloat *pressed, GLfloat *onover);
	void SetNormalCoord(GLfloat *coord);
	void SetPressedCoord(GLfloat *coord);
	void SetOnOverCoord(GLfloat *coord);

	void SetButtonShift(GLfloat x, GLfloat y, GLfloat z); // Shift button in space, when pressed (if needed)

	virtual void Draw();

protected:

	// Texture numbers
	GLuint m_normal, m_pressed, m_onover; // Normal, pressed and OnOver texture numbers
	GLfloat m_standard_coord[8];
	GLfloat *m_normal_coord, *m_pressed_coord, *m_onover_coord;

	GLfloat m_but_shift_x, m_but_shift_y, m_but_shift_z; // Button shift coordinates (when pressed)
	GLboolean m_but_shift; // Shift flag (True - if shift is needed)
};


//==///////////////////////////////////////////////////////////////////////////////==
//                           CGLI_CheckBox2D class
//==///////////////////////////////////////////////////////////////////////////////==

class CGLI_CheckBox2D : public CGLI_Button2D
{
public:

	CGLI_CheckBox2D();
	virtual ~CGLI_CheckBox2D();

	void SetCheckedColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
	void SetType(GLuint type);
	
	GLboolean isChecked();

	virtual void Draw();

protected:

	virtual void ProcessInternalCallBack(GLuint obj_id);

	GLfloat m_cr, m_cg, m_cb, m_ca; // Color of checked box
	GLboolean m_checked;
	GLuint m_checkbox_type; // Type of checkbox
};

//==///////////////////////////////////////////////////////////////////////////////==
//                           CGLI_CheckBoxTexture class
//==///////////////////////////////////////////////////////////////////////////////==

class CGLI_CheckBoxTexture : public CGLI_ButtonTexture
{
public:

	CGLI_CheckBoxTexture();
	virtual ~CGLI_CheckBoxTexture();

	GLboolean isChecked();

	virtual void Draw();

protected:

	virtual void ProcessInternalCallBack(GLuint obj_id);

	GLboolean m_checked;
};


#endif

