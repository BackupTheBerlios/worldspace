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
#include <stdlib.h>
#include <math.h>

#ifdef MACOSX
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include "gli_glf.h"
#include "string"


//==///////////////////////////////////////////////////////////////////////////////==
//      This function check that this machine is little endian
//      Return value:   1 - little endian
//                                      0 - big endian
//==///////////////////////////////////////////////////////////////////////////////==
static int LittleEndian()
{
    int endianTester = 1;
    char *endianChar = 0;

    endianChar = (char *) &endianTester;
    if (*endianChar)
        return 1;
    return 0;
}


//==///////////////////////////////////////////////////////////////////////////////==
//                           CGLI_VectorFont class
//==///////////////////////////////////////////////////////////////////////////////==

CGLI_VectorFont::CGLI_VectorFont()
{
    SymbolDist = 0.2f;          // Distance between symbols (Variable constant)
    SymbolDepth = 0.2f;         // Symbol Depth in 3D space (Variable constant)
    SpaceSize = 2.0f;           // Space size (Variable constant)
    console_msg = GLF_NO;
    texturing = GLF_NO;
    contouring = GLF_NO;

    for (int i = 0; i < GLF_MAX_FONTS; i++)
        fonts[i] = NULL;

    curfont = -1;
    ap = GLF_LEFT_CENTER;       // Set anchor point to center of each symbol
    texturing = GLF_NO;         // By default texturing is NOT Enabled 
    contouring = GLF_NO;        // By default contouring is NOT Enabled
    m_string_center = GL_FALSE;
}

CGLI_VectorFont::~CGLI_VectorFont()
{
    for (int i = 0; i < GLF_MAX_FONTS; i++)
        glfUnloadFontD(i);
}


//==///////////////////////////////////////////////////////////////////////////////==
//      This function read font file and store information in memory
//      Return: GLF_OK - if all OK
//      Return: GLF_ERROR - if any error 
//==///////////////////////////////////////////////////////////////////////////////==
int CGLI_VectorFont::ReadFont(char *font_name, struct glf_font *glff)
{

    FILE *fontf;
    char buffer[64];
    int i, j;
    unsigned char temp, code, verts, fcets, lns;
    float tempfx, tempfy;
    unsigned char *tp;
    int LEndian;                // True if little endian machine

    fontf = fopen(font_name, "rb");
    if (fontf == NULL)
        return GLF_ERROR;

    fread(buffer, 3, 1, fontf);
    buffer[3] = 0;
    if (strcmp(buffer, "GLF")) {
        // If header is not "GLF"
        if (console_msg)
            printf("Error reading font file: incorrect file format\n");
        return GLF_ERROR;
    }
    // Check for machine type 
    LEndian = LittleEndian();

    fread(glff->font_name, 96, 1, fontf);
    glff->font_name[96] = 0;

    fread(&glff->sym_total, 1, 1, fontf);       // Read total symbols in font

    for (i = 0; i < 256; i++)
        glff->symbols[i] = NULL;

    for (i = 0; i < 28; i++)
        fread(&temp, 1, 1, fontf);      // Read unused data

    // Now start to read font data

    for (i = 0; i < glff->sym_total; i++) {
        fread(&code, 1, 1, fontf);      // Read symbol code
        fread(&verts, 1, 1, fontf);     // Read vertexs count
        fread(&fcets, 1, 1, fontf);     // Read facets count
        fread(&lns, 1, 1, fontf);       // Read lines count

        if (glff->symbols[code] != NULL) {
            if (console_msg)
                printf
                    ("Error reading font file: encountered symbols in font\n");
            return GLF_ERROR;
        }

        glff->symbols[code] =
            (struct one_symbol *) malloc(sizeof(struct one_symbol));
        glff->symbols[code]->vdata = (float *) malloc(8 * verts);
        glff->symbols[code]->fdata = (unsigned char *) malloc(3 * fcets);
        glff->symbols[code]->ldata = (unsigned char *) malloc(lns);

        glff->symbols[code]->vertexs = verts;
        glff->symbols[code]->facets = fcets;
        glff->symbols[code]->lines = lns;

        // Read vertexs data
        glff->symbols[code]->leftx = 10;
        glff->symbols[code]->rightx = -10;
        glff->symbols[code]->topy = 10;
        glff->symbols[code]->bottomy = -10;

        for (j = 0; j < verts; j++) {
            fread(&tempfx, 4, 1, fontf);
            fread(&tempfy, 4, 1, fontf);

            // If machine is bigendian -> swap low and high words in
            // tempfx and tempfy
            if (!LEndian) {
                tp = (unsigned char *) &tempfx;
                temp = tp[0];
                tp[0] = tp[3];
                tp[3] = temp;
                temp = tp[1];
                tp[1] = tp[2];
                tp[2] = temp;
                tp = (unsigned char *) &tempfy;
                temp = tp[0];
                tp[0] = tp[3];
                tp[3] = temp;
                temp = tp[1];
                tp[1] = tp[2];
                tp[2] = temp;
            }
            glff->symbols[code]->vdata[j * 2] = tempfx;
            glff->symbols[code]->vdata[j * 2 + 1] = tempfy;

            if (tempfx < glff->symbols[code]->leftx)
                glff->symbols[code]->leftx = tempfx;
            if (tempfx > glff->symbols[code]->rightx)
                glff->symbols[code]->rightx = tempfx;
            if (tempfy < glff->symbols[code]->topy)
                glff->symbols[code]->topy = tempfy;
            if (tempfy > glff->symbols[code]->bottomy)
                glff->symbols[code]->bottomy = tempfy;
        }
        for (j = 0; j < fcets; j++)
            fread(&glff->symbols[code]->fdata[j * 3], 3, 1, fontf);
        for (j = 0; j < lns; j++)
            fread(&glff->symbols[code]->ldata[j], 1, 1, fontf);
    }
    fclose(fontf);
    return GLF_OK;
}

