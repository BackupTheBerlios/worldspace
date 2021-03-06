/***************************************************************************
  musica_ogg.c  funciones para la carga y reproduccion de archivos Ogg Vorbis
                             -------------------
    begin                : Jue mar 13 2003
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
#include <string.h>
#include "w3d_base.h"
#include "globales.h"
#include "sdl_gl.h"
#include "musica_ogg.h"

/* Estos defines puede que se cambien en un futuro */
#define NUM_BUFFER_MUSICA 70
#define BUFFER_MUSICA 256


ALenum formato; /* Utilizado en la carga de archivos OGG */
OggVorbis_File buff;
int repeticion;
int current_section = -1;
vorbis_info *informacion = NULL;

ALuint streambuffers[NUM_BUFFER_MUSICA]; /* Utilizado en la carga de archivos OGG */
ALshort waveout [BUFFER_MUSICA];  /* Donde almacenamos los OGG Vorbis decodificados */
ALuint streamsource[1]; /* Utilizado en la carga de archivos OGG */
SDL_Thread *threadmusica; /* Thread de audio */

/*****************************************************************************************
Funcion       : cargar_ogg ( char *fichero_ogg )
*****************************************************************************************/

int cargar_ogg ( char *fichero_ogg ){

    /* Variables locales */
    FILE *fichero;
    char filename[LON_BUFF];
    ALint error;
    int i, cont, posicion = 0;

    /* Establecemos donde estara situado el directorio para los sonidos */
    strcpy(filename, "musicas");
    strcat(filename, "/");
    strcat(filename, fichero_ogg);
    log_msj("[musica_ogg.c] Cargando musica %s\n", filename);

    /* Abrimos fichero para lectura */
    if ( ( fichero = abre_fichero ( filename, "rb" )) == NULL ){
      log_msj( "[KO] No se puede cargar fichero %s\n", fichero_ogg );
      return NO;
    }

    /* Accedemos al fichero ogg */
    if( ov_open ( fichero, &buff, NULL, 0 ) < 0) {
      log_msj("[KO] Esto no es un fichero ogg.\n" );
      return NO;
    }

    /* Obtenemos formato, frecuencia */
    informacion = ov_info ( &buff, -1);

    /* Adjudicamos valores, que son necesarios para una correcta reproduccion*/
    if ((informacion->channels) == 2){
      formato = AL_FORMAT_STEREO16;
    }else {
      formato = AL_FORMAT_MONO16;
    }
    /* Imprimimos informacion para el log */
    log_msj ("[musica_ogg.c] Musica cargada es de %d, con %ld Hz y un bitrate de %ld bps\n",informacion->channels,informacion->rate,
                  informacion->bitrate_nominal);

    /* Generamos  buffers para hacer el streaming */
    alGenBuffers ( NUM_BUFFER_MUSICA, streambuffers);
    if ( (error = alGetError()) != AL_NO_ERROR){
      log_msj ("[KO] Fallo al crear los buffers para la musica en cargar_ogg:%s\n", alGetString(error));
      return NO;
    }

    /* Rellenamos los buffers creados con la musica decodificada */
    for ( i=0; i < NUM_BUFFER_MUSICA ; i++){
      cont = ov_read ( &buff, (char *)&waveout[posicion], BUFFER_MUSICA , 0, 2, 1, &current_section );
      if (cont == 0){
        break;
      }else{
        alBufferData ( streambuffers[i], formato, waveout , BUFFER_MUSICA , informacion->rate );
        if ( (error =alGetError ()) != AL_NO_ERROR ){
          log_msj ("[KO] Error al asignar datos al buffer %i en cargar_ogg:%s\n",i,alGetString(error));
          return NO;
        }
      }
    }

    /* Creamos la fuente y definimos sus propiedades */
    alGenSources( 1, streamsource );
    if ( (error = alGetError()) != AL_NO_ERROR ){
      log_msj ("[KO] Error al generar la fuente de sonido en cargar_ogg: %s\n", alGetString (error));
      return NO;
    }

    /* Defino propiedades para la fuente */
    alSourcei ( streamsource[0], AL_SOURCE_RELATIVE, AL_TRUE ); /* Para que se mueva con el listener */
    alSourcei ( streamsource[0], AL_LOOPING, AL_FALSE ); /* No se repite por ella sola */
    alSourcef ( streamsource[0], AL_GAIN, 0.9f ); /* Para que suene menos que los sonidos */

    /* Asignamos los buffers creados a la fuente */
    alSourceQueueBuffers ( streamsource[0], NUM_BUFFER_MUSICA, streambuffers );
    if ( (error = alGetError()) != AL_NO_ERROR ){
      log_msj ("[KO] Error al asignar buffers a la fuente en cargar_ogg: %s\n", alGetString (error));
      return NO;
    }
    return SI;
}

/******************************************************
Funcion       : pausar_ogg (int pausa_ogg)
******************************************************/

int pausar_ogg (int pausa_ogg){

    ALint error;

    /* Pausamos la musica */
   if (pausa_ogg == 1){
     alSourcePause(streamsource[0]);
      if ( (error = alGetError()) != AL_NO_ERROR ){
        log_msj ("[KO] Error al pausar la fuente de sonido: %s\n", alGetString (error));
        return NO;
      }
   }
   /* Reanudamos la musica */
   if (pausa_ogg == 0){
     alSourcePlay(streamsource[0]);
     if ( (error = alGetError()) != AL_NO_ERROR ){
        log_msj ("[KO] Error al reanudar la reproduccion de la fuente de sonido: %s\n", alGetString (error));
        return NO;
     }
   }
   return SI;

}



