/***************************************************************************
                          audio.c  -  description
                             -------------------
    begin                : dom mar 9 2003
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


#include <stdio.h>
#include <stdlib.h>
#include "w3d_base.h"
#include "globales.h"
#include "audio.h"


/*!
================================== DECLARACION DE VARIABLES
!*/
ALCdevice *Device = NULL;       /* Dispositivo de sonido */
ALCcontext *Context = NULL;    /* Contexto */


/*!
================================== DECLARACION DE FUNCIONES
!*/
 /*!
=================================================================
Funcion         : ini_audio ( )
Objetivo         : Esta funcion mira los dispositivos/drivers disponibles y
                          asigna un contexto para que funcione OpenAL
Parametros    : No hay que pasarle ningun parametro
=================================================================
*/
int ini_audio(void)
{
  T_FUNC_IN
        /* Asignamos el mejor dispositivo de audio disponible */ 
#ifdef _LINUX
  if ((Device = alcOpenDevice((ALubyte *) "sdl")) == NULL) {
    log_msj("No existe ALSA Backend\n");
    if ((Device = alcOpenDevice((ALubyte *) "alsa")) == NULL) {
      log_msj("No existe SDL Backend\n");
#endif
#ifdef _WIN32
  if ((Device = alcOpenDevice((ALubyte *) "DirectSound3D")) == NULL) {
    log_msj("No existe DirectSound3D Backend\n");
    if ((Device = alcOpenDevice((ALubyte *) "DirectSound")) == NULL) {
      log_msj("No existe DirectSound Backend\n");
#endif
      if ((Device = alcOpenDevice((ALubyte *) "waveout")) == NULL) {
        log_msj("No existe waveout Backend\n");
        if ((Device = alcOpenDevice(NULL)) == NULL) {
          log_msj ("[KO] No hay disponible ningun dispositivo de audio\n");
          return NO;
        }
      }
    }
  }
         
  /* Creamos un contexto y lo asignamos (comprobando si hay errores) */ 
  if (Device != NULL) {
    Context = alcCreateContext(Device, NULL);      /* Creamos */
    if (alcGetError(Device) != ALC_NO_ERROR) {
      log_msj ("[KO] No se puede crear un contexto para el sistema de audio\n");
      return NO;
    }
    alcMakeContextCurrent(Context);       /* Asignamos */
    if (alcGetError(Device) != ALC_NO_ERROR) {
      log_msj ("[KO] No se puede asignar el contexto para el sistema de audio\n");
      return NO;
    }
  }

  /* Ahora inicializamos Mikmod */
      
  /* Registramos el driver OpenAL */
  MikMod_RegisterDriver(&drv_sdl);

  /* Registramos los diferentes formatos (it, s3m, xm y mod) */
  MikMod_RegisterAllLoaders();


  /* Inicializamos la libreria */
  if (MikMod_Init("")) {
    log_msj ("No se puede inicializar Mikmod: %s\n",MikMod_strerror(MikMod_errno));
    return NO;
  }

  log_msj("[OK] OpenAL y Mikmod se han inicializado correctamente\n");
  _return SI;
}

/*!
=================================================================
Funcion        : cerrar_audio ( )
Objetivo        : Esta funcion destruye el contexto creado y desconecta
                        del dispositivo de audio
Parametros   : No hay que pasarle ningun parametro
=================================================================
*/

int cerrar_audio (void){
    
  T_FUNC_IN
  
  alcMakeContextCurrent ( NULL ); /* Desactivamos el contexto */
  alcDestroyContext ( Context ); /* Destruimos el contexto */
  alcCloseDevice ( Device ); /* Cerramos el dispositivo */
  MikMod_Exit();  /* Cerramos Mikmod */  
  log_msj ("[OK] OpenAL y Mikmod se han cerrado correctamente\n");

  _return SI;
}