int CGLI_VectorFont::ReadFontFromMemory(unsigned char *memory,
                                        struct glf_font *glff)
{
    char buffer[64];
    int i, j;
    unsigned char temp, code, verts, fcets, lns;
    float tempfx, tempfy;
    unsigned char *tp;
    int LEndian;                // True if little endian machine

    memcpy(buffer, memory, 3);
    buffer[3] = 0;
    if (strcmp(buffer, "GLF")) {
        // If header is not "GLF"
        if (console_msg)
            printf("Error reading font file: incorrect file format\n");
        return GLF_ERROR;
    }
    // Check for machine type 
    LEndian = LittleEndian();

    memory += 3;
    memcpy(glff->font_name, memory, 96);
    glff->font_name[96] = 0;

    memory += 96;
    memcpy(&glff->sym_total, memory++, 1);      // Read total symbols in font

    for (i = 0; i < 256; i++)
        glff->symbols[i] = NULL;

    memory += 28;               // Read unused data

    // Now start to read font data

    for (i = 0; i < glff->sym_total; i++) {
        memcpy(&code, memory++, 1);     // Read symbol code
        memcpy(&verts, memory++, 1);    // Read vertexs count
        memcpy(&fcets, memory++, 1);    // Read facets count
        memcpy(&lns, memory++, 1);      // Read lines count

        if (glff->symbols[code] != NULL) {
            if (console_msg)
                printf
                    ("Error reading font file: encountered symbols in font\n");
            return GLF_ERROR;
        }

        glff->symbols[code] =
            (struct one_symbol *) malloc(sizeof(struct one_symbol));
        glff->symbols[code]->vdata = (float *) malloc(8 * verts);
        glff->symbols[code]->fdata = (unsigned char *) malloc(3 * fcets);
        glff->symbols[code]->ldata = (unsigned char *) malloc(lns);

        glff->symbols[code]->vertexs = verts;
        glff->symbols[code]->facets = fcets;
        glff->symbols[code]->lines = lns;

        // Read vertexs data
        glff->symbols[code]->leftx = 10;
        glff->symbols[code]->rightx = -10;
        glff->symbols[code]->topy = 10;
        glff->symbols[code]->bottomy = -10;

        for (j = 0; j < verts; j++) {
            memcpy(&tempfx, memory, 4);
            memory += 4;
            memcpy(&tempfy, memory, 4);
            memory += 4;

            // If machine is bigendian -> swap low and high words in
            // tempfx and tempfy
            if (!LEndian) {
                tp = (unsigned char *) &tempfx;
                temp = tp[0];
                tp[0] = tp[3];
                tp[3] = temp;
                temp = tp[1];
                tp[1] = tp[2];
                tp[2] = temp;
                tp = (unsigned char *) &tempfy;
                temp = tp[0];
                tp[0] = tp[3];
                tp[3] = temp;
                temp = tp[1];
                tp[1] = tp[2];
                tp[2] = temp;
            }
            glff->symbols[code]->vdata[j * 2] = tempfx;
            glff->symbols[code]->vdata[j * 2 + 1] = tempfy;

            if (tempfx < glff->symbols[code]->leftx)
                glff->symbols[code]->leftx = tempfx;
            if (tempfx > glff->symbols[code]->rightx)
                glff->symbols[code]->rightx = tempfx;
            if (tempfy < glff->symbols[code]->topy)
                glff->symbols[code]->topy = tempfy;
            if (tempfy > glff->symbols[code]->bottomy)
                glff->symbols[code]->bottomy = tempfy;
        }
        for (j = 0; j < fcets; j++) {
            memcpy(&glff->symbols[code]->fdata[j * 3], memory, 3);
            memory += 3;
        }
        for (j = 0; j < lns; j++)
            memcpy(&glff->symbols[code]->ldata[j], memory++, 1);
    }
    return GLF_OK;
}




// 
// Function loads font to memory from file
// Return value: GLF_ERROR  - if error
//               >=0 - returned font descriptor (load success)
//
int CGLI_VectorFont::glfLoadFont(char *font_name)
{
    int i;
    char flag;                  // Temporary flag

    // First we find free font descriptor
    flag = 0;                   // Descriptor not found yet
    for (i = 0; i < GLF_MAX_FONTS; i++)
        if (fonts[i] == NULL) {
            // Initialize this font
            fonts[i] = (struct glf_font *) malloc(sizeof(struct glf_font));
            flag = 1;
            break;
        }

    if (!flag)
        return GLF_ERROR;       // Free font not found
    if (ReadFont(font_name, fonts[i]) == GLF_OK) {
        curfont = i;            // Set curfont to just loaded font
        return i;
    }

    if (fonts[i] != NULL) {
        free(fonts[i]);
        fonts[i] = NULL;
    }
    return GLF_ERROR;
}

