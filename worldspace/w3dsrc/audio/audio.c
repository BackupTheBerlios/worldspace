#include <stdio.h>
#include <stdlib.h>
#include "audio.h"

/*!
================================== DECLARACION DE VARIABLES
!*/
ALCdevice *Device = NULL;       /* Dispositivo de sonido */

#ifdef _LINUX
    ALvoid * Context = NULL;    /* Contexto para Linux */

#endif  /*  */
#ifdef _WIN32
    ALCcontext * Context = NULL;        /* Contexto para Windows */

#endif
int inicializar_audio()
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
                    log_msj
                        ("No hay disponible ningun dispositivo de audio\n");
                    return NO;
                }
            }
        }
    }
    
#endif  /*  */
#ifdef _WIN32
        if ((Device = alcOpenDevice((ALubyte *) "DirectSound3D")) == NULL) {
        log_msj("No existe DirectSound3D Backend\n");
        if ((Device = alcOpenDevice((ALubyte *) "DirectSound")) == NULL) {
            log_msj("No existe DirectSound Backend\n");
            if ((Device = alcOpenDevice((ALubyte *) "WaveOut")) == NULL) {
                log_msj("No existe WaveOut Backend\n");
                if ((Device = alcOpenDevice(NULL)) == NULL) {
                    log_msj
                        ("No hay disponible ningun dispositivo de audio\n");
                    return NO;
                }
            }
        }
    }
    
#endif  /*  */
        
        /* Creamos un contexto y lo asignamos (comprobando si hay errores) */ 
        if (Device != NULL) {
        Context = alcCreateContext(Device, NULL);      /* Creamos */
        if (alcGetError(Device) != ALC_NO_ERROR) {
            log_msj
                ("No se puede crear un contexto para el sistema de audio\n");
            return NO;
        }
        alcMakeContextCurrent(Context);       /* Asignamos */
        if (alcGetError(Device) != ALC_NO_ERROR) {
            log_msj
                ("No se puede asignar el contexto para el sistema de audio\n");
            return NO;
        }
    }
    return SI;
}
