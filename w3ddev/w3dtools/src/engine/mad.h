/***************************************************************************
                          mad.h  -  Funciones exportadas por mad.c
                             -------------------
    begin                : sáb ene 11 2003
    copyright            : (C) 2003 by neuralgya
    email                : neuralgya@users.berlios.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
  ***************************************************************************/


#include "w3d_base.h"

extern modelo *carga_mad(char *file);
extern int render_mad(modelo * mad);