int CGLI_VectorFont::glfLoadFontFromMemory(unsigned char *memory)
{
    int i;
    char flag;                  // Temporary flag

    // First we find free font descriptor
    flag = 0;                   // Descriptor not found yet
    for (i = 0; i < GLF_MAX_FONTS; i++)
        if (fonts[i] == NULL) {
            // Initialize this font
            fonts[i] = (struct glf_font *) malloc(sizeof(struct glf_font));
            flag = 1;
            break;
        }

    if (!flag)
        return GLF_ERROR;       // Free font not found
    if (ReadFontFromMemory(memory, fonts[i]) == GLF_OK) {
        curfont = i;            // Set curfont to just loaded font
        return i;
    }

    if (fonts[i] != NULL) {
        free(fonts[i]);
        fonts[i] = NULL;
    }
    return GLF_ERROR;
}


// 
// Unload current font from memory
// Return value: GLF_OK  - if all OK
//               GLF_ERROR -  if error
//
int CGLI_VectorFont::glfUnloadFont()
{
    int i;

    if ((curfont < 0) || (fonts[curfont] == NULL))
        return GLF_ERROR;

    for (i = 0; i < 256; i++) {
        if (fonts[curfont]->symbols[i] != NULL) {
            free(fonts[curfont]->symbols[i]->vdata);
            free(fonts[curfont]->symbols[i]->fdata);
            free(fonts[curfont]->symbols[i]->ldata);
            free(fonts[curfont]->symbols[i]);
        }
    }

    free(fonts[curfont]);
    fonts[curfont] = NULL;
    curfont = -1;
    return GLF_OK;
}

// Unload font by font descriptor
int CGLI_VectorFont::glfUnloadFontD(int font_descriptor)
{
    int temp;

    if ((font_descriptor < 0) || (fonts[font_descriptor] == NULL))
        return GLF_ERROR;

    temp = curfont;
    curfont = font_descriptor;
    glfUnloadFont();
    if (temp != font_descriptor)
        curfont = temp;
    else
        curfont = -1;
    return GLF_OK;
}

void CGLI_VectorFont::glfDrawWiredSymbol(char s)
{
    int i, cur_line;
    float *tvp;                 // temporary vertex pointer
    float x, y;

    if ((curfont < 0) || (fonts[curfont] == NULL))
        return;
    if (fonts[curfont]->symbols[s] == NULL)
        return;

    glBegin(GL_LINE_LOOP);
    tvp = fonts[curfont]->symbols[s]->vdata;
    cur_line = 0;
    for (i = 0; i < fonts[curfont]->symbols[s]->vertexs; i++) {
        x = *tvp++;
        y = *tvp++;
        glVertex2f(x, y);
        if (fonts[curfont]->symbols[s]->ldata[cur_line] == i) {
            glEnd();
            cur_line++;
            if (cur_line < fonts[curfont]->symbols[s]->lines)
                glBegin(GL_LINE_LOOP);
            else
                break;          // No more lines
        }
    }
}

// Draw wired symbol by font_descriptor
void CGLI_VectorFont::glfDrawWiredSymbolF(int font_descriptor, char s)
{
    int temp;

    temp = curfont;
    curfont = font_descriptor;
    glfDrawWiredSymbol(s);
    curfont = temp;
}

void CGLI_VectorFont::glfDrawWiredString(char *s)
{
    int i;
    float sda, sdb;
    float distance;

    if (!strcmp(s, ""))
        return;
    if (curfont == -1)
        return;

    if (m_string_center) {
        distance = 0;
        for (i = 0; i < (int) strlen(s); i++) {
            if ((fonts[curfont]->symbols[s[i]] == NULL) || (s[i] == ' '))
                distance += SpaceSize;
            else if (i < ((int) strlen(s) - 1))
                if (s[i + 1] == ' ')
                    distance += SymbolDist;
                else {
                    if (fonts[curfont]->symbols[s[i + 1]] == NULL)
                        continue;
                    sda = fonts[curfont]->symbols[s[i]]->rightx;
                    sdb = -fonts[curfont]->symbols[s[i + 1]]->leftx;
                    distance += sda + sdb + SymbolDist;
                }
        }
    }

    glPushMatrix();
    if (m_string_center)
        glTranslatef(-distance / 2, 0, 0);
    else
        glTranslatef(-
                     (1 -
                      (float) fabs(fonts[curfont]->symbols[s[0]]->leftx)),
                     0, 0);
    for (i = 0; i < (int) strlen(s); i++) {
        if (s[i] != ' ')
            glfDrawWiredSymbol(s[i]);
        if ((fonts[curfont]->symbols[s[i]] == NULL) || (s[i] == ' '))
            glTranslatef(SpaceSize, 0, 0);
        else if (i < ((int) strlen(s) - 1))
            if (s[i + 1] == ' ')
                glTranslatef(SymbolDist, 0, 0);
            else {
                if (fonts[curfont]->symbols[s[i + 1]] == NULL)
                    continue;
                sda = fonts[curfont]->symbols[s[i]]->rightx;
                sdb = -fonts[curfont]->symbols[s[i + 1]]->leftx;
                glTranslatef(sda + sdb + SymbolDist, 0, 0);
            }
    }
    glPopMatrix();
}

/* Draw wired string by font_descriptor */
void CGLI_VectorFont::glfDrawWiredStringF(int font_descriptor, char *s)
{
    int temp;

    temp = curfont;
    curfont = font_descriptor;
    glfDrawWiredString(s);
    curfont = temp;
}

