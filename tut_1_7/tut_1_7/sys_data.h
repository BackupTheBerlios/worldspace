/***************************************************************************
                          sys_data.h  -  datos globales del sistema
                             -------------------
    begin                : mié jul 10 2002
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



/*! Inicialización-Cierre del sistema */

extern int system_init(void);					
extern int system_close(void);

/*! Variable para almacenar la configuración */
extern configuracion config;	

/*! Salida de mensajes */
extern FILE *logs;		
