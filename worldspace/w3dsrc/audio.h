/***************************************************************************
                          audio.h  -  funciones relativas al audio
                             -------------------
    begin                : Sab mar 8 2003
    copyright          : (C) 2003 by Grupo WorldSpace
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
 

 /*!
=================================================================
Funcion         : ini_audio ( )
Objetivo         : Esta funcion mira los dispositivos/drivers disponibles y
                          asigna un contexto para que funcione OpenAL
Parametros    : No hay que pasarle ningun parametro
=================================================================
*/
extern int ini_audio(void);

/*!
=================================================================
Funcion        : cerrar_audio ( )
Objetivo        : Esta funcion destruye el contexto creado y desconecta
                        del dispositivo de audio
Parametros   : No hay que pasarle ningun parametro
=================================================================
*/

extern int cerrar_audio (void);