void CGLI_VectorFont::glfDrawSolidSymbol(char s)
{
    unsigned char *b;           /* Face pointer   */
    float *vp;                  /* Vertex pointer */
    int i, j;
    float x, y;

    if ((curfont < 0) || (fonts[curfont] == NULL))
        return;

    if (fonts[curfont]->symbols[s] == NULL)
        return;

    b = fonts[curfont]->symbols[s]->fdata;
    vp = fonts[curfont]->symbols[s]->vdata;

    glBegin(GL_TRIANGLES);
    for (i = 0; i < fonts[curfont]->symbols[s]->facets; i++) {
        for (j = 0; j < 3; j++) {
            x = vp[*b * 2];
            y = vp[*b * 2 + 1];
            if (texturing == GLF_YES)
                glTexCoord2f((x + 1) / 2, (y + 1) / 2);
            glVertex2f(x, y);
            b++;
        }
    }
    glEnd();
}

// Draw solid symbol by font_descriptor 
void CGLI_VectorFont::glfDrawSolidSymbolF(int font_descriptor, char s)
{
    int temp;

    temp = curfont;
    curfont = font_descriptor;
    glfDrawSolidSymbol(s);
    curfont = temp;
}

void CGLI_VectorFont::glfDrawSolidString(char *s)
{
    int i;
    float sda, sdb;
    float distance;

    if (!s)
        return;
    if (!*s)
        return;
    if (curfont == -1)
        return;

    if (m_string_center) {
        distance = 0;
        for (i = 0; i < (int) strlen(s); i++) {
            if ((fonts[curfont]->symbols[s[i]] == NULL) || (s[i] == ' '))
                distance += SpaceSize;
            else if (i < ((int) strlen(s) - 1))
                if (s[i + 1] == ' ')
                    distance += SymbolDist;
                else {
                    if (fonts[curfont]->symbols[s[i + 1]] == NULL)
                        continue;
                    sda = fonts[curfont]->symbols[s[i]]->rightx;
                    sdb = -fonts[curfont]->symbols[s[i + 1]]->leftx;
                    distance += sda + sdb + SymbolDist;
                }
        }
    }

    glPushMatrix();

    if (m_string_center)
        glTranslatef(-distance / 2, 0, 0);
    else
        glTranslatef(-
                     (1 -
                      (float) fabs(fonts[curfont]->symbols[s[0]]->leftx)),
                     0, 0);

    for (i = 0; i < (int) strlen(s); i++) {
        if (s[i] != ' ')
            glfDrawSolidSymbol(s[i]);
        if ((fonts[curfont]->symbols[s[i]] == NULL) || (s[i] == ' '))
            glTranslatef(SpaceSize, 0, 0);
        else if (i < ((int) strlen(s) - 1))
            if (s[i + 1] == ' ')
                glTranslatef(SymbolDist, 0, 0);
            else {
                if (fonts[curfont]->symbols[s[i + 1]] == NULL)
                    continue;
                sda = fonts[curfont]->symbols[s[i]]->rightx;
                sdb = -fonts[curfont]->symbols[s[i + 1]]->leftx;
                glTranslatef(sda + sdb + SymbolDist, 0, 0);
            }
    }
    glPopMatrix();
}

// Draw solid string by font_descriptor
void CGLI_VectorFont::glfDrawSolidStringF(int font_descriptor, char *s)
{
    int temp;

    temp = curfont;
    curfont = font_descriptor;
    glfDrawSolidString(s);
    curfont = temp;
}

// Get the size a string will have on screen
void CGLI_VectorFont::glfGetStringBoundsF(int fd, char *s, float *minx,
                                          float *miny, float *maxx,
                                          float *maxy)
{
    struct glf_font *font;
    int i;
    float sda, sdb, cw = 0, minxx = 10;
    float top = 10, bottom = -10;

    if (fd < 0 || fd > (GLF_MAX_FONTS - 1))
        return;
    font = fonts[fd];

    if (font == NULL)
        return;

    if (font->symbols[s[0]])
        minxx = font->symbols[s[0]]->leftx;
    else
        minxx = 0.0;

    for (i = 0; i < (int) strlen(s); i++) {
        if ((font->symbols[s[i]] == NULL) || (s[i] == ' '))
            cw += SpaceSize;
        else {
            sdb = -font->symbols[(int) s[i]]->leftx;
            sda = font->symbols[(int) s[i]]->rightx;

            cw += sda + sdb + SymbolDist;

            // Update top/bottom bounds
            if (font->symbols[(int) s[i]]->bottomy > bottom)
                bottom = font->symbols[(int) s[i]]->bottomy;

            if (font->symbols[(int) s[i]]->topy < top)
                top = font->symbols[(int) s[i]]->topy;
        }
    }

    cw += minxx;

    if ((maxx) && (maxy)) {
        *maxx = cw;
        *maxy = bottom;
//              anchor_proc(font->symbols[0]->leftx, maxx, maxy);
    }

    if ((minx) && (miny)) {
        *minx = minxx;
        *miny = top;
//              anchor_proc(font->symbols[0]->leftx, minx, miny);
    }
}

void CGLI_VectorFont::glfGetStringBounds(char *s, float *minx, float *miny,
                                         float *maxx, float *maxy)
{
    glfGetStringBoundsF(curfont, s, minx, miny, maxx, maxy);
}

void CGLI_VectorFont::glfSetSymbolSpace(float sp)
{
    SymbolDist = sp;
}

float CGLI_VectorFont::glfGetSymbolSpace()
{
    return SymbolDist;
}

