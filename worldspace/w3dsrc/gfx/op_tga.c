//==========================================================================
//  op_tga.c  -  Carga de imagenes en formatos TGA
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
#include "op_tga.h"
#include <string.h>
//==========================================================================
//  CargaTGA de Neuralgya
//==========================================================================
//  ! Carga un TGA en memoria. El TGA debe cumplir las siguientes
//  características:
//   - Ser de 24 bits + Canal ALPHA. (32 bits) y SIN COMPRIMIR
//   - El tamaño debe ser cuadrado (x=y) y 32x32 o 64x64 o 128x128
//     o 256x256
//  Devuelve un puntero a la imagen y el tamaño (variable tam) de
//  la imagen.
//==========================================================================
//  Se está pidiendo funciones de carga de TGAs comprimidos
//  esta función no lo hace (?)
//==========================================================================
void * carga_tga  ( char * sFichero, int *tam_x, int *tam_y )
{
	GLubyte	  TGAheader[12]={0,0,2,0,0,0,0,0,0,0,0,0};			
	GLubyte	  TGAcompare[12];							
	GLubyte	  header[6];							
	GLuint	  bytesPerPixel;						
	GLuint	  imageSize;							
	GLuint	  temp,i;								
	GLubyte	* aux;      
	FILE    * fichero;

    miImagenTGA  rImgTga;

	T_FUNC_IN;

	fichero = abre_fichero (sFichero, "rb");
	if (fichero == NULL)
	{ _return NULL; }

	// Esto abre y comprueba que es un TGA.
	fread(TGAcompare,1,sizeof(TGAcompare),fichero);
	if (memcmp(TGAheader,TGAcompare,sizeof(TGAheader))!=0)
	{
		log_msj("\n No es un fichero TGA: %s",sFichero);
		fclose(fichero);
		_return NULL;
	}

    // Leemos la cabecera.
	fread(header,1,sizeof(header),fichero);

	// Determinamos el tamaño.
	rImgTga.width  = header[1] * 256 + header[0];		
	rImgTga.height = header[3] * 256 + header[2];		

	// Vemos las características y comprobamos si son correctas.
 	if(	rImgTga.width	<=0	||					
		rImgTga.height	<=0	||	
		rImgTga.width >256 ||
		rImgTga.height !=rImgTga.width ||
		( header[4]!=32))					
	{
		log_msj("\n Fichero TGA de características incorrectas: %s",sFichero);
		fclose(fichero);
		_return NULL;
	}

	// Calculamos la memoria que será necesaria.
	rImgTga.bpp	  = header[4];
	bytesPerPixel = rImgTga.bpp/8;
	imageSize	  = rImgTga.width*rImgTga.height*bytesPerPixel;

	// Reservamos memoria.
	rImgTga.imageData=(GLubyte *)dar_m(imageSize);
	if (rImgTga.imageData==NULL)
	{
		fclose(fichero);								
		_return NULL;								
	}

	// Cargamos y hacemos alguna comprobaciones.
	if (fread(rImgTga.imageData, 1, imageSize, fichero)!=imageSize)
	{
		log_msj("\n Lectura de la imagen del TGA: %s",sFichero);
		rImgTga.imageData = (GLubyte *)liberar_m(rImgTga.imageData);
		fclose(fichero);								
		_return NULL;								
	}

    // El TGA viene en formato BGR, lo pasamos a RGB.
	for(i=0; i<(GLuint)(imageSize); i+=bytesPerPixel)	
	{										
		temp=rImgTga.imageData[i];			
		rImgTga.imageData[i] = rImgTga.imageData[i + 2];
		rImgTga.imageData[i + 2] = temp;					
	}

	fclose (fichero);								
    
	// Ahora, cambiamos el orden de las líneas, como si hiciesemos
	// un flip vertical.
	aux=(GLubyte *)dar_m(imageSize);
	for(i=0; i<rImgTga.height; i++)			
		memcpy(&aux[imageSize-((i+1)*rImgTga.width*4)],
		       &rImgTga.imageData[i*rImgTga.width*4],
			   rImgTga.width*4);

	//	aux=rImgTga.imageData;
	// tam devolverá el tamaño.
	*tam_x=rImgTga.width;
	*tam_y=rImgTga.height;
	// Liberamos memoria.
	rImgTga.imageData = (GLubyte *) liberar_m(rImgTga.imageData);
	
	// Todo fue bien!
	_return aux;
}


//==========================================================================
//  Fin de op_tga.c
//==========================================================================
