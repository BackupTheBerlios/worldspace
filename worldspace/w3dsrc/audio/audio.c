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
  if ((Device = alcOpenDevice((ALubyte *) "'alsa")) == NULL) {
    log_msj("No existe ALSA Backend\n");
    if ((Device = alcOpenDevice((ALubyte *) "sdl")) == NULL) {
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

  log_msj("[OK] OpenAL se ha iniciado correctamente\n");
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
  log_msj ("[OK] OpenAL se ha cerrado correctamente\n");

  _return SI;
}
