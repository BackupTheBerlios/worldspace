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
 
#include <AL/al.h>
#include <AL/alc.h>
#include "alut.h"
#include <vorbis/codec.h>
#include <vorbis/vorbisfile.h>


 
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

extern void actualizar_listener ( ALuint num, ALfloat x_pos, ALfloat y_pos,
                      ALfloat z_pos, ALfloat x_vel, ALfloat y_vel, ALfloat z_vel,
			    ALfloat x_sup, ALfloat y_sup, ALfloat z_sup, ALfloat x_fro,
			    ALfloat y_fro, ALfloat z_fro );


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

extern void  carga_sonido ( char *fichero_wav, int identificador );


/*!
===========================================================================
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
===========================================================================
*/

extern void reproducir_sonido ( int identificador, ALfloat src_pos[3], ALfloat src_vel[3],
		      ALfloat ganancia, ALfloat pitch,ALfloat distancia_maxima, ALboolean repeticion );


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

extern void actualizar_source ( ALuint identificador, ALfloat src_pos[3]);


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


extern void configurar_entorno ( ALsizei identificador, ALenum modelo,
                         ALfloat doppler_factor, ALfloat doppler_vel,
                         ALint room, ALint room_high_frequency,
                         ALfloat rolloff_factor, ALfloat decay_time,
                         ALfloat decay_high_frequency_ratio, ALint reflections,
                         ALfloat reflections_delay, ALint reverb,
                         ALfloat reverb_delay, ALfloat diffusion,
                         ALfloat density, ALfloat high_frequency_reference );

/********************************************************
Funcion       : reproducir_musica ( )
Objetivo      : reproduce la musica seleccionada
Parametros :

int repeticion ---> -1 bucle infinito y 1,2,3.... numero de veces
                            que se repite
********************************************************/

extern int reproducir_musica ( int repeticion );

/******************************************************************************************************
Funcion       : actualizar_musica (  )
Objetivo      : Esta funcion rellena los buffers segun se van vaciando. Hay que llamarla
                    muy muy a menudo ya que es la que realmente realiza el streaming.
                    Preferiblemente hay que incluirla en un thread independiente.
Parametros : No hay que pasarle parametros
******************************************************************************************************/

extern int  actualizar_musica (void);

/***********************************************************************************************
Funcion      : resetear_musica (  )

Objetivo      : Esta funcion elimina la musica para poder cargar otro archivo OGG
Parametros : No hay que pasarle parametros
************************************************************************************************/

extern int resetear_musica (void);

/******************************************************
Funcion       : pausar_musica ( )
Objetivo      : Pausa la musica seleccionada
Parametros : No hay que pasarle parametros
******************************************************/

extern int pausar_musica (void);

/*****************************************************************************************
Funcion       : cargar_musica ( char *fichero_ogg )
Objetivo      : Esta funcion decodifica un fichero ogg y lo pasa a un buffer
                    en formato wav
Parametros : Hay que pasarle 2 parametros

char *fichero_ogg --> Nombre del archivo de musica que queremos cargar

*****************************************************************************************/

extern int cargar_musica ( char *fichero_ogg );
