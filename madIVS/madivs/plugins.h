/***************************************************************************
                          plugins.h  -  description
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
  
#include "globales.h"
extern int buscar_plugins (char *dir, plugin_info * plugin_tag);
extern int importar_modelo (int n_plugin, char *file);