/***********************************************************************************************
Funcion      : resetear_ogg (  )
************************************************************************************************/

int resetear_ogg (void){

      ALint error;

     /* Cuando queremos cambiar la cancion, paramos todo y borramos buffers y fuentes */
     alSourceStopv(1, streamsource);
     if ( (error = alGetError()) != AL_NO_ERROR){
       log_msj ("[KO] No se pueden parar el streamsource en resetear_ogg: %s\n",alGetString (error));
       return NO;
     }
     /* Matamos el thread*/
     SDL_KillThread ( threadmusica );
     /* Borramos buffers y sources */
     alDeleteSources(1, streamsource);
     if ( (error = alGetError()) != AL_NO_ERROR){
       log_msj ("[KO] No se puede borrar el stremsource en resetear_ogg: %s\n",alGetString (error));
       return NO;
     }
     alDeleteBuffers(NUM_BUFFER_MUSICA, streambuffers);
     if ( ( error = alGetError()) != AL_NO_ERROR){
       log_msj ("[KO] No se pueden borrar los buffers en resetear_ogg: %s\n",alGetString (error));
       return NO;
     }
     /* Lo reseteamos */
     ov_clear(&buff);

     return SI;
}


/******************************************************************************************************
Funcion       : actualizar_ogg (  )
******************************************************************************************************/

int  actualizar_ogg ( void ){

    ALint error;
    int cont = 0,contador = 0, cancion_acabada = NO, repeticion_acabada = NO;
    ALuint buffer_intercambio;
    int buffers_vacios = 0;
    ALint estado;

    /* Aqui establacemos el primer bucle para la repeticion */
    while ( repeticion_acabada == NO ){
      /* A partir de aqui es donde realmente empieza el Streaming*/
      while ( cancion_acabada == NO ){
        /* Comprobamos estado de los buffers */
        alGetSourcei ( streamsource[0], AL_BUFFERS_PROCESSED, &buffers_vacios);
        /* Si algun buffer esta vacio, lo rellenamos */
        if ( buffers_vacios > 0 ){
          while ( buffers_vacios ){
            /* Desasignamos buffers para rellenarlos */
            alSourceUnqueueBuffers ( streamsource[0], 1, &buffer_intercambio );
            if ( (error = alGetError( )) != AL_NO_ERROR ){
              log_msj ("[KO] No se puede desasignar buffers en actualizar_ogg: %s\n",alGetString (error));
              return NO;
            }
            /* Descomprimimos datos en el buffer intermedio */
            if ( (cont = ov_read ( &buff, (char *)&waveout, BUFFER_MUSICA, 0, 2, 1, &current_section)) == 0){
              cancion_acabada = SI;
              break;
            }
            /* Los  anyadimos en el buffer */
            alBufferData ( buffer_intercambio, formato, waveout, BUFFER_MUSICA, informacion->rate );
            if ((error = alGetError()) != AL_NO_ERROR ){
              log_msj ("[KO] No se puede a�adir datos al buffer en actualizar_ogg: %s\n",alGetString (error));
              return NO;
            }
            /* Asignamos de nuevo los buffers al streamsource */
            alSourceQueueBuffers ( streamsource[0], 1, &buffer_intercambio );
            if ((error = alGetError()) != AL_NO_ERROR ){
              log_msj ("[KO] No se puede asignar buffers a la fuente en actualizar_ogg: %s\n",alGetString (error));
              return NO;
            }
            buffers_vacios --;
          }
        }
        /* Si ocurre buffer underrun lo ponemos en marcha de nuevo o si esta en pausa lo paramos*/
        alGetSourcei(streamsource[0], AL_SOURCE_STATE, &estado);
        if (estado != AL_PLAYING){
          if (estado != AL_PAUSED){
            alSourcePlay(streamsource[0]);
            if ((error = alGetError()) != AL_NO_ERROR ){
              log_msj ("[KO] No se puede arreglar el buffer underrun en actualizar_ogg: %s\n",alGetString (error));
              return NO;
            }
          }else{
            while (estado == AL_PAUSED){
              alGetSourcei(streamsource[0], AL_SOURCE_STATE, &estado);
              SDL_Delay(10);
            }
          }
        }
        /* Para sincronizar mejor la musica y que no se imponga al thread principal */
        SDL_Delay(20);
      }
      /* A partir de aqui miramos cuantas veces tiene que ser repetida la musica */
      contador = contador + 1;
      if ( (contador >= repeticion) && (repeticion != -1) ){
        repeticion_acabada = SI;
      }else{
	/* Rebobinamos la musica hasta el principio */
	if ( ov_time_seek ( &buff, 0 ) != 0 ){
          log_msj ("[KO] No se puede rebobinar la musica\n");
          repeticion_acabada = SI;
	}else{
	  cancion_acabada = NO;
	}
      }
    }
    return SI;
}

/********************************************************
Funcion       : reproducir_ogg ( int repetir )
********************************************************/

int reproducir_ogg ( int repetir ){

    /* Para la repeticion de la musica */
    repeticion = repetir;

    /* Creamos thread independiente para la musica */
    threadmusica = SDL_CreateThread ((void *)actualizar_ogg, NULL);
    if (threadmusica == NULL) {
      log_msj ("[KO] No podemos crear el thread para la musica.\n");
      return NO;
    }
    return SI;
    
}
