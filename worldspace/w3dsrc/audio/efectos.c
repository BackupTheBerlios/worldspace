/***************************************************************************
                          efectos.c  -  description
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


/* Aqui definimos el nº de sonidos, musicas, entornos y listeners que vamos a utilizar */

#define NUM_SONIDOS     1
#define NUM_LISTENER    1
#ifdef _LINUX
#define NUM_ENTORNOS    1
#endif

/* Definimos estructura del listener y lo creamos */
typedef struct {
	ALfloat    Posicion[3];
	ALfloat    Velocidad[3];
	ALfloat    Orientacion[6];
}LISTENER;

LISTENER Listener[NUM_LISTENER];
static ALuint buffer[NUM_SONIDOS];
static ALuint source[NUM_SONIDOS];
#ifdef _LINUX
static ALuint entornos[NUM_ENTORNOS];
#endif

 /*!
 ======================================================================
Funcion       : actualizar_listener ( ALuint num, ALfloat x_pos, ALfloat y_pos,
                           ALfloat z_pos, ALfloat x_vel, ALfloat y_vel, ALfloat z_vel,
                           ALfloat x_sup, ALfloat y_sup, ALfloat z_sup, ALfloat x_fro,
                           ALfloat y_fro, ALfloat z_fro )
Objetivo       : Esta funcion actualiza los parametros del listener y
                     facilita la posibilidad de pasarle los datos de
                     posicion, velocidad y orientacion del player
Parametros : Hay que pasarle 13 parametros

ALuint  num --> El numero del listener
ALfloat x_pos --> La posicion en el eje x del listener/player
ALfloat y_pos --> La posicion en el eje y del listener/player
ALfloat z_pos --> La posicion en el eje z del listener/player
ALfloat x_vel --> La velocidad en el eje x del listener/player
ALfloat y_vel --> La velocidad en el eje y del listener/player
ALfloat z_vel --> La velocidad en el eje z del listener/player
ALfloat x_sup --> Direccion vector saliente perpendicular a la cabeza (hacia arriba) en x
ALfloat y_sup --> Direccion vector saliente perpendicular a la cabeza (hacia arriba) en y
ALfloat z_sup --> Direccion vector saliente perpendicular a la cabeza (hacia arriba) en z
ALfloat x_fro --> Direccion vector saliente perpendicular a los ojos (hacia delante) en x
ALfloat y_fro --> Direccion vector saliente perpendicular a los ojos (hacia delante) en y
ALfloat z_fro --> Direccion vector saliente perpendicular a los ojos (hacia delante) en z
=========================================================================
*/

void actualizar_listener ( ALuint num, ALfloat x_pos, ALfloat y_pos,
                      ALfloat z_pos, ALfloat x_vel, ALfloat y_vel, ALfloat z_vel,
			    ALfloat x_sup, ALfloat y_sup, ALfloat z_sup, ALfloat x_fro,
			    ALfloat y_fro, ALfloat z_fro ) {

	/* Asignamos valores a los posibles listener */
	Listener[num].Posicion[0] = x_pos;
	Listener[num].Posicion[1] = y_pos;
	Listener[num].Posicion[2] = z_pos;
	Listener[num].Velocidad[0] = x_vel;
	Listener[num].Velocidad[1] = y_vel;
	Listener[num].Velocidad[2] = z_vel;
	Listener[num].Orientacion[0] = x_sup;
	Listener[num].Orientacion[1] = y_sup;
	Listener[num].Orientacion[2] = z_sup;
	Listener[num].Orientacion[3] = x_fro;
	Listener[num].Orientacion[4] = y_fro;
	Listener[num].Orientacion[5] = z_fro;

	/* Actualizamos el valor de la posicion, velocidad y orientacion */

	alListenerfv ( AL_POSITION, Listener[num].Posicion );
	alListenerfv ( AL_VELOCITY, Listener[num].Velocidad );
	alListenerfv ( AL_ORIENTATION, Listener[num].Orientacion );
}


/*!
===========================================================================
Funcion       : carga_sonido ( char *fichero_wav, ALuint identificador )
Objetivo      : Esta funcion carga un fichero WAVE en memoria y lo asigna
                    a una fuente (source)
Parametros : Hay que pasarle 2 parametros

char *fichero_wav --> Nombre del archivo de sonido que queremos cargar
ALuint identificador --> Para indicar que sonido hemos cargado
===========================================================================
*/