void CGLI_VectorFont::glfSetSpaceSize(float sp)
{
    SpaceSize = sp;
}

float CGLI_VectorFont::glfGetSpaceSize()
{
    return SpaceSize;
}

void CGLI_VectorFont::glfSetSymbolDepth(float dpth)
{
    SymbolDepth = dpth;
}

float CGLI_VectorFont::glfGetSymbolDepth()
{
    return SymbolDepth;
}

int CGLI_VectorFont::glfSetCurrentFont(int Font_Descriptor)
{
    if ((Font_Descriptor < 0) || (fonts[Font_Descriptor] == NULL))
        return GLF_ERROR;

    curfont = Font_Descriptor;
    return GLF_OK;
}

int CGLI_VectorFont::glfGetCurrentFont()
{
    return curfont;
}

void CGLI_VectorFont::glfSetAnchorPoint(int anchp)
{
    if ((anchp >= GLF_LEFT_UP) && (anchp <= GLF_RIGHT_DOWN))
        ap = anchp;
}

void CGLI_VectorFont::glfEnable(int what)
{
    switch (what) {
    case GLF_CONSOLE_MESSAGES:
        console_msg = GLF_YES;
        break;
    case GLF_TEXTURING:
        texturing = GLF_YES;
        break;
    }
}

void CGLI_VectorFont::glfDisable(int what)
{
    switch (what) {
    case GLF_CONSOLE_MESSAGES:
        console_msg = GLF_NO;
        break;
    case GLF_TEXTURING:
        texturing = GLF_NO;
        break;
    }
}

void CGLI_VectorFont::glfStringCentering(GLboolean center)
{
    m_string_center = center;
}

GLboolean CGLI_VectorFont::glfGetStringCentering()
{
    return m_string_center;
}

#define SEEK_SET_POS 4195

// ---------------- Internal functions -----------------------------


// Some color conversions
static void bwtorgba(unsigned char *b, unsigned char *l, int n)
{
    while (n--) {
        l[0] = *b;
        l[1] = *b;
        l[2] = *b;
        l[3] = 0xff;
        l += 4;
        b++;
    }
}

static void latorgba(unsigned char *b, unsigned char *a, unsigned char *l,
                     int n)
{
    while (n--) {
        l[0] = *b;
        l[1] = *b;
        l[2] = *b;
        l[3] = *a;
        l += 4;
        b++;
        a++;
    }
}

static void rgbtorgba(unsigned char *r, unsigned char *g, unsigned char *b,
                      unsigned char *l, int n)
{
    while (n--) {
        l[0] = r[0];
        l[1] = g[0];
        l[2] = b[0];
        l[3] = 0xff;
        l += 4;
        r++;
        g++;
        b++;
    }
}

static void rgbatorgba(unsigned char *r, unsigned char *g,
                       unsigned char *b, unsigned char *a,
                       unsigned char *l, int n)
{
    while (n--) {
        l[0] = r[0];
        l[1] = g[0];
        l[2] = b[0];
        l[3] = a[0];
        l += 4;
        r++;
        g++;
        b++;
        a++;
    }
}

typedef struct _ImageRec {
    unsigned short imagic;
    unsigned short type;
    unsigned short dim;
    unsigned short xsize, ysize, zsize;
    unsigned int min, max;
    unsigned int wasteBytes;
    char name[80];
    unsigned long colorMap;
    FILE *file;
    unsigned char *tmp, *tmpR, *tmpG, *tmpB;
    unsigned long rleEnd;
    unsigned int *rowStart;
    int *rowSize;
} ImageRec;

static void ConvertShort(unsigned short *array, long length)
{
    unsigned b1, b2;
    unsigned char *ptr;

    ptr = (unsigned char *) array;
    while (length--) {
        b1 = *ptr++;
        b2 = *ptr++;
        *array++ = (b1 << 8) | (b2);
    }
}

static void ConvertLong(unsigned *array, long length)
{
    unsigned b1, b2, b3, b4;
    unsigned char *ptr;

    ptr = (unsigned char *) array;
    while (length--) {
        b1 = *ptr++;
        b2 = *ptr++;
        b3 = *ptr++;
        b4 = *ptr++;
        *array++ = (b1 << 24) | (b2 << 16) | (b3 << 8) | (b4);
    }
}

// Open RGB Image
static ImageRec *ImageOpen(FILE * f)
{
    union {
        int testWord;
        char testByte[4];
    } endianTest;

    ImageRec *image;
    int swapFlag;
    int x;

    endianTest.testWord = 1;
    if (endianTest.testByte[0] == 1)
        swapFlag = 1;
    else
        swapFlag = 0;

    image = (ImageRec *) malloc(sizeof(ImageRec));
    if (image == NULL) {
        fprintf(stderr, "Out of memory!\n");
        exit(1);
    }

    image->file = f;

    fread(image, 1, 12, image->file);

    if (swapFlag)
        ConvertShort(&image->imagic, 6);

    image->tmp = (unsigned char *) malloc(image->xsize * 256);
    image->tmpR = (unsigned char *) malloc(image->xsize * 256);
    image->tmpG = (unsigned char *) malloc(image->xsize * 256);
    image->tmpB = (unsigned char *) malloc(image->xsize * 256);
    if (image->tmp == NULL || image->tmpR == NULL || image->tmpG == NULL ||
        image->tmpB == NULL) {
        fprintf(stderr, "Out of memory!\n");
        exit(1);
    }

    if ((image->type & 0xFF00) == 0x0100) {
        x = image->ysize * image->zsize * sizeof(unsigned);
        image->rowStart = (unsigned *) malloc(x);
        image->rowSize = (int *) malloc(x);
        if (image->rowStart == NULL || image->rowSize == NULL) {
            fprintf(stderr, "Out of memory!\n");
            exit(1);
        }
        image->rleEnd = 512 + (2 * x);
        fseek(image->file, 512 + SEEK_SET_POS, SEEK_SET);
        fread(image->rowStart, 1, x, image->file);
        fread(image->rowSize, 1, x, image->file);
        if (swapFlag) {
            ConvertLong(image->rowStart, x / (int) sizeof(unsigned));
            ConvertLong((unsigned *) image->rowSize,
                        x / (int) sizeof(int));
        }
    } else {
        image->rowStart = NULL;
        image->rowSize = NULL;
    }
    return image;
}

