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
#include <stdlib.h>
#include "gli_texture_tga.h"

//==///////////////////////////////////////////////////////////////////////////////==
//                           Loading TGA Images
//==///////////////////////////////////////////////////////////////////////////////==

// This function reads TGA file
GLubyte *read_texture_tga(char *filename, int *width, int *height,
                          int *components)
{
    FILE *f;
    unsigned char Header[18];   // TGA file header
    GLubyte *image;
    GLubyte b;
    int image_size;

    if (!(f = fopen(filename, "rb"))) {
        fclose(f);
        return NULL;
    }
    // Read TGA header
    if (fread(Header, 1, 18, f) != 18) {
        // Some error while reading header
        fclose(f);
        return NULL;
    }
    // Check the header, at time supported only uncompressed true color TGA image
    if ((Header[1] != 0) && (Header[2] != 2)) {
        // Not supported TGA file
        fclose(f);
        return NULL;
    }

    *width = (int) Header[13] * 256 + Header[12];
    *height = (int) Header[15] * 256 + Header[14];

    // Check that we have true color, non-empty image
    if ((*width == 0) || (*height == 0) || (Header[16] < 24)) {
        // Not supported TGA file
        fclose(f);
        return NULL;
    }

    if (Header[16] == 24)
        *components = 3;
    else
        *components = 4;

    // Skip ID info (if present)
    fseek(f, Header[0], SEEK_CUR);

    image_size = (*width) * (*height) * (*components);

    // Allocate memory for image
    image = (GLubyte *) malloc(image_size);

    if (!image) {
        // Not enought memory for image
        fclose(f);
        return NULL;
    }

    if ((int) fread(image, 1, image_size, f) != image_size) {
        // error in TGA file
        free(image);
        fclose(f);
        return NULL;
    }
    // Translate from BGR->RGB
    for (int i = 0; i < image_size; i += (*components)) {
        b = image[i];
        image[i] = image[i + 2];
        image[i + 2] = b;
    }

    fclose(f);

    return image;
}