void  carga_sonido ( char *fichero_wav, int identificador ){

	/* Variables locales */
	ALsizei *size = NULL, *freq = NULL;
	static void **data = NULL;
    ALenum *format = NULL;
#ifdef _LINUX
    ALsizei *bits = NULL;
#endif
#ifdef _WIN32
	ALboolean loop = AL_FALSE;
#endif

	/* Generamos buffer, le asignamos un identificador y comprobamos errores */
	alGenBuffers( 1, &buffer[identificador] );
	if ( !alIsBuffer ( buffer[identificador] )){
		log_msj ( "[KO] error al crear los buffers\n");
	}

	/* Cargamos ficheros Wave */
#ifdef _LINUX
	alutLoadWAV ( fichero_wav, data, format, size, bits, freq ); /* Cargamos en memoria */
	alBufferData ( buffer[identificador], *format, data, *size, *freq ); /* Almacenamos en buffer */
	free (data); /* liberamos */
#endif
#ifdef _WIN32
	alutLoadWAVFile ( fichero_wav, format, data, size, freq, &loop );
	alBufferData ( buffer[identificador], *format, data, *size, *freq );
	alutUnLoadWAV ( *format, data, *size, *freq );
#endif

	/* Generamos las fuentes de sonido y comprobamos errores */
	alGenSources( 1, &source[identificador] );
	if ( !alIsSource ( source[identificador])){
		log_msj ("[KO] No se pueden crear las fuentes de sonido\n");
	}

	/* Pasamos el archivo wav del buffer a la fuente */
	alSourcei ( source[identificador], AL_BUFFER, buffer[identificador]);

}


/*!
=======================================================================================
Funcion    : reproducir_sonido ( ALuint identificador, ALfloat src_pos[3], ALfloat src_vel[3],
                           ALfloat ganancia, Alfloat pitch, ALboolean repeticion )
Objetivo   : Hace sonar el sonido especificado en la posicion y velocidad indicados
              y con la ganancia, frecuencia y repeticion que se les introduzca
Parametros : Hay que pasarle 6 parametros

ALuint identificador --> Para indicar que sonido queremos escuchar
ALfloat src_pos[3] --> Indica la posicion donde se va escuchar el sonido
ALfloat src_vel[3] --> Indica la velocidad del sonido
ALfloat ganancia --> Ganancia en amplitud de la fuente
ALfloat pitch --> Frecuencia de la fuente
ALboolean repeticion --> Si se repite o no
======================================================================================
*/

void reproducir_sonido ( int identificador, ALfloat src_pos[3], ALfloat src_vel[3],
		      ALfloat ganancia, ALfloat pitch,ALfloat distancia_maxima, ALboolean repeticion ){

	/* Configuramos la fuente con los parametros */
	alSourcefv ( source[identificador], AL_POSITION, src_pos); /* Posicion */
	alSourcefv ( source[identificador], AL_VELOCITY, src_vel); /* Velocidad */
	alSourcef ( source[identificador], AL_GAIN, ganancia); /* Ganancia */
	alSourcef ( source[identificador], AL_PITCH, pitch); /* Frecuencia */
	alSourcei ( source[identificador], AL_LOOPING, repeticion); /* Repeticion */
	alSourcef ( source[identificador],AL_MAX_DISTANCE,distancia_maxima);/* Distancia a partir de la cual no se oye */

	/* Hacemos que suene */
	alSourcePlay ( source[identificador] );
}


/*!
===============================================================================
Funcion      : actualizar_source ( ALuint identificador, ALfloat src_pos[3])
Objetivo     : Actualizar la posicion de la fuente para sonidos moviles,
                   como por ejemplo,el sonido del motor de una nave
Parametros : Hay que pasarle 2 parametros

ALuint identificador --> Para indicar que sonido queremos escuchar
ALfloat src_pos[3] --> Indica la posicion donde se va escuchar el sonido
===============================================================================
*/

void actualizar_source ( ALuint identificador, ALfloat src_pos[3]){

	/* Introducimos nueva posicion */
	alSourcefv ( source[identificador], AL_POSITION, src_pos);
}


