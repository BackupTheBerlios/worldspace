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
#include "audio.h"

/* Estos defines puede que se cambien en un futuro */
#define NUM_BUFFER_MUSICA 40
#define BUFFER_MUSICA 256


ALenum formato; /* Utilizado en la carga de archivos OGG */
OggVorbis_File buff;
ALint estado;
int repeticion;
int buffers_vacios = 0;
int current_section = -1;
vorbis_info *informacion = NULL;
ALuint streambuffers[NUM_BUFFER_MUSICA]; /* Utilizado en la carga de archivos OGG */
ALshort waveout [BUFFER_MUSICA];  /* Donde almacenamos los OGG Vorbis decodificados */
ALuint streamsource[1]; /* Utilizado en la carga de archivos OGG */
SDL_Thread *threadmusica; /* Thread de audio */

/*****************************************************************************************
Funcion       : cargar_musica ( char *fichero_ogg )
Objetivo      : Esta funcion decodifica un fichero ogg y lo pasa a un buffer
                    en formato wav
Parametros : Hay que pasarle 2 parametros

char *fichero_ogg --> Nombre del archivo de musica que queremos cargar

*****************************************************************************************/

int cargar_musica ( char *fichero_ogg ){

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
    
    /* Generamos  buffers para hacer el streaming */
    alGenBuffers ( NUM_BUFFER_MUSICA, streambuffers);
    if ( (error = alGetError()) != AL_NO_ERROR){
      log_msj ("[KO] Fallo al crear los buffers para la musica:%s\n", alGetString(error));
      return NO;
    }
      
    /* Rellenamos los buffers creados con la musica decodificada */
    for ( i=0; i < NUM_BUFFER_MUSICA ; i++){
      cont = ov_read ( &buff, (char *)&waveout[posicion], BUFFER_MUSICA , 0, 2, 1, &current_section );
      if (cont == 0){
        log_msj ("El archivo se ha terminado de decodificar");
        break;
      }else{
        alBufferData ( streambuffers[i], formato, waveout , BUFFER_MUSICA , informacion->rate );
        if ( (error =alGetError ()) != AL_NO_ERROR ){
          log_msj ("[KO] Error al anyadir datos al buffer %i:%s\n",i,alGetString(error));
          return NO;
        }
      }
    }

    /* Creamos la fuente y definimos sus propiedades */
    alGenSources( 1, streamsource );
    if ( (error = alGetError()) != AL_NO_ERROR ){
      log_msj ("[KO] Error al generar la fuente de sonido: %s\n", alGetString (error));
      return NO;
    }

    /* Defino propiedades para la fuente */
    alSourcei ( streamsource[0], AL_SOURCE_RELATIVE, AL_TRUE ); /* Para que se mueva con el listener */
    alSourcei ( streamsource[0], AL_LOOPING, AL_FALSE ); /* No se repite por ella sola */
    alSourcef ( streamsource[0], AL_GAIN, 0.9f ); /* Para que suene menos que los sonidos */

    /* Asignamos los buffers creados a la fuente */
    alSourceQueueBuffers ( streamsource[0], NUM_BUFFER_MUSICA, streambuffers );
     
    return SI;    
}

/******************************************************
Funcion       : pausar_musica ( )
Objetivo      : Pausa la musica seleccionada
Parametros : No hay que pasarle parametros
******************************************************/

int pausar_musica (int pausa){
 
   if (pausa == 1){
     alSourcePause(streamsource[0]);
   }
   if (pausa == 0){
     alSourcePlay(streamsource[0]);
   }
   return SI;

}



/***********************************************************************************************
Funcion      : resetear_musica (  )

Objetivo      : Esta funcion elimina la musica para poder cargar otro archivo OGG
Parametros : No hay que pasarle parametros
************************************************************************************************/

int resetear_musica (void){

     /* Cuando queremos cambiar la cancion, paramos todo y borramos buffers y fuentes */
     alSourceStopv(1, streamsource);
     if (alGetError() != AL_NO_ERROR){
       log_msj ("[KO] No se pueden parar el streamsource\n");
       return NO;
     }
     /* Matamos el thread*/
     SDL_KillThread ( threadmusica );
     /* Borramos buffers y sources */
     alDeleteSources(1, streamsource);
     if (alGetError() != AL_NO_ERROR){
       log_msj ("[KO] No se puede borrar el stremsource\n");
       return NO;
     }
     alDeleteBuffers(NUM_BUFFER_MUSICA, streambuffers);
     if (alGetError() != AL_NO_ERROR){
       log_msj ("[KO] No se pueden borrar los buffers\n");
       return NO;
     }
     return SI;
}


/******************************************************************************************************
Funcion       : actualizar_musica (  )
Objetivo      : Esta funcion rellena los buffers segun se van vaciando. Hay que llamarla
                    muy muy a menudo ya que es la que realmente realiza el streaming.
                    Preferiblemente hay que incluirla en un thread independiente.
Parametros : No hay que pasarle parametros
******************************************************************************************************/

int  actualizar_musica ( void ){
  
    int cont = 0,contador = 0, cancion_acabada = NO, repeticion_acabada = NO;
    ALuint buffer_intercambio;

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
            if ( (alGetError( )) != AL_NO_ERROR ){
              log_msj ("[KO] No va el streaming\n");
            }
            /* Descomprimimos datos en el buffer intermedio */	
            if ( (cont = ov_read ( &buff, (char *)&waveout, BUFFER_MUSICA, 0, 2, 1, &current_section)) == 0){
              cancion_acabada = SI;
              break;
            }
            /* Los  anyadimos en el buffer */
            alBufferData ( buffer_intercambio, formato, waveout, BUFFER_MUSICA, informacion->rate );
            if ((alGetError()) != AL_NO_ERROR ){
              log_msj ("[KO] No se puede añadir datos al buffer\n");
            }
            /* Asignamos de nuevo los buffers al streamsource */
            alSourceQueueBuffers ( streamsource[0], 1, &buffer_intercambio );
            buffers_vacios --;
          }
        }
        /* Si ocurre buffer underrun lo ponemos en marcha de nuevo o si esta en pausa lo paramos*/
        alGetSourcei(streamsource[0], AL_SOURCE_STATE, &estado);
        if (estado != AL_PLAYING){
          if (estado != AL_PAUSED){
            alSourcePlay(streamsource[0]);
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
Funcion       : reproducir_musica ( int repetir )
Objetivo      : reproduce la musica seleccionada
Parametros :

int repetir  --> -1 bucle infinito y 1,2,3.... numero de veces
                            que se repite
********************************************************/

int reproducir_musica ( int repetir ){

    /* Para la repeticion de la musica */
    repeticion = repetir;
  
    /* Creamos thread independiente para la musica */
    threadmusica = SDL_CreateThread ((void *)actualizar_musica, NULL);
    if (threadmusica == NULL) {
      log_msj ("[KO] No podemos crear el thread para la musica.\n");
      return NO;
    }
    return SI;
    
}
