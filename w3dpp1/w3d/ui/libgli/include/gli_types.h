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
#ifndef __GLI_TYPES_H__
#define __GLI_TYPES_H__

// Mouse types
#define	GLI_MOUSE_CLICK				1
#define	GLI_MOUSE_MOTION			2
#define	GLI_MOUSE_MOTION_BUTTON			3

#define	GLI_MOUSE_BUTTON_NONE			100
#define GLI_MOUSE_BUTTON_LEFT			101
#define GLI_MOUSE_BUTTON_MIDDLE			102
#define GLI_MOUSE_BUTTON_RIGHT			103
#define GLI_KEYBOARD				104

#define	GLI_MOUSE_BUTTON_UP			104
#define	GLI_MOUSE_BUTTON_DOWN			105

#define GLI_VERTEX				0
#define GLI_VERTEX_NORMAL			1
#define GLI_VERTEX_TEXTURE			2
#define GLI_VERTEX_NORMAL_TEXTURE		3

#define GLI_BUTTON_NORMAL			0
#define GLI_BUTTON_PRESSED			1

// Events type
#define GLI_NONE				0
#define GLI_PRESSED				1
#define GLI_RELEASED				2
#define GLI_CLICKED				3
#define GLI_INFOCUS				4
#define GLI_ONOVER				5

// Window buttons
#define GLI_BUTTON_MINIMIZE			1
#define GLI_BUTTON_MAXIMIZE			2
#define GLI_BUTTON_CLOSE			4

// Window types
#define GLI_WINDOW_FILLED			1
#define GLI_WINDOW_FRAMED			2

// Font types
#define GLI_FONT_VECTOR				1
#define GLI_FONT_BITMAP				2

// Checkbox types
#define GLI_CHECKBOX_COLOR			1
#define GLI_CHECKBOX_CROSS			2
#define GLI_CHECKBOX_SQUARE			3


#endif