// Close Image and free data
static void ImageClose(ImageRec * image)
{
    free(image->tmp);
    free(image->tmpR);
    free(image->tmpG);
    free(image->tmpB);
    free(image->rowSize);
    free(image->rowStart);
    free(image);
}

// Pixels row decoding (if used RLE encoding)
static void ImageGetRow(ImageRec * image, unsigned char *buf, int y, int z)
{
    unsigned char *iPtr, *oPtr, pixel;
    int count;

    if ((image->type & 0xFF00) == 0x0100) {
        fseek(image->file,
              (long) image->rowStart[y + z * image->ysize] + SEEK_SET_POS,
              SEEK_SET);
        fread(image->tmp, 1,
              (unsigned int) image->rowSize[y + z * image->ysize],
              image->file);

        iPtr = image->tmp;
        oPtr = buf;
        for (;;) {
            pixel = *iPtr++;
            count = (int) (pixel & 0x7F);
            if (!count)
                return;
            if (pixel & 0x80)
                while (count--)
                    *oPtr++ = *iPtr++;
            else {
                pixel = *iPtr++;
                while (count--)
                    *oPtr++ = pixel;
            }
        }
    } else {
        fseek(image->file,
              512 + (y * image->xsize) +
              (z * image->xsize * image->ysize) + SEEK_SET_POS, SEEK_SET);
        fread(buf, 1, image->xsize, image->file);
    }
}

// Read SGI (RGB) Image from file
static unsigned *read_texture(FILE * f, int *width, int *height,
                              int *components)
{
    unsigned *base, *lptr;
    unsigned char *rbuf, *gbuf, *bbuf, *abuf;
    ImageRec *image;
    int y;

    image = ImageOpen(f);

    if (!image)
        return NULL;
    (*width) = image->xsize;
    (*height) = image->ysize;
    (*components) = image->zsize;

    base =
        (unsigned *) malloc(image->xsize * image->ysize *
                            sizeof(unsigned));
    rbuf = (unsigned char *) malloc(image->xsize * sizeof(unsigned char));
    gbuf = (unsigned char *) malloc(image->xsize * sizeof(unsigned char));
    bbuf = (unsigned char *) malloc(image->xsize * sizeof(unsigned char));
    abuf = (unsigned char *) malloc(image->xsize * sizeof(unsigned char));

    if (!base || !rbuf || !gbuf || !bbuf)
        return NULL;
    lptr = base;
    for (y = 0; y < image->ysize; y++) {
        if (image->zsize >= 4) {
            ImageGetRow(image, rbuf, y, 0);
            ImageGetRow(image, gbuf, y, 1);
            ImageGetRow(image, bbuf, y, 2);
            ImageGetRow(image, abuf, y, 3);
            rgbatorgba(rbuf, gbuf, bbuf, abuf, (unsigned char *) lptr,
                       image->xsize);
            lptr += image->xsize;
        } else if (image->zsize == 3) {
            ImageGetRow(image, rbuf, y, 0);
            ImageGetRow(image, gbuf, y, 1);
            ImageGetRow(image, bbuf, y, 2);
            rgbtorgba(rbuf, gbuf, bbuf, (unsigned char *) lptr,
                      image->xsize);
            lptr += image->xsize;
        } else if (image->zsize == 2) {
            ImageGetRow(image, rbuf, y, 0);
            ImageGetRow(image, abuf, y, 1);
            latorgba(rbuf, abuf, (unsigned char *) lptr, image->xsize);
            lptr += image->xsize;
        } else {
            ImageGetRow(image, rbuf, y, 0);
            bwtorgba(rbuf, (unsigned char *) lptr, image->xsize);
            lptr += image->xsize;
        }
    }
    ImageClose(image);
    free(rbuf);
    free(gbuf);
    free(bbuf);
    free(abuf);

    return (unsigned *) base;
}

// Font texture conversion to mask texture
unsigned *texture_to_mask(unsigned *tex, int width, int height)
{
    int nSize, i;
    unsigned *ret;

    nSize = width * height;
    ret = (unsigned *) malloc(nSize * sizeof(unsigned));
    for (i = 0; i < nSize; i++)
        ret[i] = tex[i] & 0x00ffffff ? 0 : 0x00ffffff;

    return ret;
}

//==///////////////////////////////////////////////////////////////////////////////==
//                           CGLI_BitmapFont class
//==///////////////////////////////////////////////////////////////////////////////==

