#include <stdio.h>
#include <stdlib.h>
#include "w3d_base.h"
#include "globales.h"
#ifdef _LINUX
#include <AL/al.h>
#include <AL/alc.h>
#include "alut.h"
#endif
#ifdef _WIN32
#include <AL\al.h>
#include <AL\alc.h>
#include "alut.h"
#include <AL\eax.h>
#endif

/*!
================================== DECLARACION DE VARIABLES
!*/
ALCdevice *Device = NULL;       /* Dispositivo de sonido */
#ifdef _LINUX
ALvoid * Context = NULL;    /* Contexto para Linux */
#endif  
#ifdef _WIN32
ALCcontext * Context = NULL;        /* Contexto para Windows */
#endif


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
        /* Asignamos el mejor dispositivo de audio disponible */ 
#ifdef _LINUX
  if ((Device = alcOpenDevice((ALubyte *) "alsa")) == NULL) {
    log_msj("No existe ALSA Backend\n");
    if ((Device = alcOpenDevice((ALubyte *) "emu10k1")) == NULL) {
      log_msj("No existe Sound Blaster Live Backend\n");
      if ((Device = alcOpenDevice((ALubyte *) "waveout")) == NULL) {
        log_msj("No existe waveout Backend\n");
        if ((Device = alcOpenDevice(NULL)) == NULL) {
          log_msj ("No hay disponible ningun dispositivo de audio\n");
          return NO;
        }
      }
    }
  }
#endif
#ifdef _WIN32
  if ((Device = alcOpenDevice((ALubyte *) "DirectSound3D")) == NULL) {
    log_msj("No existe DirectSound3D Backend\n");
    if ((Device = alcOpenDevice((ALubyte *) "DirectSound")) == NULL) {
      log_msj("No existe DirectSound Backend\n");
      if ((Device = alcOpenDevice((ALubyte *) "WaveOut")) == NULL) {
        log_msj("No existe WaveOut Backend\n");
        if ((Device = alcOpenDevice(NULL)) == NULL) {
          log_msj ("No hay disponible ningun dispositivo de audio\n");
          return NO;
        }
      }
    }
  }
#endif 
        
  /* Creamos un contexto y lo asignamos (comprobando si hay errores) */ 
  if (Device != NULL) {
    Context = alcCreateContext(Device, NULL);      /* Creamos */
    if (alcGetError(Device) != ALC_NO_ERROR) {
      log_msj ("No se puede crear un contexto para el sistema de audio\n");
      return NO;
    }
    alcMakeContextCurrent(Context);       /* Asignamos */
    if (alcGetError(Device) != ALC_NO_ERROR) {
      log_msj ("No se puede asignar el contexto para el sistema de audio\n");
      return NO;
    }
  }

  return SI;
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
	alcMakeContextCurrent ( NULL ); /* Desactivamos el contexto */
	alcDestroyContext ( Context ); /* Destruimos el contexto */
	alcCloseDevice ( Device ); /* Cerramos el dispositivo */
    log_msj ("El dispositivo de audio se ha cerrado correctamente\n");

    return SI;
}
