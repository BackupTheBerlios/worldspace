/***************************************************************************
                          globales.h  -  description
                             -------------------
    begin                : jue jun 13 2002
    copyright            : (C) 2002 by neuralgya
    email                : neuralgya@mail.berlios.de
 ***************************************************************************/
 
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/ 
  
#define VERSION_MAJ 0
#define VERSION_MIN 1
  
#include "estructuras.h"
#include <v/vbglcnv.h>
  
#ifndef _PLUGIN_INFO
#define _PLUGIN_INFO
  typedef struct plugin_info_tag
{
  char nombre[128];
   int version[3];
   char autor[128];
   int fecha[3];
   char info[1024];
   char fich[2048];
   char extension[1024];
 } plugin_info;

#endif /*  */
extern plugin_info *plugins;
extern int numero_plugins;
extern char **extensiones;

/* Flags*/ 
extern char textura_cargada;
extern char modelo_cargado;
extern char modo_dibujo;
extern char luces;
extern modelo *model;
extern GLuint textura;
extern char RUNPATH[];

