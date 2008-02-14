/***************************************************************************
 *   Copyright (C) 2008 by tyler   *
 *   tyler@khand   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "globals.h"

#define _MAX_TAM 1024 
/*! Utilizamos esta estructura para cargar TGA. */
typedef struct
{
  GLubyte *imageData;
  GLuint bpp;
  GLuint width;
  GLuint height;
  GLuint texID;
} Imagen;

typedef unsigned char byte;
typedef GLubyte rgbapacket[4];
typedef struct pcx_header_tag
{

  byte manufacturer;
  byte version;
  byte encoding;
  byte bpp;
  short int size[4];
  short int res[2];
  byte colormap[48];
  byte reserved;
  byte nplanes;
  unsigned short int bpl;
  unsigned short int pa_info;
  byte filler[58];
} pcx_h;


/*! Carga un TGA en memoria. El TGA debe cumplir las siguientes características:
Ser de 24 bits + Canal ALPHA. (32 bits) y SIN COMPRIMIR
El tamaño debe ser cuadrado (x=y) y 32x32 o 64x64 o 128x128 o 256x256
Devuelve un puntero a la imagen y el tamaño (variable tam) de la imagen.*/

void *
CargaTGA (char filename[], int *tam_x, int *tam_y)
{
  GLubyte TGAheader[12] = { 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  GLubyte TGAheaderc[12] = { 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  GLubyte TGAcompare[12];
  GLubyte header[6];
  GLuint bytesPerPixel;
  GLuint imageSize;
  GLuint temp, i;
  GLuint type = GL_RGBA;
  Imagen texture;
  GLubyte *aux;

  GLubyte *data;
  GLubyte *datos;
  byte buffer;
  rgbapacket buf;
  byte count;
  byte done = 0;
  unsigned int tc, j,totalc,lines;

  char aux2[2048];
  FILE *fichero,*output;



  fichero = fopen (filename, "rb");


  /* Esto abre y comprueba que es un TGA */

  fread (TGAcompare, 1, sizeof (TGAcompare), fichero);

  if (memcmp (TGAheader, TGAcompare, sizeof (TGAheader)) == 0)
    {

      /* Esto es un TGA no comprimido */
      /* Leemos la cabecera */

      fread (header, 1, sizeof (header), fichero);

      /* Determinamos el tamaño */

      texture.width = header[1] * 256 + header[0];
      texture.height = header[3] * 256 + header[2];


      /* Vemos las características y comprobamos si son correctas */
      if (texture.width <= 0 ||
	  texture.height <= 0 ||
	  texture.width > _MAX_TAM ||
	  texture.height != texture.width || (header[4] != 32))
	{
	  printf("File not valid\n");
	  fclose (fichero);
	  return NULL;
	}


      /* Calculamos la memoria que será necesaria */

      texture.bpp = header[4];
      bytesPerPixel = texture.bpp / 8;
      imageSize = texture.width * texture.height * bytesPerPixel;


      /* Reservamos memoria */
      texture.imageData = (GLubyte *) malloc (imageSize);

      /* Cargamos y hacemos alguna comprobaciones */

      if (texture.imageData == NULL ||
	  fread (texture.imageData, 1, imageSize, fichero) != imageSize)
	{
	  if (texture.imageData != NULL)
	    free (texture.imageData);

	  fclose (fichero);
	  return NULL;
	}


      /* El TGA viene en formato BGR, lo pasamos a RGB */
      for (i = 0; i < (GLuint) (imageSize); i += bytesPerPixel)
	{
	  temp = texture.imageData[i];
	  texture.imageData[i] = texture.imageData[i + 2];
	  texture.imageData[i + 2] = temp;
	}


      fclose (fichero);

      /* Ahora, cambiamos el orden de las líneas, como si hiciesemos
         un flip vertical. */

      aux = (GLubyte *) malloc (imageSize);
      for (i = 0; i < texture.height; i++)
	memcpy (&aux[imageSize - ((i + 1) * texture.width * 4)],
		&texture.imageData[i * texture.width * 4], texture.width * 4);

      /* tam devolverá el tamaño */
      *tam_x = texture.width;
      *tam_y = texture.height;
      /* Liberamos memoria */
      free (texture.imageData);

      /* Todo fue bien! */
      return aux;
    }
  else if (memcmp (TGAheaderc, TGAcompare, sizeof (TGAheader)) == 0)
    {

      /* Esto es un TGA comprimido */
      /* Leemos la cabecera */

      fread (header, 1, sizeof (header), fichero);

      /* Determinamos el tamaño */

      texture.width = header[1] * 256 + header[0];
      texture.height = header[3] * 256 + header[2];


      /* Vemos las características y comprobamos si son correctas */
      if (texture.width <= 0 ||
	  texture.height <= 0 ||
	  texture.width > _MAX_TAM ||
	  texture.height != texture.width || (header[4] != 32))
	{
	  printf("File not valid (TGA compressed) width:%d header:%c\n",texture.width,&header[4]);
	  fclose (fichero);
	  return NULL;
	}


      /* Calculamos la memoria que será necesaria */

      texture.bpp = header[4];
      bytesPerPixel = texture.bpp / 8;
      imageSize = texture.width * texture.height * bytesPerPixel;
      *tam_x = texture.width;
      *tam_y = texture.height;




      /* Reservamos memoria */
      data = (GLubyte *) malloc (imageSize);

      /* Cargamos y hacemos alguna comprobaciones */

       output=fopen("salida.pnm","wb");
      fprintf(output,"P6\n256 256\n255\n");


      fread (&buffer, 1, 1, fichero);

      tc = 0;
      totalc=0;lines=0;

      /* Compresión RLE */
      while (!feof(fichero))
  	{
	  if ((buffer > 127))        // Paquete RLE
	    {
	      /* Los siguientes 7 bits indican cuantas veces repetir el siguiente pixel */
	      count = buffer & 127;
        count++;
        fread (&buf, sizeof(rgbapacket), 1, fichero); // Leemos el pixel
    	  for (j = 0; j < count; j++)
	      {

          data[tc] = buf[0];
	        tc++;
	        data[tc] = buf[1];
	        tc++;
	        data[tc] = buf[2];
	        tc++;
	        data[tc] = buf[3];
          tc++;
        }
	    }
	  else {                            // Paquete RAW
        count = buffer & 127;
        count++;
        fread (&data[tc],4,count , fichero); // Leemos count pixels
        tc+=count*4;
	
    }
        fread (&buffer, 1, 1, fichero);
	
  }

   for (i = 0; i < tc; i += bytesPerPixel)
	{
	  temp = data[i];
	  data[i] = data[i + 2];
	  data[i + 2] = temp;
	}

/* Ahora, cambiamos el orden de las líneas, como si hiciesemos
         un flip vertical. */

      aux = (GLubyte *) malloc (imageSize);
      for (i = 0; i < texture.height; i++)
	memcpy (&aux[imageSize - ((i + 1) * texture.width * 4)],
		&data[i * texture.width * 4], texture.width * 4);

   free(data);
   return aux;



}


  else
    return NULL;
}


void *
CargaPCX (char filename[], int *x, int *y)
{

  FILE *input;


  pcx_h input_h;
  unsigned char *data;
  GLubyte *datos, *aux;
  byte buffer;
  byte count, i;
  byte done = 0;
  byte paleta[256][3];
  int tam_x, tam_y, tc, j;


  input = fopen (filename, "rb");
  printf ("Tamaño cabecera PCX %d bytes\n", sizeof (pcx_h));
  fread (&input_h, sizeof (pcx_h), 1, input);

  printf ("Información...\n");
  printf ("Magic Number: %d\n", input_h.manufacturer);
  printf ("Version: %d\n", input_h.version);
  printf ("Encoding: %d\n", input_h.encoding);
  printf ("Bits per Pixel: %d\n", input_h.bpp);
  printf ("Bytes per Line: %d\n", input_h.bpl);
  printf ("Pal. info: %d\n", input_h.pa_info);
  printf ("(%d,%d)-(%d,%d)\n", input_h.size[0], input_h.size[1],
	  input_h.size[2], input_h.size[3]);
  printf ("X res: %d\n", input_h.res[0]);
  printf ("Y res: %d\n", input_h.res[1]);

  tam_x = input_h.size[2] - input_h.size[0] + 1;
  tam_y = input_h.size[3] - input_h.size[1] + 1;

  data = (unsigned char *) malloc (tam_x * tam_y);


  fread (&buffer, 1, 1, input);
  tc = 0;
  /* Compresión RLE */
  while (done == 0)
    {
      if ((buffer & 192) == 192)
	{
	  /* Los siguientes 6 bits indican cuantas veces repetir el siguiente byte */
	  count = buffer & 63;
	  fread (&buffer, 1, 1, input);
	  if (count == 0)
	    count++;
	}
      else
	count = 1;

      for (i = 0; i < count; i++)
	{
	  data[tc] = buffer;
	  tc++;
	}
      if (tc == tam_x * tam_y)
	done = 1;
      else
	fread (&buffer, 1, 1, input);
      if (feof (input))
	done = 1;
    }

  /*   El PCX ya está decodificado. Ahora debemos leer la paleta   */
  fread (&buffer, 1, 1, input);
  if (buffer == 12)
    printf ("Paleta detectada..ok\n");

  printf ("Colores en la paleta %d\n", fread (paleta, 3, 256, input));
  datos = (GLubyte *) malloc (tam_x * tam_y * 4);
  aux = datos;

  for (j = 0; j < tc; j++)
    {
      *datos = paleta[(GLubyte) data[j]][0];
      datos++;
      *datos = paleta[(GLubyte) data[j]][1];
      datos++;
      *datos = paleta[(GLubyte) data[j]][2];
      datos++;
      *datos = 255;
      datos++;			// PCX no tienen canal ALPHA
    }

  printf ("\nTotal bytes a memoria %d . Deberían ser: %d\n", j * 4 + 3,
	  tam_x * tam_y * 4);
  fclose (input);
  *x = tam_x;
  *y = tam_y;
  return aux;
}
