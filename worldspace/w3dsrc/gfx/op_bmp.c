//==========================================================================
//  op_bmp.c  -  Carga de imagenes en formatos BMP
//
//  begin     : sat apr 12 2003 / sab 12 abr 2003
//  copyright : (C) 2003 by Grupo WorldSpace
//  email     : eric@users.berlios.de
//==========================================================================
//                                                                         *
//   This program is free software; you can redistribute it and/or modify  *
//   it under the terms of the GNU General Public License as published by  *
//   the Free Software Foundation; either version 2 of the License, or     *
//   (at your option) any later version.                                   *
//                                                                         *
//==========================================================================

#include "memoria.h"
#include "globales.h"
#include "sdl_gl.h"
#include "op_bmp.h"
#include <string.h>
#include <math.h>

//==========================================================================
// Carga un fichero BMP. Devuelve un puntero al bitmap si hay exito,
// y NULL si no.
// Aquí se utiliza la función de SDL de carga de BMP: SDL_LoadBMP.
// Suministramos otra función que no utiliza la carga de SDL.
//==========================================================================
SDL_Surface * carga_bmp_SDL (char *sFichero)
{
    int i, j;
    Uint8 * rowhi, *rowlo;
    Uint8 * tmpbuf, tmpch;

    SDL_Surface *image;

	T_FUNC_IN;

    image = SDL_LoadBMP(sFichero);
    if ( image == NULL )
	{
        log_msj( "\n Incapaz de cargar %s: %s\n", sFichero, SDL_GetError());
        _return (NULL);
    }

    /* GL surfaces are upsidedown and RGB, not BGR :-) */
    tmpbuf = (Uint8 *)dar_m(image->pitch);
    rowhi = (Uint8 *)image->pixels;
    rowlo = rowhi + (image->h * image->pitch) - image->pitch;
    for ( i=0; i<image->h/2; ++i ) {
        for ( j=0; j<image->w; ++j ) {
            tmpch = rowhi[j*3];
            rowhi[j*3] = rowhi[j*3+2];
            rowhi[j*3+2] = tmpch;
            tmpch = rowlo[j*3];
            rowlo[j*3] = rowlo[j*3+2];
            rowlo[j*3+2] = tmpch;
        }
        memcpy(tmpbuf, rowhi, image->pitch);
        memcpy(rowhi, rowlo, image->pitch);
        memcpy(rowlo, tmpbuf, image->pitch);
        rowhi += image->pitch;
        rowlo -= image->pitch;
    }
    liberar_m(tmpbuf);

    _return (image);
}


//===========================================================================
// Carga un fichero BMP. Devuelve un puntero al bitmap si hay exito,
// y NULL si no.
// Utilizo métodos de lectura del libro "Programación en OpenGL"
//===========================================================================
static miBitmap * info;
//===========================================================================
void * carga_bmp ( char * sFichero, int * TamX, int * TamY )
{
	FILE   * fp;		 // Open file pointer 
	void   * bits;		 // Bitmap pixel bits
	size_t   bitsize,	 // Size of bitmap
			 infosize,	 // Size of header information
			 bytleidos;  // Número de bytes leidos
	miBitmapFicCab	header = { 0x00, 0x0000, 0x00, 0x00, 0x0000 };  // File header
	miByte14		headerLec;

	T_FUNC_IN;

	// Try opening the file; use "rb" mode to read this *binary* file.
	fp = abre_fichero(sFichero, "rb");
	if (fp == NULL)
	{ _return (NULL); }

	// No puedo hacer una lectura con header como miBitmapFicCab
	// Nos fabricamos : miByte14		headerLec;
	// --
	// Para no utilizar el mismo nombre que en windows he definido
	// BITMAPFILEHEADER como miBitmapFicCab para que sea común con Linux.
	// El caso es que el sizeof de cada uno da diferente con los mismos
	// contenidos ???????????????!!!!!!!!!!!!!!!!!!
	// El sizeof(BITMAPFILEHEADER) = 14 y se supone que miBitmapFicCab
	// lo hemos definido igual
	// pero resulta que sizeof(miBitmapFicCab) = 16 !!!!!????????
	//
	// Así que meto a pedal el valor esperado :: 14  con miByte14
	// o con sizeof(headerLec)
	//

	// Read the file header and any following bitmap information...
	bytleidos = fread(&headerLec, sizeof(headerLec), 1, fp);
	if (bytleidos < 1)
	{
		log_msj("\n Lectura de la cabecera de Bitmap [%s]",sFichero);
		fclose(fp);
		_return (NULL);
	};

	header.bfTipo = headerLec.bCad[1] * 0x100 +	headerLec.bCad[0];
	header.bfSize = headerLec.bCad[5] * 0x1000000 +
					headerLec.bCad[4] * 0x10000+
					headerLec.bCad[3] * 0x100 +
					headerLec.bCad[2];
	header.bfReservado1 = headerLec.bCad[7] * 0x100 + headerLec.bCad[6];
	header.bfReservado2 = headerLec.bCad[9] * 0x100 + headerLec.bCad[8];
	header.bfBitsSuma = headerLec.bCad[13] * 0x1000000 +
						headerLec.bCad[12] * 0x10000+
						headerLec.bCad[11] * 0x100 +
						headerLec.bCad[10];

	// (headerLec.bCad[0] != 'B' || headerLec.bCad[1] != 'M')  // "BM" o  M * 256 + B
	if (header.bfTipo != VALOR_MB)  // Check for BM reversed ...
	{
		log_msj("\n Este fichero [%s] no es de tipo bitmap",sFichero);
		fclose(fp);
		_return (NULL);
	}

	infosize = header.bfBitsSuma - sizeof(headerLec);

	info = (miBitmap *) dar_m(infosize);
	if ( info == NULL)
	{
		log_msj("\n Memoria para el 'Info' del Bitmap: %s",sFichero);
		fclose(fp);
		_return (NULL);
	}

	bytleidos = fread(info, 1, infosize, fp);
	if ( bytleidos < infosize)
	{
		log_msj("\n Lectura de Info. del Bitmap [%s]",sFichero);
		info = liberar_m (info);
		fclose(fp);
		_return (NULL);
	}

	// Now that we have all the header info read in, allocate memory for the
	// bitmap and read *it* in...
	*TamX = info->bmiHeader.biAncho;
	*TamY = info->bmiHeader.biAlto;

	bitsize = info->bmiHeader.biSizeImagen;
	if (bitsize == 0)
		 bitsize = (*TamX * info->bmiHeader.biCuentaBits + 7) / 8 * abs(*TamY);

	info = liberar_m(info);
	bits = dar_m (bitsize);
	if (bits == NULL)
	{
		log_msj("\n Memoria para la imagen del Bitmap: %s",sFichero);
		fclose(fp);
		_return NULL;
	}

	bytleidos = fread(bits, 1, bitsize, fp);
	if (bytleidos < bitsize)
	{
		log_msj("\n Lectura de la imagen del Bitmap [%s]",sFichero);
		bits  = liberar_m(bits);		// bits = NULL, con lo que se devuelve NULL
	}

	fclose(fp);
	_return bits;
}


//==========================================================================
//  Fin de op_bmp.c
//==========================================================================