CGLI_BitmapFont::CGLI_BitmapFont()
{
    int i;
    sym_space = 0.001f;
    for (i = 0; i < GLF_MAX_FONTS; i++)
        bmf_in_use[i] = 0;
    for (i = 0; i < GLF_MAX_FONTS; i++)
        m_max_height[i] = 0;
    bmf_curfont = -1;
    m_string_center = GL_FALSE;
}

CGLI_BitmapFont::~CGLI_BitmapFont()
{

}


// Load BMF file format, function return bitmap font descriptor
int CGLI_BitmapFont::glfLoadBMFFont(char *FName)
{
    FILE *f;
    char Header[4];
    char FontName[97];
    int i, flag;
    int LEndian;
    float tx, ty, tw, th;
    unsigned char temp, *tp;
    unsigned *texture;          // Texture image
    unsigned *mask;             // Mask texture
    int twidth, theight, tcomp; // Image parameters
    float *temp_width;

    LEndian = LittleEndian();

    f = fopen(FName, "rb");
    if (f == NULL)
        return GLF_ERROR;       /* Error opening file */

    /* Get header */
    fread(Header, 1, 3, f);
    Header[3] = 0;
    if (strcmp(Header, "BMF"))
        return GLF_ERROR;       /* Not BMF format */

    /* Get font name */
    fread(FontName, 1, 96, f);
    FontName[96] = 0;

    // Allocate space for temp widths

    temp_width = new float[256];

    // Read all 256 symbols information
    for (i = 0; i < 256; i++) {
        fread(&tx, 4, 1, f);
        fread(&ty, 4, 1, f);
        fread(&tw, 4, 1, f);
        fread(&th, 4, 1, f);

        if (!LEndian) {
            tp = (unsigned char *) &tx;
            temp = tp[0];
            tp[0] = tp[3];
            tp[3] = temp;
            temp = tp[1];
            tp[1] = tp[2];
            tp[2] = temp;
            tp = (unsigned char *) &ty;
            temp = tp[0];
            tp[0] = tp[3];
            tp[3] = temp;
            temp = tp[1];
            tp[1] = tp[2];
            tp[2] = temp;
            tp = (unsigned char *) &tw;
            temp = tp[0];
            tp[0] = tp[3];
            tp[3] = temp;
            temp = tp[1];
            tp[1] = tp[2];
            tp[2] = temp;
            tp = (unsigned char *) &th;
            temp = tp[0];
            tp[0] = tp[3];
            tp[3] = temp;
            temp = tp[1];
            tp[1] = tp[2];
            tp[2] = temp;
        }

        Symbols[i].x = tx;
        Symbols[i].y = ty;
        Symbols[i].width = tw;
        Symbols[i].height = th;
        temp_width[i] = tw * 16;
    }

    /* Read texture image from file and build texture */
    texture = read_texture(f, &twidth, &theight, &tcomp);
    /* Generate mask texture */
    mask = texture_to_mask(texture, twidth, theight);

    /* Find unused font descriptor */
    flag = 0;
    for (i = 0; i < GLF_MAX_FONTS; i++)
        if (bmf_in_use[i] == 0) {
            /* Initialize this font */
            bmf_in_use[i] = 1;
            bmf_curfont = i;
            flag = 1;
            break;
        }
    if (!flag)                  // Not enought space for new texture
    {
        fclose(f);
        free(texture);
        free(mask);
        delete[]temp_width;
        return -1;
    }

    m_widths[bmf_curfont].width = temp_width;

    // Generating textures for font and mask
    glGenTextures(1, &bmf_texture[bmf_curfont]);
    glGenTextures(1, &bmf_mask[bmf_curfont]);


    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Build font texture
    glBindTexture(GL_TEXTURE_2D, bmf_texture[bmf_curfont]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, twidth, theight, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, texture);

    // Linear filtering for better quality
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Build mask texture
    glBindTexture(GL_TEXTURE_2D, bmf_mask[bmf_curfont]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, twidth, theight, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, mask);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    free(texture);
    free(mask);
    fclose(f);

    // Now build list for each symbol
    list_base[bmf_curfont] = glGenLists(256);
    for (i = 0; i < 256; i++) {
        glNewList(list_base[bmf_curfont] + i, GL_COMPILE);

        glBegin(GL_QUADS);
        glTexCoord2f(Symbols[i].x, Symbols[i].y);
        glVertex2f(0, 0);
        glTexCoord2f(Symbols[i].x + Symbols[i].width, Symbols[i].y);
        glVertex2f(Symbols[i].width * 16, 0);
        glTexCoord2f(Symbols[i].x + Symbols[i].width,
                     Symbols[i].y + Symbols[i].height);
        glVertex2f(Symbols[i].width * 16, Symbols[i].height * 16);
        glTexCoord2f(Symbols[i].x, Symbols[i].y + Symbols[i].height);
        glVertex2f(0, Symbols[i].height * 16);
        glEnd();
        glTranslatef(Symbols[i].width * 16 + sym_space, 0, 0);

        glEndList();
        if (Symbols[i].height * 16 > m_max_height[bmf_curfont])
            m_max_height[bmf_curfont] = Symbols[i].height * 16;
    }
    return bmf_curfont;
}

// Unloads bitmap font by descriptor 
int CGLI_BitmapFont::glfUnloadBMFFontD(int bmf_descriptor)
{
    if ((bmf_descriptor < 0) || (bmf_in_use[bmf_descriptor] == 0))
        return GLF_ERROR;

    bmf_in_use[bmf_descriptor] = 0;

    glDeleteTextures(1, &bmf_texture[bmf_descriptor]);
    glDeleteTextures(1, &bmf_mask[bmf_descriptor]);

    if (bmf_descriptor == bmf_curfont)
        bmf_curfont = -1;

    return GLF_OK;
}