/*!
================================================================================
Funcion       : configurar_entorno ( ALuint identificador, ALenum modelo,
                                  ALfloat doppler_factor, ALfloat doppler_vel,
                                  ALint room, Alint room_high_frequency,
                                  ALfloat rolloff_factor, ALfloat decay_time,
                                  ALfloat decay_high_frecuency_ratio, ALint reflections,
                                  ALfloat reflections_delay, ALint reverb,
                                  ALfloat reverb_delay, ALfloat diffusion,
                                  ALfloat density, ALfloat high_frequency_reference )
Objetivo      : Configurar nuestro entorno lo maximo posible para obtener los
                    efectos deseados
Parametros : Hay que pasarle 16 parametros

ALuint identificador --> Para indicar el entorno a configurar
ALenum modelo --> Indica el modelo de atenuacion por la distancia
ALfloat doppler_factor --> Indica el factor de escalado del efecto doppler
ALfloat doppler_vel --> Indica velocidad de propagacion
ALint room --> Tipo de entorno
Alint room_high_frequency --> La frecuencia
ALfloat rolloff_factor  --> El factor rolloff
ALfloat decay_time --> El tiempo de cese
ALfloat decay_high_frecuency_ratio --> El radio de cese de la frecuencia
ALint reflections --> La reflexion
ALfloat reflections_delay --> Cese de la reflexion
ALint reverb --> La reverberacion
ALfloat reverb_delay --> Retraso de la reverberacion
ALfloat diffusion --> La difusion
ALfloat density --> La densidad
ALfloat high_frequency_reference --> La referencia de la frecuencia
================================================================================
*/


void configurar_entorno ( ALsizei identificador, ALenum modelo,
                         ALfloat doppler_factor, ALfloat doppler_vel,
                         ALint room, ALint room_high_frequency,
                         ALfloat rolloff_factor, ALfloat decay_time,
                         ALfloat decay_high_frequency_ratio, ALint reflections,
                         ALfloat reflections_delay, ALint reverb,
                         ALfloat reverb_delay, ALfloat diffusion,
                         ALfloat density, ALfloat high_frequency_reference ){



	/* Configuramos la atenuacion y el efecto doppler */
	alEnable ( AL_DISTANCE_MODEL );
	alDistanceModel ( modelo );
	alDopplerFactor ( doppler_factor );
	alDopplerVelocity ( doppler_vel ); /* Recordad que en metros la velocidad del sonido es 343 */

#ifdef _LINUX
	/* Generamos el entorno y comprobamos errores */
	alGenEnvironmentIASIG ( identificador, &entornos[identificador] );
	if ( !alIsEnvironmentIASIG ( entornos[identificador] )){
		log_msj ("[KO] No se puede configurar parte del entorno\n");
	}

	/* Configuramos las propiedades del entorno */
	alEnvironmentiIASIG ( entornos[identificador], AL_ENV_ROOM_IASIG, room );
	alEnvironmentiIASIG ( entornos[identificador], AL_ENV_ROOM_HIGH_FREQUENCY_IASIG,
	                      room_high_frequency);

	alEnvironmentfIASIG ( entornos[identificador], AL_ENV_ROOM_ROLLOFF_FACTOR_IASIG, rolloff_factor );
	alEnvironmentfIASIG ( entornos[identificador], AL_ENV_DECAY_TIME_IASIG, decay_time );
	alEnvironmentfIASIG ( entornos[identificador], AL_ENV_DECAY_HIGH_FREQUENCY_RATIO_IASIG,
	                      decay_high_frequency_ratio );
	alEnvironmentiIASIG ( entornos[identificador], AL_ENV_REFLECTIONS_IASIG, reflections );
	alEnvironmentfIASIG ( entornos[identificador], AL_ENV_REFLECTIONS_DELAY_IASIG, reflections_delay );
	alEnvironmentiIASIG ( entornos[identificador], AL_ENV_REVERB_IASIG, reverb );
	alEnvironmentfIASIG ( entornos[identificador], AL_ENV_REVERB_DELAY_IASIG, reverb_delay );
	alEnvironmentfIASIG ( entornos[identificador], AL_ENV_DIFFUSION_IASIG, diffusion );
	alEnvironmentfIASIG ( entornos[identificador], AL_ENV_DENSITY_IASIG, density );
	alEnvironmentfIASIG ( entornos[identificador], AL_ENV_HIGH_FREQUENCY_REFERENCE_IASIG,
	                      high_frequency_reference );
#endif
#ifdef _WIN32
	/* Para windows se pueden crear y configurar entornos utilizando las extensiones EAX
	que admiten algunas tarjetas Soundblaster. Pero como no sé si es gratuito la utilizacion
	de dichas extensiones, de momento para windows no se generaran entornos
	*/
#endif
}
