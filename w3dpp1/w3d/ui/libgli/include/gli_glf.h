//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Part of GLF Library
// 
//  Author: Roman Podobedov
//  Email: romka@ut.ee
//  WEB: http://romka.demonews.com
//  Copyright (C) 2000-2001, Romka Graphics
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef __GLI_GLF_H__
#define __GLI_GLF_H__


#define GLF_ERROR				-1
#define GLF_OK					0
#define GLF_YES					1
#define GLF_NO					2

#define GLF_CONSOLE_MESSAGES	10
#define GLF_TEXTURING			11
#define GLF_CONTOURING			12

#define GLF_LEFT_UP				20
#define GLF_LEFT_CENTER			21
#define GLF_LEFT_DOWN			22
#define GLF_CENTER_UP			23
#define GLF_CENTER_CENTER		24
#define GLF_CENTER_DOWN			25
#define GLF_RIGHT_UP			26
#define GLF_RIGHT_CENTER		27
#define GLF_RIGHT_DOWN			28
#define GLF_CENTER				24

#define GLF_MAX_FONTS			4096



//==///////////////////////////////////////////////////////////////////////////////==
//                           CGLI_VectorFont class
//==///////////////////////////////////////////////////////////////////////////////==

// Vector font class
class CGLI_VectorFont
{
public:

	CGLI_VectorFont();
	virtual ~CGLI_VectorFont();

	int glfLoadFont(char *font_name);
	int glfLoadFontFromMemory(unsigned char *memory);

	int glfUnloadFont();
	int glfUnloadFontD(int font_descriptor);
	void glfDrawWiredSymbol(char s);

	void glfDrawWiredSymbolF(int font_descriptor, char s);
	void glfDrawWiredString(char *s);
	void glfDrawWiredStringF(int font_descriptor, char *s);
	void glfDrawSolidSymbol(char s);
	void glfDrawSolidSymbolF(int font_descriptor, char s);
	void glfDrawSolidString(char *s);
	void glfDrawSolidStringF(int font_descriptor, char *s);
	void glfGetStringBoundsF(int fd, char *s, float *minx, float *miny, float *maxx, float *maxy);
	void glfGetStringBounds(char *s, float *minx, float *miny, float *maxx, float *maxy);
	void glfSetSymbolSpace(float sp);
	float glfGetSymbolSpace();
	void glfSetSpaceSize(float sp);
	float glfGetSpaceSize();
	void glfSetSymbolDepth(float dpth);
	float glfGetSymbolDepth();
	int glfSetCurrentFont(int Font_Descriptor);
	int glfGetCurrentFont();
	void glfSetAnchorPoint(int anchp);
	void glfSetContourColor(float r, float g, float b, float a);
	void glfEnable(int what);
	void glfDisable(int what);
	void glfStringCentering(GLboolean center);
	GLboolean glfGetStringCentering();

protected:


	// Color structure
	struct color
	{
		float r, g, b, a;
	};

	// One symbol of font
	struct one_symbol
	{
		unsigned char vertexs; // Number of vertexs
		unsigned char facets;  // Number of facets
		unsigned char lines;   // Number of lines in symbol
	
		float *vdata;          // Pointer to Vertex data
		unsigned char *fdata;  // Pointer to Facets data
		unsigned char *ldata;  // Pointer to Line data

		float leftx;           // Smaller x coordinate
		float rightx;          // Right x coordinate
		float topy;            // Top y coordinate
		float bottomy;         // Bottom y coordinate
	};

	// Font structure
	struct glf_font
	{
		char font_name [97];
		unsigned char sym_total;          // Total symbols in font
		struct one_symbol *symbols[256];  // Pointers to symbols
	};

	// Main variables

	float SymbolDist;  // Distance between symbols (Variable constant)
	float SymbolDepth; // Symbol Depth in 3D space (Variable constant)
	float SpaceSize;   // Space size (Variable constant)

	// Array of font pointers, up to MAX_FONTS fonts can be loaded at once
	// if (fonts[i] == NULL) then this font is not present in memory
	struct		glf_font *fonts[GLF_MAX_FONTS];
	int			curfont;					// Index of current font pointer
	char		ap;			// Anchor point
	char		console_msg;
	char		texturing;
	char		contouring;

	// String allign types
	GLboolean m_string_center; // Center the string?

	// Protected functions
	int ReadFont(char *font_name, glf_font *glff);
	int ReadFontFromMemory(unsigned char *memory, struct glf_font *glff);

};


//==///////////////////////////////////////////////////////////////////////////////==
//                           CGLI_BitmapFont class
//==///////////////////////////////////////////////////////////////////////////////==


// Bitmap font class
class CGLI_BitmapFont
{
public:

	CGLI_BitmapFont();
	virtual ~CGLI_BitmapFont();

	int glfLoadBMFFont(char *FName);
	int glfUnloadBMFFontD(int bmf_descriptor);
	int glfUnloadBMFFont();

	int glfSetCurrentBMFFont(int Font_Descriptor);
	int glfGetCurrentBMFFont();

	void glfStartBitmapDrawing();
	void glfStopBitmapDrawing();

	void glfDrawBSymbol(char s);
	void glfDrawBString(char *s);
	void glfDrawBMaskSymbol(char s);
	void glfDrawBMaskString(char *s);

	GLfloat glfGetMaxHeight(); // Get Maximal height of symbol

	void glfStringCentering(GLboolean center);
	GLboolean glfGetStringCentering();

protected:

	struct coord_rect
	{
		float x, y, width, height;
	};

	struct widths
	{
		float *width;
	};

	// Constants
	float sym_space; // Space between symbols

	// One font variables
	struct coord_rect Symbols[256];
	
	GLboolean bmf_texturing; // GL_TEXTURE_2D is enabled?
	int	bmf_curfont; // Current Bitmap font
	
	GLuint bmf_texture[GLF_MAX_FONTS]; // All fonts
	GLfloat m_max_height[GLF_MAX_FONTS]; // Maximal height of each font
	struct widths m_widths[GLF_MAX_FONTS]; // Width of each symbols in each font
	GLuint bmf_mask[GLF_MAX_FONTS]; // All fonts (masked)
	char bmf_in_use[GLF_MAX_FONTS]; // 1 - if font is used, 0 - otherwise
	int list_base[GLF_MAX_FONTS]; // List base for each font

	// String allign types
	GLboolean m_string_center; // Center the string?

};


#endif