// Unloads current bitmap font
int CGLI_BitmapFont::glfUnloadBMFFont()
{
    return glfUnloadBMFFontD(bmf_curfont);
}

// Start bitmap drawing function
void CGLI_BitmapFont::glfStartBitmapDrawing()
{
    /* Enable 2D Texturing */
    glGetBooleanv(GL_TEXTURE_2D, &bmf_texturing);
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, bmf_texture[bmf_curfont]);
}

// Stop bitmap drawing function
void CGLI_BitmapFont::glfStopBitmapDrawing()
{
    /* Return previuos state of texturing */
    if (bmf_texturing)
        glEnable(GL_TEXTURE_2D);
    else
        glDisable(GL_TEXTURE_2D);
}

// Select current BMF font
int CGLI_BitmapFont::glfSetCurrentBMFFont(int Font_Descriptor)
{
    if ((Font_Descriptor < 0) || (bmf_in_use[Font_Descriptor] == 0))
        return GLF_ERROR;

    bmf_curfont = Font_Descriptor;
    return GLF_OK;
}

// Get current BMF font
int CGLI_BitmapFont::glfGetCurrentBMFFont()
{
    return bmf_curfont;
}

// Draw one bitmapped symbol by current font
void CGLI_BitmapFont::glfDrawBSymbol(char s)
{
    if ((bmf_curfont < 0) || (bmf_in_use[bmf_curfont] == 0))
        return;

    glCallList(list_base[bmf_curfont] + (unsigned char) s);
}

// Draw bitmapped string
void CGLI_BitmapFont::glfDrawBString(char *s)
{
    if ((bmf_curfont < 0) || (bmf_in_use[bmf_curfont] == 0))
        return;

    GLfloat temp_trans = 0;

    // Calculate length of all string
    for (int i = 0; i < (int) strlen(s); i++)
        temp_trans += m_widths[bmf_curfont].width[s[i]] + sym_space;

    glListBase(list_base[bmf_curfont]);
    if (m_string_center == GL_TRUE) {
        glPushMatrix();
        glTranslatef(-temp_trans / 2, 0, 0);
    }
    glCallLists(strlen(s), GL_UNSIGNED_BYTE, (unsigned char *) s);
    if (m_string_center == GL_TRUE) {
        glPopMatrix();
    }
}

void CGLI_BitmapFont::glfDrawBMaskSymbol(char s)
{
    if ((bmf_curfont < 0) || (bmf_in_use[bmf_curfont] == 0))
        return;

    glPushMatrix();
    glPushAttrib(GL_CURRENT_BIT);

    // Draw the text as a mask in black
    glColor3ub(0xff, 0xff, 0xff);
    glBlendFunc(GL_DST_COLOR, GL_ZERO);
    glBindTexture(GL_TEXTURE_2D, bmf_mask[bmf_curfont]);

    glCallList(list_base[bmf_curfont] + (unsigned char) s);

    glPopAttrib();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, bmf_texture[bmf_curfont]);

    // Now draw the text over only the black bits in the requested color
    glBlendFunc(GL_ONE, GL_ONE);

    glCallList(list_base[bmf_curfont] + (unsigned char) s);
}

void CGLI_BitmapFont::glfDrawBMaskString(char *s)
{
    if ((bmf_curfont < 0) || (bmf_in_use[bmf_curfont] == 0))
        return;

    GLfloat temp_trans = 0;

    // Calculate length of all string
    for (int i = 0; i < (int) strlen(s); i++)
        temp_trans += m_widths[bmf_curfont].width[s[i]] + sym_space;

    glPushMatrix();
    glPushAttrib(GL_CURRENT_BIT);

    // Draw the text as a mask in black
    glColor3ub(0xff, 0xff, 0xff);
    glBlendFunc(GL_DST_COLOR, GL_ZERO);
    glBindTexture(GL_TEXTURE_2D, bmf_mask[bmf_curfont]);

    glListBase(list_base[bmf_curfont]);
    if (m_string_center == GL_TRUE) {
        glPushMatrix();
        glTranslatef(-temp_trans / 2, 0, 0);
    }
    glCallLists(strlen(s), GL_UNSIGNED_BYTE, (unsigned char *) s);
    if (m_string_center == GL_TRUE)
        glPopMatrix();

    glPopAttrib();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, bmf_texture[bmf_curfont]);

    // Now draw the text over only the black bits in the requested color
    glBlendFunc(GL_ONE, GL_ONE);
    glListBase(list_base[bmf_curfont]);
    if (m_string_center == GL_TRUE) {
        glPushMatrix();
        glTranslatef(-temp_trans / 2, 0, 0);
    }
    glCallLists(strlen(s), GL_UNSIGNED_BYTE, (unsigned char *) s);
    if (m_string_center == GL_TRUE)
        glPopMatrix();
}

// Get Maximal height of symbol
GLfloat CGLI_BitmapFont::glfGetMaxHeight()
{
    return m_max_height[bmf_curfont];
}


void CGLI_BitmapFont::glfStringCentering(GLboolean center)
{
    m_string_center = center;
}

GLboolean CGLI_BitmapFont::glfGetStringCentering()
{
    return m_string_center;
}
